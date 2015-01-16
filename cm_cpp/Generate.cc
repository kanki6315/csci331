using namespace std;
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip> // for spacing in cout/cerr
#include <sstream> // stringstream
#include "compiler.h"
#include "support.h"
#include "Generate.h"

Generate::Generate() { 
    symTabPtr = NULL;
}

// Generate tm code. The symbol tree is attached to the node when needed.
void Generate::generateCode(TreeNode* nodePtr) {
    program(nodePtr);
}

/****************************************************************************/
/*                                                                          */
/* code generation routines                                                 */
/*                                                                          */
/****************************************************************************/

// 1. prog -> declList  
void Generate::program(TreeNode* nodePtr) {
    SemanticRec* semRecPtr;
    int loc, main1, main2;

    symTabPtr = nodePtr->symTabPtr;        // Get global symbol table 
    if (!symTabPtr) {
	cerr << "You must generate a symbol table first.\n";
	exit(1);
    }

    // Run-time environment setup instructions
    emitRM("LD",gp,0,ac0,"Set GP");                  // GP = dMem[0] = size-1
    loc = emitSkip(2);                               // Init FP,SP here later
    emitRM("ST",ac0,0,ac0,"Clear dMem[0]");          // re-init dMem[0] = 0
    push(fp,"Save FP");                              // dMem[sp] = fp
    main1 = emitSkip(1);                             // Re-Init SP here later
    emitRM("LDA",ac0,1,pc,"Get PC for Halt");      // ac0 has PC for HALT line
    main2 = emitSkip(1);                             // Init PC here
    emitRO("HALT",0,0,0,"Function Halt");            // Stop.
     
    // Code for the input function
    semRecPtr = symTabPtr->lookup(nodePtr->line, "input");
    semRecPtr->addr = emitSkip(0);
    emitRM("ST",ac0,-1,fp,"Input Function, store return addr");
    emitRO("IN",ac0,0,0,  "     Get input");
    emitRM("LD",pc,-1,fp, "     Return (end of function)");
     
    semRecPtr = symTabPtr->lookup(nodePtr->line, "output");
    semRecPtr->addr = emitSkip(0);
    emitRM("ST",ac0,-1,fp,"Output Function, store return addr");
    emitRM("LD",ac0,-2,fp,"     Get output");
    emitRO("OUT",ac0,0,0, "     Give output");
    emitRM("LD",pc,-1,fp, "     Return (end of function)");
     
    declarationList(nodePtr->ptr1);                  // Code for declList
     
    emitBackup(loc);
    emitRM("LDA",fp,-symTabPtr->used,gp,"Set FP below globals"); 
    emitRM("LDA",sp,-symTabPtr->used,gp,"Set SP below globals"); 
    emitRestore();
    semRecPtr = symTabPtr->lookup(nodePtr->line, "main");
    emitBackup(main2);
    emitRMAbs("LDA",pc,semRecPtr->addr,"Jump to main");// PC = main
    emitRestore();
    emitBackup(main1);
    emitRM("LDA",sp,-(semRecPtr->localSpace+1),sp,"Set SP below locals");
    emitRestore();
    popScope();
}

// 2. declList -> decl declList | decl  
void Generate::declarationList(TreeNode* nodePtr) {
    if (nodePtr->kind == declList1) {
	declaration(nodePtr->ptr1);
	declarationList(nodePtr->ptr2);
    }
    else //if (nodePtr->kind == declList2) {
	declaration(nodePtr->ptr1);
}

// 3. decl -> varDecl | funDecl  
void Generate::declaration(TreeNode* nodePtr) {
    if (nodePtr->kind == decl1) {
	varDeclaration(nodePtr->ptr1);
    } else //if (nodePtr->kind == decl2) {
	funDeclaration(nodePtr->ptr1);
}

// 4. varDecl -> typeSpec ID ';' | typeSpec ID '[' NUM ']' ';'  
// 5. typeSpec -> INT | VOID  
void Generate::varDeclaration(TreeNode* nodePtr) {
}

// 6. funDecl -> typeSpec ID '(' params ')' compStmt   
void Generate::funDeclaration(TreeNode* nodePtr) {
    SemanticRec* semRecPtr;

    semRecPtr = symTabPtr->lookup(nodePtr->line, nodePtr->strval);
    semRecPtr->addr = emitSkip(0);             // Func code starts here
     
    pushScope(nodePtr);
     
    params(nodePtr->ptr2);                     // Output params code
  
    emitRM("ST",ac0,-1,fp,"Function " + nodePtr->strval 
	   + ": dMem[FP-1] = return address");
     
    functionStmt(nodePtr->ptr3);               // Output compStmt code
     
    emitRM("LD",pc,-1,fp,"End of function (PC = return addr)");

    popScope();                                // Pop scope
}

// 7. params -> paramList | VOID  
void Generate::params(TreeNode* nodePtr) {
    if (nodePtr->kind == params1) {
	paramList(nodePtr->ptr1);                  // Output paramList code
    } //else if (nodePtr->kind == params2) {
}

// 8. paramList -> param ',' paramList | param  
void Generate::paramList(TreeNode* nodePtr) {
    if(nodePtr->kind == paramList1) {
	param(nodePtr->ptr1);                      // Output param code
	paramList(nodePtr->ptr2);                  // Output paramList code
    } else //if (nodePtr->kind == paramList2) {
	param(nodePtr->ptr1);                      // Ouput code for param
}

// 9. param -> typeSpec ID | typeSpec ID '[' ']'  
void Generate::param(TreeNode* nodePtr) {
}

// 10. funcStmt -> '{' localDecl stmtList '}'  
void Generate::functionStmt(TreeNode* nodePtr) {
    localDeclaration(nodePtr->ptr1);          // Output code for localDecl
    statementList(nodePtr->ptr2);             // Output code for stmtList
}

// 11. localDecl -> varDecl localDecl | empty  
void Generate::localDeclaration(TreeNode* nodePtr) {
    if (nodePtr->kind == localDecl1) {
	varDeclaration(nodePtr->ptr1);         // Output code for varDecl
	localDeclaration(nodePtr->ptr2);       // Output code for localDecl
    } 
}

// 12. stmtList -> stmt stmtList | empty  
void Generate::statementList(TreeNode* nodePtr) {
    if (nodePtr->kind == stmtList1) {
	statement(nodePtr->ptr1);              // Output code for stmt
	statementList(nodePtr->ptr2);          // Output code for stmtList
    } 
}

// 13. stmt -> expStmt | compStmt | selStmt | retStmt  
// 13a. e_stmt -> expStmt | compStmt | e_selStmt | retStmt  
void Generate::statement(TreeNode* nodePtr) {
    if (nodePtr->kind == stmt1)
	expressionStmt(nodePtr->ptr1);   // Output code for expStmt
    else if (nodePtr->kind == stmt2)
	compoundStmt(nodePtr->ptr1);     // Output code for compStmt
    else if (nodePtr->kind == stmt3)
	selectionStmt(nodePtr->ptr1);    // Output code for selStmt
    else //if (nodePtr->kind == stmt5)
	returnStmt(nodePtr->ptr1);       // Output code for retStmt
}

// 14. expStmt -> exp ';' | ';'  
void Generate::expressionStmt(TreeNode* nodePtr) {
    if (nodePtr->kind == expStmt1)
	expression(nodePtr->ptr1);       // Output code for exp
    //else if (nodePtr->kind == expStmt2)
}

// 15. compStmt -> '{' localDecl stmtList '}'  
void Generate::compoundStmt(TreeNode* nodePtr) {
    pushScope(nodePtr);
    localDeclaration(nodePtr->ptr1);    // Output code for localDecl  
    statementList(nodePtr->ptr2);       // Output code for stmtList    
    popScope();
}

// 16. selStmt -> if '(' exp ')' stmt | if '(' exp ')' stmt else stmt  
// 16a. e_selStmt -> if '(' exp ')' e_stmt else stmt  
void Generate::selectionStmt(TreeNode* nodePtr) {
    int loc, loc2, loc3, loc4;
    if (nodePtr->kind == selStmt1) {
	expression(nodePtr->ptr1);     // Output exp code
	loc = emitSkip(1);             // Save space for "if" test
	statement(nodePtr->ptr2);      // Output stmt code

	loc2 = emitSkip(0);            // Get jump destination (end)
	emitBackup(loc);               // Backup numbering to "if" test
	emitRMAbs("JEQ",ac0,loc2,
		  "  if: Jump over true part if test is false (exp == 0)");
	emitRestore();                 // Restore numbering
    } else { //if (nodePtr->kind == selStmt2)

	expression(nodePtr->ptr1);        // Output exp code
	loc = emitSkip(1);                // Skip jump1 loc
	statement(nodePtr->ptr2);         // Output stmt1 code

	emitRM("LDC",ac0,0,0,
	       "  if: Put a 0 in ac0 so we jump over the else part");
	loc2 = emitSkip(1);               // Skip jump2 loc
	loc3 = emitSkip(0);               // Get jump1 destination (else)
	statement(nodePtr->ptr3);         // Output stmt2 code
	loc4 = emitSkip(0);               // Get jump2 destination (end)
 
	emitBackup(loc);                  // Go back to jump1 loc
	emitRMAbs("JEQ",ac0,loc3,
		  "  if: Jump to else part if test is false (exp == 0)");
	emitRestore();                    // Restore instr counter to else

	emitBackup(loc2);                 // Go back to jump2 loc
	emitRMAbs("JEQ",ac0,loc4,"  if: Jump to the end");     // Jump to end
	emitRestore();                    // Restore instr counter to end
    } 
}



// 18. retStmt -> return ';' | return exp ';'  
void Generate::returnStmt(TreeNode* nodePtr) {
    if (nodePtr->kind == retStmt1)
	emitRM("LD",pc,-1,fp,"Returning (end of function)");
    else { //if (nodePtr->kind == retStmt2) {
	expression(nodePtr->ptr1);       // Output exp code (ans in ac0)
	emitRM("LD",pc,-1,fp,"Returning (end of function)"); 
    }
}

// 19. exp -> var '=' exp | simpExp  
void Generate::expression(TreeNode* nodePtr) {
    if (nodePtr->kind == exp1) {
	expression(nodePtr->ptr2);         // Output exp code (ans in ac0)
	push(ac0,"  assignment: save value");  
	var(nodePtr->ptr1, 0);             // Output var code (addr in ac1)
	pop(ac0,"  assignment: retrieve value");
	emitRM("ST",ac0,0,ac1,"  assignment: variable = dMem[ac1] = value");
    } else //if (nodePtr->kind == exp2) {
	simpleExp(nodePtr->ptr1);
}

// 20. var -> ID | ID '[' exp ']'  
void Generate::var(TreeNode* nodePtr, int rlval) {
    SemanticRec* semRecPtr;
    int loc, loc2;
    if (nodePtr->kind == var1) {
	semRecPtr = symTabPtr->lookup(nodePtr->line, nodePtr->strval);
	if (rlval == 0)  // we want the lvalue, ac1 = var addr
	    emitRM("LDA",ac1,semRecPtr->offset,semRecPtr->base,
		   "  variable: AC1 = address of " + nodePtr->strval);
	else                               // we want the rvalue
	    switch(semRecPtr->kind) {
	    case intvar:                   // ac0 = var value
		emitRM("LD",ac0,semRecPtr->offset,semRecPtr->base,
		       "  variable: AC0 = value of " + nodePtr->strval);
		break;
	    case intarr:                   // ac0 = array addr
		emitRM("LDA",ac0,semRecPtr->offset,semRecPtr->base,
		       "  variable: AC0 = address of array " 
		       + nodePtr->strval);
		break;
	    case refarr:                   // ac0 = array addr
		emitRM("LD",ac0,semRecPtr->offset,semRecPtr->base,
		       "  variable: AC0 = address of array " 
		       + nodePtr->strval);
		break;
	    }
    } else { //if (nodePtr->kind == var2) {
	
	expression(nodePtr->ptr1);          // Output exp code
	
	loc = emitSkip(1);                  // Jump if subscript legal
	emitRO("HALT",0,0,0,"  variable: Stop. Neg subscripts illegal.");
	loc2 = emitSkip(0);
	emitBackup(loc);
	emitRMAbs("JGE",ac0,loc2,"  variable: Jump if subscript >= 0");
	emitRestore();                      // Restore instr counter
	
	semRecPtr = symTabPtr->lookup(nodePtr->line, nodePtr->strval);
	
	if (rlval == 0) { // we want the lvalue, Get arr[exp] addr. 
	    if (semRecPtr->kind == intarr) {  // For intarr
		emitRM("LDA",ac1,semRecPtr->offset,semRecPtr->base,
		       "  variable: AC1 = address of array " 
		       + nodePtr->strval);
		emitRO("SUB",ac1,ac1,ac0,
		       "  variable: AC1 = address of " 
		       + nodePtr->strval + "[index]");
	    }
	    else {                              // For refarr
		emitRM("LD",ac1,semRecPtr->offset,semRecPtr->base,
		       "  variable: AC1 = address of array " 
		       + nodePtr->strval);
		emitRO("SUB",ac1,ac1,ac0,
		       "  variable: AC1 = address of " 
		       + nodePtr->strval + "[index]");
	    }
	    
	} else { // we want the rvalue, Get arr[exp] value
	    if (semRecPtr->kind == intarr) {       // For intarr
		emitRM("LDA",ac1,semRecPtr->offset,semRecPtr->base,
		       "  variable: AC1 = address of array " 
		       + nodePtr->strval);
		// Get arr addr
		emitRO("SUB",ac1,ac1,ac0,"  variable: AC1 = address of " 
		       + nodePtr->strval + "[index]");
		emitRM("LD",ac0,0,ac1,"  variable: AC0 = value of " 
		       + nodePtr->strval + "[index]");
	    }
	    else {                                   // For refarr
		emitRM("LD",ac1,semRecPtr->offset,semRecPtr->base,
		       "  variable: AC1 = address of array " 
		       + nodePtr->strval);
		emitRO("SUB",ac1,ac1,ac0,"  variable: AC1 = address of " 
		       + nodePtr->strval + "[index]");
		emitRM("LD",ac0,0,ac1,"  variable: AC0 = value of " 
		       + nodePtr->strval + "[index]");
	    }
	    
	}
    } 
}

// 21. simpExp -> addExp relop addExp | addExp  
// 22. relop -> '<=' | '<' | '>' | '>=' | '==' | '!='  
void Generate::simpleExp(TreeNode* nodePtr) {
    int loc, loc2, loc3, loc4;
    if (nodePtr->kind == simpExp1) {
	additiveExp(nodePtr->ptr1);   // Output code for addExp1 (ans in ac0)
	push(ac0,"  binary op: save left side");
	additiveExp(nodePtr->ptr3);   // Output code for addExp2 (ans in ac0)
	pop(ac1,"  binary op: retrieve left side");

	emitRO("SUB",ac0,ac1,ac0,"  binary op: AC0 = left - right");
	loc = emitSkip(1);            // Relop: jump to T or continue to F
	emitRM("LDC",ac0,0,0,"  binary op: AC0 = FALSE");
	emitRM("LDC",ac1,0,0,"  binary op: AC0 = 1 so we force the jump");
	loc2 = emitSkip(1);           // Jump to end
	loc3 = emitSkip(0);           // True location             
	emitRM("LDC",ac0,1,0,"  binary op: AC0 = TRUE");
	loc4 = emitSkip(0);           // End location
	  
	emitBackup(loc);              // Fill in relop jump instr
	if (nodePtr->ptr2->kind == relop1)
	    emitRMAbs("JLE",ac0,loc3,"  binary op: jump instr for <=");
	else if (nodePtr->ptr2->kind == relop2)
	    emitRMAbs("JLT",ac0,loc3,"  binary op: jump instr for <");
	else if (nodePtr->ptr2->kind == relop3)
	    emitRMAbs("JGT",ac0,loc3,"  binary op: jump instr for >");
	else if (nodePtr->ptr2->kind == relop4)
	    emitRMAbs("JGE",ac0,loc3,"  binary op: jump instr for >=");
	else if (nodePtr->ptr2->kind == relop5)
	    emitRMAbs("JEQ",ac0,loc3,"  binary op: jump instr for ==");
	else //if (nodePtr->ptr2->kind == relop6)
	    emitRMAbs("JNE",ac0,loc3,"  binary op: jump instr for !=");
	emitRestore();

	emitBackup(loc2);             // Fill in jump to end instr
	emitRMAbs("JEQ",ac1,loc4,"  binary op: Jump to end");
	emitRestore();
    } else //if (nodePtr->kind == simpExp2) { 
	additiveExp(nodePtr->ptr1);   // Output code for addExp
}

// 23. addExp -> addExp addop term | term  
// 24. addop -> '+' | '-'  
void Generate::additiveExp(TreeNode* nodePtr) {
    if (nodePtr->kind == addExp1) {
	additiveExp(nodePtr->ptr1);        // Output addExp code (ans in ac0)
	push(ac0,"  binary op: save left side");
	term(nodePtr->ptr3);               // Output term code (ans in ac0)
	// 2nd operand now in ac0, no need to push/pop
	pop(ac1,"  binary op: retrieve left side");
	if(nodePtr->ptr2->kind == addop1)
	    emitRO("ADD",ac0,ac1,ac0,"  binary op: AC0 = left + right");
	else
	    emitRO("SUB",ac0,ac1,ac0,"  binary op: AC0 = left - right");
    } else //if (nodePtr->kind == addExp2) {
	term(nodePtr->ptr1);               // Output code for term
}

// 25. term -> term mulop factor | factor  
// 26. mulop -> '*' | '/'  
void Generate::term(TreeNode* nodePtr) {
    if (nodePtr->kind == term1) {
	term(nodePtr->ptr1);                 // Output term code (ans in ac0)
	push(ac0,"  binary op: save left side");
	factor(nodePtr->ptr3);               // Output factor code (ans in ac0)
	// 2nd operand now in ac0, no need to push/pop
	pop(ac1,"  binary op: retrieve left side");
	if(nodePtr->ptr2->kind == mulop1)
	    emitRO("MUL",ac0,ac1,ac0,"  binary op: AC0 = left * right");
	else
	    emitRO("DIV",ac0,ac1,ac0,"  binary op: AC0 = left / right");
    } else //if (nodePtr->kind == term2) {
	factor(nodePtr->ptr1);               // Output code for factor
}

// 27. factor -> '(' exp ')' | var | call | NUM  
void Generate::factor(TreeNode* nodePtr) {
    if (nodePtr->kind == factor1) {
	expression(nodePtr->ptr1);           // Output exp code (ans in ac0)
    } else if (nodePtr->kind == factor2) {
	var(nodePtr->ptr1,1);                // Output var code (rvalue in ac0)
    } else if (nodePtr->kind == factor3) {
	call(nodePtr->ptr1);                 // Output call code (ans in ac0)
    } else { //if (nodePtr->kind == factor4) 
	stringstream out;
	out << nodePtr->numval;
	emitRM("LDC",ac0,nodePtr->numval,0,"  int: AC0 = " + out.str());
    }
}

// 28. call -> ID '(' args ')'  
void Generate::call(TreeNode* nodePtr) {
    SemanticRec* semRecPtr;

    semRecPtr = symTabPtr->lookup(nodePtr->line, nodePtr->strval);
    push(fp,"     Funct call, save old FP"); // Save old FP
    emitRM("LDA",sp,-1,sp,"     Save space for return addr");
    
    args(nodePtr->ptr1);                     // Output args code
    
    emitRM("LDA",fp,semRecPtr->numParams+2,sp,"     Set FP to top of frame");
    emitRM("LDA",sp,-nodePtr->locals_so_far,sp, "     Set SP after locals");
    
    emitRM("LDA",ac0,1,pc,"     Get return addr");  // ac0 = return addr (pc+1)
    emitRMAbs("LDA",pc,semRecPtr->addr,
	      "     Jump to function " + nodePtr->strval); 
    emitRM("LDA",sp,0,fp,                "     Restore old SP");
    emitRM("LD",fp,0,fp,                 "     Restore old FP");
}
     
// 29. args -> argList | empty  
void Generate::args(TreeNode* nodePtr) {
    if (nodePtr->kind == args1) {
	argList(nodePtr->ptr1);              // Output argList code
    } 
}

// 30. argList -> exp ',' argList | exp  
void Generate::argList(TreeNode* nodePtr) {
    if (nodePtr->kind == argList1) {
	expression(nodePtr->ptr1);           // Output exp code 
	push(ac0,"    Push argument onto stack");
	argList(nodePtr->ptr2);              // Output arglist code
    } else { //if (nodePtr->kind == argList2) {
	expression(nodePtr->ptr1);           // Output exp code
	push(ac0,"    Push argument onto stack");
    } 
}

/****************************************************************************/
/*                                                                          */
/* code generation routines                                                 */
/*                                                                          */
/****************************************************************************/
// From Louden "Compiler Construction".

/* TM location number for current instruction emission */
static int emitLoc = 0;

/* Highest TM location emitted so far
   For use in conjunction with emitSkip,
   emitBackup, and emitRestore */
static int highEmitLoc = 0;

/* Function emitSkip skips "howMany" code
 * locations for later backpatch. It also
 * returns the current code position
 */
int Generate::emitSkip(int howMany){  
    int i = emitLoc;
    emitLoc += howMany;
    if (highEmitLoc < emitLoc)  highEmitLoc = emitLoc;
    return i;
} /* emitSkip */

/* Procedure emitBackup backs up to 
 * loc = a previously skipped location
 */
void Generate::emitBackup( int loc){ 
    if (loc > highEmitLoc) emitComment("BUG in emitBackup");
    emitLoc = loc;
} /* emitBackup */

/* Procedure emitRestore restores the current 
 * code position to the highest previously
 * unemitted position
 */
void Generate::emitRestore(void) { emitLoc = highEmitLoc; }

/* Procedure emitComment prints a comment line 
 * with comment c in the code file
 */
void Generate::emitComment(string c) { cout << " * " << c << endl; }

/* Procedure emitRO emits a register-only
 * TM instruction
 * op = the opcode
 * r = target register
 * s = 1st source register
 * t = 2nd source register
 * c = a comment to be printed if TraceCode is TRUE
 */
void Generate::emitRO(string op, int r, int s, int t, string c){
    cout << setw(3) << emitLoc++ << ":  " << setw(5) << op << "  "
	 << r << "," << s << "," << t << "\t\t" << c << "\n";
    if (highEmitLoc < emitLoc) highEmitLoc = emitLoc;
} /* emitRO */

/* Procedure emitRM emits a register-to-memory TM instruction
 * op = the opcode
 * r = target register
 * d = the offset
 * s = the base register
 * c = a comment to be printed if TraceCode is TRUE
 */
void Generate::emitRM(string op, int r, int d, int s, string c){ 
    cout << setw(3) << emitLoc++ << ":  " << setw(5) << op << "  "
	 << r << "," << d << "(" << s << ")\t\t" << c << "\n";
    //printf("%3d:  %5s  %d,%d(%d)\t\t%s\n",emitLoc++,op,r,d,s,c);
    if (highEmitLoc < emitLoc)  highEmitLoc = emitLoc;
} /* emitRM */

/* Procedure emitRM_Abs converts an absolute reference 
 * to a pc-relative reference when emitting a
 * register-to-memory TM instruction
 * op = the opcode
 * r = target register
 * a = the absolute location in memory
 * c = a comment to be printed if TraceCode is TRUE
 */
void Generate::emitRMAbs(string op, int r, int a, string c){ 
    cout << setw(3) << emitLoc << ":  " << setw(5) << op << "  "
	 << r << "," << a-(emitLoc+1) << "(" << pc << ")\t" 
	 << a << "\t" << c << "\n";
    //printf("%3d:  %5s  %d,%d(%d)\t%d\t%s\n",emitLoc,op,r,a-(emitLoc+1),pc,a,c);
    ++emitLoc;
    if (highEmitLoc < emitLoc) highEmitLoc = emitLoc;
} /* emitRM_Abs */


// Shortcuts (code by Jay Aslam)

void Generate::push(int reg, string comm) {
    emitRM("ST",reg,0,sp,"");
    emitRM("LDA",sp,-1,sp,comm);
}

void Generate::pop(int reg, string comm) {
    emitRM("LDA",sp,1,sp,"");
    emitRM("LD",reg,0,sp,comm);
}

// Go down to the scope at this node
void Generate::pushScope(TreeNode* nodePtr) {
    symTabPtr = nodePtr->symTabPtr;            // Get current symbol table
}

// Go up to the previous scope
void Generate::popScope() {
    SymbolTable* tempScopePtr = symTabPtr;       // Point to scope
    symTabPtr = symTabPtr->prevScope;            // Scope is prev scope
    delete tempScopePtr;
}

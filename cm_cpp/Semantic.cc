using namespace std;
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "compiler.h"
#include "support.h"
#include "Semantic.h"

Semantic::Semantic() { 
    locals = 0;                              // Setup member data
    theNumParams = 0;
    symTabPtr = NULL; 
}

void Semantic::semanticCheck(TreeNode* nodePtr) {
    program(nodePtr);                        // Check the tree
}

/****************************************************************************/
/*                                                                          */
/* semantic checking routines                                               */
/*                                                                          */
/****************************************************************************/
/* 1. prog -> declList */
void Semantic:: program(TreeNode* nodePtr) {
    SemanticRec* semRecPtr;
    
    // Setup the top scope
    pushScope();                                // Push sym tab scope
    symTabPtr->base = gp;                       // Base = gp reg (4)
    symTabPtr->used = 0;                        // No spc used yet
    
    // Make a semantic rec for the input function
    semRecPtr = new SemanticRec();
    semRecPtr->kind = func;
    semRecPtr->numParams = 0;
    semRecPtr->localSpace = 0;
    symTabPtr->insert(nodePtr->line, "input", semRecPtr);
    
    // Make a semantic rec for the output function
    semRecPtr = new SemanticRec();              // Make semantic rec for output
    semRecPtr->kind = func;
    semRecPtr->numParams = 1;
    semRecPtr->localSpace = 0;
    symTabPtr->insert(nodePtr->line, "output", semRecPtr);
    
    declarationList(nodePtr->ptr1);          // Check declList code

    // Clean up the top scope
    nodePtr->symTabPtr = symTabPtr;          // Save symbol table for later use
    popScope();
}

/* 2. declList -> decl declList | decl */
void Semantic::declarationList(TreeNode* nodePtr) {
    if (nodePtr->kind == declList1) {
	declaration(nodePtr->ptr1);           // Check declaration code
	declarationList(nodePtr->ptr2);       // Check declList code
    }
    else //if (nodePtr->kind == declList2)
	declaration(nodePtr->ptr1);           // Check declaration code
}

/* 3. decl -> varDecl | funDecl */
void Semantic::declaration(TreeNode* nodePtr) {
    if (nodePtr->kind == decl1)
	varDeclaration(nodePtr->ptr1);
    else //if (nodePtr->kind == decl2)
	funDeclaration(nodePtr->ptr1);
}

/* 4. varDecl -> typeSpec ID ';' | typeSpec ID '[' NUM ']' ';' */
/* 5. typeSpec -> INT | VOID */
void Semantic::varDeclaration(TreeNode* nodePtr) {
    SemanticRec* semRecPtr;

    // For variables...
    if (nodePtr->kind == varDecl1) {
	_test(nodePtr->ptr1,"vardecl->typespec");

        // Make sure it's not void
	if (nodePtr->ptr1->kind == typeSpec2) {
	    cerr << "Static semantic error!  Line " << nodePtr->line
		 << ", variable " << nodePtr->strval << " declared void.\n";
	    exit(1);
	}
	
        // Make a semantic record for it
	semRecPtr = new SemanticRec();
	semRecPtr->kind = intvar;
	semRecPtr->base = symTabPtr->base;
	semRecPtr->offset = -symTabPtr->used;
	symTabPtr->used++;  // 1 more space has been used
	symTabPtr->insert(nodePtr->line, nodePtr->strval, semRecPtr);
	locals++;
     }

     // For array variables...
     else if (nodePtr->kind == varDecl2) {
          _test(nodePtr->ptr1,"vardecl->typespec");
	  
	  // Make sure it's not void
	  if (nodePtr->ptr1->kind == typeSpec2) { // VOID ID [NUM] is illegal
	      cerr << "Static semantic error!  Line " << nodePtr->line
		   << ", array " << nodePtr->strval << " declared void.\n";
	      exit(1);
	  }

          // Make sure it has length > 0
	  if (nodePtr->numval < 1) { // Num must be > 0
	      cerr << "Static semantic error!  Line " << nodePtr->line
		   << ", array " << nodePtr->strval 
		   << " has " << nodePtr->numval << " elements.\n";
	      exit(1);
	  }

          // Make a semantic record for it
	  semRecPtr = new SemanticRec();
	  semRecPtr->kind = intarr;
	  semRecPtr->base = symTabPtr->base;
	  semRecPtr->offset = -symTabPtr->used;
	  symTabPtr->used += nodePtr->numval;
	  symTabPtr->insert(nodePtr->line,nodePtr->strval,semRecPtr);
	  locals += nodePtr->numval;
     } 
}

/* 6. funDecl -> typeSpec ID '(' params ')' compStmt  */
void Semantic::funDeclaration(TreeNode* nodePtr) {
     SemanticRec* semRecPtr;

     semRecPtr = new SemanticRec();
     semRecPtr->kind = func;
     semRecPtr->numParams = -1;            // Dummy value
     semRecPtr->localSpace = -1;           // Dummy value
     symTabPtr->insert(nodePtr->line,nodePtr->strval,semRecPtr);
     
     pushScope();                           // Push scope onto sym tab
     symTabPtr->base = fp;                   // Base = FP
     symTabPtr->used = 2;                    // Spc for old fp, return addr
     theNumParams = 0;                       // No params yet
     
     params(nodePtr->ptr2);                  // Check params code
  
     semRecPtr->numParams = theNumParams;  // Record num of params
     locals = 0;                             // No spc for locals yet either
     
     functionStmt(nodePtr->ptr3);            // Check compStmt code
     
     semRecPtr->localSpace = locals;
     nodePtr->symTabPtr = symTabPtr;         // Save symbol table for later use
     popScope();

}

/* 7. params -> paramList | VOID */
void Semantic::params(TreeNode* nodePtr) {
     if (nodePtr->kind == params1)
	 paramList(nodePtr->ptr1);          // Check paramList code
     //else if (nodePtr->kind == params2)   // No checks needed
 }

/* 8. paramList -> param ',' paramList | param */
void Semantic::paramList(TreeNode* nodePtr) {
     if(nodePtr->kind == paramList1) {
	  param(nodePtr->ptr1);              // Check param code
	  paramList(nodePtr->ptr2);          // Check paramList code
     } else //if (nodePtr->kind == paramList2) {
	  param(nodePtr->ptr1);              // Ouput param code
}

/* 9. param -> typeSpec ID | typeSpec ID '[' ']' */
void Semantic::param(TreeNode* nodePtr) {
    SemanticRec* semRecPtr;

    // For variable parameters...
    if (nodePtr->kind == param1) {
	
	// Make sure its not type void. 'void ID' is not legal.
	if (nodePtr->ptr1->kind == typeSpec2) {
	    cerr << "Static semantic error!  Line " << nodePtr->line
		 << ", variable parameter " << nodePtr->strval 
		 << " declared void.\n";
	    exit(1);
	}

        // Make a semantic record for the parameter (local variable).
	semRecPtr = new SemanticRec();
	semRecPtr->kind = intvar;
	semRecPtr->base = symTabPtr->base;
	semRecPtr->offset = -symTabPtr->used;
	symTabPtr->used++;
	symTabPtr->insert(nodePtr->line,nodePtr->strval,semRecPtr);
	theNumParams++;
    }

    // For array variable parameters...
    else { //if (nodePtr->kind == param2)

        // Make sure its not type void. 'void ID []' is not legal.
	if (nodePtr->ptr1->kind == typeSpec2) {
	    cerr << "Static semantic error!  Line " << nodePtr->line
		 << ", variable parameter " << nodePtr->strval 
		 << " declared void.\n";
	    exit(1);
	}

        // Make a semantic record for the parameter (local array variable).
	semRecPtr = new SemanticRec();           // new semantic record (var)
	semRecPtr->kind = refarr;        // Kind = reference array
	semRecPtr->base = symTabPtr->base;  // set base loc
	semRecPtr->offset = -symTabPtr->used; // set offset loc
	symTabPtr->used++;                    // update spc used
	symTabPtr->insert(nodePtr->line,nodePtr->strval,semRecPtr);
	theNumParams++;                    // inc num of params
    } 
}

/* 10. funcStmt -> '{' localDecl stmtList '}' */
void Semantic::functionStmt(TreeNode* nodePtr) {
     localDeclaration(nodePtr->ptr1);        // Check localDecl code
     statementList(nodePtr->ptr2);           // Check stmtList code
}

/* 11. localDecl -> varDecl localDecl | empty */
void Semantic::localDeclaration(TreeNode* nodePtr) {
     if (nodePtr->kind == localDecl1) {
	  varDeclaration(nodePtr->ptr1);     // Check  varDecl code
	  localDeclaration(nodePtr->ptr2);   // Check localDecl code
     } //else if (nodePtr->kind == localDecl2) // No checks needed
}

/* 12. stmtList -> stmt stmtList | empty */
void Semantic::statementList(TreeNode* nodePtr) {
     if (nodePtr->kind == stmtList1) {
	  statement(nodePtr->ptr1);          // Check stmt code
	  statementList(nodePtr->ptr2);      // Check stmtList code
     } //else if (nodePtr->kind == stmtList2) // No checks needed
}

/* 13. stmt -> expStmt | compStmt | selStmt | retStmt */
/* 13a. e_stmt -> expStmt | compStmt | e_selStmt | retStmt */
void Semantic::statement(TreeNode* nodePtr) {
     if (nodePtr->kind == stmt1)
	  expressionStmt(nodePtr->ptr1);     // Check expStmt code
     else if (nodePtr->kind == stmt2)
          compoundStmt(nodePtr->ptr1);       // Check compStmt code
     else if (nodePtr->kind == stmt3)
	  selectionStmt(nodePtr->ptr1);      // Check selStmt code
     else if (nodePtr->kind == stmt5)
	  returnStmt(nodePtr->ptr1);         // Check retStmt code
}

/* 14. expStmt -> exp ';' | ';' */
void Semantic::expressionStmt(TreeNode* nodePtr) {
     if (nodePtr->kind == expStmt1)
	  expression(nodePtr->ptr1);         // Check code for exp
     //else if (nodePtr->kind == expStmt2)   // No checks needed
}

/* 15. compStmt -> '{' localDecl stmtList '}' */
void Semantic::compoundStmt(TreeNode* nodePtr) {
    pushScope();                        // Push scope onto sym tab     
    symTabPtr->base = fp;               // Base = FP                      
    symTabPtr->used = symTabPtr->prevScope->used; 
            // Same space amount as outer scope

    localDeclaration(nodePtr->ptr1);    // Check localDecl code  
    statementList(nodePtr->ptr2);       // Check stmtList code    
    nodePtr->symTabPtr = symTabPtr;     // Save symbol table for later use
    popScope();
}

/* 16. selStmt -> if '(' exp ')' stmt | if '(' exp ')' stmt else stmt */
/* 16a. e_selStmt -> if '(' exp ')' e_stmt else stmt */
void Semantic::selectionStmt(TreeNode* nodePtr) {
     if (nodePtr->kind == selStmt1) {
	  expression(nodePtr->ptr1);         // Check exp code
	  statement(nodePtr->ptr2);          // Check stmt code
     } else { //if (nodePtr->kind == selStmt2)
	  expression(nodePtr->ptr1);         // Check exp code
	  statement(nodePtr->ptr2);          // Check stmt1 code
	  statement(nodePtr->ptr3);          // Check stmt2 code
     }
}

/* 18. retStmt -> return ';' | return exp ';' */
void Semantic::returnStmt(TreeNode* nodePtr) {
    //if (nodePtr->kind == retStmt1)       // No checks needed
    if (nodePtr->kind == retStmt2)
	expression(nodePtr->ptr1);         // Check exp code
}

/* 19. exp -> var '=' exp | simpExp */
void Semantic::expression(TreeNode* nodePtr) {
     if (nodePtr->kind == exp1) {
	  expression(nodePtr->ptr2);         // Check exp code
	  var(nodePtr->ptr1, 0);             // Check var code
     } else //if (nodePtr->kind == exp2)
	  simpleExp(nodePtr->ptr1);
}

/* 20. var -> ID | ID '[' exp ']' */
void Semantic::var(TreeNode* nodePtr, int rlval) {
    SemanticRec* semRecPtr;
    
    // For variables...
    if (nodePtr->kind == var1) {
	semRecPtr = symTabPtr->lookup(nodePtr->line, nodePtr->strval);
	
	if (rlval == 0) {                  // we want the lvalue
            // Make sure we don't take the l-value of something not an int.
	    if (semRecPtr->kind != intvar) {
		cerr << "Static semantic error!  Line " << nodePtr->line
		     << ", identifier " << nodePtr->strval 
		     << " not a legal l-value.\n";
		exit(1);
	    }
	}
	else {// we want the rvalue

            // Make sure we don't take the r-value of a function
	    if (semRecPtr->kind ==  func) {
		cerr << "Static semantic error!  Line " << nodePtr->line
		     << ", identifier " << nodePtr->strval 
		     << " not a legal r-value.\n";
		exit(1);
	    }
	    
	}
    } 
    // For array variables...
    else if (nodePtr->kind == var2) {
	expression(nodePtr->ptr1);          // Check exp code
	
	semRecPtr = symTabPtr->lookup(nodePtr->line,nodePtr->strval);
	
        // Make sure this is an array before we find its subscript!
	if (semRecPtr->kind != intarr && semRecPtr->kind != refarr) {
	    cerr << "Static semantic error!  Line " << nodePtr->line 
		 << ", identifier " << nodePtr->strval << " not a legal ";
	    if (rlval == 0)       // we want the lvalue
		cerr << "l-value.\n";
	    else                  // we want the rvalue
		cerr << "r-value.\n";

	    exit(1);
	}
    } 
}

/* 21. simpExp -> addExp relop addExp | addExp */
/* 22. relop -> '<=' | '<' | '>' | '>=' | '==' | '!=' */
void Semantic::simpleExp(TreeNode* nodePtr) {
     if (nodePtr->kind == simpExp1) {
	  additiveExp(nodePtr->ptr1);        // Check addExp1 code
	  additiveExp(nodePtr->ptr3);        // Check addExp2 code

	  _test(nodePtr->ptr2, "simpexp->relop");
	  if (nodePtr->ptr2->kind < relop1 || nodePtr->ptr2->kind > relop6) {
	      cerr << "Static semantic error!  Line " << nodePtr->line
		   << ", unknown relational operator.\n";
	  }

     } else //if (nodePtr->kind == simpExp2)
	 additiveExp(nodePtr->ptr1);        // Check addExp code
}

/* 23. addExp -> addExp addop term | term* /
/* 24. addop -> '+' | '-' */
void Semantic::additiveExp(TreeNode* nodePtr) {
     if (nodePtr->kind == addExp1) {
	  additiveExp(nodePtr->ptr1);        // Check addExp code
	  term(nodePtr->ptr3);               // Check term code
     } else //if (nodePtr->kind == addExp2)
	  term(nodePtr->ptr1);               // Check code for term
}

/* 25. term -> term mulop factor | factor */
/* 26. mulop -> '*' | '/' */
void Semantic::term(TreeNode* nodePtr) {
    if (nodePtr->kind == term1) {
	term(nodePtr->ptr1);                 // Check term code
	factor(nodePtr->ptr3);               // Check factor code
    } else //if (nodePtr->kind == term2)
	factor(nodePtr->ptr1);               // Check code for factor
}

/* 27. factor -> '(' exp ')' | var | call | NUM */
void Semantic::factor(TreeNode* nodePtr) {
    if (nodePtr->kind == factor1)
	expression(nodePtr->ptr1);           // Check exp code
    else if (nodePtr->kind == factor2)
	var(nodePtr->ptr1,1);                // Check var code
    else if (nodePtr->kind == factor3)
	call(nodePtr->ptr1);                 // Check call code
    else ; //if (nodePtr->kind == factor4)   // No checks needed
}

/* 28. call -> ID '(' args ')' */
void Semantic::call(TreeNode* nodePtr) {
    SemanticRec* semRecPtr;

    semRecPtr = symTabPtr->lookup(nodePtr->line,nodePtr->strval);
    args(nodePtr->ptr1);                     // Check args code
    if (semRecPtr->localSpace >= 0)
	nodePtr->locals_so_far = semRecPtr->localSpace;
    else
	nodePtr->locals_so_far = locals;
}
     
 /* 29. args -> argList | empty */
void Semantic::args(TreeNode* nodePtr) {
    if (nodePtr->kind == args1)
	argList(nodePtr->ptr1);              // Check argList code
    //else if (nodePtr->kind == args2)       // No checks needed
}

/* 30. argList -> exp ',' argList | exp */
void Semantic::argList(TreeNode* nodePtr) {
     if (nodePtr->kind == argList1) {
	  expression(nodePtr->ptr1);         // Check exp code 
	  argList(nodePtr->ptr2);            // Check arglist code
     } else if (nodePtr->kind == argList2)
	  expression(nodePtr->ptr1);         // Check exp code
}

/****************************************************************************/
/*                                                                          */
/* helper routines                                                          */
/*                                                                          */
/****************************************************************************/

// Make a new scope and push it on the symbol table.
void Semantic::pushScope() {
    SymbolTable * tempScope = new SymbolTable(); // Make a new scope
    tempScope->prevScope = symTabPtr;              // Set the prev scope
    symTabPtr = tempScope;                         // Point to the scope
}

void Semantic::popScope() {
    symTabPtr = symTabPtr->prevScope;
}

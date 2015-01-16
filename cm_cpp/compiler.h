#ifndef _COMPILER_H
#define _COMPILER_H

#define pc  7            // Program Counter (next instruction addr)
#define sp  6            // Stack Pointer (top of stack)
#define fp  5            // Frame Pointer (top of current frame in stack)
#define gp  4            // Globals Pointer (top of program)
#define ac1 1            // Accumulator 1 (addresses frequently go here)
#define ac0 0            // Accumulator 0 (return values go here)
// ac2 and ac3 exist but are currently unused. You may use them.

#include "support.h"

// Types: int, array of int, array of ptr to int, function
enum {intvar, intarr, refarr, func}; 

// Kinds of tree nodes. One for each production (P1 : P2)
// There are many because this is a parse tree
enum {prog1, declList1, declList2, decl1, decl2, varDecl1, varDecl2,
      typeSpec1, typeSpec2, funDecl1, params1, params2, paramList1,
      paramList2, param1, param2, compStmt1, localDecl1, localDecl2,
      stmtList1, stmtList2, funStmt1,
      stmt1, stmt2, stmt3, stmt4, stmt5, expStmt1, expStmt2, selStmt1,
      selStmt2, iterStmt1, retStmt1, retStmt2, exp1, exp2, var1, var2,
      simpExp1, simpExp2, relop1, relop2, relop3, relop4, relop5,
      relop6, addExp1, addExp2, addop1, addop2, term1, term2, mulop1,
      mulop2, factor1, factor2, factor3, factor4, call1, args1, args2,
      argList1, argList2};

extern TreeNode*      parseTree;
extern int            lineno;

// For debugging purposes
#define _test(a,b)  if (NULL==a) fprintf(stderr, "ACCESSING NULL %s\n", b);

#endif

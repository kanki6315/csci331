#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include "support.h"

// Class to perform semantic checking on a parse tree
// Creates a scope structure, does not harm the parse tree.
class Semantic {
public:
    Semantic();
    void semanticCheck(TreeNode* nodePtr);
private:
    int  locals;          // Number of local variables in the current scope
    int  theNumParams;    // Number of params in the current function
    SymbolTable* symTabPtr; 

    void program(TreeNode* nodePtr);
    void declarationList(TreeNode* nodePtr);
    void declaration(TreeNode* nodePtr);
    void varDeclaration(TreeNode* nodePtr);
    void funDeclaration(TreeNode* nodePtr);
    void params(TreeNode* nodePtr);
    void paramList(TreeNode* nodePtr);
    void param(TreeNode* nodePtr) ;
    void functionStmt(TreeNode* nodePtr);
    void compoundStmt(TreeNode* nodePtr);
    void localDeclaration(TreeNode* nodePtr);
    void statementList(TreeNode* nodePtr);
    void statement(TreeNode* nodePtr);
    void expressionStmt(TreeNode* nodePtr);
    void selectionStmt(TreeNode* nodePtr);
    void returnStmt(TreeNode* nodePtr);
    void expression(TreeNode* nodePtr);
    void var(TreeNode* nodePtr, int rlval);
    void simpleExp(TreeNode* nodePtr);
    void additiveExp(TreeNode* nodePtr);
    void term(TreeNode* nodePtr);
    void factor(TreeNode* nodePtr);
    void call(TreeNode* nodePtr);
    void args(TreeNode* nodePtr);
    void argList(TreeNode* nodePtr);

    void pushScope();
    void popScope();
};

#endif

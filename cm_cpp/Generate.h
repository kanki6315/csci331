#include "support.h"

class Generate {
public:
    Generate();
    void generateCode(TreeNode* nodePtr);

private:
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

    int  emitSkip(int howMany);
    void emitBackup(int loc);
    void emitRestore(void);
    void emitComment(string c);
    void emitRO(string op, int r, int s, int t, string c);
    void emitRM(string op, int r, int d, int s, string c);
    void emitRMAbs(string op, int r, int a, string c);
    void push(int reg, string comm) ;
    void pop(int reg, string comm);

    void pushScope(TreeNode* nodePtr);
    void popScope();
};


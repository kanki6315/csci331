#ifndef SUPPORT_H_
#define SUPPORT_H_

using namespace std;
#include<iostream>
#include<string>
#define M 11    // Max HashTable size...


/* Semantic Record node for a variable or a function.
 * The type semRec is a union of two structures
 * Union means the semRec is either a v (variable) or f (function)
 * It is accessed as if the union has two members v and f except that you may
 * only access one of them. Example: semRec sr; sr.v.kind = intvar;
 * The type checker *should* notice if you try to use it as both v and f.
 */

class SemanticRec {
public:
    SemanticRec();
    ~SemanticRec();
    int kind;            // Variable type or Function type

    // For variables
    int base;            // Memory location (usually fp - offset)
    int offset;

    // For functions
    int addr;            // Memory location where the code is stored
    int numParams;       // Number of parameters
    int localSpace;      // Space for local variables
};

// HashNode. Points to a semantic record.
class HashNode {
public:
    HashNode();
    ~HashNode();
    string       key;             // Variable or function name
    int          theLine;         // Code line in .cm file
    SemanticRec* theSemRec;       // The semantic record.
    HashNode*   nextNode;
};

// Symbol Table. Contains a hash table of all the semantic 
// records in its scope.
class SymbolTable {
public:
    SymbolTable();
    ~SymbolTable();
    void insert(int line, string theName, SemanticRec* theRec);
    SemanticRec* lookup(int line, string theName);
    SymbolTable* prevScope;  // Pointer to previous scope
    int          base;       // Frame Pointer
    int          used;       // Space used by variables
private:
    int hashFunct(string theName);
    HashNode*    theTable[M];// Pointer to this scope's semantic records
};

// Parse Tree node.
class TreeNode {
public:
    TreeNode();
    TreeNode(int lineno);
    ~TreeNode();
    int           kind;          // From the enum above (e.g. prog1)
    int           numval;        // If it holds a number, its value
    string        strval;        // If it holds an id, its name
    TreeNode*     ptr1;          // Pointers to any child nodes
    TreeNode*     ptr2;
    TreeNode*     ptr3;
    int           line;          // Line number in the code

    int           locals_so_far; // used when making function calls
    SymbolTable*  symTabPtr;      // used for nodes beginning a scope
};

#endif

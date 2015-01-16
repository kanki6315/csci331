using namespace std;
#include<iostream>
#include<string>
#include "support.h"

/****************************************************************************/
/*                                                                          */
/* SemanticRec                                                              */
/*                                                                          */
/****************************************************************************/
SemanticRec::SemanticRec() {
}
SemanticRec::~SemanticRec(){
}

/****************************************************************************/
/*                                                                          */
/* HashNode                                                                 */
/*                                                                          */
/****************************************************************************/
HashNode::HashNode() {
     theSemRec = NULL;
     nextNode = NULL;
}

HashNode::~HashNode() { 
    delete theSemRec;
    delete nextNode;
}

/****************************************************************************/
/*                                                                          */
/* SymbolTable                                                              */
/*                                                                          */
/****************************************************************************/
SymbolTable::SymbolTable() { 
    int i;
    for(i=0; i<M; i++) theTable[i] = NULL; // Make the pointers NULL
    prevScope = NULL;                        // Previous symbol table
}

// Delete the symbol table (and its hash table)
SymbolTable::~SymbolTable() { 
    int i;
    for (i=0; i<M; i++) {                        // Destroy old hash table
	delete theTable[i];
    }
}

int SymbolTable::hashFunct(string theName) {
     int len,i, value;
     value = 0;
     
     len = theName.length();
     for (i=0;i<len;i++)
	  value += theName[i];

     return (value % M);
}

// Insert a record into the symbol table, keyed by name
void SymbolTable::insert(int line, string theName, SemanticRec* theRec) {
     int slot = hashFunct(theName);          // Hash the key.
     
     HashNode* box = new HashNode();         // Make a node for it.
     box->key = theName;
     box->theLine = line;
     box->theSemRec = theRec;
     box->nextNode = NULL;
     
     box->nextNode = theTable[slot];         // Insert the node.
     theTable[slot] = box;
}

// Lookup a symbol table record, keyed by name
SemanticRec* SymbolTable::lookup(int line, string theName) {
    int slot;
    SemanticRec* tempRec;
    HashNode* tempNode;
    
    slot = hashFunct(theName);               // Hash the key.
    
    tempNode = theTable[slot];               // Look for the node.
     while((tempNode != NULL) && (tempNode->key != theName))
	  tempNode = tempNode->nextNode;

     if (tempNode == NULL) {                 // If not found, 
	 if (prevScope != NULL)              // look in prev scope
	     tempRec = prevScope->lookup(line, theName);
	 else 
	     tempRec = NULL;                 // NULL if no prev scope
     }
     else                                    // Else, retrieve it.
	 tempRec = tempNode->theSemRec;

     return tempRec;
}


/****************************************************************************/
/*                                                                          */
/* TreeNode                                                                 */
/*                                                                          */
/****************************************************************************/
TreeNode::TreeNode() { }

TreeNode::TreeNode(int lineno) {
    line = lineno;
}

TreeNode::~TreeNode() { 
    delete ptr1;
    delete ptr2;
    delete ptr3;
}

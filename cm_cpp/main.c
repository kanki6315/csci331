using namespace std;
#include<iostream>
//#include<string>
#include "compiler.h"
#include "support.h"
#include "Semantic.h"
#include "Generate.h"

int yyparse(void);

// Evil Global! (the parser and main both use it)
TreeNode*    parseTree = NULL; // Pointer to the top of the parse tree

/****************************************************************************/
/*                                                                          */
/* main()                                                                   */
/*                                                                          */
/****************************************************************************/

main() {
  Semantic s;
  Generate g;

  cerr << "Creating parse tree...\n";
  yyparse();
  cerr << "Semantic checking...\n";
  s.semanticCheck(parseTree);
  cerr << "Generating code...\n";
  g.generateCode(parseTree);
  cerr << "Done!\n";
}

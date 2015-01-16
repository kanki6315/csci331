%option noyywrap
%{
/* C++ version of the separated compiler */
#include<iostream>
#include<string>
using namespace std;
#include "compiler.h"
#include "support.h"

/* function prototypes */
TreeNode * newIDNode(void);
TreeNode * newNumNode(void);
 void squeak(string s);

/*****************************************************************
 * The next section is a list of regular expressions in order and
 * the code called when each regular expression is found.
 * The whole set of regular expressions is turned into one function 
 * named yylex() which returns a token type. A loop runs repeatedly 
 * through the regular expressions (in order) and matches as many 
 * characters as it can. The function returns each time it has found 
 * a complete token. 
 *
 *   reg exp                      code
 *   [0-9]+                     return INT;
 *
 * When a number (one or more digits) is found, INT is returned.
 *
 * The tokens are defined in parse.yac but here is the list
 * ID NUM INT VOID IF ELSE WHILE RET LE LT GT GE EQ NE 
 *****************************************************************/

%}

/* These are regular expression abbreviations for later use.
 * To use the "letter" abbrev, you would write "{letter}"   
 */

letter     [a-zA-Z]
digit      [0-9]
identifier {letter}+
number     {digit}+
whitespace [ \t\r]+
newline    \n

/* These are the regular expressions. They each return a token. Some tokens
 * such as NUM require further information which is put into yylval.
 */
%%
"int"        {squeak(yytext); return INT;}
"void"       {squeak(yytext); return VOID;}
"if"         {squeak(yytext); return IF;}
"else"       {squeak(yytext); return ELSE;}
"return"     {squeak(yytext); return RET;}

{identifier} {squeak(yytext); yylval.tnp = newIDNode();  return ID;}
{number}     {squeak(yytext); yylval.tnp = newNumNode(); return NUM;}

"<="         {squeak(yytext); return LE;} 
"<"          {squeak(yytext); return LT;} 
">="         {squeak(yytext); return GE;} 
">"          {squeak(yytext); return GT;} 
"=="         {squeak(yytext); return EQ;} 
"!="         {squeak(yytext); return NE;} 

"+"          {squeak(yytext); return '+';}           
"-"          {squeak(yytext); return '-';} 
"*"          {squeak(yytext); return '*';} 
"/"          {squeak(yytext); return '/';} 
"="          {squeak(yytext); return '=';} 
 
";"          {squeak(yytext); return ';';}
","          {squeak(yytext); return ',';}
"("          {squeak(yytext); return '(';}
")"          {squeak(yytext); return ')';}
"["          {squeak(yytext); return '[';}
"]"          {squeak(yytext); return ']';}
"{"          {squeak(yytext); return '{';}
"}"          {squeak(yytext); return '}';}

"/*"         {/* In state machine format since it's easier that way */
              char c;
              int done = 0;
              do {
                while ( (c = yyinput()) != '*')
                  if (c == '\n')
                    lineno++;
                while ( (c = yyinput()) == '*') ;
                if (c == '\n')
                  lineno++;
                if (c == '/')
                  done = 1;
                } while (!done);}

{newline}    {squeak("\n"); lineno++;}

{whitespace} {squeak(" "); }

.            {cerr << "Lexical error!  Line " << lineno 
		   << ", unexpected character " << yytext[0] << endl;
              exit(1);}

%%

void squeak(string s) {
     cerr << s << endl;
}

TreeNode * newIDNode() {
     TreeNode * node = new TreeNode();
     node->strval = yytext;
     return node;
}

TreeNode * newNumNode() {
     TreeNode * node = new TreeNode();
     node->numval = atoi(yytext);
     return node;
}


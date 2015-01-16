#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "parse.yac"
#include<iostream>
#include<string>
#include "support.h"
#include "compiler.h"
using namespace std;

int lineno = 1;

typedef struct {
        TreeNode * tnp;
} tn;

/*#define YYDEBUG 1*/
#define YYSTYPE tn
#ifdef __cplusplus
#undef __cplusplus
#endif
#define __cplusplus
#line 42 "y.tab.c"
#define ID 257
#define NUM 258
#define INT 259
#define VOID 260
#define IF 261
#define ELSE 262
#define RET 263
#define LE 264
#define LT 265
#define GT 266
#define GE 267
#define EQ 268
#define NE 269
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    3,    3,    5,    5,    4,
    6,    6,    8,    8,    9,    9,    7,   10,   10,   11,
   11,   12,   12,   12,   12,   17,   17,   17,   17,   13,
   13,   14,   15,   15,   18,   16,   16,   19,   19,   20,
   20,   21,   21,   23,   23,   23,   23,   23,   23,   22,
   22,   24,   24,   25,   25,   26,   26,   27,   27,   27,
   27,   28,   29,   29,   30,   30,
};
short yylen[] = {                                         2,
    1,    2,    1,    1,    1,    3,    6,    1,    1,    6,
    1,    1,    3,    1,    2,    4,    4,    2,    0,    2,
    0,    1,    1,    1,    1,    1,    1,    1,    1,    2,
    1,    4,    5,    7,    7,    2,    3,    3,    1,    1,
    4,    3,    1,    1,    1,    1,    1,    1,    1,    3,
    1,    1,    1,    3,    1,    1,    1,    3,    1,    1,
    1,    4,    1,    0,    3,    1,
};
short yydefred[] = {                                      0,
    8,    9,    0,    1,    0,    4,    5,    0,    2,    0,
    6,    0,    0,    0,    0,    0,    0,   11,    0,    0,
    0,    0,    0,    7,    0,    0,   10,   13,   16,    0,
    0,    0,   18,    0,    0,   61,    0,    0,   31,    0,
    0,    0,    0,   22,   23,   24,   25,    0,    0,   39,
    0,    0,   55,   60,    0,    0,    0,   36,    0,    0,
    0,   17,   20,   30,    0,   44,   45,   46,   47,   48,
   49,   52,   53,    0,    0,   56,   57,    0,    0,    0,
    0,   63,    0,   37,   58,    0,   38,   59,    0,    0,
   54,   41,    0,   62,    0,   32,   65,    0,   33,    0,
    0,    0,    0,   28,    0,    0,    0,   34,    0,    0,
    0,   35,
};
short yydgoto[] = {                                       3,
    4,    5,   30,    7,   31,   17,   27,   18,   19,   32,
   42,   43,   44,   45,   46,   47,  103,  104,   48,   49,
   50,   51,   74,   75,   52,   78,   53,   54,   81,   82,
};
short yysindex[] = {                                   -153,
    0,    0,    0,    0, -153,    0,    0, -245,    0,    3,
    0, -208, -146,  -23,    0, -192,   61,    0,   65,   52,
   24,   -7, -153,    0,   25, -153,    0,    0,    0, -153,
 -140,   27,    0,  -11,   -6,    0,   79,    7,    0,   15,
 -153,   -1,   27,    0,    0,    0,    0,   66,   59,    0,
  -28,   14,    0,    0,   15,   15,   15,    0,   67,   81,
   27,    0,    0,    0,   15,    0,    0,    0,    0,    0,
    0,    0,    0,   15,   15,    0,    0,   15,   36,   83,
   90,    0,   91,    0,    0,    8,    0,    0,   53,   14,
    0,    0,   15,    0,   34,    0,    0,   94,    0,    0,
    0,    0, -127,    0,   15,   27,   96,    0,   34, -123,
   34,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,  140,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -36,    0,    0,    0,  100,    0,
   51,    0,    0,    0,    0,   20,    0,    0,    0,   20,
    0,   17,    0,    0,  -41,    0,    0,    0,    0,    0,
   20,    0,   17,    0,    0,    0,    0,    0,  -34,    0,
  -17,  -22,    0,    0,    0,  103,    0,    0,    0,    0,
   17,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  105,
    0,    0,    0,    0,    0,    0,    0,    0,   -5,  -15,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   -2,
    5,   13,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
short yygindex[] = {                                      0,
  142,    0,   63,    0,   77,    0,    0,  125,    0,   43,
   -3,  -60,  -20,  -12,    0,   -8,    1,    0,  -24,   30,
    0,   75,    0,    0,   76,    0,   74,    0,    0,   60,
};
#define YYTABLESIZE 297
short yytable[] = {                                      40,
   40,   40,   40,   40,   12,   40,   59,   59,   59,   59,
   59,   10,   59,   59,   72,   60,   73,   40,   51,   40,
   51,   51,   51,   43,   59,   50,   43,   50,   50,   50,
   79,   80,   83,   56,   99,   42,   51,   22,   42,   63,
   87,   43,   13,   50,   23,  108,   40,   11,   99,   14,
  108,   40,   25,   42,   40,   76,   22,   86,   59,   19,
   77,   11,    6,   23,   21,   58,   40,    6,   80,   20,
   51,   25,   33,   40,  100,   43,    8,   50,   19,   12,
  107,    8,  101,   61,   55,   39,  102,   42,  100,   16,
  100,   15,   39,   12,   15,   72,  101,   73,  101,   16,
  102,   22,  102,   88,   88,    1,    2,   88,   23,  110,
   24,  112,    1,   15,   25,   26,   34,   29,   57,   65,
   22,   85,   22,   62,   64,   84,   93,   23,   92,   23,
   94,   95,   96,  105,  106,   25,  109,   25,  111,    3,
   14,   21,   19,   64,   19,   66,    9,   28,   89,   41,
   90,   91,   97,    0,    0,    0,   41,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    9,    0,   40,   40,   40,   40,   40,   40,    0,   59,
   59,   59,   59,   59,   59,   66,   67,   68,   69,   70,
   71,   51,   51,   51,   51,   51,   51,    0,   50,   50,
   50,   50,   50,   50,   22,   22,    0,    0,   22,   26,
   22,   23,   23,   35,   36,   23,   27,   23,    0,   25,
   25,   35,   36,   25,   29,   25,   19,   19,    0,    0,
   19,    0,   19,   35,   36,    0,    0,   37,    0,   38,
   35,   36,    0,    0,   98,    0,   38,
};
short yycheck[] = {                                      41,
   42,   43,   44,   45,   41,   47,   41,   42,   43,   44,
   45,  257,   47,   38,   43,   40,   45,   59,   41,   61,
   43,   44,   45,   41,   59,   41,   44,   43,   44,   45,
   55,   56,   57,   40,   95,   41,   59,   40,   44,   43,
   65,   59,   40,   59,   40,  106,   40,   59,  109,  258,
  111,   93,   40,   59,   40,   42,   59,   61,   93,   40,
   47,   59,    0,   59,  257,   59,   40,    5,   93,   93,
   93,   59,   30,   40,   95,   93,    0,   93,   59,   91,
  105,    5,   95,   41,   91,   59,   95,   93,  109,   13,
  111,   41,   59,   91,   44,   43,  109,   45,  111,   23,
  109,   41,  111,   74,   75,  259,  260,   78,   44,  109,
   59,  111,  259,  260,   91,  123,  257,   93,   40,   61,
  123,   41,  125,  125,   59,   59,   44,  123,   93,  125,
   41,   41,  125,   40,  262,  123,   41,  125,  262,    0,
   41,  125,  123,   41,  125,   41,    5,   23,   74,  123,
   75,   78,   93,   -1,   -1,   -1,  123,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  257,   -1,  264,  265,  266,  267,  268,  269,   -1,  264,
  265,  266,  267,  268,  269,  264,  265,  266,  267,  268,
  269,  264,  265,  266,  267,  268,  269,   -1,  264,  265,
  266,  267,  268,  269,  257,  258,   -1,   -1,  261,  262,
  263,  257,  258,  257,  258,  261,  262,  263,   -1,  257,
  258,  257,  258,  261,  262,  263,  257,  258,   -1,   -1,
  261,   -1,  263,  257,  258,   -1,   -1,  261,   -1,  263,
  257,  258,   -1,   -1,  261,   -1,  263,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 269
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'",0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,
"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"ID","NUM","INT","VOID","IF","ELSE","RET","LE","LT","GT",
"GE","EQ","NE",
};
char *yyrule[] = {
"$accept : prog",
"prog : declList",
"declList : decl declList",
"declList : decl",
"decl : varDecl",
"decl : funDecl",
"varDecl : typeSpec ID ';'",
"varDecl : typeSpec ID '[' NUM ']' ';'",
"typeSpec : INT",
"typeSpec : VOID",
"funDecl : typeSpec ID '(' params ')' funStmt",
"params : paramList",
"params : VOID",
"paramList : param ',' paramList",
"paramList : param",
"param : typeSpec ID",
"param : typeSpec ID '[' ']'",
"funStmt : '{' localDecl stmtList '}'",
"localDecl : varDecl localDecl",
"localDecl :",
"stmtList : stmt stmtList",
"stmtList :",
"stmt : expStmt",
"stmt : compStmt",
"stmt : selStmt",
"stmt : retStmt",
"e_stmt : expStmt",
"e_stmt : compStmt",
"e_stmt : e_selStmt",
"e_stmt : retStmt",
"expStmt : exp ';'",
"expStmt : ';'",
"compStmt : '{' localDecl stmtList '}'",
"selStmt : IF '(' exp ')' stmt",
"selStmt : IF '(' exp ')' e_stmt ELSE stmt",
"e_selStmt : IF '(' exp ')' e_stmt ELSE e_stmt",
"retStmt : RET ';'",
"retStmt : RET exp ';'",
"exp : var '=' exp",
"exp : simpExp",
"var : ID",
"var : ID '[' exp ']'",
"simpExp : addExp relop addExp",
"simpExp : addExp",
"relop : LE",
"relop : LT",
"relop : GT",
"relop : GE",
"relop : EQ",
"relop : NE",
"addExp : addExp addop term",
"addExp : term",
"addop : '+'",
"addop : '-'",
"term : term mulop factor",
"term : factor",
"mulop : '*'",
"mulop : '/'",
"factor : '(' exp ')'",
"factor : var",
"factor : call",
"factor : NUM",
"call : ID '(' args ')'",
"args : argList",
"args :",
"argList : exp ',' argList",
"argList : exp",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 527 "parse.yac"

#include "lex.yy.c"

void yyerror(char const* s) {
  fprintf(stderr,"Syntactic error!  Line %d, unexpected token ",lineno);
  switch (yychar) {
  case ';':  
    fprintf(stderr,"\";\".\n");
    break;
  case '[':  
    fprintf(stderr,"\"[\".\n");
    break;
  case ']':  
    fprintf(stderr,"\"]\".\n");
    break;
  case '(':
    fprintf(stderr,"\"(\".\n");
    break;
  case ')':
    fprintf(stderr,"\")\".\n");
    break;
  case ',':
    fprintf(stderr,"\",\".\n");
    break;
  case '{':
    fprintf(stderr,"\"{\".\n");
    break;
  case '}':
    fprintf(stderr,"\"{\".\n");
    break;
  case '=':
    fprintf(stderr,"\"=\".\n");
    break;
  case LE:
    fprintf(stderr,"\"<=\".\n");
    break;
  case LT:
    fprintf(stderr,"\"<\".\n");
    break;
  case GT:
    fprintf(stderr,"\">\".\n");
    break;
  case GE:
    fprintf(stderr,"\">=\".\n");
    break;
  case EQ:
    fprintf(stderr,"\"==\".\n");
    break;
  case NE:
    fprintf(stderr,"\"!=\".\n");
    break;
  case '+':
    fprintf(stderr,"\"+\".\n");
    break;
  case '-':
    fprintf(stderr,"\"-\".\n");
    break;
  case '*':
    fprintf(stderr,"\"*\".\n");
    break;
  case '/':
    fprintf(stderr,"\"/\".\n");
    break;
  case INT:
    fprintf(stderr,"\"int\".\n");
    break;
  case VOID:
    fprintf(stderr,"\"void\".\n");
    break;
  case IF:
    fprintf(stderr,"\"if\".\n");
    break;
  case ELSE:
    fprintf(stderr,"\"else\".\n");
    break;
  case RET:
    fprintf(stderr,"\"return\".\n");
    break;
  case ID:
    cerr << yylval.tnp->strval << endl;
    break;
  case NUM:
    fprintf(stderr,"\"%d\".\n",yylval.tnp->numval);
    break;
  default:	
	fprintf(stderr,"\"%s\".\n",yytext);
	
  }
  exit(1);
}

#line 407 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 42 "parse.yac"
{
  parseTree = new TreeNode();  /* Make a new tree node for it. */
  parseTree->kind = prog1;         /* Set its kind from the enum types. */
  parseTree->ptr1 = yyvsp[0].tnp;            /* Point to the component nodes. */
}
break;
case 2:
#line 51 "parse.yac"
{
  yyval.tnp = new TreeNode();
  yyval.tnp->kind = declList1;
  yyval.tnp->ptr1 = yyvsp[-1].tnp;
  yyval.tnp->ptr2 = yyvsp[0].tnp;
}
break;
case 3:
#line 58 "parse.yac"
{
  yyval.tnp = new TreeNode();
  yyval.tnp->kind = declList2;
  yyval.tnp->ptr1 = yyvsp[0].tnp;
}
break;
case 4:
#line 67 "parse.yac"
{
  yyval.tnp = new TreeNode();
  yyval.tnp->kind = decl1;
  yyval.tnp->ptr1 = yyvsp[0].tnp;
}
break;
case 5:
#line 73 "parse.yac"
{
  yyval.tnp = new TreeNode();
  yyval.tnp->kind = decl2;
  yyval.tnp->ptr1 = yyvsp[0].tnp;
}
break;
case 6:
#line 82 "parse.yac"
{
  yyval.tnp = yyvsp[-1].tnp;
  yyval.tnp->kind = varDecl1;
  yyval.tnp->ptr1 = yyvsp[-2].tnp;
}
break;
case 7:
#line 88 "parse.yac"
{
  yyval.tnp = yyvsp[-4].tnp;
  yyval.tnp->kind = varDecl2;
  yyval.tnp->ptr1 = yyvsp[-5].tnp;
  yyval.tnp->numval = yyvsp[-2].tnp->numval;
  free(yyvsp[-2].tnp);
}
break;
case 8:
#line 99 "parse.yac"
{ 
  yyval.tnp = new TreeNode();
  yyval.tnp->kind = typeSpec1;
}
break;
case 9:
#line 104 "parse.yac"
{ yyval.tnp = new TreeNode();
  yyval.tnp->kind = typeSpec2;
}
break;
case 10:
#line 111 "parse.yac"
{
  yyval.tnp = yyvsp[-4].tnp;
  yyval.tnp->kind = funDecl1;
  yyval.tnp->ptr1 = yyvsp[-5].tnp;
  yyval.tnp->ptr2 = yyvsp[-2].tnp;
  yyval.tnp->ptr3 = yyvsp[0].tnp;
}
break;
case 11:
#line 122 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = params1;          /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 12:
#line 128 "parse.yac"
{
   yyval.tnp = new TreeNode();    /* Set the node. */
   yyval.tnp->kind = params2;         /* Set the kind. */
}
break;
case 13:
#line 136 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = paramList1;       /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-2].tnp;               /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[0].tnp;
}
break;
case 14:
#line 143 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = paramList2;       /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 15:
#line 152 "parse.yac"
{
  yyval.tnp = yyvsp[0].tnp;                     /* Set the node. */
  yyval.tnp->kind = param1;           /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-1].tnp;               /* Set the pointers. */
}
break;
case 16:
#line 158 "parse.yac"
{
  yyval.tnp = yyvsp[-2].tnp;                     /* Set the node. */
  yyval.tnp->kind = param2;           /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-3].tnp;               /* Set the pointers. */
}
break;
case 17:
#line 167 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = funStmt1;        /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-2].tnp;               /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[-1].tnp;
}
break;
case 18:
#line 177 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = localDecl1;       /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-1].tnp;               /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[0].tnp;
}
break;
case 19:
#line 184 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = localDecl2;/* Set the kind. */
}
break;
case 20:
#line 192 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = stmtList1;        /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-1].tnp;               /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[0].tnp;
}
break;
case 21:
#line 199 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = stmtList2;        /* Set the kind. */
}
break;
case 22:
#line 207 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = stmt1;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 23:
#line 213 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = stmt2;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 24:
#line 219 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = stmt3;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 25:
#line 225 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = stmt5;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 26:
#line 234 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = stmt1;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 27:
#line 240 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = stmt2;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 28:
#line 246 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = stmt3;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 29:
#line 252 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = stmt5;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 30:
#line 261 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = expStmt1;         /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-1].tnp;               /* Set the pointers. */
}
break;
case 31:
#line 267 "parse.yac"
{
  yyval.tnp = new TreeNode(); /* Set the node. */
  yyval.tnp->kind = expStmt2; /* Set the kind. */
  /* Set the pointers. */
}
break;
case 32:
#line 276 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = compStmt1;        /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-2].tnp;               /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[-1].tnp;
}
break;
case 33:
#line 286 "parse.yac"
{
  yyval.tnp = new TreeNode(); /* Set the node. */
  yyval.tnp->kind = selStmt1; /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-2].tnp; /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[0].tnp;
}
break;
case 34:
#line 293 "parse.yac"
{
  yyval.tnp = new TreeNode(); /* Set the node. */
  yyval.tnp->kind = selStmt2; /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-4].tnp;   /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[-2].tnp;
  yyval.tnp->ptr3 = yyvsp[0].tnp;
}
break;
case 35:
#line 304 "parse.yac"
{
  yyval.tnp = new TreeNode(); /* Set the node. */
  yyval.tnp->kind = selStmt2; /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-4].tnp;   /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[-2].tnp;
  yyval.tnp->ptr3 = yyvsp[0].tnp;
}
break;
case 36:
#line 315 "parse.yac"
{
  yyval.tnp = new TreeNode(); /* Set the node. */
  yyval.tnp->kind = retStmt1; /* Set the kind. */
}
break;
case 37:
#line 320 "parse.yac"
{
  yyval.tnp = new TreeNode(); /* Set the node. */
  yyval.tnp->kind = retStmt2; /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-1].tnp;  /* Set the pointers. */
}
break;
case 38:
#line 329 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = exp1;             /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-2].tnp;               /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[0].tnp;
}
break;
case 39:
#line 336 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = exp2;             /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 40:
#line 345 "parse.yac"
{
  yyval.tnp = yyvsp[0].tnp;                     /* Set the node. */
  yyval.tnp->kind = var1;             /* Set the kind. */
}
break;
case 41:
#line 350 "parse.yac"
{
  yyval.tnp = yyvsp[-3].tnp;                     /* Set the node. */
  yyval.tnp->kind = var2;             /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-1].tnp;               /* Set the pointers. */
}
break;
case 42:
#line 359 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = simpExp1;         /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-2].tnp;               /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[-1].tnp;
  yyval.tnp->ptr3 = yyvsp[0].tnp;
}
break;
case 43:
#line 367 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = simpExp2;         /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 44:
#line 376 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = relop1; }
break;
case 45:
#line 380 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = relop2; }
break;
case 46:
#line 384 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = relop3; }
break;
case 47:
#line 388 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = relop4; }
break;
case 48:
#line 392 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = relop5; }
break;
case 49:
#line 396 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = relop6; }
break;
case 50:
#line 403 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = addExp1;          /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-2].tnp;               /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[-1].tnp;
  yyval.tnp->ptr3 = yyvsp[0].tnp;
}
break;
case 51:
#line 411 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = addExp2;          /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 52:
#line 420 "parse.yac"
{ 
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = addop1;     /* Set the kind. */
}
break;
case 53:
#line 425 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = addop2; 
}
break;
case 54:
#line 433 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = term1;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-2].tnp;               /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[-1].tnp;
  yyval.tnp->ptr3 = yyvsp[0].tnp;
}
break;
case 55:
#line 441 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = term2;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 56:
#line 450 "parse.yac"
{ 
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = mulop1;           /* Set the kind. */ 
}
break;
case 57:
#line 455 "parse.yac"
{ 
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = mulop2; 
}
break;
case 58:
#line 463 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = factor1;          /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-1].tnp;               /* Set the pointers. */
}
break;
case 59:
#line 469 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = factor2;          /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 60:
#line 475 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = factor3;          /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 61:
#line 481 "parse.yac"
{
  yyval.tnp = yyvsp[0].tnp;                     /* Set the node. */
  yyval.tnp->kind = factor4;          /* Set the kind. */
}
break;
case 62:
#line 489 "parse.yac"
{
  yyval.tnp = yyvsp[-3].tnp;                     /* Set the node. */
  yyval.tnp->kind = call1;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-1].tnp;               /* Set the pointers. */
}
break;
case 63:
#line 498 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = args1;            /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
case 64:
#line 504 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = args2;            /* Set the kind. */
}
break;
case 65:
#line 512 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = argList1;         /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[-2].tnp;               /* Set the pointers. */
  yyval.tnp->ptr2 = yyvsp[0].tnp;
}
break;
case 66:
#line 519 "parse.yac"
{
  yyval.tnp = new TreeNode();     /* Set the node. */
  yyval.tnp->kind = argList2;         /* Set the kind. */
  yyval.tnp->ptr1 = yyvsp[0].tnp;               /* Set the pointers. */
}
break;
#line 1113 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}

#  include <vips/vips.h>

/* symbol table */
struct symbol {		/* a variable name */
  char *name;
  struct utils *value;    
  struct ast *func;	/* stmt for the function */
  struct symlist *syms; /* list of dummy args */
};

/* simple symtab of fixed size */
#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char*);

/* list of symbols, for an argument list */
struct symlist {
  struct symbol *sym;
  struct symlist *next;
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

/* node types
 *  + - * / |
 *  0-7 comparison ops, bit coded 04 equal, 02 less, 01 greater
 *  M unary minus
 *  L statement list
 *  I IF statement
 *  W WHILE statement
 *  N symbol ref
 *  = assignment
 *  S list of symbols
 *  F built in function call
 *  C user function call
 */ 

/* nodes in the Abstract Syntax Tree */
/* all have common initial nodetype */

enum bifs {			/* built-in functions */
  B_print = 1,
  I_width,
  I_invert,
  I_average
};

struct ast {
  int nodetype;
  struct ast *l;
  struct ast *r;
};

struct ufncall {		/* user function */
  int nodetype;			/* type C */
  struct ast *l;		/* list of arguments */
  struct symbol *s;
};

struct fncall {			/* built-in function */
  int nodetype;			/* type F */
  struct ast *l;
  enum bifs functype;
};

struct flow {
  int nodetype;			/* type I or W */
  struct ast *cond;		/* condition */
  struct ast *tl;		/* then or do list */
  struct ast *el;		/* optional else list */
};

struct utils
{
  int nodetype;
};

struct integer
{
  int nodetype;      /* type i */
  int i;
};

struct doublePrecision
{
  int nodetype;      /* type D */
  double d;
};
 
struct str
{
  int nodetype;     /* type S */
  char * str;
};

struct img
{
  int nodetype;     /* type P */
  char * path;      //Image path
  VipsImage * img;
};

struct symref {
  int nodetype;			/* type N */
  struct symbol *s;
};

struct symasgn {
  int nodetype;			/* type = */
  struct symbol *s;
  struct ast *v;		/* value */
};

/* build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newint(int i);
struct ast *newimg(char * path);
struct ast *newdouble(double i);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);

/* define a function */
void dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);

/* evaluate an AST */
struct utils *eval(struct ast *);

/* built-in functions */
void print_B(struct utils * v);
void getWidth(struct symref * v);
void invert(struct symref * v);
void average(struct symref * v);


/* delete and free an AST */
void treefree(struct ast *);

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);

extern int debug;
void dumpast(struct ast *a, int level);


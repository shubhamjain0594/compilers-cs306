/* Changes:  */

/* 1. Character constants removed */
/* 2. Changed INTCONSTANT to INT_CONSTANT */
/* 3. Changed the production for constant_expression to include FLOAT_CONSTANT */
/* 4. Added examples of FLOAT_CONSTANTS */
/* 5. Added the description of STRING_LITERAL */
/* 6. Changed primary_expression and FOR */
/* 7. The grammar permits a empty statement. This should be  */
/*    explicitly represented in the AST. */
/* 8. To avoid local decl inside blocks, a rule for statement  */
/*    has been changed. */

/* ----------------------------------------------------------------------- */

/* start symbol is translation_unit */

/* ---------------------------------------------------- */
%scanner Scanner.h
%scanner-token-function d_scanner.lex()
%polymorphic STMT:stmt_node*; EXP:exp_node*; ARRAY:array_ref_node*; TYPE_INT: int*; TYPE_STRING: string;TYPE_FLOAT: float*; EXP_LIST: exp_node_list*; STMT_LIST: stmt_node_list*;
%type <STMT> translation_unit function_definition compound_statement statement assignment_statement selection_statement iteration_statement
%type <EXP> expression logical_and_expression equality_expression relational_expression additive_expression multiplicative_expression unary_expression postfix_expression primary_expression l_expression
%type <EXP_LIST> expression_list
%type <STMT_LIST> statement_list
%type <TYPE_STRING> unary_operator IDENTIFIER INT_CONSTANT STRING_LITERAL FLOAT_CONSTANT
%token VOID INT FLOAT AND_OP OR_OP EQ_OP NE_OP LE_OP GE_OP IF ELSE WHILE FOR RETURN INC_OP 

%%

translation_unit
  : function_definition
  {
    $1->print();
  } 
  | translation_unit function_definition 
  {
    $$ = $1;
    $2->print();
  }
  ;

function_definition
  : type_specifier fun_declarator compound_statement 
  {
    $$ = $3;
  }
  ;

type_specifier
  : VOID  
  | INT   
  | FLOAT 
  ;

fun_declarator
  : IDENTIFIER '(' parameter_list ')' 
  | IDENTIFIER '(' ')' 
  ;

parameter_list
  : parameter_declaration 
  | parameter_list ',' parameter_declaration 
  ;

parameter_declaration
  : type_specifier declarator 
  ;

declarator
  : IDENTIFIER 
  | declarator '[' constant_expression ']' 
  ;

constant_expression 
  : INT_CONSTANT 
  | FLOAT_CONSTANT 
  ;

compound_statement
  : '{' '}' 
  | '{' statement_list '}'
  { 
    $$ = new block_node($2);
  }
  | '{' declaration_list statement_list '}' 
  {
    $$ = new block_node($3);
  }
  ;

statement_list
  : statement
  {
    $$ = new stmt_node_list();
    ($$)->add_stmt($1);
  }   
  | statement_list statement
  {
    ($1)->add_stmt($2);
     $$ = $1;
  }
  ;

statement
  : '{' statement_list '}'  //a solution to the local decl problem
  {
    $$ = new block_node($2);
  }
  | selection_statement
  {
    $$ = $1; 
  }   
  | iteration_statement
  {
    $$ = $1;
  }   
  | assignment_statement
  {
    $$ = $1;
  } 
  | RETURN expression ';' 
  {
    $$ = new return_node($2);
  }
  ;

assignment_statement
  : ';'
  {
    $$ = new stmt_node();
  }                 
  |  l_expression '=' expression ';'  
  {
    $$ = new ass_node($1,$3);
  }
  ;

expression
    : logical_and_expression 
    {
      $$ = $1;
    }
    | expression OR_OP logical_and_expression
    {
      string k;
      k = "OR";
      $$ = new op_node(k,$1,$3);
    }
    ;

logical_and_expression
    : equality_expression
    {
      $$ = $1;
    }
    | logical_and_expression AND_OP equality_expression
    { 
      string k;
      k = "AND";
      $$ = new op_node(k,$1,$3); 
    } 
    ;

equality_expression
  : relational_expression
  {
    $$ = $1;
  } 
  | equality_expression EQ_OP relational_expression
  { 
    string k;
    k = "ASSIGN_EXP";
    $$ = new op_node(k,$1,$3);
  }   
  | equality_expression NE_OP relational_expression
  {
    string k;
    k = "NE";
    $$ = new op_node(k,$1,$3);
  }
  ;

relational_expression
  : additive_expression
  {
    $$ = $1;
  }
  | relational_expression '<' additive_expression
  {
    string k;
    k = "LT";
    $$ = new op_node(k,$1,$3);
  } 
  | relational_expression '>' additive_expression
  {
    string k;
    k = "GT";
    $$ = new op_node(k,$1,$3);
  } 
  | relational_expression LE_OP additive_expression
  {
    string k;
    k = "LE";
    $$ = new op_node(k,$1,$3);  
  } 
  | relational_expression GE_OP additive_expression
  {
    string k;
    k = "GE";
    $$ = new op_node(k,$1,$3);  
  } 
  ;

additive_expression 
  : multiplicative_expression
  {
    $$ = $1;  
  }
  | additive_expression '+' multiplicative_expression
  {
    string k;
    k = "PLUS";
    $$ = new op_node(k,$1,$3);  
  } 
  | additive_expression '-' multiplicative_expression
  {
    string k;
    k = "MINUS";
    $$ = new op_node(k,$1,$3); 
  } 
  ;

multiplicative_expression
  : unary_expression
  {
    $$ = $1;
  }
  | multiplicative_expression '*' unary_expression
  {
    string k;
    k = "MULTIPLY";
    $$ = new op_node(k,$1,$3);  
  } 
  | multiplicative_expression '/' unary_expression
  {
    string k;
    k = "DIVIDE";
    $$ = new op_node(k,$1,$3);  
  } 
  ;

unary_expression
  : postfix_expression
  {
    $$ = $1;
  }         
  | unary_operator postfix_expression
  {
    $$ = new unary_op_node($1 , $2);
  } 
  ;

postfix_expression
  : primary_expression
  {
    $$ = $1;
  }
  | IDENTIFIER '(' ')'
  {
    exp_node_list* temp_list = new exp_node_list();
    $$ = new funcall_node($1, temp_list);
  }
  | IDENTIFIER '(' expression_list ')'
  {
    $$ = new funcall_node($1, $3);
  } 
  | l_expression INC_OP
  {
    string k = "PP";
    $$ = new unary_op_node(k,$1);
  }
  ;

primary_expression
  : l_expression
  {
    $$ = $1;
  }
  | l_expression '=' expression // added this production
  {
    string k ="ASSIGN";
    $$ = new op_node(k,$1,$3);
  }
  | INT_CONSTANT
  {
    $$ = new intconst_node($1);
  }
  | FLOAT_CONSTANT
  {
    $$ = new floatconst_node($1); 
  }
  | STRING_LITERAL
  {
    $$ = new stringconst_node($1);  
  }
  | '(' expression ')'
  {
    $$ = $2;
  }   
  ;

l_expression
    : IDENTIFIER
    {
      $$ = new identifier_array_ref_node($1);     
    }
    | l_expression '[' expression ']'
    {
      $$ = new index_node($1, $3);   
    }   
    ;

expression_list
        : expression
        {
          ($$)->add_exp($1);
        }
        | expression_list ',' expression
        {
          ($1)->add_exp($3);
          $$ = $1;
        }
        ;

unary_operator
  : '-'
  {
    $$ = "-";
  } 
  | '!'
  {
    $$ = "!";
  }   
  ;

selection_statement
    : IF '(' expression ')' statement ELSE statement
    {
      $$ = new if_node($3,$5,$7);
    } 
  ;

iteration_statement
  : WHILE '(' expression ')' statement
  {
    $$ = new while_node($3,$5);
  }   
  | FOR '(' expression ';' expression ';' expression ')' statement  //modified this production
  {
    $$ = new for_node($3,$5,$7,$9);
  }
  ;

declaration_list
    : declaration           
    | declaration_list declaration
  ;

declaration
  : type_specifier declarator_list';'
  ;

declarator_list
  : declarator
  | declarator_list ',' declarator 
  ;


/* A description of integer and float constants. Not part of the grammar.   */

/* Numeric constants are defined as:  */

/* C-constant: */
/*   C-integer-constant */
/*   floating-point-constant */
 
/* C-integer-constant: */
/*   [1-9][0-9]* */
/*   0[bB][01]* */
/*   0[0-7]* */
/*   0[xX][0-9a-fA-F]* */
 
/* floating-point-constant: */
/*   integer-part.[fractional-part ][exponent-part ] */

/* integer-part: */
/*   [0-9]* */
 
/* fractional-part: */
/*   [0-9]* */
 
/* exponent-part: */
/*   [eE][+-][0-9]* */
/*   [eE][0-9]* */

/* The rule given above is not entirely accurate. Correct it on the basis of the following examples: */

/* 1. */
/* 23.1 */
/* 01.456 */
/* 12.e45 */
/* 12.45e12 */
/* 12.45e-12 */
/* 12.45e+12 */

/* The following are not examples of FLOAT_CONSTANTs: */

/* 234 */
/* . */

/* We have not yet defined STRING_LITERALs. For our purpose, these are */
/* sequence of characters enclosed within a pair of ". If the enclosed */
/* sequence contains \ and ", they must be preceded with a \. Apart from */
/* \and ", the only other character that can follow a \ within a string */
/* are t and n.  */




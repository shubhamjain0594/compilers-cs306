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


%token VOID INT FLOAT FLOAT_CONSTANT INT_CONSTANT AND_OP OR_OP EQ_OP NE_OP LE_OP GE_OP STRING_LITERAL IF ELSE WHILE FOR RETURN IDENTIFIER INC_OP

%%

translation_unit
	: function_definition 
	| translation_unit function_definition 
        ;

function_definition
	: type_specifier fun_declarator compound_statement 
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
        | '{' declaration_list statement_list '}' 
	;

statement_list
	: statement		
        | statement_list statement	
	;

statement
    : '{' statement_list '}'  //a solution to the local decl problem
    {

    }
    | selection_statement
    {
    	$$ = new_node 
    } 	
    | iteration_statement
    {

    } 	
	| assignment_statement	
    | RETURN expression ';'	
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
    	$$ = new op_node("OR_OP",$1,$3);
    }
	;

logical_and_expression
    : equality_expression
    {
    	$$ = $1;
    }
    | logical_and_expression AND_OP equality_expression
    {
    	$$ = new op_node("AND_OP",$1,$3);	
    } 
	;

equality_expression
	: relational_expression
	{
		$$ = $1;
	} 
    | equality_expression EQ_OP relational_expression
    {
    	$$ = new op_node("EQ_OP",$1,$3);
    } 	
	| equality_expression NE_OP relational_expression
	{
		$$ = new op_node("NE_OP",$1,$3);
	}
	;

relational_expression
	: additive_expression
	{
		$$ = $1;
	}
    | relational_expression '<' additive_expression
    {
    	$$ = new op_node("LT_OP",$1,$3);
    } 
	| relational_expression '>' additive_expression
	{
    	$$ = new op_node("GT_OP",$1,$3);
    } 
	| relational_expression LE_OP additive_expression
	{
		$$ = new op_node("LE_OP",$1,$3);	
	} 
    | relational_expression GE_OP additive_expression
    {
    	$$ = new op_node("GE_OP",$1,$3);	
    } 
	;

additive_expression 
	: multiplicative_expression
	{
		$$ = $1;	
	}
	| additive_expression '+' multiplicative_expression
	{
    	$$ = new op_node("PLUS_OP",$1,$3);	
    } 
	| additive_expression '-' multiplicative_expression
	{
    	$$ = new op_node("MINUS_OP",$1,$3);	
    } 
	;

multiplicative_expression
	: unary_expression
	{
		$$ = $1;
	}
	| multiplicative_expression '*' unary_expression
	{
    	$$ = new op_node("MULTIPLY_OP",$1,$3);	
    } 
	| multiplicative_expression '/' unary_expression
	{
    	$$ = new op_node("DIVIDE_OP",$1,$3);	
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
    	identifier_node* id = new identifier_node($1);
    	exp_node_list* temp_list = new exp_node_list();
    	temp_list->add_exp(id);
    	$$ = new funcall_node(temp_list)
    }
	| IDENTIFIER '(' expression_list ')'
	{
		identifier_node* id = new identifier_node($1);
    	($3)->add_exp_at_front(id);
    	$$ = new funcall_node($3);
	} 
	| l_expression INC_OP
	{
		$$ = new unary_op("INC_OP",$1);
	}
	;

primary_expression
	: l_expression
	{
		$$ = $1;
	}
    | l_expression '=' expression // added this production
    {
    	$$ = new op_node("EQ_OP",$1,$3);
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
		$1 = new identifier_node($1);   	
	}
	| l_expression '[' expression ']'
	{

	} 	
	;	

expression_list
  : expression
  | expression_list ',' expression
  ;

unary_operator
    : '-'
    {
    	$$ = $1;
    }	
	| '!'
	{
		$$ = $1;
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
		$$ = new while_node($2,$4);
	} 	
  | FOR '(' expression ';' expression ';' expression ')' statement  //modified this production
  {
  	$$ = new for_node($3,$4,$5,$6);
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




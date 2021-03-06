%scanner Scanner.h
%scanner-token-function d_scanner.lex()

%token VOID INT FLOAT IF ELSE FOR WHILE RETURN IDENTIFIER
%token INC_OP EQ_OP LE_OP NE_OP GE_OP AND_OP OR_OP
%token INT_CONSTANT STRING_CONSTANT FLOAT_CONSTANT

%%
translation_unit
	: function_definition
  {
    count++;
    $$=count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"translation_unit\"];"<<std::endl;
  }
	| translation_unit function_definition
  {
    count++;
    $$=count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;   
    std::cout<<$$<<" [label=\"translation_unit\"];"<<std::endl;
  }
	;

function_definition
	: type_specifier fun_declarator compound_statement
  {
    count++;
    $$=count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"function_definition\"];"<<std::endl;
  }
	;

type_specifier
	: VOID
  {
    count++;
    $1=count;
    count++;
    $$=count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"type_specifier\"];"<<std::endl;
    std::cout<<$1<<" [label=\"VOID\"];"<<std::endl;
  }
	| INT
  {
    count++;
    $1=count;
    count++;
    $$=count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"type_specifier\"];"<<std::endl;
    std::cout<<$1<<" [label=\"INT\"];"<<std::endl;
  }
	| FLOAT
  {
    count++;
    $1=count;
    count++;
    $$=count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"type_specifier\"];"<<std::endl;
    std::cout<<$1<<" [label=\"FLOAT\"];"<<std::endl;
  }
	;

fun_declarator
	: IDENTIFIER '(' parameter_list ')'
  {
    count++;
    $1 = count;
    count++;
    $2 = count;
    count++;
    $4 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<"->"<<$4<<";"<<std::endl;
    std::cout<<$$<<" [label=\"fun_declarator\"];"<<std::endl;
    std::cout<<$1<<" [label=\"IDENTIFIER\"];"<<std::endl;
    std::cout<<$2<<" [label=\"(\"];"<<std::endl;
    std::cout<<$4<<" [label=\")\"];"<<std::endl;
  }
	| IDENTIFIER '(' ')'
  {
    count++;
    $1 = count;
    count++;
    $2 = count;
    count++;
    $3 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"fun_declarator\"];"<<std::endl;
    std::cout<<$1<<" [label=\"IDENTIFIER\"];"<<std::endl;
    std::cout<<$2<<" [label=\"(\"];"<<std::endl;
    std::cout<<$3<<" [label=\")\"];"<<std::endl;
  }
	;

parameter_list
	: parameter_declaration
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"parameter_list\"];"<<std::endl;
  }
	| parameter_list ',' parameter_declaration
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl; 
    std::cout<<$$<<" [label=\"parameter_list\"];"<<std::endl;
    std::cout<<$2<<" [label=\",\"];"<<std::endl;
  }
	;

parameter_declaration
	: type_specifier declarator
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<" [label=\"parameter_declaration\"];"<<std::endl;
  }
	;

declarator
	: IDENTIFIER
  {
    count++;
    $1 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"declarator\"];"<<std::endl;
    std::cout<<$1<<" [label=\"IDENTIFIER\"];"<<std::endl;
  }
	| declarator '[' constant_expression ']'
  {
    count++;
    $2 = count;
    count++;
    $4 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<"->"<<$4<<";"<<std::endl;
    std::cout<<$$<<" [label=\"declarator\"];"<<std::endl;
    std::cout<<$2<<" [label=\"[\"];"<<std::endl;
    std::cout<<$4<<" [label=\"]\"];"<<std::endl;
  }
	;

constant_expression
  : INT_CONSTANT
  {
    count++;
    $1 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"constant_expression\"];"<<std::endl;
    std::cout<<$1<<" [label=\"INT_CONSTANT\"];"<<std::endl;
  }
  | FLOAT_CONSTANT
  {
    count++;
    $1 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"constant_expression\"];"<<std::endl;
    std::cout<<$1<<" [label=\"FLOAT_CONSTANT\"];"<<std::endl;
  }
  ;

compound_statement
	: '{' '}'
  {
    count++;
    $1 = count;
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl; 
    std::cout<<$$<<" [label=\"compound_statement\"];"<<std::endl;
    std::cout<<$1<<" [label=\"{\"];"<<std::endl;
    std::cout<<$2<<" [label=\"}\"];"<<std::endl;
  }
	| '{' statement_list '}'
  {
    count++;
    $1 = count;
    count++;
    $3 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl; 
    std::cout<<$$<<"->"<<$3<<";"<<std::endl; 
    std::cout<<$$<<" [label=\"compound_statement\"];"<<std::endl;
    std::cout<<$1<<" [label=\"{\"];"<<std::endl;
    std::cout<<$3<<" [label=\"}\"];"<<std::endl;
  }
  | '{' declaration_list statement_list '}'
  {
    count++;
    $1 = count;
    count++;
    $4 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl; 
    std::cout<<$$<<"->"<<$3<<";"<<std::endl; 
    std::cout<<$$<<"->"<<$4<<";"<<std::endl; 
    std::cout<<$$<<" [label=\"compound_statement\"];"<<std::endl;
    std::cout<<$1<<" [label=\"{\"];"<<std::endl;
    std::cout<<$4<<" [label=\"}\"];"<<std::endl;
  }
	;

statement_list
	: statement
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"statement_list\"];"<<std::endl;
  }
	| statement_list statement
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl; 
    std::cout<<$$<<" [label=\"statement_list\"];"<<std::endl;
  }
	;

statement
  : compound_statement
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"statement\"];"<<std::endl; 
  }
	| selection_statement
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"statement\"];"<<std::endl; 
  }
	| iteration_statement
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"statement\"];"<<std::endl; 
  }
	| assignment_statement
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"statement\"];"<<std::endl; 
  }
  | RETURN expression ';'
  {
    count++;
    $1 = count;
    count++;
    $3 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"statement\"];"<<std::endl; 
    std::cout<<$1<<" [label=\"RETURN\"];"<<std::endl;  
    std::cout<<$3<<" [label=\";\"];"<<std::endl;  
  }
	;

assignment_statement
	: ';'
  {
    count++;
    $1 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"assignment_statement\"];"<<std::endl; 
    std::cout<<$1<<" [label=\";\"];"<<std::endl;  
  }
	|  l_expression '=' expression ';'
  {
    count++;
    $2 = count;
    count++;
    $4 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<"->"<<$4<<";"<<std::endl;
    std::cout<<$$<<" [label=\"assignment_statement\"];"<<std::endl; 
    std::cout<<$2<<" [label=\"=\"];"<<std::endl;  
    std::cout<<$4<<" [label=\";\"];"<<std::endl;  
  }
	;

expression
	: logical_and_expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";\n";
    std::cout<<$$<<" [label=\"expression\"];\n";  
  }
	| expression OR_OP logical_and_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"expression\"];"<<std::endl;  
    std::cout<<$2<<" [label=\"OR_OP\"];"<<std::endl;  
  }
	;

logical_and_expression
	: equality_expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"logical_and_expression\"];"<<std::endl;  
  }
	| logical_and_expression AND_OP equality_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"logical_and_expression\"];"<<std::endl;  
    std::cout<<$2<<" [label=\"AND_OP\"];"<<std::endl;   
  }
	;

equality_expression
	: relational_expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"equality_expression\"];"<<std::endl;      
  }
	| equality_expression EQ_OP relational_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"equality_expression\"];"<<std::endl;      
    std::cout<<$2<<" [label=\"EQ_OP\"];"<<std::endl;    
  }
	| equality_expression NE_OP relational_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"equality_expression\"];"<<std::endl;      
    std::cout<<$2<<" [label=\"NE_OP\"];"<<std::endl; 
  }
	;

relational_expression
	: additive_expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"relational_expression\"];"<<std::endl;   
  }
	| relational_expression '<' additive_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"relational_expression\"];"<<std::endl;   
    std::cout<<$2<<" [label=\"<\"];"<<std::endl;      
  }
	| relational_expression '>' additive_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"relational_expression\"];"<<std::endl;   
    std::cout<<$2<<" [label=\">\"];"<<std::endl;      
  }
	| relational_expression LE_OP additive_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"relational_expression\"];"<<std::endl;   
    std::cout<<$2<<" [label=\"LE_OP\"];"<<std::endl;      
  }
	| relational_expression GE_OP additive_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"relational_expression\"];"<<std::endl;   
    std::cout<<$2<<" [label=\"GE_OP\"];"<<std::endl;     
  }
	;

additive_expression
	: multiplicative_expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"additive_expression\"];"<<std::endl;   
  }
	| additive_expression '+' multiplicative_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"additive_expression\"];"<<std::endl;      
    std::cout<<$2<<" [label=\"+\"];"<<std::endl;      
  }
	| additive_expression '-' multiplicative_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"additive_expression\"];"<<std::endl;     
    std::cout<<$2<<" [label=\"-\"];"<<std::endl;   
  }
	;

multiplicative_expression
	: unary_expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"multiplicative_expression\"];"<<std::endl;    
  }
	| multiplicative_expression '*' unary_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"multiplicative_expression\"];"<<std::endl;       
    std::cout<<$2<<" [label=\"*\"];"<<std::endl;    
  }
	| multiplicative_expression '/' unary_expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"multiplicative_expression\"];"<<std::endl;        
    std::cout<<$2<<" [label=\"/\"];"<<std::endl;      
  }
	;

unary_expression
	: postfix_expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"unary_expression\"];"<<std::endl;    
  }
	| unary_operator postfix_expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<" [label=\"unary_expression\"];"<<std::endl;        
  }
	;

postfix_expression
	: primary_expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"postfix_expression\"];"<<std::endl;        
  }
	| IDENTIFIER '(' ')'
  {
    count++;
    $1 = count;
    count++;
    $2 = count;
    count++;
    $3 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"postfix_expression\"];"<<std::endl;
    std::cout<<$1<<" [label=\"IDENTIFIER\"];"<<std::endl;        
    std::cout<<$2<<" [label=\"(\"];"<<std::endl;
    std::cout<<$3<<" [label=\")\"];"<<std::endl;
  }
	| IDENTIFIER '(' expression_list ')'
  {
    count++;
    $1 = count;
    count++;
    $2 = count;
    count++;
    $4 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<"->"<<$4<<";"<<std::endl;
    std::cout<<$$<<" [label=\"postfix_expression\"];"<<std::endl;
    std::cout<<$1<<" [label=\"IDENTIFIER\"];"<<std::endl;        
    std::cout<<$2<<" [label=\"(\"];"<<std::endl;
    std::cout<<$4<<" [label=\")\"];"<<std::endl;
  }
	| l_expression INC_OP
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<" [label=\"postfix_expression\"];"<<std::endl;
    std::cout<<$2<<" [label=\"INC_OP\"];"<<std::endl;
    
  }
	;

primary_expression
	: l_expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"primary_expression\"];"<<std::endl;
  }
  | l_expression '=' expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"primary_expression\"];"<<std::endl;
    std::cout<<$2<<" [label=\"=\"];"<<std::endl;
  }
	| INT_CONSTANT
  {
    count++;
    $1 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"primary_expression\"];"<<std::endl;
    std::cout<<$1<<" [label=\"INT_CONSTANT\"];"<<std::endl;
  }
	| FLOAT_CONSTANT
  {
    count++;
    $1 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"primary_expression\"];"<<std::endl;
    std::cout<<$1<<" [label=\"FLOAT_CONSTANT\"];"<<std::endl;
  }
  | STRING_CONSTANT
  {
    count++;
    $1 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"primary_expression\"];"<<std::endl;
    std::cout<<$1<<" [label=\"STRING_CONSTANT\"];"<<std::endl;
  }
	| '(' expression ')'
  {
    count++;
    $1 = count;
    count++;
    $3 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"primary_expression\"];"<<std::endl;
    std::cout<<$1<<" [label=\"(\"];"<<std::endl;
    std::cout<<$3<<" [label=\")\"];"<<std::endl;
  }
	;

l_expression
  : IDENTIFIER
  {
    count++;
    $1 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"l_expression\"];"<<std::endl;
    std::cout<<$1<<" [label=\"IDENTIFIER\"];"<<std::endl;
  }
  | l_expression '[' expression ']'
  {
    count++;
    $2 = count;
    count++;
    $4 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<"->"<<$4<<";"<<std::endl;
    std::cout<<$$<<" [label=\"l_expression\"];"<<std::endl;
    std::cout<<$2<<" [label=\"[\"];"<<std::endl;
    std::cout<<$4<<" [label=\"]\"];"<<std::endl;
  } 
  ;

expression_list
  : expression
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"expression_list\"];"<<std::endl;
  }
  | expression_list ',' expression
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"expression_list\"];"<<std::endl;
    std::cout<<$2<<" [label=\",\"];"<<std::endl;
  }
  ;

unary_operator
	: '-'
  {
    count++;
    $1 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"unary_operator\"];"<<std::endl;
    std::cout<<$1<<" [label=\"-\"];"<<std::endl; 
  }
	| '!'
  {
    count++;
    $1 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"unary_operator\"];"<<std::endl;
    std::cout<<$1<<" [label=\"!\"];"<<std::endl;
  }
	;


selection_statement
  : IF '(' expression ')' statement ELSE statement
  {
    count++;
    $1 = count;
    count++;
    $2 = count;
    count++;
    $4 = count;
    count++;
    $6 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<"->"<<$4<<";"<<std::endl;
    std::cout<<$$<<"->"<<$5<<";"<<std::endl;
    std::cout<<$$<<"->"<<$6<<";"<<std::endl;
    std::cout<<$$<<"->"<<$7<<";"<<std::endl;
    std::cout<<$$<<" [label=\"selection_statement\"];"<<std::endl;
    std::cout<<$1<<" [label=\"IF\"];"<<std::endl;
    std::cout<<$2<<" [label=\"(\"];"<<std::endl;
    std::cout<<$4<<" [label=\")\"];"<<std::endl;
    std::cout<<$6<<" [label=\"ELSE\"];"<<std::endl; 
  }
	;

iteration_statement
	: WHILE '(' expression ')' statement
  {
    count++;
    $1 = count;
    count++;
    $2 = count;
    count++;
    $4 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<"->"<<$4<<";"<<std::endl;
    std::cout<<$$<<"->"<<$5<<";"<<std::endl;
    std::cout<<$$<<" [label=\"iteration_statement\"];"<<std::endl;
    std::cout<<$1<<" [label=\"WHILE\"];"<<std::endl;
    std::cout<<$2<<" [label=\"(\"];"<<std::endl;
    std::cout<<$4<<" [label=\")\"];"<<std::endl; 
  }
	| FOR '(' expression ';' expression ';' expression ')' statement
  {
    count++;
    $1 = count;
    count++;
    $2 = count;
    count++;
    $4 = count;
    count++;
    $6 = count;
    count++;
    $8 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<"->"<<$4<<";"<<std::endl;
    std::cout<<$$<<"->"<<$5<<";"<<std::endl;
    std::cout<<$$<<"->"<<$6<<";"<<std::endl;
    std::cout<<$$<<"->"<<$7<<";"<<std::endl;
    std::cout<<$$<<"->"<<$8<<";"<<std::endl;
    std::cout<<$$<<"->"<<$9<<";"<<std::endl;
    std::cout<<$$<<" [label=\"iteration_statement\"];"<<std::endl;
    std::cout<<$1<<" [label=\"FOR\"];"<<std::endl;
    std::cout<<$2<<" [label=\"(\"];"<<std::endl;
    std::cout<<$4<<" [label=\";\"];"<<std::endl;
    std::cout<<$6<<" [label=\";\"];"<<std::endl; 
    std::cout<<$8<<" [label=\")\"];"<<std::endl; 
  }
	;

declaration_list
	: declaration
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"declaration_list\"];"<<std::endl;
  }
	| declaration_list declaration
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<" [label=\"declaration_list\"];"<<std::endl; 
  }
	;

declaration
	: type_specifier declarator_list ';'
  {
    count++;
    $3 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"declaration\"];"<<std::endl;
    std::cout<<$3<<" [label=\";\"];"<<std::endl; 
  }
	;

declarator_list
	: declarator
  {
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<" [label=\"declarator_list\"];"<<std::endl; 
  }
	| declarator_list ',' declarator
  {
    count++;
    $2 = count;
    count++;
    $$ = count;
    std::cout<<$$<<"->"<<$1<<";"<<std::endl;
    std::cout<<$$<<"->"<<$2<<";"<<std::endl;
    std::cout<<$$<<"->"<<$3<<";"<<std::endl;
    std::cout<<$$<<" [label=\"declarator_list\"];"<<std::endl;
    std::cout<<$2<<" [label=\",\"];"<<std::endl; 
  }
	;

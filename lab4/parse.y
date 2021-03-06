/*%debug */
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
%polymorphic STMT:stmt_node*; EXP:exp_node*; ARRAY:array_ref_node*; TYPE_INT: int*; TYPE_STRING: string;TYPE_FLOAT: float*; EXP_LIST: exp_node_list*; STMT_LIST: stmt_node_list*; ABST: abstract_astnode*; DEC_STR: decl_struct *; 
%type <STMT> translation_unit function_definition compound_statement statement assignment_statement selection_statement iteration_statement
%type <EXP> expression logical_and_expression equality_expression relational_expression additive_expression multiplicative_expression unary_expression postfix_expression primary_expression l_expression
%type <EXP_LIST> expression_list
%type <STMT_LIST> statement_list
%type <TYPE_STRING> unary_operator IDENTIFIER INT_CONSTANT STRING_LITERAL FLOAT_CONSTANT type_specifier VOID INT FLOAT fun_declarator
%token AND_OP OR_OP EQ_OP NE_OP LE_OP GE_OP IF ELSE WHILE FOR RETURN INC_OP
%type <DEC_STR> declarator constant_expression
%%

// push to ast list rather than printing
translation_unit
  : function_definition
  {
    //cout<<current_func_name<<endl;
    if(printables.find(current_func_name)!=printables.end()){
      $1->print();
    }
  } 
  | translation_unit function_definition 
  {
    $$ = $1;
    //cout<<current_func_name<<endl;
    if(printables.find(current_func_name)!=printables.end()){
      $2->print();
    }
  }
  ;

// checking if function redefined with same name
function_definition
  : type_specifier {current_scope = new symbol_table;current_scope->offset = 0; does_return=false;current_func_type=$1;} fun_declarator {current_scope->offset=-4;if(check_declaration_function($3))
    {
      symbol_table_node* stn = new symbol_table_node($3, "function", current_scope);
      decl_struct *temp = new decl_struct($3);
      temp->type = $1;
      stn->decl_type = temp;
      gst->insert_entry($3, stn);
      current_func_name=$3;
  }
  } compound_statement 
  {
    if(!does_return && $1!="void"){
      add_error(Scanner::line_num, "function must return "+current_func_type);
    }
    $$ = $5;
  }
  ;

// pass types
type_specifier
  : VOID
  {
    $$=$1;
  }
  | INT
  {
    $$=$1;
  }   
  | FLOAT
  {
    $$=$1;
  }
  ;

// declaring functions
fun_declarator
  : IDENTIFIER '(' parameter_list ')'
  {
    $$ = $1;
  } 
  | IDENTIFIER '(' ')' 
  {
    $$ = $1;
  }
  ;

parameter_list
  : parameter_declaration
  | parameter_list ',' parameter_declaration 
  ;

// adds parameters to current scope and checks if parameter has been redefined or type is void
parameter_declaration
  : type_specifier declarator
  {
    //need to check for void declarations
    //cout<<Scanner::line_num<<endl;
    if(check_declaration(($2)->name,$1))
    {
      //need to check for conflicting declarations
      // what about the size, type, offset of variables 
      ($2)->type = $1;
      //cout<<($2)->name<<" "<<$1<<" "<<current_scope->offset<<endl;
      symbol_table_node* temp = new symbol_table_node(($2)->name,$1,current_scope->offset);
      temp->type = "param";
      temp->decl_type = $2;
      temp->size = ($2)->calculate_size();
      temp->offset=temp->offset+temp->size;
      current_scope->insert_entry(temp->name,temp);
      current_scope->offset = current_scope->offset + temp->size;
      //current_scope->print();
      //cout<<temp->size;
      // adding parameters declaration struction to parameters vector
      current_scope->parameters.push_back($2);
    }
  } 
  ;

// declares new declarator struct
declarator
  : IDENTIFIER
  {
    $$ = new decl_struct($1);
  } 
  | declarator '[' constant_expression ']'
  {
    // checks if constant expression is int
    if(check_int(($3)->type)){
      (($1)->indices).push_back(stoi(($3)->name));
      $$ = $1;
    }
  } 
  ;

// returns value and type of constant expression
constant_expression 
  : INT_CONSTANT
  {
    $$ = new decl_struct($1);
    ($$)->type="int";
  }
  | FLOAT_CONSTANT
  {
    $$ = new decl_struct($1);
    ($$)->type="float";
  }
  ;

// 
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
    // check return type of expression
    if(check_return_expression($2)){
      does_return = true;
      $$ = new return_node($2);
    }
  }
  | IDENTIFIER '(' ')' ';' 
  {
    // check function exists and parameters are correct
    exp_node_list* temp_list = new exp_node_list();
    if(valid_funcall($1, temp_list)){
      $$ = new funcall_stmt_node($1, temp_list);
    }
  }
  | IDENTIFIER '(' expression_list ')' ';' 
  {
    // check function exists and parameters are correct
    if(valid_funcall($1, $3)){
      $$ = new funcall_stmt_node($1, $3);
    }
  }
  ;

assignment_statement
  : ';'
  {
    $$ = new stmt_node();
  }                 
  |  l_expression '=' expression ';'  
  {
    if(check_int_float($3->type->type)&&check_type($1, $3)){
      $$ = new ass_node($1,$3);
    }
  }
  ;

expression
    : logical_and_expression 
    {
      $$ = $1;
    }
    | expression OR_OP logical_and_expression
    {
      // checks that both expressions must be either float or int
      // casts if both are not of same type
      if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
        string k;
        k = "OR";
        $$ = new op_node(k,$1,$3);
      }
    }
    ;

logical_and_expression
    : equality_expression
    {
      $$ = $1;
    }
    | logical_and_expression AND_OP equality_expression
    { 
      // checks that both expressions must be either float or int
      // casts if both are not of same type
      if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
        string k;
        k = "AND";
        $$ = new op_node(k,$1,$3); 
      }
    } 
    ;

equality_expression
  : relational_expression
  {
    $$ = $1;
  } 
  | equality_expression EQ_OP relational_expression
  { 
    // checks that both expressions must be either float or int
    // casts if both are not of same type
    if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
      string k;
      k = "EQ";
      $$ = new op_node(k,$1,$3);
    }
  }   
  | equality_expression NE_OP relational_expression
  {
    // checks that both expressions must be either float or int
    // casts if both are not of same type
    if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
      string k;
      k = "NE";
      $$ = new op_node(k,$1,$3);
    }
  }
  ;

relational_expression
  : additive_expression
  {
    $$ = $1;
  }
  | relational_expression '<' additive_expression
  {
    // checks that both expressions must be either float or int
    // casts if both are not of same type
    if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
      string k;
      k = "LT";
      $$ = new op_node(k,$1,$3);
    }
  } 
  | relational_expression '>' additive_expression
  { 
    // checks that both expressions must be either float or int
    // casts if both are not of same type
    if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
      string k;
      k = "GT";
      $$ = new op_node(k,$1,$3);
    }
  } 
  | relational_expression LE_OP additive_expression
  {
    // checks that both expressions must be either float or int
    // casts if both are not of same type
    if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
      string k;
      k = "LE";
      $$ = new op_node(k,$1,$3);  
    }
  } 
  | relational_expression GE_OP additive_expression
  { 
    // checks that both expressions must be either float or int
    // casts if both are not of same type
    if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
      string k;
      k = "GE";
      $$ = new op_node(k,$1,$3);  
    }
  } 
  ;

additive_expression 
  : multiplicative_expression
  {
    $$ = $1;  
  }
  | additive_expression '+' multiplicative_expression
  {
    // checks both expressions must be int or float
    // casts if both are not same type
    if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
      string k;
      k = "PLUS";
      $$ = new op_node(k,$1,$3);  
    }
  } 
  | additive_expression '-' multiplicative_expression
  {
    // checks both expressions must be int or float
    // casts if both are not same type
    if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
      string k;
      k = "MINUS";
      $$ = new op_node(k,$1,$3); 
    }
  } 
  ;

multiplicative_expression
  : unary_expression
  {
    $$ = $1;
  }
  | multiplicative_expression '*' unary_expression
  {
    // checks both expressions must be int or float
    // casts if both are not same type
    if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
      string k;
      k = "MULTIPLY";
      $$ = new op_node(k,$1,$3);  
    }
  } 
  | multiplicative_expression '/' unary_expression
  {
    // checks both expressions must be int or float
    // casts if both are not same type
    if(check_int_float(($1)->type->type)&&check_int_float(($3)->type->type)&&check_arith_type($1, $3)){
      string k;
      k = "DIVIDE";
      $$ = new op_node(k,$1,$3);  
    }
  } 
  ;

unary_expression
  : postfix_expression
  {
    $$ = $1;
  }         
  | unary_operator postfix_expression
  {
    if(check_int_float(($2)->type->type)){
      $$ = new unary_op_node($1 , $2);
    }
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
    if(valid_funcall($1, temp_list)){
      $$ = new funcall_node($1, temp_list);
    }
  }
  | IDENTIFIER '(' expression_list ')'
  {
    // check if funcall exists and number of parameters and type of parameters are equal else we need to type cast
    if(valid_funcall($1, $3)){
      $$ = new funcall_node($1, $3);
    }
  } 
  | l_expression INC_OP
  {
    // checks if type of l_expression is int or float and adds appropriate operator to INC_OP such as PP_FLOAT
    if(check_int_float($1->type->type)){
      string k = "PP";
      $$ = new unary_op_node(k,$1);
    }
  }
  ;

primary_expression
  : l_expression
  {
    $$ = $1;
  }
  | l_expression '=' expression // added this production
  {
    //check expression should not be void
    //cast expression to type of l_expression
    //check both indices must be equal
    if(check_int_float($3->type->type)&&check_type($1, $3))
    {
      string k ="ASSIGN";
      $$ = new op_node(k,$1,$3);
    }
  }
  | INT_CONSTANT
  {
    // creates new ast with type int and name as string value of integer
    $$ = new intconst_node($1);
  }
  | FLOAT_CONSTANT
  {
    // creates new ast with type float and name as string value of decimal
    $$ = new floatconst_node($1); 
  }
  | STRING_LITERAL
  {
    // creates new ast with type string and name as string literal
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
      // check for declaration of variable
      if(check_declared($1)){
        $$ = new identifier_array_ref_node($1);     
      }
    }
    | l_expression '[' expression ']'
    // checks if l_expression array does not exceed number of dimensions of variable defined by array
    {
      if(check_inbound($1)&&check_int(($3)->type->type)){
        $$ = new index_node($1, $3);   
      }
    }   
    ;

expression_list
        : expression
        {
          $$ = new exp_node_list();
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
      //check that expression should not be of void type
      if(check_int_float($3->type->type)){
        $$ = new if_node($3,$5,$7);
      }
    } 
  ;

iteration_statement
  : WHILE '(' expression ')' statement
  {
    //check that expression should not be of void type
    if(check_int_float($3->type->type)){
      $$ = new while_node($3,$5);
    }
  }   
  | FOR '(' expression ';' expression ';' expression ')' statement  //modified this production
  {
    //check that expression2 should not be of void type
    if(check_int_float($5->type->type)){
      $$ = new for_node($3,$5,$7,$9);
    }
  }
  ;

declaration_list
    : declaration           
    | declaration_list declaration
  ;

declaration
  : type_specifier {temp_type = $1;} declarator_list';'
  ;

declarator_list
  : declarator
  {
    ($1)->type = temp_type;
    //check if variable declared void , redeclared
    if(check_declaration(($1)->name,temp_type)){
    	symbol_table_node* temp = new symbol_table_node(($1)->name,temp_type,current_scope->offset);
    	temp->type = "local";
    	temp->decl_type = $1;
    	temp->size = ($1)->calculate_size();
    	current_scope->insert_entry(temp->name,temp);
    	current_scope->offset = current_scope->offset - temp->size;
    	//current_scope->print();
    	//cout<<temp->size;    
    }
  }
  | declarator_list ',' declarator 
  {
    ($3)->type = temp_type;
    //check if variable declared void , redeclared
    if(check_declaration(($3)->name,temp_type)){
      symbol_table_node* temp = new symbol_table_node(($3)->name,temp_type,current_scope->offset);
      temp->type = "local";
      temp->decl_type = $3;
      temp->size = ($3)->calculate_size();
      current_scope->insert_entry(temp->name,temp);
      current_scope->offset = current_scope->offset - temp->size;
      //current_scope->print();
      //cout<<temp->size;    
    }
  }
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




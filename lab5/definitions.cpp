#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <set>
#include <list>

using namespace std;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
bool does_return = false;
int tab_count = 0;
string temp_type;
symbol_table *gst = new symbol_table();
symbol_table *current_scope = gst;
string current_func_type="";
string current_func_name="";
set<string> printables;
vector<string> regs_type(4);
string code_set="";
// keeps track of labels used and gives unique labels for each time
int label_num=0;

decl_struct::decl_struct(string n)
{
  name = n;
}
decl_struct::decl_struct()
{
}

int decl_struct::calculate_size()
{
  int size=0;
  if(type=="void")
  {
    size=0;
  }
  else
  {
    size = 4;
    for(int i=0; i<indices.size();i++)
    {
      size = size * indices[i];
    }
  }
  return size;
}

void decl_struct::print()
{
  for(int i=0; i<indices.size(); i++)
  {
    cout<<"array("<<indices[i]<<",";
  }
  cout<<type;
  for(int i=0; i<indices.size(); i++)
  {
    cout<<")";
}
}

symbol_table_node::symbol_table_node(string n, string t, int o)
{
  name = n;
  offset = o;
  if(type=="int")
  {
    size=4;
  }
  else if(type=="void")
  {
    size = 0;
  }
}


int getSize(string t){
  if(t=="int"){
    return 4;
  }
  if(t=="float"){
    return 4;
  }
  if(t=="void"){
    return 0;
  }
  return 0;
}

symbol_table_node::symbol_table_node(string n, string t, symbol_table* st)
{
  name = n;
  type=t;
  offset = 0;
  local_symbol_table = st;
}

void symbol_table_node::print()
{
  cout<<name<<" "<<type <<" "<<offset<<" ";
  decl_type->print();
  if(type!="function")
  {
    cout<<" "<<size;
  }
  cout<<endl;
}

symbol_table::symbol_table()
{
  offset = 0;
}

void symbol_table::insert_entry(string s, symbol_table_node* stn){
  st.insert(make_pair(s,stn));
}

void symbol_table::print(){
  for(map<string,symbol_table_node*>::iterator it = st.begin(); it!=st.end(); it++ )
  {
    (*it).second->print();
  }
}

void print_tab(){
  for(int i=0;i<tab_count;i++){
    cout<<"\t";
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////

bool exists(string name, symbol_table* scope)
{
  return scope->st.find(name)!=scope->st.end(); 
}

// returns type of name if exists
decl_struct* get_type(string name){
  symbol_table* scope;
  if(exists(name, current_scope)){
    scope=current_scope;
  }else if(exists(name, gst)){
    scope=gst;
  }else{
    decl_struct* t= new decl_struct();
  }
  decl_struct* temp=scope->st[name]->decl_type;
  // cout<<name<<" "<<temp->indices.size()<<" "<<temp->type<<endl;
  decl_struct* n=new decl_struct(temp->name);
  n->type=temp->type;
  n->indices=*(new vector<int>(temp->indices));
  // cout<<n->indices.size()<<endl;
  return n;
}
// checks if function is not declared else returns true
bool check_declaration_function(string name)
{
  //function should not be redeclared
  string error_msg;
  if(exists(name, gst))
  {
    error_msg = "function redeclared";
    add_error(Scanner::line_num, error_msg);
    return false;
  }
  return true;
}

bool check_declaration(string name, string type)
{
  string error_msg;
  if(type == "void")
  {
    error_msg = "variable declared void";
    add_error(Scanner::line_num, error_msg);
    return false;
  }
  //variable should not be redeclared
  if(exists(name, current_scope))
  {
    error_msg = "variable redeclared";
    add_error(Scanner::line_num, error_msg);
    return false;
  }
  return true;
}

// used to check if variable used in expression is declared before using
bool check_declared(string name){
  // current_scope->print();
  if(exists(name, current_scope)){
    return true;
  }else{
    add_error(Scanner::line_num,"undeclared variable "+name);
    return false;
  }
}

// print error and exit
void add_error(int line, string s)
{
  string temp = "Line number: " + std::to_string(line) + " : Error : " + s;
  cout<<temp<<endl;
  exit(0);
}

// checks if array does not go out of bounds
bool check_inbound(exp_node* &l){
  // cout<<l->type->indices.size()<<endl;
  if(l->type->indices.size()>0){
    return true;
  }
  add_error(Scanner::line_num,"array out of bounds");
  return false;
}

// checks if type of two expressions i.e same indices
// also has side effect of casting expression according to left expression
bool check_type(exp_node*& l, exp_node*& r){
  // cout<<l->type->type<<" "<<r->type->type<<" "<<l->type->indices.size()<<" "<<r->type->indices.size()<<endl;
  if(l->type->indices.size()==r->type->indices.size()){
    if(l->type->type!=r->type->type){
      r->isCast=true;
      r->castTo=l->type->type;
    }
    return true;
  }
  add_error(Scanner::line_num, "incompatible types");
  return false;
}
// checks if type of two expressions is same
// also has side effect of casting expression according to expression which has float
bool check_arith_type(exp_node*& l, exp_node*& r){
  // cout<<l->type->type<<" "<<r->type->type<<" "<<l->type->indices.size()<<" "<<r->type->indices.size()<<endl;
  if(l->type->indices.size()==r->type->indices.size()){
    if(l->type->type!=r->type->type){
      if(l->type->type=="float"){
        r->isCast=true;
        r->castTo="float";
      }else{
        l->isCast=true;
        l->castTo="float";
      }
    }
    return true;
  }
  add_error(Scanner::line_num, "incompatible types");
  return false;
}
// checks if type is int
bool check_int(string s){
  if(s=="int"){
    return true;
  }
  add_error(Scanner::line_num, s+" used in array index");
  return false;
}

// checks if type is float
bool check_int_float(string s){
  if(s=="int"||s=="float"){
    return true;
  }
  add_error(Scanner::line_num, "float or int is required");
  return false;
}
// checks if type of expression is int or float
// also has side effect of casting expression to int if has float
bool check_logical_type(exp_node*& e){
  // cout<<l->type->type<<" "<<r->type->type<<" "<<l->type->indices.size()<<" "<<r->type->indices.size()<<endl;
  if(check_int_float(e->type->type)){
    if(e->type->type=="float"){
      e->isCast=true;
      e->castTo="int";
    }
    return true;
  }
  return false;
}
// checks if type of expression is int or float
// also has side effect of casting expression to int if has float
bool check_logical_type(exp_node*& l, exp_node*& r){
  // cout<<l->type->type<<" "<<r->type->type<<" "<<l->type->indices.size()<<" "<<r->type->indices.size()<<endl;
  if(check_int_float(l->type->type)&&check_int_float(r->type->type)){
    if(l->type->type=="float"){
      l->isCast=true;
      l->castTo="int";
    }
    if(r->type->type=="float"){
      r->isCast=true;
      r->castTo="int";
    }
    return true;
  }
  return false;
}
// puts uppercase string in str
string getUppercase(string str){
  string s=str;
  for(int i=0;i<str.size();i++){
    s[i]=toupper(str[i]);
  }
  // cout<<str<<endl;
  return s;
}
// checks if function call is valid by checking parameters and existence of function
bool valid_funcall(string& s, exp_node_list*& e){
  if(s=="printf"&&e->exp_list->size()>0){
    return true;
  }else if(s=="printf"&&e->exp_list->size()==0){
    add_error(Scanner::line_num,"requires at least one argument");
    return false;
  }
  if(exists(s, current_scope)){
    add_error(Scanner::line_num,"invalid call to variable "+s);
    return false;
  }
  if(!exists(s, gst)){
    add_error(Scanner::line_num,"undefined function "+s);
    return false;
  }
  symbol_table_node* func_st=gst->st[s];
  vector<decl_struct*> params=func_st->local_symbol_table->parameters;
  if(params.size()!=e->exp_list->size()){
    add_error(Scanner::line_num,"invalid function call to "+s);
    return false; 
  }
  for(int i=0;i<params.size();i++){
    if((*(e->exp_list))[i]->type->type=="void"){
      add_error(Scanner::line_num,"void parameter given to function call "+s);
      return false;   
    }
    if(params[i]->type!=(*(e->exp_list))[i]->type->type){
      (*(e->exp_list))[i]->isCast=true;
      (*(e->exp_list))[i]->castTo=params[i]->type;
    }
  }
  return true;
}

// checks if return type is valid
// type cast is side effect
bool check_return_expression(exp_node*& r){
  if(current_func_type!="void"){
    if(r->type->indices.size()==0){
      if(r->type->type!=current_func_type){
        r->isCast=true;
        r->castTo=current_func_type;
      }
    }else{
      add_error(Scanner::line_num,"invalid return expression");
      return false;
    }
  }
  return true;
}
// checks if identifier is printf, it can be used in funcall node
bool check_printf(string& s){
  if(s=="printf"){
    add_error(Scanner::line_num,"invalid function call to "+s);
    return false;
  }
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////
stmt_node::stmt_node()
{

}
void stmt_node::print(){
  cout<<"(Empty)"<<endl;
}
block_node::block_node(stmt_node_list*& sln_arg)
{
  sln = sln_arg;
}
// done
void block_node::print()
{
  cout<<"(Block ";
  sln->print();
  cout<<")"<<endl;
}
stmt_node_list::stmt_node_list()
{
  stmt_list = new vector<stmt_node*>;
}
void stmt_node_list::add_stmt(stmt_node*& stmt)
{
  stmt_list->push_back(stmt);
}
// done
void stmt_node_list::print(){
  cout<<"["<<endl;
  tab_count++;
  for(int i=0;i<stmt_list->size();i++){
    print_tab();
    (*stmt_list)[i]->print();
  }
  tab_count--;
  print_tab();
  cout<<"]";
}

ass_node::ass_node(exp_node*& l, exp_node*& r )
{
  left = l;
  right = r;
}
// done
void ass_node::print()
{ 
  cout<<"(Ass ";
  left->print();
  right->print();
  cout<<")"<<endl;
}
return_node::return_node(exp_node*& c)
{
  child = c;
}
// done
void return_node::print(){
  cout<<"(Return ";
  child->print();
  cout<<")"<<endl;
}
funcall_stmt_node::funcall_stmt_node(string& i, exp_node_list*& e)
{
  id = i;
  enl = e;
}
void funcall_stmt_node::print(){
  cout<<"(FuncallStmt";
  cout<<"( Id \" "<<id<<" \" )";
  enl->print();
  cout<<")"<<endl;
}
if_node::if_node(exp_node*& l, stmt_node*& m, stmt_node*& r)
{
  left = l;
  middle = m;
  right = r;
}
// done
void if_node::print(){
  cout<<"(If "<<endl;
  tab_count++;
  print_tab();
  left->print();
  cout<<endl;
  print_tab();
  middle->print();
  print_tab();
  right->print();
  tab_count--;
  print_tab();
  cout<<")"<<endl; 
}
while_node::while_node(exp_node*& l, stmt_node*& r)
{
  left = l;
  right = r;
}
// done
void while_node::print(){
  cout<<"(While "<<endl;
  tab_count++;
  print_tab();
  left->print();
  cout<<endl;
  print_tab();
  right->print();
  tab_count--;
  print_tab();
  cout<<")"<<endl;   
}

for_node::for_node(exp_node*& l, exp_node*& m, exp_node*& r, stmt_node*& b)
{
  left = l;
  middle = m;
  right = r;
  body = b;
}
// done
void for_node::print(){
  cout<<"(For "<<endl;
  tab_count++;
  print_tab();
  left->print();
  cout<<endl;
  print_tab();
  middle->print();
  cout<<endl;
  print_tab();
  right->print();
  cout<<endl;
  print_tab();
  body->print();
  tab_count--;
  print_tab();
  cout<<")"<<endl;    
}
op_node::op_node(string& o, exp_node*& l, exp_node*& r)
{
  if(o=="ASSIGN")
  {
    type = l->type;
  }else{
    if(l->isCast){
      type=r->type;
    }else{
      type=l->type;
    }
  }
  op = o;
  left = l;
  right = r;
  if(o=="GE"||o=="LE"||o=="LT"||o=="GT"||o=="NE"||o=="EQ"||o=="AND"||o=="OR"){
    type = new decl_struct(o);
    type->type="int";
  }
}
// done
void op_node::print(){
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"("<<op<<"_"<<getUppercase(type->type);
  left->print();
  right->print();
  cout<<")";
  if(isCast){
    cout<<" )";
  }
}

unary_op_node::unary_op_node(string& o, exp_node*& c)
{
  // cout<<"Here"<<endl;
  op = o;
  child = c;
  // nam->name;
  type=c->type;
}
void unary_op_node::print(){
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"("<<op<<"_"<<getUppercase(type->type);
  child->print();
  cout<<")";
  if(isCast){
    cout<<" )";
  }
}

funcall_node::funcall_node(string& i, exp_node_list*& e)
{
  id = i;
  enl = e;
  type = gst->st[i]->decl_type;
}
void funcall_node::print(){
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"(Funcall";
  cout<<"( Id \" "<<id<<" \" )";
  enl->print();
  cout<<")";
  if(isCast){
    cout<<" )";
  } 
}

exp_node_list::exp_node_list(){ 
  exp_list = new vector<exp_node*>;
}
void exp_node_list::add_exp(exp_node*& exp)
{
  exp_list->push_back(exp);
}

void exp_node_list::print(){
  for(int i=0;i<exp_list->size();i++){
    (*exp_list)[i]->print();
    cout<<" ";
  }
}

floatconst_node::floatconst_node(string& n)
{
  isIndex = 1;
  num = atof(n.c_str());
  type = new decl_struct(n);
  type->type = "float";
}

void floatconst_node::print()
{
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"( FloatConst "<<num<<" )"; 
  if(isCast){
    cout<<" )";
  } 
}
intconst_node::intconst_node(string& n)
{
  isIndex = 1;
  num = atoi(n.c_str());
  type = new decl_struct(n);
  type->type = "int";
}
void intconst_node::print()
{
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"( IntConst "<<num<<" )";
  if(isCast){
    cout<<" )";
  }
}
stringconst_node::stringconst_node(string& s)
{
  str = s;
  type = new decl_struct(s);
  type->type = "string";
}

void stringconst_node::print()
{
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"( StringConst "<<str<<" )"; 
  if(isCast){
    cout<<" )";
  }
}
identifier_node::identifier_node(string& i)
{
  id = i;
}
void identifier_node::print()
{
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"( Id \" "<<id<<" \" )";
  if(isCast){
    cout<<" )";
  }
}
array_ref_node::array_ref_node(string& i){
  id = i;
  exp = new vector<exp_node*>();
  type = get_type(i); 
  isIndex = 1;
  // cout<<"Here"<<endl;
}
void array_ref_node::print()
{
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"( Id \" "<<id; 
  for(int i=0;i<exp->size();i++){
    cout<< " [ ";
    (*exp)[i]->print(); 
    cout<< " ] ";   
  }
  cout<<" \" )";
  if(isCast){
    cout<<" )";
  }
}

////////////////////////////////////////////////////////////////////////////

// returns offset of id as in symbol table
string getOffset(string id, symbol_table* stble){
  return std::to_string(stble->st[id]->offset);
}
// returns type of an expression taking into account the cast
string getType(exp_node*& e){
  if(!e->isCast){
    return e->type->type;
  }
  return e->castTo;
}
// returns size of index at i for variable id
int getIndexSize(string id, int i, symbol_table* stble){
  return (((stble->st)[id])->decl_type->indices)[i];
}

string getReg(int i)
{

  switch (i) {
    case 1:
    return "eax";
    case 2:
    return "ebx";
    case 3:
    return "ecx";
    case 4:
    return "edx";
    default:
    return "none";
  }
}

void add_code(string& code, string to_add)
{
  if(to_add!="")
    code = code +"\t"+to_add + ";\n";
}
// returns the offset of local variable at top point in stack so that it can be used for pointing stack pointer to correct position
int getmin_offset(symbol_table* current_sym_tab)
{
  int min=0;
  typedef map<string, symbol_table_node*>::iterator it_type;
  for(it_type iterator = current_sym_tab->st.begin(); iterator != current_sym_tab->st.end(); iterator++) {
    // iterator->first = key
    if(iterator->second->offset<min){
      min=iterator->second->offset;
    }
    // Repeat if you also want to iterate through the second map.
  }
  return min;
}
// adds the code to final code set, called from parser
void gencode(stmt_node*& st, string func_name){
  code_set = code_set+"void "+current_func_name+"(){\n";
  if(current_func_name=="main"){
    if(current_func_type=="int"){
      add_code(code_set,"pushi(0)");    
    }else if(current_func_type=="float"){
      add_code(code_set,"pushf(0)");    
    }
  }
  add_code(code_set,"pushi(ebp)");
  add_code(code_set,"move(esp, ebp)");
  add_code(code_set,"addi("+std::to_string(getmin_offset(current_scope))+", esp)");
  code_set=code_set+st->generate_code(current_scope);
  add_code(code_set,"e: ");
  add_code(code_set,"move(ebp, esp)");
  add_code(code_set,"loadi(ind(ebp), ebp)");
  add_code(code_set,"popi(1)");
  add_code(code_set,"return");
  if(current_func_name=="main"){
    if(current_func_type=="int"){
      add_code(code_set,"popi(0)");    
    }else if(current_func_type=="float"){
      add_code(code_set,"popf(0)");    
    }
  }
  code_set = code_set+"}\n";
}

void add_label(string& code){
  add_code(code, "l"+std::to_string(label_num)+": ");
  label_num++;
}

string intconst_node::generate_code(symbol_table* current_sym_tab)
{
  string code="";
  string temp_type="int";
  //get the free register
  string temp_reg = getReg(freeReg);
  //get the value in temp_reg
  add_code(code, "move("+std::to_string(num)+", "+temp_reg+")");
  //type cast if required
  if(isCast)
  { 
    temp_type = castTo;
    if(castTo=="float"){
      add_code(code, "intTofloat("+temp_reg+")");
    }
  }
  //push it in stack if required
  if(onStack)
  {
    if(temp_type=="int")
      add_code(code, "pushi("+temp_reg+")");
    else if(temp_type=="float")
      add_code(code, "pushf("+temp_reg+")");
  }
  regs_type[freeReg-1]=temp_type;
  return code;
}

string floatconst_node::generate_code(symbol_table* current_sym_tab)
{
  string code="";
  string temp_type="float";
  //get the free register
  string temp_reg = getReg(freeReg);
  //get the value in ebx
  add_code(code, "move("+std::to_string(num)+", "+temp_reg+")");
  //type cast if required
  if(isCast)
  { 
    temp_type = castTo;
    if(castTo=="int"){
      add_code(code, "floatToint("+temp_reg+")");
    }
  }
  //push it in stack if required
  if(onStack)
  {
    if(temp_type=="int")
      add_code(code, "pushi("+temp_reg+")");
    else if(temp_type=="float")
      add_code(code, "pushf("+temp_reg+")");
  }
  regs_type[freeReg-1]=temp_type;
  return code;
}

// code to handle array ref nodes
string array_ref_node::generate_code(symbol_table* current_sym_tab)
{
  string code="";
  string temp_type = type->type;
  //get the free register
  string temp_reg = getReg(freeReg);
  //get offset somehow;
  //int offset = get_offset();
  string offset = getOffset(id, current_sym_tab);
  // case when value is a variable not an array
  if(exp->size()==0){
    // if return offset is set then return only offset
    if(retOff){
      add_code(code, "move("+offset+", "+temp_reg+")");
      regs_type[freeReg-1] = "int";
    }
    else{
      //load the value in ebx
      if(temp_type=="int")
        add_code(code, "loadi(ind(ebp, "+offset+"),  "+temp_reg+")");
      else if(temp_type=="float")
        add_code(code, "loadf(ind(ebp, "+offset+"),  "+temp_reg+")");
    //type cast as required
      if(isCast){ 
        temp_type = castTo;
        if(castTo=="float"){
          add_code(code, "intTofloat( "+temp_reg+")");
        }
        else if(castTo=="int"){
          add_code(code, "floatToint( "+temp_reg+")");
        }
      }
      regs_type[freeReg-1] = temp_type;
    }
    //store it on stack if required otherwise let it remain on ebx
    if(onStack)
    {
      if(temp_type=="int")
        add_code(code, "pushi( "+temp_reg+")");
      else if(temp_type=="float")
        add_code(code, "pushf( "+temp_reg+")");
    }
    return code; 
  }else{
    // this variable maintains free register for each expression in indices
    int tempFreeReg=freeReg;
    for(int i=0;i<exp->size();i++){
      (*exp)[i]->freeReg = tempFreeReg;
      (*exp)[i]->onStack = 0;

      if(i==0&&freeReg>2){
        // for first expression if free registers are 2 then store on stack else store in register itself and after every iteration we will add offset in the register itself else on stack
        tempFreeReg--;
      }
      code = code+(*exp)[i]->generate_code(current_sym_tab);
      // adding offset to already found offset
      string indexSize = std::to_string(getIndexSize(id, i, current_sym_tab));
      // we multiply by size of index only in case when index is not the last in index list i.e a[2][3] of a[5][5] must give 2*5+3, we see 3 is not multiplied by 5
      if(freeReg>2){
        if(i==0&&i<exp->size()-1){
          add_code(code, "muli("+indexSize+", "+temp_reg+")");
        }else{
          if(i<exp->size()-1){
            add_code(code, "muli("+indexSize+", "+getReg(tempFreeReg)+")");
          }
          if(i!=0){
            add_code(code, "addi("+getReg(tempFreeReg)+", "+temp_reg+")");
          }
        }
      }else{
        if(i<exp->size()-1){
          add_code(code, "muli("+indexSize+", "+temp_reg+")");
        }
        if(i>0){
          // case when we have to add up indices so we load from stack and add
          add_code(code, "loadi(ind(esp), "+getReg(freeReg-1)+")");
          add_code(code, "addi("+getReg(freeReg-1)+", "+temp_reg+")"); 
        }
        if(i<exp->size()-1&&i!=0){
          // case when we have to store changed offset to top stack and replace old value
          add_code(code, "storei("+temp_reg+", ind(esp))");
        }else if(i==0&&i!=exp->size()-1){
          // case when we have to push offset onto stack for first time and it must not be last index
          add_code(code, "pushi("+temp_reg+")");
        }else if(i==exp->size()-1&&i!=0){
          // pop the stack thus restoring stack pointer to where it was before
          add_code(code, "popi(1)");
        }
      }
    }
    // multiply offset by size of I or F
    add_code(code, "muli(4, "+temp_reg+")");
    // get offset of identifier from symbol table and put in freeReg-1
    add_code(code, "move("+offset+", "+getReg(freeReg-1)+")");
    // add the offset of id and array offset
    add_code(code, "addi("+getReg(freeReg-1)+", "+temp_reg+")");
    regs_type[freeReg-1] = "int";
    // if return offset is set then return only offset
    if(!retOff){
      // calculate actual address in stack and store in temp_reg
      add_code(code, "addi(ebp, "+temp_reg+")");
      // address is stored in temp_reg
      if(temp_type=="int")
        add_code(code, "loadi(ind("+temp_reg+"),  "+temp_reg+")");
      else if(temp_type=="float")
        add_code(code, "loadf(ind("+temp_reg+"),  "+temp_reg+")");
    //type cast as required
      if(isCast){ 
        temp_type = castTo;
        if(castTo=="float")
          add_code(code, "intTofloat( "+temp_reg+")");
        else if(castTo=="int")
          add_code(code, "floatToint( "+temp_reg+")");
      }
      regs_type[freeReg-1] = temp_type;
    }
    if(onStack)
    {
      if(temp_type=="int")
        add_code(code, "pushi( "+temp_reg+")");
      else if(temp_type=="float")
        add_code(code, "pushf( "+temp_reg+")");
    }
  }
  return code;
}

string unary_op_node::generate_code(symbol_table* current_sym_tab)
{
  string code = "";
  string temp_type = type->type;
  //get the free register
  string temp_reg = getReg(freeReg);
  child->freeReg = freeReg;
  child->onStack = 0;
  code = code+child->generate_code(current_sym_tab);
  if(op=="-"){
    if(temp_type=="int"){
      add_code(code,"muli(-1, "+temp_reg+")");
    }else{
      add_code(code,"mulf(-1, "+temp_reg+")");
    }
  }else if(op=="!"){
    if(temp_type=="int"){
      add_code(code,"cmpi(0, "+temp_reg+")");
      add_code(code, "jne(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);
    }else if(temp_type=="float"){
      add_code(code,"cmpf(0, "+temp_reg+")");
      add_code(code, "jne(l"+std::to_string(label_num)+")");
      add_code(code, "move(0.0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1.0, "+temp_reg+")");
      add_label(code);
    }
  }else if(op=="PP"){
    // code for assignment
    // calculates actual address
    add_code(code, "addi(ebp, "+temp_reg+")");
    if(temp_type=="float"){
      add_code(code, "loadf(ind("+temp_reg+"), "+getReg(freeReg-1)+")");
      add_code(code, "addf(1, "+getReg(freeReg-1)+")");
      add_code(code, "storef("+getReg(freeReg-1)+", ind("+temp_reg+"))");
      add_code(code, "move("+getReg(freeReg-1)+", "+temp_reg+")");
      add_code(code, "addf(-1, "+temp_reg+")");
    }
    else if(temp_type=="int"){
      add_code(code, "loadi(ind("+temp_reg+"), "+getReg(freeReg-1)+")");
      add_code(code, "addi(1, "+getReg(freeReg-1)+")");
      add_code(code, "storei("+getReg(freeReg-1)+", ind("+temp_reg+"))");
      add_code(code, "move("+getReg(freeReg-1)+", "+temp_reg+")");
      add_code(code, "addi(-1, "+temp_reg+")");
    }
  }
  if(isCast){ 
    temp_type = castTo;
    if(castTo=="float")
      add_code(code, "intTofloat( "+temp_reg+")");
    else if(castTo=="int")
      add_code(code, "floatToint( "+temp_reg+")");
  }
  if(onStack)
  {
    if(temp_type=="int")
      add_code(code, "pushi( "+temp_reg+")");
    else if(temp_type=="float")
      add_code(code, "pushf( "+temp_reg+")");
  }
  regs_type[freeReg-1] = temp_type;
  return code;
}

string op_node::generate_code(symbol_table* current_sym_tab)
{
  string code="";
  string temp_type=type->type;
  //get the free register
  string temp_reg = getReg(freeReg);
  // first evaluate the right expression and if free registers are equal to or less than 2 then store the value in stack and later pop it
  right->freeReg = freeReg;
  right->onStack = 0;
  left->onStack = 0;
  // we ensure here that ouput of right code is in top of rstack and output of left code is on the next regsiter on rstack
  code = code + right->generate_code(current_sym_tab);
  if(freeReg>2){
    left->freeReg = freeReg-1;
  }else{
    left->freeReg = freeReg;
    if(temp_type=="int")
      add_code(code, "pushi( "+temp_reg+")");
    else if(temp_type=="float")
      add_code(code, "pushf( "+temp_reg+")");
  }
  code = code + left->generate_code(current_sym_tab);
  if(!(freeReg>2)){
    add_code(code, "move("+temp_reg+", "+getReg(freeReg-1)+")");
    // restoring back stack pointer to initial state
    if(temp_type=="int"){
      add_code(code, "loadi(ind(esp), "+temp_reg+")");
      add_code(code, "popi(1)");
    }
    else if(temp_type=="float"){
      add_code(code, "loadf(ind(esp), "+temp_reg+")");
      add_code(code, "popf(1)");
    }
  }
  string leftReg = getReg(freeReg-1);
  string rightReg = temp_reg;
  if(op=="PLUS"){
    // code for addition
    if(temp_type=="float")
      add_code(code, "addf("+leftReg+", "+rightReg+")");
    else if(temp_type=="int")
      add_code(code, "addi("+leftReg+", "+rightReg+")");
  }else if (op=="MINUS"){
    // code for subtraction
    //multiply value in ebp by -1 and store in rightReg itself and then perform usual addition
    if(temp_type=="float"){
      add_code(code, "mulf(-1, "+rightReg+")");
      add_code(code, "addf("+leftReg+", "+rightReg+")");
    }
    else if(temp_type=="int"){
      add_code(code, "muli(-1, "+rightReg+")");
      add_code(code, "addi("+leftReg+", "+rightReg+")");
    }
  }else if(op=="MULTIPLY"){
    // code for multiplication
    if(temp_type=="float"){
      add_code(code, "mulf("+leftReg+", "+rightReg+")");
    }
    else if(temp_type=="int"){
      add_code(code, "muli("+leftReg+", "+rightReg+")");
    }
  }else if(op=="DIVIDE"){
    // code for division
    if(temp_type=="float"){
      add_code(code, "divf("+leftReg+", "+rightReg+")");
    }
    else if(temp_type=="int"){
      add_code(code, "divi("+leftReg+", "+rightReg+")");
    }
  }else if(op=="ASSIGN"){
    // code for assignment
    // calculates actual address
    add_code(code, "addi(ebp, "+leftReg+")");
    if(temp_type=="float"){
      add_code(code, "storef("+rightReg+", ind("+leftReg+"))");
    }
    else if(temp_type=="int"){
      add_code(code, "storei("+rightReg+", ind("+leftReg+"))");
    }
  }
  //in case of OR AND EQ NE LT LE GT GE the type of op_node is changed to int, but in that case we dont know the actual type of left or right operand which can be found using their type values. 
  else if(op=="OR"){
    // code for OR operation
    string child_type = getType(left);
    if(child_type=="int"){
      add_code(code,"cmpi(0, "+leftReg+")");
      add_code(code, "jne(l"+std::to_string(label_num)+")");
      add_code(code,"cmpi(0, "+rightReg+")");
      add_code(code, "jne(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code); 
    }else if(child_type=="float"){
      add_code(code,"cmpf(0, "+leftReg+")");
      add_code(code, "jne(l"+std::to_string(label_num)+")");
      add_code(code,"cmpf(0, "+rightReg+")");
      add_code(code, "jne(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
      
    }
  }else if(op=="AND"){
    // code for OR operation
    string child_type = getType(left);
    if(child_type=="int"){
      add_code(code,"cmpi(0, "+leftReg+")");
      add_code(code, "je(l"+std::to_string(label_num)+")");
      add_code(code,"cmpi(0, "+rightReg+")");
      add_code(code, "je(l"+std::to_string(label_num)+")");
      add_code(code, "move(1, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(0, "+temp_reg+")");
      add_label(code);    
    }else if(child_type=="float"){
      add_code(code,"cmpf(0, "+leftReg+")");
      add_code(code, "je(l"+std::to_string(label_num)+")");
      add_code(code,"cmpf(0, "+rightReg+")");
      add_code(code, "je(l"+std::to_string(label_num)+")");
      add_code(code, "move(1, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(0, "+temp_reg+")");
      add_label(code);    
      
    }
  }else if(op=="EQ"){
    // code for OR operation
    string child_type = getType(left);
    if(child_type=="int"){
      add_code(code,"cmpi("+rightReg+", "+leftReg+")");
      add_code(code, "je(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
      
    }else if(child_type=="float"){
      add_code(code,"cmpf("+rightReg+", "+leftReg+")");
      add_code(code, "je(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
      
    }
  }else if(op=="NE"){
    // code for OR operation
    string child_type = getType(left);
    if(child_type=="int"){
      add_code(code,"cmpi("+rightReg+", "+leftReg+")");
      add_code(code, "jne(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
      
    }else if(child_type=="float"){
      add_code(code,"cmpf("+rightReg+", "+leftReg+")");
      add_code(code, "jne(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
      
    }
  }else if(op=="LT"){
    // code for OR operation
    string child_type = getType(left);
    if(child_type=="int"){
      add_code(code,"cmpi("+leftReg+", "+rightReg+")");
      add_code(code, "jl(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
    }else if(child_type=="float"){
      add_code(code,"cmpf("+leftReg+", "+rightReg+")");
      add_code(code, "jl(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
    }
  }else if(op=="GT"){
    // code for OR operation
    string child_type = getType(left);
    if(child_type=="int"){
      add_code(code,"cmpi("+leftReg+", "+rightReg+")");
      add_code(code, "jg(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
    }else if(child_type=="float"){
      add_code(code,"cmpf("+leftReg+", "+rightReg+")");
      add_code(code, "jg(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
    }
  }else if(op=="GE"){
    // code for OR operation
    string child_type = getType(left);
    if(child_type=="int"){
      add_code(code,"cmpi("+leftReg+", "+rightReg+")");
      add_code(code, "jge(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
    }else if(child_type=="float"){
      add_code(code,"cmpf("+leftReg+", "+rightReg+")");
      add_code(code, "jge(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
    }
  }else if(op=="LE"){
    // code for OR operation
    string child_type = getType(left);
    if(child_type=="int"){
      add_code(code,"cmpi("+leftReg+", "+rightReg+")");
      add_code(code, "jle(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
    }else if(child_type=="float"){
      add_code(code,"cmpf("+leftReg+", "+rightReg+")");
      add_code(code, "jle(l"+std::to_string(label_num)+")");
      add_code(code, "move(0, "+temp_reg+")");
      add_code(code, "j(l"+std::to_string(label_num+1)+")");
      add_label(code);
      add_code(code, "move(1, "+temp_reg+")");
      add_label(code);    
    }
  }
  // cast if required
  if(isCast){ 
    temp_type = castTo;
    if(castTo=="float")
      add_code(code, "intTofloat( "+temp_reg+")");
    else if(castTo=="int")
      add_code(code, "floatToint( "+temp_reg+")");
  }
  //push it on stack if required otherwise let it remain in ebx(do nothing)
  if(onStack)
  {
    if(temp_type=="float")
      add_code(code, "pushf(ebx)");
    else if(temp_type=="int")
      add_code(code, "pushi(ebx)");
  }
  regs_type[freeReg-1] = temp_type;
  return code;
}

// code to handle expression node list
string exp_node_list::generate_code(symbol_table* current_sym_tab)
{
  string code = "";
  //get the free register
  string temp_reg = getReg(freeReg);
  //we have to travel the list in reverse as the first parameter should be pushed most recently
  for(int i=exp_list->size()-1; i>=0; i--)
  {
    exp_node* temp_exp = (*exp_list)[i];
    temp_exp->onStack = false;
    temp_exp->freeReg=freeReg;
    code=code+temp_exp->generate_code(current_sym_tab);
    //assume that exp node stores the value in ebx after evaluation
    if(!temp_exp->isCast){
      if(temp_exp->type->type == "float")
      {
        add_code(code,"pushf("+temp_reg+")");
      }
      else if(temp_exp->type->type == "int")
      {
        add_code(code,"pushi("+temp_reg+")");
      }
    }else{
      if(temp_exp->castTo == "float")
      {
        add_code(code,"pushf("+temp_reg+")");
      }
      else if(temp_exp->castTo == "int")
      {
        add_code(code,"pushi("+temp_reg+")");
      }
    }
  }
  return code;
}

string if_node::generate_code(symbol_table* current_sym_tab)
{
  string code="";
  string temp_type;
  //get the free register
  left->freeReg = 4;
  left->onStack = false;
  string left_code = left->generate_code(current_sym_tab);
  string middle_code = middle->generate_code(current_sym_tab);
  string right_code = right->generate_code(current_sym_tab);
  code =  code + left_code;
  add_code(code, "cmpi(0, "+getReg(4)+")");
  add_code(code, "je(l"+std::to_string(label_num)+")");
  code = code + middle_code;
  add_code(code, "j(l"+std::to_string(label_num+1)+")");
  add_label(code); 
  code = code + right_code;
  add_label(code);
  return code;    
}

string while_node::generate_code(symbol_table* current_sym_tab)
{
  string code="";
  string temp_type;
  //get the free register
  left->freeReg = 4;
  string left_code = left->generate_code(current_sym_tab);
  string right_code = right->generate_code(current_sym_tab);
  add_label(code);
  code = code+left_code;
  add_code(code, "cmpi(0, "+getReg(4)+")");
  add_code(code, "je(l"+std::to_string(label_num)+")");
  code = code+right_code;
  add_code(code, "j(l"+std::to_string(label_num-1)+")");
  add_label(code);
  return code;
}

string for_node::generate_code(symbol_table* current_sym_tab)
{
  string code="";
  string temp_type;
  //get the free register
  left->freeReg = 4;
  middle->freeReg = 4;
  right->freeReg = 4;
  string left_code = left->generate_code(current_sym_tab);
  string middle_code = middle->generate_code(current_sym_tab);
  string right_code = right->generate_code(current_sym_tab);
  string body_code = body->generate_code(current_sym_tab);
  code = code+left_code;
  add_label(code);
  code = code+middle_code;
  add_code(code, "cmpi(0, "+getReg(4)+")");
  add_code(code, "je(l"+std::to_string(label_num)+")");
  code = code+body_code;
  code = code+right_code;
  add_code(code, "j(l"+std::to_string(label_num-1)+")");
  add_label(code);
  return code;
}

string ass_node::generate_code(symbol_table* current_sym_tab)
{
  // cout<<"Here"<<endl;
  string code="";
  string temp_type=left->type->type;
  // first evaluate the right expression and if free registers are equal to or less than 2 then store the value in stack and later pop it
  right->freeReg = 4;
  right->onStack = 0;
  left->onStack = 0;
  // we ensure here that ouput of right code is in top of rstack and output of left code is on the next regsiter on rstack
  code = code + right->generate_code(current_sym_tab);
  left->freeReg = 3;
  code = code + left->generate_code(current_sym_tab);
  // contains left expression return value
  // cout<<"Here"<<endl;
  string leftReg = getReg(3);
  // contains right expression return value
  string rightReg = getReg(4);
  // code for assignment
  // calculates actual address
  add_code(code, "addi(ebp, "+leftReg+")");
  if(temp_type=="float"){
    add_code(code, "storef("+rightReg+", ind("+leftReg+"))");
  }
  else if(temp_type=="int"){
    add_code(code, "storei("+rightReg+", ind("+leftReg+"))");
  }
  return code;
}

// stores return value in return position
string return_node::generate_code(symbol_table* current_sym_tab)
{
  string code = "";
  string temp_type = child->type->type;
  //get the free register
  string temp_reg = getReg(4);
  int offs=4;
  if((current_sym_tab->parameters).size()!=0){
    string last_param=(current_sym_tab->parameters)[(current_sym_tab->parameters).size()-1]->name; 
    symbol_table_node* last_stn=(current_sym_tab->st)[last_param];
    offs=last_stn->offset+last_stn->decl_type->calculate_size();
  }
  child->freeReg=4;
  code=code+child->generate_code(current_sym_tab);
  if(temp_type=="int"){
    add_code(code,"storei("+temp_reg+", ind(ebp, "+std::to_string(offs)+"))");
  }else if(temp_type=="float"){
    add_code(code,"storef("+temp_reg+", ind(ebp, "+std::to_string(offs)+"))");
  }
  add_code(code,"j(e)");
  return code;
}

string funcall_node::generate_code(symbol_table* current_sym_tab)
{
  string code = "";
  string temp_type = type->type;
   //get the free register
  string temp_reg = getReg(freeReg);
  vector<string> temp_regs_type=regs_type;
  for(int i=4;i>freeReg;i--){
    if(temp_regs_type[i-1]=="int"){
      add_code(code, "pushi("+getReg(i)+")");
    }else if(temp_regs_type[i-1]=="float"){
      add_code(code, "pushf("+getReg(i)+")");
    }
  }
  // make space for return value if not void
  if(temp_type == "int")
  {
    add_code(code,"pushi(0)");
  }
  else if(temp_type == "float")
  {
    add_code(code,"pushf(0.0)");
  }
  //push the parameters
  enl->freeReg=4;
  code=code+enl->generate_code(current_sym_tab);
  //call the function;
  add_code(code,id+"()");
  //cleanup code
  //popping the params in reverse order of pushing
  vector<exp_node*>* temp_vec = (enl->exp_list);
  for(int i=0; i<temp_vec->size(); i++)
  {
    exp_node* temp_exp = (*temp_vec)[i];
    //determine the type of value generated by expression?
    if(!temp_exp->isCast){
      if(temp_exp->type->type == "float")
      {
        add_code(code,"popf(1)");
      }
      else if(temp_exp->type->type == "int")
      {
        add_code(code,"popi(1)");
      }
    }else{
      if(temp_exp->castTo == "float")
      {
        add_code(code,"popf(1)");
      }
      else if(temp_exp->castTo == "int")
      {
        add_code(code,"popi(1)");
      }
    }
  }
  // take the return value from stack to temp_reg
  if(temp_type == "int")
  {
    add_code(code, "loadi(ind(esp), "+temp_reg+")");
    add_code(code,"popi(1)");
  }else if(temp_type == "float")
  {
    add_code(code, "loadf(ind(esp), "+temp_reg+")");
    add_code(code,"popf(1)");
  } 
  for(int i=freeReg+1;i<5;i++){
    if(temp_regs_type[i-1] == "int")
    {
      add_code(code, "loadi(ind(esp), "+getReg(i)+")");
      add_code(code,"popi(1)");
    }else if(temp_regs_type[i-1] == "float")
    {
      add_code(code, "loadf(ind(esp), "+getReg(i)+")");
      add_code(code,"popf(1)");
    }
  }
  // restore type of values in register
  regs_type=temp_regs_type;
  if(isCast){ 
    temp_type = castTo;
    if(castTo=="float")
      add_code(code, "intTofloat( "+temp_reg+")");
    else if(castTo=="int")
      add_code(code, "floatToint( "+temp_reg+")");
  }
  if(onStack)
  {
    if(temp_type=="int")
      add_code(code, "pushi( "+temp_reg+")");
    else if(temp_type=="float")
      add_code(code, "pushf( "+temp_reg+")");
  }
  regs_type[freeReg-1] = temp_type;
  return code;
}

//same definition as above
string funcall_stmt_node::generate_code(symbol_table* current_sym_tab)
{
  string code = "";
  // get symbol table entry of function from gst to get type
  if(id!="printf"){
    symbol_table_node* temp_func_st_node = gst->st[id];
    string temp_type = temp_func_st_node->decl_type->type;
     //get the free register
    string temp_reg = getReg(4);
    // make space for return value if not void
    if(temp_type == "int")
    {
      add_code(code,"pushi(0)");
    }
    else if(temp_type == "float")
    {
      add_code(code,"pushf(0.0)");
    }
    //push the parameters
    enl->freeReg=4;
    code=code+enl->generate_code(current_sym_tab);
    //call the function;
    add_code(code,id+"()");
    //cleanup code
    //popping the params in reverse order of pushing
    vector<exp_node*>* temp_vec = (enl->exp_list);
    for(int i=0; i<temp_vec->size(); i++)
    {
      exp_node* temp_exp = (*temp_vec)[i];
      //determine the type of value generated by expression?
      if(temp_exp->type->type == "float")
      {
        add_code(code,"popf(1)");
      }
      else if(temp_exp->type->type == "int")
      {
        add_code(code,"popi(1)");
      }
    }
    // take the return value from stack to temp_reg
    if(temp_type == "int")
    {
      add_code(code, "loadi(ind(esp), "+temp_reg+")");
      add_code(code,"popi(1)");
    }else if(temp_type == "float")
    {
      add_code(code, "loadf(ind(esp), "+temp_reg+")");
      add_code(code,"popf(1)");
    }
  }else{
    for(int i=0;i<enl->exp_list->size();i++){
      exp_node* e=(*(enl->exp_list))[i];
      if(e->type->type=="string"){
        add_code(code,"print_string("+e->generate_code(current_sym_tab)+")");
      }else if(e->type->type=="int"){
        e->freeReg=4;
        code=code+e->generate_code(current_sym_tab);
        add_code(code,"print_int("+getReg(4)+")");
      }else if(e->type->type=="float"){
        e->freeReg=4;
        code=code+e->generate_code(current_sym_tab);
        add_code(code,"print_float("+getReg(4)+")");
      }
    }
  }
  return code;
}

string stmt_node_list::generate_code(symbol_table* current_sym_tab)
{
  string code="";
  for(int i=0;i<stmt_list->size();i++){
    code=code+(*stmt_list)[i]->generate_code(current_sym_tab);
  }
  return code;
}

string block_node::generate_code(symbol_table* current_sym_tab)
{
  string code="";
  code = code + sln->generate_code(current_sym_tab);
  return code;
}

string stringconst_node::generate_code(symbol_table* current_sym_tab){
  return str;
}

string stmt_node::generate_code(symbol_table* current_sym_tab){
  return "";
}
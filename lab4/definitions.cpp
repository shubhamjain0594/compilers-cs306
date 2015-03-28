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
vector<string> errors;

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
  if(exists(name, current_scope)||exists(name, gst)){
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
// checks if two expressions have same size of indices
// does not check the type of expressions
bool check_logical_type(exp_node*& l, exp_node*& r){
  // cout<<l->type->type<<" "<<r->type->type<<" "<<l->type->indices.size()<<" "<<r->type->indices.size()<<endl;
  if(l->type->indices.size()==r->type->indices.size()){
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
  cout<<")";
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
  op = o+"_"+getUppercase(type->type);
  left = l;
  right = r;
  if(o=="GE"||o=="LE"||o=="LT"||o=="GT"||o=="NE"||o=="EQ"||o=="AND"||o=="OR"){
    type=new decl_struct(o);
    type->type="int";
  }
}
// done
void op_node::print(){
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"("<<op;
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
  op = o+"_"+getUppercase(c->type->type);
  child = c;
  // name=c->name;
  type=c->type;
}
void unary_op_node::print(){
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"("<<op;
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
identifier_array_ref_node::identifier_array_ref_node(string& i){
  id = i;
  type = get_type(i); 
  // cout<<"Here"<<endl;
}
void identifier_array_ref_node::print()
{
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
  cout<<"( Id \" "<<id<<" \" )"; 
  if(isCast){
      cout<<" )";
  }
}
index_node::index_node(exp_node*& l, exp_node*& r){
  left = l;
  right = r;
  type=l->type;
  // cout<<l->type->name<<endl;
  type->indices.erase(type->indices.begin());
  // cout<<type->indices.size()<<endl;
}
void index_node::print()
{
  if(isCast){
    cout<<"(TO_"<<getUppercase(castTo)<<" ";
  }
 cout<<"( ";
 left->print(); 
 cout<< " [ ";
 right->print(); 
 cout<< " ] "<<")"; 
  if(isCast){
      cout<<" )";
  }
}

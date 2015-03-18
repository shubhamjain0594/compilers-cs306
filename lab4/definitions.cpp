#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
int tab_count = 0;
string temp_type;
symbol_table *gst = new symbol_table();
symbol_table *current_scope = gst;
vector<string> errors;

bool exists(string name, symbol_table* scope)
{
  return scope->st.find(name)!=scope->st.end(); 
}

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

void add_error(int line, string s)
{
  string temp = "Line number: " + std::to_string(line) + " : Error :" + s;
  cout<<temp<<endl;
  errors.push_back(temp);
}

decl_struct::decl_struct(string n)
{
  name = n;
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
stmt_node::stmt_node(){

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
  op = o;
  left = l;
  right = r;
}
// done
void op_node::print(){
  cout<<"("<<op;
  left->print();
  right->print();
  cout<<")";
}

unary_op_node::unary_op_node(string& o, exp_node*& c)
{
  op = o;
  child = c;
}
void unary_op_node::print(){
  cout<<"("<<op;
  child->print();
  cout<<")";
}

funcall_node::funcall_node(string& i, exp_node_list*& e)
{
  id = i;
  enl = e;
}
void funcall_node::print(){
  cout<<"(Funcall";
  cout<<"( Id \" "<<id<<" \" )";
  enl->print();
  cout<<")";
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
}
void floatconst_node::print()
{
 cout<<"( FloatConst "<<num<<" )";  
}
intconst_node::intconst_node(string& n)
{
  num = atoi(n.c_str());
}
void intconst_node::print()
{
  cout<<"( IntConst "<<num<<" )";
}
stringconst_node::stringconst_node(string& s)
{
  str = s;
}
void stringconst_node::print()
{
  cout<<"( StringConst "<<str<<" )"; 
}
identifier_node::identifier_node(string& i)
{
  id = i;
}
void identifier_node::print()
{
  cout<<"( Id \" "<<id<<" \" )";
}
identifier_array_ref_node::identifier_array_ref_node(string& i){
  id = i;
}
void identifier_array_ref_node::print()
{
  cout<<"( Id \" "<<id<<" \" )"; 
}
index_node::index_node(exp_node*& l, exp_node*& r){
  left = l;
  right = r;
}
void index_node::print()
{
 cout<<"( ";
 left->print(); 
 cout<< " [ ";
 right->print(); 
 cout<< " ] "<<")"; 
}

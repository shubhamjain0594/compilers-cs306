#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
int tab_count = 0;
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

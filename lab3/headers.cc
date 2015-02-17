#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

class abstract_astnode{
public:
  virtual void print () = 0;
//   virtual std::string generate_code(const symbolTable&) = 0;
//   virtual basic_types getType() = 0;
//   virtual bool checkTypeofAST() = 0;
// protected:
//   virtual void setType(basic_types) = 0;
// private:
//   typeExp astnode_type;
};

class exp_node : public abstract_astnode{
};

class stmt_node : public abstract_astnode{
public:
  stmt_node();
  void print();
};

class stmt_node_list : public stmt_node{
public:
  vector<stmt_node*>* stmt_list;
  stmt_node_list();
  void add_stmt(stmt_node*& stmt);
  void print();
};

class block_node : public stmt_node{
public:
  stmt_node_list* sln;
  block_node(stmt_node_list*& sln_arg);
  void print();
};

class ass_node : public stmt_node{
public:
  exp_node *left;
  exp_node *right;
  ass_node(exp_node*& l, exp_node*& r);
  void print();
};

class return_node : public stmt_node{
public:
  exp_node *child;
  return_node(exp_node*& c);  
  void print();
};

class if_node : public stmt_node{
public:
  exp_node *left;
  stmt_node *middle;
  stmt_node *right; 
  if_node(exp_node*& l, stmt_node*& m, stmt_node*& r);
  void print();
};

class while_node : public stmt_node{
public:
  exp_node* left;
  stmt_node* right;
  while_node(exp_node*& l, stmt_node*& r);
  void print();
};

class for_node : public stmt_node{
public:
  exp_node* left;
  exp_node* middle;
  exp_node* right;
  stmt_node* body;
  for_node(exp_node*& l, exp_node*& m, exp_node*& r, stmt_node*& b);
  void print();
};

class op_node : public exp_node{
public:  
  string op;
  exp_node* left;
  exp_node* right;
  op_node(string& o, exp_node*& l, exp_node*& r);
  void print();
};

class unary_op_node : public exp_node{
public:
  string op;
  exp_node* child;
  unary_op_node(string& o, exp_node*& c); 
  void print();
};

class exp_node_list : public exp_node{
public:
  vector<exp_node*>* exp_list;
  exp_node_list();
  void add_exp(exp_node*& exp);
  void print();
};

class funcall_node : public exp_node{
public:
  string id;
  exp_node_list* enl;
  funcall_node(string& i, exp_node_list*& e);
  void print();
};

class floatconst_node : public exp_node{
public:
  float num;
  floatconst_node(string& n);
  void print();
};

class intconst_node : public exp_node{
public:
  int num;
  intconst_node(string& n);
  void print();
};

class stringconst_node : public exp_node{
public:
  string str;
  stringconst_node(string& s);
  void print();
};

class identifier_node : public exp_node{
public:
  string id;
  identifier_node(string& i);
  void print();
};

class array_ref_node : public exp_node{  
  //void print();
};

class identifier_array_ref_node : public array_ref_node{
public:
  string id;
  identifier_array_ref_node(string& i);
  void print();
};

class index_node : public array_ref_node{
public:
  exp_node* left;
  exp_node* right;  
  index_node(exp_node*& l, exp_node*& r);
  void print();
};


#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <list>

using namespace std;

void add_error(int line, string s);

struct decl_struct
{
  string name;
  string type;
  std::vector<int> indices;
  decl_struct();
  decl_struct(string n);
  int calculate_size();
  void print();
};

class symbol_table;

class symbol_table_node{
public:
  string name;
  int size; // what is the use of size
  string type;  //func, parameter, local
  decl_struct* decl_type;
  int offset;
  symbol_table* local_symbol_table;
  symbol_table_node(string n, string t, int o);
  symbol_table_node(string n, string t, symbol_table* st);
  //symbol_table_node();

  void print();
};

//for funtions where to store? 
//required - parameter list, local variables ,return stuff - all represented by symbol_table_node

class symbol_table{
public:
  map<string, symbol_table_node*> st;
  vector<decl_struct*> parameters; // used only in case of local symbol tables for functions 
  int offset;
  symbol_table();
  void insert_entry(string s, symbol_table_node* stn);
  void print();
};

class abstract_astnode{
public:
  virtual void print () = 0;
  virtual std::string generate_code(symbol_table* current_sym_tab) = 0;
  int offset;
  int size;
//   virtual basic_types getType() = 0;
//   virtual bool checkTypeofAST() = 0;
// protected:
//   virtual void setType(basic_types) = 0;
// private:
//   typeExp astnode_type;
};

class exp_node : public abstract_astnode{
public:
  bool isCast=0;
  string castTo;
  decl_struct* type;
  bool on_stack;
};

class stmt_node : public abstract_astnode{
public:
  stmt_node();
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class stmt_node_list : public stmt_node{
public:
  vector<stmt_node*>* stmt_list;
  stmt_node_list();
  void add_stmt(stmt_node*& stmt);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class block_node : public stmt_node{
public:
  stmt_node_list* sln;
  block_node(stmt_node_list*& sln_arg);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class ass_node : public stmt_node{
public:
  exp_node *left;
  exp_node *right;
  ass_node(exp_node*& l, exp_node*& r);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class return_node : public stmt_node{
public:
  exp_node *child;
  return_node(exp_node*& c);  
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class if_node : public stmt_node{
public:
  exp_node *left;
  stmt_node *middle;
  stmt_node *right; 
  if_node(exp_node*& l, stmt_node*& m, stmt_node*& r);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class while_node : public stmt_node{
public:
  exp_node* left;
  stmt_node* right;
  while_node(exp_node*& l, stmt_node*& r);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class for_node : public stmt_node{
public:
  exp_node* left;
  exp_node* middle;
  exp_node* right;
  stmt_node* body;
  for_node(exp_node*& l, exp_node*& m, exp_node*& r, stmt_node*& b);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class op_node : public exp_node{
public:  
  string op;
  exp_node* left;
  exp_node* right;
  op_node(string& o, exp_node*& l, exp_node*& r);
  void print();
  string generate_code(symbol_table* current_sym_tab);
};

class unary_op_node : public exp_node{
public:
  string op;
  exp_node* child;
  unary_op_node(string& o, exp_node*& c); 
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class exp_node_list : public exp_node{
public:
  vector<exp_node*>* exp_list;
  exp_node_list();
  void add_exp(exp_node*& exp);
  void print();
  string generate_code(symbol_table* current_sym_tab);
};

class funcall_node : public exp_node{
public:
  string id;
  exp_node_list* enl;
  funcall_node(string& i, exp_node_list*& e);
  void print();
  string generate_code(symbol_table* current_sym_tab);
};

class funcall_stmt_node : public stmt_node{
public:
  string id;
  exp_node_list* enl;
  funcall_stmt_node(string& i, exp_node_list*& e);
  void print();
  string generate_code(symbol_table* current_sym_tab);
};

class floatconst_node : public exp_node{
public:
  float num;
  floatconst_node(string& n);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class intconst_node : public exp_node{
public:
  int num;
  intconst_node(string& n);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class stringconst_node : public exp_node{
public:
  string str;
  stringconst_node(string& s);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class identifier_node : public exp_node{
public:
  string id;
  identifier_node(string& i);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class array_ref_node : public exp_node{  
  //void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class identifier_array_ref_node : public array_ref_node{
public:
  string id;
  identifier_array_ref_node(string& i);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};

class index_node : public array_ref_node{
public:
  exp_node* left;
  exp_node* right;  
  index_node(exp_node*& l, exp_node*& r);
  void print();
  string generate_code(symbol_table* current_sym_tab){};
};


#include <iostream>
#include <set>
#include <string>
#include "Scanner.h"
#include "Parser.h"
using namespace std;

extern symbol_table *gst;
extern string code_set;
extern set<string> printables;
int main (int argc, char** arg)
{
  // cout<<argc<<endl;
  for(int i=1;i<argc;i++){
    // cout<<arg[i]<<endl;
    printables.insert(arg[i]);
  }
  Parser parser;
  parser.parse();
  cout<<code_set<<endl;
  // cout<<"Global Symbol Table"<<endl;
  // gst->print();
  // cout<<endl;
  // for(map<string,symbol_table_node*>::iterator it = gst->st.begin(); it!=gst->st.end(); it++)
  // {
  // 	cout<<"Symbol Table for "<<(*it).first<<endl;
  // 	(((*it).second)->	local_symbol_table)->print();
  // 	cout<<endl;	
  // }
}



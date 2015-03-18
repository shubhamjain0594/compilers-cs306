#include <iostream>
#include "Scanner.h"
#include "Parser.h"
using namespace std;

extern symbol_table *gst;

int main (int argc, char** arg)
{
  Parser parser;
  parser.parse();
  
  cout<<"Global Symbol Table"<<endl;
  gst->print();
  cout<<endl;

  for(map<string,symbol_table_node*>::iterator it = gst->st.begin(); it!=gst->st.end(); it++)
  {
  	cout<<"Symbol Table for "<<(*it).first<<endl;
  	(((*it).second)->	local_symbol_table)->print();
  	cout<<endl;	
  }
}



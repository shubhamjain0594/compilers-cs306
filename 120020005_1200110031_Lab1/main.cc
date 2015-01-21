#include <iostream>
#include "Scanner.h"
using namespace std;
int main()
{
	Scanner scanner;   // define a Scanner object
  while (int token = scanner.lex()) // get all tokens
  {
  	string const &text = scanner.matched();
  	// cout << token << " " << text << '\n';
  	switch (token)
  	{
  		case Scanner::IDENTIFIER:
  		cout << "IDENTIFIER: " << text << '\n';
  		break;
  		case Scanner::INT_CONSTANT:
  		cout << "INTEGER CONSTANT: " << text << '\n';
  		break;

  		case Scanner::STRING_CONSTANT:
  		cout << "STRING CONSTANT: " << text << '\n';
  		break;

  		case Scanner::FLOAT_CONSTANT:
  		cout << "FLOAT CONSTANT: " << text << '\n';
  		break;

  		case Scanner::INC_OP:
  		cout << "INCREMENT OPERATOR: " << text << '\n';
  		break;

  		case Scanner::VOID:
  		cout << "VOID: " << text << '\n';
  		break;	

  		case Scanner::INT:
  		cout << "INT: " << text << '\n';
  		break;

  		case Scanner::FLOAT:
  		cout << "FLOAT: " << text << '\n';
  		break;

  		case Scanner::IF:
  		cout << "IF: " << text << '\n';
  		break;

  		case Scanner::ELSE:
  		cout << "ELSE: " << text << '\n';
  		break;

  		case Scanner::FOR:
  		cout << "FOR: " << text << '\n';
  		break;

  		case Scanner::WHILE:
  		cout << "WHILE: " << text << '\n';
  		break;

  		case Scanner::RETURN:
  		cout << "RETURN: " << text << '\n';
  		break;

  		case Scanner::EQ_OP:
  		cout << "EQUAL TO OPERATOR: " << text << '\n';
  		break;

  		case Scanner::LE_OP:
  		cout << "LESS THAN EQUAL TO OPERATOR: " << text << '\n';
  		break;

  		case Scanner::NE_OP:
  		cout << "NOT EQUAL TO OPERATOR: " << text << '\n';
  		break;

  		case Scanner::GE_OP:
  		cout << "GREATER THAN EQUAL TO OPERATOR: " << text << '\n';
  		break;

  		case Scanner::AND_OP:
  		cout << "AND OPERATOR: " << text << '\n';
  		break;

  		case Scanner::OR_OP:
  		cout << "OR OPERATOR: " << text << '\n';
  		break;

  		case Scanner::WHITESPACES:
  		cout << "WHITESPACES: " << text << '\n';
  		break;

  		case Scanner::COMMENT:
  		cout << "COMMENT: " << text << '\n';
  		break;

  		default:
  		cout <<text<<":  " << text << '\n';
  	}
  }
}

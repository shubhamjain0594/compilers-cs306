WHITESPACES	[ \t\n]
VOID				void
INT 				int
FLOAT 			float
DIGIT				[0-9]
LETTER				[a-zA-Z]
IF                  if
ELSE                else
FOR                 for
WHILE               while
RETURN              return 		
IDENTIFIER			{LETTER}({LETTER}|{DIGIT})*
INC_OP				\+\+
EQ_OP				==
LE_OP               (\<=)|(=\<)
GE_OP               (\>=)|(=\>)
NE_OP               !=  
AND_OP              &&
OR_OP               \|\|
INT_CONSTANT		([1-9][0-9]*)|(0[bB][01]*)|(0[0-7]*)|(0[xX][0-9a-fA-F]*)
STRING_CONSTANT     [\"]([^\\\"](\\\")?(\\n)?(\\t)?(\\\\)?)*[\"]
FLOAT_CONSTANT		(({DIGIT}+\.)|(\.{DIGIT}+)|({DIGIT}+\.{DIGIT}+))((([eE][+-][0-9]*)|([eE][0-9]*))?)
PUNCTUATIONS     	\(|\)|\{|\}|\[|\]|,|;|!|\+|-|\*|\/|\=
COMMENT 	([\/][\*][^\*]*([\*]([^\/\*][^\*]*)?)*[\*][\/]) 
%%

{VOID}	return Parser::VOID;
{INT}	return Parser::INT;
{FLOAT}	return Parser::FLOAT;
{IF} 						return Parser::IF;	                		 		
{ELSE}                		return Parser::ELSE;
{FOR}               		return Parser::FOR;
{WHILE}               		return Parser::WHILE;
{RETURN}              		return Parser::RETURN; 		
{IDENTIFIER}				return Parser::IDENTIFIER;
{INC_OP}					return Parser::INC_OP;		
{EQ_OP}						return Parser::EQ_OP;
{LE_OP}               		return Parser::LE_OP;
{GE_OP}               		return Parser::GE_OP;
{NE_OP}               		return Parser::NE_OP;
{AND_OP}              		return Parser::AND_OP;
{OR_OP}               		return Parser::OR_OP;
{INT_CONSTANT}				return Parser::INT_CONSTANT;
{STRING_CONSTANT}     		return Parser::STRING_CONSTANT;
{FLOAT_CONSTANT}			return Parser::FLOAT_CONSTANT;
{PUNCTUATIONS} 			return matched()[0];

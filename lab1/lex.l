WHITESPACES	[ \t\n]
VOID				void
INT 				int
FLOAT 			float
DIGIT				[0-9]
LETTER				[a-zA-z]
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
INT_CONSTANT		({DIGIT}+)|(0[bB][01]*)|(0[0-7]*)|(0[xX][0-9a-fA-F]*)
STRING_CONSTANT     [\"]([^\"](\\\")?)*[\"]
FLOAT_CONSTANT		(({DIGIT}+\.)|(\.{DIGIT}+)|({DIGIT}+\.{DIGIT}+))((([eE][+-][0-9]*)|([eE][0-9]*))?)
PUNCTUATIONS     	\(|\)|\{|\}|\[|\]|,|;|!|\+|-|\*|\/
%%

{VOID}	return VOID;
{INT}	return INT;
{FLOAT}	return FLOAT;
{IF} 						return IF;	                		 		
{ELSE}                		return ELSE;
{FOR}               		return FOR;
{WHILE}               		return WHILE;
{RETURN}              		return RETURN; 		
{IDENTIFIER}				return IDENTIFIER;
{INC_OP}					return INC_OP;		
{EQ_OP}						return EQ_OP;
{LE_OP}               		return LE_OP;
{GE_OP}               		return GE_OP;
{NE_OP}               		return NE_OP;
{AND_OP}              		return AND_OP;
{OR_OP}               		return OR_OP;
{INT_CONSTANT}				return INT_CONSTANT;
{STRING_CONSTANT}     		return STRING_CONSTANT;
{FLOAT_CONSTANT}			return FLOAT_CONSTANT;
{WHITESPACES}				return WHITESPACES;
{PUNCTUATIONS} 			return matched()[0];
.							return 0;

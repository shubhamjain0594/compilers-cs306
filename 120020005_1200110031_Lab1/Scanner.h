// Generated by Flexc++ V1.08.00 on Tue, 20 Jan 2015 21:30:32 +0530

#ifndef Scanner_H_INCLUDED_
#define Scanner_H_INCLUDED_

// $insert baseclass_h
#include "Scannerbase.h"


// $insert classHead
class Scanner: public ScannerBase
{
    public:
        explicit Scanner(std::istream &in = std::cin,
                                std::ostream &out = std::cout);

        Scanner(std::string const &infile, std::string const &outfile);
        
        // $insert lexFunctionDecl
        int lex();
        enum Tokens{VOID=0x100,
                    INT,
                    FLOAT,
                    IF,
                    ELSE,
                    FOR,
                    WHILE,
                    RETURN,
                    IDENTIFIER,
                    INC_OP,
                    EQ_OP,
                    LE_OP,
                    NE_OP,
                    GE_OP,
                    AND_OP,
                    OR_OP,
                    INT_CONSTANT,
                    STRING_CONSTANT,
                    FLOAT_CONSTANT,
                    WHITESPACES,
                    COMMENT,
                    OTHERS};

    private:
        int lex__();
        int executeAction__(size_t ruleNr);

        void print();
        void preCode();     // re-implement this function for code that must 
                            // be exec'ed before the patternmatching starts

        void postCode(PostEnum__ type);    
                            // re-implement this function for code that must 
                            // be exec'ed after the rules's actions.
};

// $insert scannerConstructors
inline Scanner::Scanner(std::istream &in, std::ostream &out)
:
    ScannerBase(in, out)
{}

inline Scanner::Scanner(std::string const &infile, std::string const &outfile)
:
    ScannerBase(infile, outfile)
{}

// $insert inlineLexFunction
inline int Scanner::lex()
{
    return lex__();
}

inline void Scanner::preCode() 
{
    // optionally replace by your own code
}

inline void Scanner::postCode(PostEnum__ type) 
{
    // optionally replace by your own code
}

inline void Scanner::print() 
{
    print__();
}


#endif // Scanner_H_INCLUDED_


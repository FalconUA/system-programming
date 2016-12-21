from purplex import Lexer, TokenDef


# Python language
class PYTHON_LEXER(Lexer):
    # Important stuff
    COMMENT                 = TokenDef(r'#.*\n')
    STATEMENT_DELIMITER     = TokenDef(r'[;\n]')

    # Language-specific stuff
    BLOCK_BEGIN             = TokenDef(r':.*\n')
    RESERVED_WORD           = TokenDef(r'(and)|(as)|(assert)|(break)|(class)|(continue)|(def)|(del)|(elif)|(else)|(except)|(exec)|(finally)|(for)|(from)|(global)|(if)|(import)|(in)|(is)|(lambda)|(not)|(or)|(pass)|(print)|(raise)|(return)|(try)|(while)|(with)|(yield)')
    BUILT_IN_OBJECT         = TokenDef(r'(None)|(True)|(False)|(object)')
#    TABULATION              = TokenDef(r'(    )|(\t)')

    # Things that every language has
    IDENTIFIER              = TokenDef(r'[A-Za-z_][A-Za-z0-9_]*')
    L_ROUND_BRACKET         = TokenDef(r'\(')
    R_ROUND_BRACKET         = TokenDef(r'\)')
    L_SQUARE_BRACKET        = TokenDef(r'\[')
    R_SQUARE_BRACKET        = TokenDef(r'\]')
    L_CURLY_BRACKET         = TokenDef(r'\{')
    R_CURLY_BRACKET         = TokenDef(r'\}')
    COMA                    = TokenDef(r'\,')
    OPERATOR                = TokenDef(r'(=)|(==)|(\+)|(\-)|(\*)|(/)|(<)|(>)|(<=)|(>=)')
    NUMERIC_LITERAL         = TokenDef(r'\b((?:0x[a-zA-Z_]+)|(?:0[a-zA-Z\d]+)|(?:\d*\.?\d*E\-?\d*)|(?:\d*\.(?:\d{0,3}_?)*)|(?:\d+)|(?:\d*\.\d+))\b')
    STRING_LITERAL          = TokenDef(r'(\".*\")|(\'.*\')')

    # Useless stuff
    WHITESPACE              = TokenDef(r'[\s\n]+', ignore=True)


# C language
class C_LEXER(Lexer):
    COMMENT                 = TokenDef(r'//.*?\n|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"')

    PREPROCESSOR_DIRECTIVE  = TokenDef(r'\#.*\n')
    STATEMENT_DELIMITER     = TokenDef(r';')

    # Language-specific stuff
    BLOCK_BEGIN             = TokenDef(r'\{')
    BLOCK_END               = TokenDef(r'\}')
    RESERVED_WORD           = TokenDef(r'(const)|(struct)|(break)|(continue)|(switch)|(else)|(for)|(case)|(default)|(register)|(sizeof)|(typedef)|(volatile)|(enum)|(goto)|(do)|(return)|(static)|(union)|(while)|(extern)|(if)')
    BUILT_IN_TYPE           = TokenDef(r'(char)|(unsigned char)|(signed char)|(int)|(unsigned int)|(short)|(unsigned short)|(long)|(unsigned long)|(float)|(double)|(long double)|(void)|(long long int)|(unsigned long long int)')

    # Symbols and operands
    IDENTIFIER              = TokenDef(r'[A-Za-z_][A-Za-z0-9_]*')
    L_ROUND_BRACKET         = TokenDef(r'\(')
    R_ROUND_BRACKET         = TokenDef(r'\)')
    L_SQUARE_BRACKET        = TokenDef(r'\[')
    R_SQUARE_BRACKET        = TokenDef(r'\]')
    DOT                     = TokenDef(r'\.')
    COMA                    = TokenDef(r'\,')
    ARROW                   = TokenDef(r'\->')
    OPERATOR                = TokenDef(r'(=)|(==)|(\+\+)|(\+=)|(\+)|(\-\-)|(\-=)|(\-)|(\*=)|(\*)|(/=)|(/)|(<)|(>)|(<=)|(>=)|(\|\|)|(\|)|(\^)|(\&&)\(\&)')
    NUMERIC_LITERAL         = TokenDef(r'\b((?:0x[a-zA-Z_]+)|(?:0[a-zA-Z\d]+)|(?:\d*\.?\d*E\-?\d*)|(?:\d*\.(?:\d{0,3}_?)*)|(?:\d+)|(?:\d*\.\d+))\b')
    STRING_LITERAL          = TokenDef(r'(\".*\")')
    CHAR_LITERAL            = TokenDef(r'\'.\'') 

    WHITESPACE              = TokenDef(r'[\s\n]+', ignore=True)


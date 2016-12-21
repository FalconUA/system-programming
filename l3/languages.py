from purplex import Lexer, TokenDef


class PYTHON_LEXER(Lexer):
    # Important stuff
    COMMENT                 = TokenDef(r'#.*\n')
    STATEMENT_DELIMITER     = TokenDef(r'[;\n]')

    # Things that every language has
    IDENTIFIER              = TokenDef(r'[A-Za-z_][A-Za-z0-9_]*')
    L_ROUND_BRACKET         = TokenDef(r'\(')
    R_ROUND_BRACKET         = TokenDef(r'\)')
    L_SQUARE_BRACKET        = TokenDef(r'\[')
    R_SQUARE_BRACKET        = TokenDef(r'\]')
    L_CURLY_BRACKET         = TokenDef(r'\{')
    R_CURLY_BRACKET         = TokenDef(r'\}')
    OPERATOR                = TokenDef(r'(=)|(==)|(\+)|(\-)|(\*)|(/)|(<)|(>)|(<=)|(>=)')
    NUMERIC_LITERAL         = TokenDef(r'\b((?:0x[a-zA-Z_]+)|(?:0[a-zA-Z\d]+)|(?:\d*\.?\d*E\-?\d*)|(?:\d*\.(?:\d{0,3}_?)*)|(?:\d+)|(?:\d*\.\d+))\b')
    STRING_LITERAL          = TokenDef(r'(\".*\")|(\'.*\')')

    # Language-specific stuff
    BLOCK_BEGIN             = TokenDef(r':.*\n')
    RESERVED_WORD           = TokenDef(r'(and)|(as)|(assert)|(break)|(class)|(continue)|(def)|(del)|(elif)|(else)|(except)|(exec)|(finally)|(for)|(from)|(global)|(if)|(import)|(in)|(is)|(lambda)|(not)|(or)|(pass)|(print)|(raise)|(return)|(try)|(while)|(with)|(yield)')
    BUILT_IN_OBJECT         = TokenDef(r'(None)|(True)|(False)|(object)')
#    TABULATION              = TokenDef(r'(    )|(\t)')

    # Useless stuff
    WHITESPACE              = TokenDef(r'[\s\n]+', ignore=True)


class C_LEXER(Lexer):
    COMMENT                 = TokenDef(r'(//.*\n)|(/[*][.\n]*[*]/)')
    PREPROCESSOR_DIRECTIVE  = TokenDef(r'\#.*\n')
    STATEMENT_DELIMITER     = TokenDef(r'[;\n]+')

    

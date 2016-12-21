import re
import sys
import itertools
import collections

from purplex import Lexer, TokenDef, END_OF_INPUT_TOKEN
from languages import C_LEXER, PYTHON_LEXER


LEXER = {
        'c': C_LEXER,
        'python': PYTHON_LEXER,
}

def analyze(filename, language):
    text = open(filename, 'r').read()
    lexer = LEXER[language](text)
    tokens = iter(itertools.chain(lexer))

    while True:
        try:
            token = next(tokens)
            print(token)
        except StopIteration:
            break


if __name__ == '__main__':
    if (len(sys.argv) == 3):
        analyze(sys.argv[1], sys.argv[2])

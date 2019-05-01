"""."""
import re


class ActionType2:

    MATH = r"\s(PRODUKT|SUM|DIFF|QUOSHUNT|MOD|BIGGR|SMALLR)\sOF"
    BOOL = r"(BOTH|EITHER|NOT)\sOF*"
    LOOP = r"(TIL|WILE)"
    COUNT = r"(UPPIN|NERFIN)\sYR"
    COMPARISON = r"(SAEM|DIFFRNT)"
    IN_OUT = r"\s(GIMMEH|VISIBLE)"
    var_type = r"\s([a-zA-Z]+\w*)\s"


class ActionType:

    OPERATORS = re.compile(r'''(\bPRODUKT\b)|(\bSUM\b)|(\bDIFF\b)|
                           (\bQUOSHUNT\b)|(\bMOD\b)|(\bBIGGR\b)|(\bSMALLR\b)|
                           (\bOF\b)|(\bBOTH\b)|(\bEITHER\b)|(\bNOT\b)|
                           (\bSAEM\b)|(\bDIFFRNT\b)|(\bAN\b)''', re.X)

    LOOP = re.compile(r'(\bIM\b)|(\bIN\b)|(\bYR\b)|(\bOUTTA\b)')

    LOOPS = re.compile(r"(\bTIL\b)|(\bWILE\b)")

    COUNT = re.compile(r"(\bUPPIN\b)|(\bNERFIN\b)")

    VARASS = re.compile(r"(\bGIMMEH\b)|(\bVISIBLE\b)|(\bR\b)")

    VARDICC = re.compile(r'(\bI\b)|(\bHAS\b)|(\bA\b)|(\bITZ\b)')

    CONDITIONALS = re.compile(r'''(\bO\b)|(\bRLY\b)|(\b\?\b)|(\bYA\b)|
                              (\bNO\b)|(\bWAI\b)|(\bOIC\b)''', re.X)

    START_END = re.compile(r'(\bHAI\b)|(\bKTHXBYE\b)')

    var_type = re.compile(r"\s*(\b[a-zA-Z]+\w*\b)\s")


class LSyntax:
    """."""

    expression = r""

    init = re.compile(r"\s*HAI\s(\d+\.\d*\s)*")

    varDeclaration = re.compile(r"I\sHAS\sA" + ActionType.var_type +
                                r"(ITZ)*(\sLIKE)*\s*(\w*|" +
                                ActionType.var_type+")*")

    loop_stmnt = re.compile(
        r'\s*IM\sIN\sYR' + ActionType.var_type + ActionType.COUNT +
        ActionType.var_type + ActionType.LOOP + ActionType.COMPARISON +
        ActionType.var_type + 'AN' + ActionType.var_type, re.X)

    end_loop = re.compile(r"IM\sOUTTA\sYR" + ActionType.var_type)

    if_stmnt = re.compile(expression + r"\sO\sRLY?\s" + r"YA\sRLY\s"+expression
                          + r"\sNO\sWAI\s" + expression + r"\sOIC\s")

    varPrint = re.compile(ActionType.OUTPUT + ActionType.var_type)

    VarInitialization = re.compile(ActionType.var_type + "R" + '(' +
                                   ActionType.MATH+'|'+ActionType.BOOL + ')'
                                   + ActionType.var_type + "", re.X)

    end = re.compile(r"\s*KTHXBYE\s")


'''
def if_st(nLinea, lines, match):
    """O RLY?."""
    nw = 0
    oic = 0

    #  if re.search(Exp(), lines[nLinea - 1]):

        if re.search(r"YA\s+RLY", lines[nLinea + 1]):

            for i in lines[nLinea + 1:-1]:
                if re.search(r"O\s+RLY\?", i):
                    if_st(nLinea, lines, match)

                if re.search(r"NO\s+WAI", i):
                    nw = nLinea

                if re.search("OIC", i):
                    oic = 1

                nLinea += 1

'''


class LolCode:
    """."""

    In_stmnt = ActionType.INPUT + ActionType.var_type

    Out_stmnt = ActionType.OUTPUT + r'\s\w*'

    varASS_stmnt = ActionType.var_type + r'R\s(\w)*'

    varD_stmnt = r'I\sHAS\sA' + ActionType.var_type + r'(ITZ\s\w*)*'

    '''
    stmt_list = r'(' + if_stmnt + r'|' + loop_stmnt + r'|' + varD_stmnt +
    r'|' + varASS_stmnt + r'|' + In_stmnt + r'|' + Out_stmnt + r')*'

    if_stmnt = (Exp() + r',\sO\sRLY?\s' + r'YA\sRLY,\s' + stmt_list +
    r'\sNO\sWAI' + stmt_list)

    loop_stmnt = r'IM\sIN\sYR' + ActionType.var_type + ActionType.COUNT +
    ActionType.var_type + ActionType.LOOP + expression + stmt_list +
    r'\sIM\sOUTTA\YR' + ActionType.var_type

    program = r'HAI\s*(\d*\.\d*)*\s*' + stmt_list + r'\sKTHXBYE(\s)*'


class LolCode_withColor:

'''

'''
colors = {
    'OPERATORS':    '\033[94m',
    'START_END':    '\033[92m',
    'LOOPS':        '\033[95m',
    'BLACK':        '\033[30m',
    'CONDITIONALS': '\033[36m',
    'VARIABLES':    '\033[93m',
    'VARIABLES2':   '\033[31m',
    'FAIL':         '\033[41m',
    'END':          '\033[0m',
    }
'''

nameFile = input("File name :D \n")

with open(nameFile, 'r') as f:

    nLinea = 0
    nL = []

    lines = f.readlines()

    if lines[0].strip() != 'HAI':
        for match in lines:
            print(colors['FAIL'] + match.strip() + colors['END'])

    elif lines[-1].strip() != 'KTHXBYE':
        for match in lines:
            print(colors['FAIL'] + match.strip() + colors['END'])

    else:
        for match in lines:

            if LSyntax.init.match(match) or LSyntax.end.match(match):
                print(colors['START_END'] + match.strip() + colors['END'])

            elif re.search(LolCode.varD_stmnt, match):
                x = []
                for i in re.finditer(LolCode.varD_stmnt, match):
                    L = colors['VARIABLES2'] + i.group(1) + colors['END']
                    print(i.group(1))
                    x.append(L)
                print(" ".join(x) + '\t\t\t' + match.strip())

                """
            elif re.search(r"O\sRLY\?", match):
                if_st(nLinea,lines,match)
                """

            else:
                print(colors['FAIL'] + match.strip() + colors['END'])

            nLinea += 1

"""
O RLY?

<expresion> << ERROR

YA RLY

<expresion>

NO WAY

<expresion>

OIC

"""


# files = "".join(file_b.readlines())
regex = re.compile(r"\bI\sHAS\sA\b")
print(regex.split("I HAS A variable ITZ 18356"))
regex2 = "".join(regex.split("I HAS A variable ITZ 18356"))
# regex3 = re.compile(r"z)

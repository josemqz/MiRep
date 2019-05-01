import re


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


def Exp():      # terminar pls
    """Expresion mas general posible (es posible!)."""
    expression = (ActionType.var_type + r"|" + r"("
                  + ActionType.OPERATORS + Exp() + 'AN' + Exp() + r')'
                  + r'(' + ActionType.var_type + r'|' + r'\d*' + r')')

    return expression


if re.search(Exp(), "wea"):     # expresion anterior
    print(True)

"""."""
import re


class ActionType:
    """."""

    MATH = r"\s(PRODUKT|SUM|DIFF|QUOSHUNT|MOD|BIGGR|SMALLR)\sOF"
    BOOL = r"(BOTH|EITHER|NOT)\sOF*"
    COMPARISON = r"(SAEM|DIFFRNT)"
    LOOP = r"(TIL|WILE)"
    COUNT = r"(UPPIN|NERFIN)\sYR"
    IN_OUT = r"\s(GIMMEH|VISIBLE)"
    var_type = r"\s([a-zA-Z]+\w*)\s"


class LSyntax:
    """."""

    expression = r""

    init = re.compile(r"HAI\s(\d+\.\d*\s)?")

    varDeclaration = re.compile(
        r"I\sHAS\sA" + ActionType.var_type
        + r"(ITZ)*(\w*|" + ActionType.var_type + ")*")

    loop_stmnt = re.compile(
        r"IM\sIN\sYR" + ActionType.var_type + ActionType.COUNT +
        ActionType.var_type + ActionType.LOOP + r"\s("
        + ActionType.BOOL + r"\s)?" + ActionType.COMPARISON
        + ActionType.var_type + "AN" + ActionType.var_type)

    math_st = ActionType.MATH + "(" + ActionType.var_type + "|" + self.math_st + "|"
    + "AN" + ActionType.var_type

    end_loop = re.compile(r"IM\sOUTTA\sYR" + ActionType.var_type)

    if_stmnt = re.compile(
        expression + r"\sO\sRLY?\s" + r"YA\sRLY\s"+expression
        + r"\sNO\sWAI\s" + expression + r"\sOIC\s")

    varInO = re.compile(ActionType.IN_OUT + ActionType.var_type)

    VarInitialization = re.compile(
        ActionType.var_type + "R" + '(' + ActionType.MATH + '|'
        + ActionType.BOOL + ')*' + ActionType.var_type + "")

    end = re.compile(r"\s*KTHXBYE\s")


class BColors:
    """."""

    OPERATORS = '\033[94m'
    START_END = '\033[92m'
    LOOPS = '\033[95m'
    BLACK = '\033[30m'
    CONDITIONALS = '\033[36m'
    VARIABLES = '\033[93m'
    VARIABLES2 = '\033[31m'
    FAIL = '\033[41m'
    END = '\033[0m'


nameFile = input("File name :D \n")

with open(nameFile, 'r') as f:

    lines = f.readlines()

    for match in lines:

        if LSyntax.init.match(match):
            print(BColors.START_END + match + BColors.END)

        elif LSyntax.end.match(match):
            print(BColors.START_END + match + BColors.END)

        elif LSyntax.varDeclaration.match(match):
            print(BColors.VARIABLES + match + BColors.END)

        elif LSyntax.VarInitialization.match(match):
            print(BColors.VARIABLES2 + match + BColors.END)

        elif LSyntax.loop_stmnt.match(match):
            print(BColors.LOOPS + match + BColors.END)

        elif LSyntax.end_loop.match(match):
            print(BColors.LOOPS + match + BColors.END)

        elif LSyntax.varInO.match(match):
            print(BColors.VARIABLES2 + match + BColors.END)
            # LSyntax.varPrint.match(match).group(1) + "\n")

        else:
            print(BColors.FAIL + BColors.BLACK + match + BColors.END)
f.close()

"""
HAI 1.2

  I HAS A y
  y R DIFF OF 10 AN 2   BTW 8
  I HAS A x ITZ SUM OF PRODUKT OF 3 AN 1 AN y   BTW x = (3*1)+y
  VISIBLE x

  IM IN YR c UPPIN YR y WILE DIFFRINT x AN 5            <<<<<<<----------------
    y R SUM OF 1 AN x
    x R DIFF OF x AN 1
  IM OUTTA YR c
  VISIBLE y

KTHXBYE
"""

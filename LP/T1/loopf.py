import re


class TypeAction:

    varType = r"[A-Za-z]+\w*\s*"
    vardicc1 = r"\s*I\s+HAS\s+A\s+"
    GIMMEH = r"\s*GIMMEH\s+"
    VISIBLE = r"\s*VISIBLE\s+"
    iLOOP = r"\s*IM\sIN\sYR\s+"
    fLOOP = r"\s*IM\sOUTTA\sYR\s+"
    LOOP2 = r"\s+(TIL|WILE)\s*"
    COUNT = r"\s+(UPPIN|NERFIN)\sYR\s*"
    COMPARISON = r"\s+(BOTH\sSAEM|DIFFRINT)\s*"
    MATH = r"\s*(PRODUKT|SUM|DIFF|QUOSHUNT|MOD|BIGGR|SMALLR)\sOF\s+"
    BIN = r"(PRODUKT|SUM|DIFF|QUOSHUNT|MOD|BIGGR|SMALLR|BOTH\sSAEM|DIFFRINT)\sOF\s+"

class ActionType:

    VARDICC0 = re.compile(r"(" + TypeAction.vardicc1 + TypeAction.varType + ")")
    varDICC = re.compile(TypeAction.vardicc1)
    varDICC2 = re.compile(r"\s*ITZ\s*")
    varASS = re.compile(r"(" + TypeAction.varType + r"R\s+" + r"\w+\s*)")

    # iLOOP = re.compile(r"(" + TypeAction.iLOOP + TypeAction.varType + r")")
    fLOOP = re.compile(r"(" + TypeAction.fLOOP + TypeAction.varType + r")")
    LOOP2 = re.compile(TypeAction.LOOP2)
    COUNT = re.compile(TypeAction.COUNT)

    ILOOP = re.compile("(" + TypeAction.iLOOP + TypeAction.varType + TypeAction.COUNT + TypeAction.varType
                       + TypeAction.LOOP2 + r"(\w| )+)", re.X)

    VISIBLE = re.compile(r"\s*VISIBLE\s + (" + TypeAction.vardicc1 + "|" + TypeAction.varType + ")")
    GIMMEH = re.compile(r"(\b" + TypeAction.GIMMEH + TypeAction.varType + r"\b)")
    NOT = re.compile(r"\s*NOT\s*")
    MATH = re.compile(TypeAction.MATH)
    COMPARISON = re.compile(TypeAction.COMPARISON)
    BIN = re.compile(TypeAction.BIN)
    ANY = re.compile(r"\w*")
    HAI = re.compile(r"\bHAI\s*")
    KTHXBYE = re.compile(r"\bKTHXBYE\b")

    SAVEUS = re.compile(r"((PRODUKT|SUM|DIFF|QUOSHUNT|MOD|BIGGR|SMALLR)\sOF)(\s*\w*\s+)AN(\s+\w*\s*)")

file_a = input("Giv Neim\n")

with open(file_a, "r") as file_b:

    lines = file_b.readlines()

    stripedLines = [line.strip() for line in lines]

    nLinea = 0

    cLOOPi = []    # loops -> (nombre, linea)
    cLOOPf = []

    LPF = []    # Final -> para exceptions

    for line in stripedLines:

        aux = 0

        for m in ActionType.ILOOP.finditer(line):
            aux += 1

        if aux == 1:
            if ActionType.ILOOP.search(line):
                # nombre loop, linea
                cLOOPi.append([nLinea, ActionType.ILOOP.match(line).group().split()[3]])
                # iLP.append(line[ActionType.ILOOP.match(line).end():])       # check

        aux = 0
        for m in ActionType.fLOOP.finditer(line):
            aux += 1

        if aux == 1:
            if ActionType.fLOOP.search(line):
                # nombre loop, linea
                cLOOPf.append([nLinea, ActionType.fLOOP.match(line).group().split()[-1]])
                # iLP.append(line[ActionType.ILOOP.match(line).end():])       # check

        nLinea += 1


        nLine = line

        Llen = 0
        if ActionType.BIN.search(line):
            for m in ActionType.BIN.finditer(line):
                Llen += 1

            contfunc = 0
            while contfunc < Llen:
                listA = []

                for n in ActionType.BIN.finditer(nLine):
                    listA.append(nLine[n.end():].split(" AN "))

                if Llen != 0 and listA != []:
                    print(listA[-1])

                    if len(listA[-1]) > 1:

                        nLine = (re.sub(TypeAction.BIN + listA[-1][0] + r"\s+AN\s+" + listA[-1][1], "funcionBinaria", nLine))

                contfunc += 1

            if "funcionBinaria" in lines:
                EXCEPTIONS.add(nLinea)




    '''



    posL = 0
    while posL < len(cLOOPf):
        c = 0
        for i in cLOOPi:
            if i[1] == cLOOPf[posL][1]:
                c += 1
        if c == 0:
            cLOOPf.remove(cLOOPf[posL])
            posL -= 1
        posL += 1


    cLOOPi.sort(reverse=True)
    for st in cLOOPi:

        tmp = [end for end in cLOOPf if end[0] > st[0]]

        if len(tmp) != 0:

            for may in tmp:
                print("m ", may, "st ", st)

                if may[1] == st[1]:
                    if may == tmp[0]:

                        inExp = st[0]
                        finExp = may[0]
                        fExp = [ft for ft in lines[st[0]+1:may[0]] if ActionType.ANY.search(ft)]

                        if fExp != []:
                            LPF.append(st)
                            LPF.append(may)

                    cLOOPf.remove(may)
                    break
                cLOOPf.remove(may)
    print(LPF)
'''

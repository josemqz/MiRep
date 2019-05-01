import re


class TypeAction:

    varType = r"[A-Za-z]+\w*\s*"
    vardicc1 = r"\s*I\s+HAS\s+A\s*"
    GIMMEH = r"\s*GIMMEH\s+"
    VISIBLE = r"\s*VISIBLE\s+"
    iLOOP = r"\s*IM\sIN\sYR\s*"
    fLOOP = r"\s*IM\sOUTTA\sYR\s*"
    MATH = r"\s*(PRODUKT|SUM|DIFF|QUOSHUNT|MOD|BIGGR|SMALLR)\sOF\s*"


class ActionType:

    VARDICC0 = re.compile(r"(" + TypeAction.vardicc1 + TypeAction.varType + ")")
    varDICC = re.compile(TypeAction.vardicc1)
    varDICC2 = re.compile(r"\s*ITZ\s*")
    varASS = re.compile(r"(" + TypeAction.varType + "R)")

    iLOOP = re.compile(r"(" + TypeAction.iLOOP + TypeAction.varType + r")")
    fLOOP = re.compile(r"(" + TypeAction.fLOOP + TypeAction.varType + r")")
    LOOP2 = re.compile(r"\s*(TIL|WILE)\s*")
    COUNT = re.compile(r"\s*(UPPIN|NERFIN)\sYR\s*")

    VISIBLE = re.compile(r"\s*VISIBLE\s + (" + TypeAction.vardicc1 + "|" + TypeAction.varType + ")")
    GIMMEH = re.compile(r"(\b" + TypeAction.GIMMEH + TypeAction.varType + r"\b)")
    NOT = re.compile(r"\s*NOT\s*")
    MATH = re.compile(TypeAction.MATH)

    HAI = re.compile(r"\bHAI\s*")
    KTHXBYE = re.compile(r"\bKTHXBYE\b")


colors = [

    '\033[94m',  # OPERATORS

    '\033[92m',  # START_END

    '\033[41m',  # FAIL

    '\033[0m',   # END

    '\033[95m',  # LOOPS

    '\033[30m',  # BLACK

    '\033[36m',  # CONDITIONALS

    '\033[93m',  # VARDICC

    '\033[31m',  # VARASS
    ]


def ColorHai(stripedLines):

    HAI_count = 0
    l_count = 0
    HaiLine = 0

    for line in stripedLines:
        if ActionType.HAI.match(line):
            HAI_count += 1
            HaiLine = l_count
        l_count += 1

    if HAI_count != 1:
        i = 0
        while i != HaiLine:
            stripedLines[i] = colors[2] + stripedLines[i] + colors[3]
            i += 1
    stripedLines[HaiLine] = colors[1] + stripedLines[HaiLine] + colors[3]   # coloreo hai


def ColorBye(stripedLines):

    BYE_count = 0
    ByeLine = 0
    L = len(stripedLines) - 1

    while L > 0:
        if ActionType.KTHXBYE.match(stripedLines[L]):
            BYE_count += 1
            ByeLine = L
        L -= 1

    if BYE_count != 1:
        i = len(stripedLines) - 1
        while i != ByeLine:
            stripedLines[i] = colors[2] + stripedLines[i] + colors[3]
            i -= 1
    stripedLines[ByeLine] = colors[1] + stripedLines[ByeLine] + colors[3]   # coloreo bye


file_a = input("Giv Neim\n")

with open(file_a, "r") as file_b:

    lines = file_b.readlines()

    stripedLines = [line.strip() for line in lines]

    index = 0

    EXCEPTIONS = set()

    nLinea = 0

    # cLOOPi = []    # loops -> (nombre, linea)
    # cLOOPf = []
    cLOOP = {}
    LPF = []    # Final -> para exceptions

    # iLP = []
    # fLP = []

    for line in stripedLines:
        '''
        x = []
        y = []

        [x.append(line[m.end():]) for m in ActionType.varDICC.finditer(line)]
        [y.append(line[m.end():]) for m in ActionType.varDICC2.finditer(line)]
        '''
        aux = 0
        for m in ActionType.iLOOP.finditer(line):
            aux += 1

        if aux == 1:
            if ActionType.iLOOP.search(line):
                # nombre loop, linea
                if ActionType.iLOOP.match(line).group().split()[-1] not in cLOOP:
                    cLOOP[ActionType.iLOOP.match(line).group().split()[-1]] = [nLinea]
                    # iLP.append(line[ActionType.iLOOP.match(line).end():])       # check
                else:
                    cLOOP[ActionType.iLOOP.match(line).group().split()[-1] + "N"] = [nLinea]

        aux = 0
        for m in ActionType.fLOOP.finditer(line):
            aux += 1

        if aux == 1:
            if ActionType.fLOOP.search(line):
                if ActionType.fLOOP.match(line).group().split()[-1] in cLOOP:
                    if len(cLOOP[ActionType.fLOOP.match(line).group().split()[-1]]) == 2:
                        cLOOP[ActionType.fLOOP.match(line).group().split()[-1] + "N"].append(nLinea)
                    else:
                        cLOOP[ActionType.fLOOP.match(line).group().split()[-1]].append(nLinea)
                        # fLP.append(line[ActionType.fLOOP.match(line).end():])       # check

        '''
        [EXCEPTIONS.add(stripedLines.index(line)) if len(y)!=0 and len(y) == len(x) and ActionType.VARDICC0.search(line) or ActionType.GIMMEH.search(line) and line not in EXCEPTIONS else "" ]
        #[EXCEPTIONS.append(stripedLines.index(line)) if ActionType.VARDICC0.search(line) and line not in EXCEPTIONS else "" ]
        #[EXCEPTIONS.append(stripedLines.index(line)) if ActionType.GIMMEH.search(line) and line not in EXCEPTIONS else "" ]
        [EXCEPTIONS.add(stripedLines.index(line)) if ActionType.iLOOP.search(line) and line not in EXCEPTIONS else "" ]
        [EXCEPTIONS.add(stripedLines.index(line)) if ActionType.fLOOP.search(line) and line not in EXCEPTIONS else "" ]
        '''
        nLinea += 1

    # cLOOP.sort(key=lambda tup: tup[0])
    print(cLOOP)
    print("last", list(cLOOP.keys())[-1])
    ###############################

    nLine = 0

    nCondI = 0
    nCondY = 0
    nCondN = 0
    nCondE = 0

    Icond = []
    Ycond = []
    Ncond = []
    Econd = []


    for line in lines:
        temp = line.strip()

        cont = 0
        for n in ActionType.SConditionals.finditer(temp):
            cont += 1
        if cont == 1:
            nCondI += 1
            if nLine not in Icond:
                Icond.append(nLine)


        cont = 0
        for n in ActionType.YConditionals.finditer(temp):
            cont += 1
        if cont == 1:
            nCondY += 1
            if nLine not in Ycond:
                Ycond.append(nLine)


        cont = 0
        for n in ActionType.NConditionals.finditer(temp):
            cont += 1
        if cont == 1:
            nCondN += 1
            if nLine not in Ncond:
                Ncond.append(nLine)


        cont = 0
        for n in ActionType.EConditionals.finditer(temp):
            cont += 1
        if cont == 1:
            nCondE += 1
            if nLine not in Econd:
                Econd.append(nLine)


        nLine += 1

    #########################################################
    lista_final = []

    print(Icond)
    print(Ycond)
    print(Ncond)
    print(Econd)

    Icond.sort(reverse=True)


    for ind in Icond:

        lista_cond = [ind]

        temp = [z for z in Ycond if z > ind]
        if len(temp) != 0:
            act = min(temp)
            lista_cond.append(act)
            Ycond.remove(act)


        temp = [z for z in Ncond if z > act]
        if len(temp) != 0:
            act = min(temp)
            lista_cond.append(act)
            Ncond.remove(act)

        temp = [z for z in Econd if z > act]
        if len(temp) != 0:
            act = min(temp)
            lista_cond.append(act)
            Econd.remove(act)

        if len(lista_cond) == 4:
            lista_final.append(lista_cond)
    ##########################################################
    for tupla in range(len(lista_final)):
        for i in range(4):
            print (lista_final[tupla][i])

    print ("revisar excepciones")

    '''
    newline = ""
    line = 0
    for line in range(len(lines)):
        if lines[line] not in EXCEPTIONS:
            newline = colors[2] + lines[line] + colors[3]
            lines[line] = newline

        else:
            print("はい、どもです")

    '''
    print("#######################")
    print(lista_final)

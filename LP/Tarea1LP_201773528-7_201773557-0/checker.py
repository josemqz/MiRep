import re

NOT_EXCEPTIONS = set()
EXCEPTIONS = set()      # conjunto de excepciones
START_LINE = 0          # comienzo codigo
END_LINE = 0            # fin codigo


# Clase de expresiones regulares

class TypeAction:

    varType = r"[A-Za-z]\w*"
    varTypHXC = r"(I\s+HAS\s+A\s+[A-Za-z]\w*)((\s+ITZ\s+)(\w*|\d*(\.|\d*)*)?)?\n"
    vardicc1 = r"(I\s+HAS\s+A\s+)"
    GIMMEH = r"\s*GIMMEH\s+"
    VISIBLE = r"\s*VISIBLE\s+"
    iLOOP = r"\s*IM\sIN\sYR\s+"
    fLOOP = r"\s*IM\sOUTTA\sYR\s+"
    LOOP2 = r"\s+(TIL|WILE)\s+"
    COUNT = r"\s+(UPPIN|NERFIN)\sYR\s+"
    COMPARISON = r"\s*(BOTH\s+SAEM|DIFFRINT)\s*"
    MATH = r"\s*(PRODUKT|SUM|DIFF|QUOSHUNT|MOD|BIGGR|SMALLR)\s+OF"
    SPECIALS = r"[^\w\s\.]"
    BIN = r"(PRODUKT|SUM|DIFF|QUOSHUNT|MOD|BIGGR|SMALLR|BOTH\sSAEM|DIFFRINT)\sOF\s+"

# Clase de expresiones regulares compiladas
class ActionType:

    R = re.compile(r"([A-Za-z]\w*|\d*(\.\d*)?)\s+R\s+((" + TypeAction.MATH + "\s+([A-Za-z]\w*|\d*(\.\d*)?)\s+AN\s+([A-Za-z]\w*|\d*(\.\d*)?))|([A-Za-z]\w*|\d*(\.\d*)))$")
    MATH = re.compile(r"^\s*"+TypeAction.MATH+"\s+([A-Za-z]\w*|\d*(\.\d*)?)\s+AN\s+([A-Za-z]\w*|\d*(\.\d*)?)$")
    COMPARISON = re.compile(TypeAction.COMPARISON + r"\s+([A-Za-z]\w*|\d*(\.\d*)?)\s+AN\s+([A-Za-z]\w*|\d*(\.\d*)?)")
    VARDICC0 = re.compile(TypeAction.varTypHXC)
    varDICC = re.compile(r"\s*I\s+HAS\s+A\s+[a-zA-Z]\w*\s+ITZ\s+"+ TypeAction.MATH + r"\s+([A-Za-z]\w*|\d*(\.\d*)?)\s+AN\s+([A-Za-z]\w*|\d*(\.\d*)?)")
    varDICC2 = re.compile(r"\s*I\s+HAS\s+A\s+[a-zA-Z]\w*\s+ITZ\s+([A-Za-z]\w*|\d*(\.\d*)?)$")
    varASS = re.compile(r"(" + TypeAction.varType + "R)")

    iLOOP = re.compile("(" + TypeAction.iLOOP + TypeAction.varType + TypeAction.COUNT + TypeAction.varType
                       + TypeAction.LOOP2 + r"(\w| )+)", re.X)
    fLOOP = re.compile(r"(" + TypeAction.fLOOP + TypeAction.varType + r")")
    LOOP2 = re.compile(r"\s*(TIL|WILE)\s*")
    COUNT = re.compile(r"\s*(UPPIN|NERFIN)\sYR\s*")

    VISIBLE = re.compile(TypeAction.VISIBLE + r"\w")
    GIMMEH = re.compile(r"(\b" + TypeAction.GIMMEH + TypeAction.varType + r"\b)")

    SConditionals = re.compile(r"O\s+RLY\?")
    YConditionals = re.compile(r"YA\s+RLY")
    NConditionals = re.compile(r"NO\s+WAI")
    EConditionals = re.compile(r"OIC")

    ANY = re.compile(r"\w*")
    BIN = re.compile(TypeAction.BIN)
    NOT = re.compile(r"\s*NOT\s+([A-Za-z]\w*|\d*\.*\d*)$")

    HAI = re.compile(r"\bHAI\s*")

    KTHXBYE = re.compile(r"\bKTHXBYE\b")


# Clase de expresiones regulares compiladas para ser usadas en el coloreo de las lineas -
class ActionType2:

    OPERATORS = re.compile(r'''(\bPRODUKT\b)|(\bSUM\b)|(\bDIFF\b)|
                           (\bQUOSHUNT\b)|(\bMOD\b)|(\bBIGGR\b)|(\bSMALLR\b)|
                           (\bOF\b)|(\bBOTH\b)|(\bEITHER\b)|(\bNOT\b)|
                           (\bSAEM\b)|(\bDIFFRNT\b)|(\bAN\b)''', re.X)

    LOOP = re.compile(r'(\bIM\b)|(\bIN\b)|(\bYR\b)|(\bOUTTA\b)')

    LOOPS = re.compile(r"(\bTIL\b)|(\bWILE\b)")

    COUNT = re.compile(r"(\bUPPIN\b)|(\bNERFIN\b)")

    VARASS = re.compile(r"(\bGIMMEH\b)|(\bVISIBLE\b)|(\bR\b)")

    VARDICC = re.compile(r'(\bI\b)|(\bHAS\b)|(\bA\b)|(\bITZ\b)')

    CONDITIONALS = re.compile(r'''(\bO\s+RLY\?)|(\bYA\s+RLY\b)|
                              (\bNO\s+WAI\b)|(\bOIC\b)''', re.X)

    START_END = re.compile(r'(\bHAI\b)|(\bKTHXBYE\b)')

#lista con los colores a utilizar
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


'''
*   funcion ColorHai
******
*   descripcion
******
*   Input:
*       Lista de lineas
******
*   Returns:
*       nada, colorea correctamente hasta la linea del ultimo HAI que encuentra
'''
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
    stripedLines[HaiLine] = colors[1] + stripedLines[HaiLine] + colors[3]
    EXCEPTIONS.add(HaiLine)


'''
*   funcion ColorBye
******
*   descripcion
******
*   Input:
*       Lista de lineas
******
*   Returns:
*       nada, colorea correctamente hasta la linea del ultimo KTHXBYE que encuentra
'''
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
    stripedLines[ByeLine] = colors[1] + stripedLines[ByeLine] + colors[3]
    EXCEPTIONS.add(ByeLine)
    END_LINE = ByeLine


file_a = input("GIMMEH A FILE ( ° ͜ʖ °)\n")

'''
*   main
*   se trabaja el archivo por secciones, para facilitar el coloreo se crea una lista de indices de linea, los cuales son las exclusiones
*   al coloreo correcto. Se trabaja pintando correctamente la mayor cantidad de lineas bien escritas para luego pintar con rojo las que no
*   pertenezcan a la lista de exclusiones.
'''
with open(file_a, "r") as file_b:

    lines = file_b.readlines()

    index = 0

    '''
    *   Primera parte:
    *       se trabaja con operadores binarios que tengan una expresion basica
    *       cada match, se mete en la lista de exclusiones
    '''
    for line in lines:

        if not re.search(TypeAction.SPECIALS, line):
            temp = line.strip()

            if ActionType.VARDICC0.match(line):
                EXCEPTIONS.add(index)

            elif ActionType.GIMMEH.match(line):
                EXCEPTIONS.add(index)

            elif ActionType.varDICC2.match(line):
                EXCEPTIONS.add(index)
            elif ActionType.varDICC.match(line):
                EXCEPTIONS.add(index)

            elif ActionType.MATH.match(line):
                EXCEPTIONS.add(index)

            elif ActionType.NOT.match(line):
                EXCEPTIONS.add(index)

            elif ActionType.COMPARISON.match(line):
                EXCEPTIONS.add(index)

            elif ActionType.R.match(line):
                EXCEPTIONS.add(index)
            elif ActionType.VISIBLE.match(line):
                EXCEPTIONS.add(index)

        index += 1

    ############################## LOOPS #######################
    stripedLines = [x.strip() for x in lines]

    '''
    *   Segunda parte:
    *       Se trabaja con las listas lpf (lista de excusion final de loops), cLOOPi y cLOOPf   (contienen los nombres y numero de linea de cada loop)
    *       esto se hace para comparar los ciclos habiertos mas cercanos y verificar si se cierran corectamente
    '''
    nLinea = 0

    cLOOPi = []    # loops -> (nombre, linea)
    cLOOPf = []

    LPF = []    # Final -> para exceptions

    for line in stripedLines:

        aux = 0

        for m in ActionType.iLOOP.finditer(line):
            aux += 1

        if aux == 1:
            if ActionType.iLOOP.search(line):
                # nombre loop, linea
                cLOOPi.append([nLinea, ActionType.iLOOP.match(line).group().split()[3]])

        aux = 0
        for m in ActionType.fLOOP.finditer(line):
            aux += 1

        if aux == 1:
            if ActionType.fLOOP.search(line):
                # nombre loop, linea
                cLOOPf.append([nLinea, ActionType.fLOOP.match(line).group().split()[-1]])


        '''
        *   parte 2.5 :
        *      se encarga de capturar la mayor cantidad de expresiones anidadas en la misma linea lo mejor posible
        '''

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

                    if len(listA[-1]) > 1:

                        nLine = (re.sub(TypeAction.BIN + listA[-1][0] + r"\s+AN\s+" + listA[-1][1], "funcionBinaria", nLine))

                contfunc += 1

        if "funcionBinaria" in line:
            EXCEPTIONS.add(nLinea)

        nLinea += 1


    #************************
    ###################################     fin parte2.5
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

                if may[1] == st[1]:
                    if may == tmp[0]:

                        inExp = st[0]
                        finExp = may[0]
                        fExp = [ft for ft in lines[st[0]+1:may[0]] if ActionType.ANY.search(ft)]

                        if fExp != []:
                            LPF.append(st[0])
                            LPF.append(may[0])

                    cLOOPf.remove(may)
                    break
                cLOOPf.remove(may)

#########
    [EXCEPTIONS.add(i) for i in LPF]


    ############################################################

    ############################### CONDITIONALS ###############

    '''
    *   Tercera parte:
    *       Se trabajan los condicionales de manera similar a los loops, comparando si se encuentran completos
    *       si se encuentran mal situados, el codigo se encargara de no introducirlos en la lista de exclusiones
    *
    '''
    nCondI = 0
    nCondY = 0
    nCondN = 0
    nCondE = 0

    Icond = []
    Ycond = []
    Ncond = []
    Econd = []

    nLine = 0

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

    ##################### COLOR #######################
    '''
    *   Cuarta parte:
    *       se colorea el archivo sin importar los errores
    '''
    for tupla in range(len(lista_final)):
        for i in range(4):
            EXCEPTIONS.add(lista_final[tupla][i])


    newline = ""
    line = 0

    file_lines = [line.strip() for line in lines]

    ColorHai(file_lines)
    ColorBye(file_lines)

    filee = "\n".join(file_lines)
    out = ""
    temp = ""
    i = 0

    for m in ActionType2.START_END.finditer(filee):
        out += "".join((filee[i:m.start()], colors[1], filee[m.start():m.end()], colors[3]))
        i = m.end()
    if out != "":
        temp = "".join((out,filee[m.end():]))
    else:
        temp = filee
    out = ""
    i = 0

    for m in ActionType2.VARDICC.finditer(temp):

        out += "".join((temp[i:m.start()], colors[7], temp[m.start():m.end()], colors[3]))
        i = m.end()
    if out != "":
        temp = "".join((out,temp[m.end():]))
    out = ""

    i = 0

    for m in ActionType2.VARASS.finditer(temp):

        out += "".join((temp[i:m.start()], colors[8], temp[m.start():m.end()], colors[3]))
        i = m.end()
    if out != "":
        temp = "".join((out,temp[m.end():]))
    out = ""

    i = 0

    for m in ActionType2.LOOP.finditer(temp):

        out += "".join( (temp[i:m.start()], colors[4], temp[m.start():m.end()], colors[3]))
        i = m.end()
    if out != "":
        temp = "".join((out,temp[m.end():]))
    out = ""

    i = 0

    for m in ActionType2.LOOPS.finditer(temp):

        out += "".join((temp[i:m.start()], colors[4], temp[m.start():m.end()], colors[3]))
        i = m.end()
    if out != "":
        temp = "".join((out,temp[m.end():]))
    out = ""

    i = 0

    for m in ActionType2.COUNT.finditer(temp):

        out += "".join((temp[i:m.start()], colors[4], temp[m.start():m.end()], colors[3]))
        i = m.end()
    if out != "":
        temp = "".join((out,temp[m.end():]))
    out = ""

    i = 0

    for m in ActionType2.OPERATORS.finditer(temp):
        out += "".join((temp[i:m.start()], colors[0] , temp[m.start():m.end()], colors[3]))
        i = m.end()
    if out != "":
        temp = "".join((out,temp[m.end():]))

    out = ""
    i = 0
    for m in ActionType2.CONDITIONALS.finditer(temp):
            out += "".join((temp[i:m.start()], colors[6], temp[m.start():m.end()], colors[3]))
            i = m.end()
    if out != "":
        temp = "".join((out,temp[m.end():]))


    lines2 = temp.split('\n')

    ##########################################################
    ##################### COLOREO CON rojo  ###################

    '''
    *   Quinta parte:
    *       se colorean con rojo las lineas que no esten en la lista de exclusiones
    '''

    for line in range(len(lines)):

        if line not in EXCEPTIONS and lines[line]!= '\n' :

            newline = colors[2] + lines[line].strip() + colors[3]
            lines2[line] = newline

    print("\n".join(lines2))
    print("LISTA EXCEPCIONES:\t",EXCEPTIONS)

    ###############################################################################

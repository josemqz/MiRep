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


colors = [

    '\033[94m',  # OPERATORS

    '\033[92m',  # START_END

    '\033[41m',   # FAIL

    '\033[0m',  # END

    '\033[95m',  # LOOPS

    '\033[30m',  # BLACK

    '\033[36m',  # CONDITIONALS

    '\033[93m',  # VARDICC

    '\033[31m',  # VARASS
]


nameFile = input("File name :D \n")

with open(nameFile, 'r') as f:

    lines = f.readlines()
    out = ""
    temp = ""
    x = ""

    cl = 0
    for lin in lines:
        if lin != "\n":
            Hai = cl
            break
        cl += 1

    if lines[cl].strip() != 'HAI':
        for match in lines:
            if match == "\n":
                print("YO")
            print(colors[2] + match.strip() + colors[3])

            """
    if lines[0].strip() != 'HAI':
        for match in lines:
            print(colors[2] + match.strip() + colors[3])
            """

    elif lines[-1].strip() != 'KTHXBYE':
        for match in lines:
            print(colors[2] + match.strip() + colors[3])

    else:
        # len_file = len(lines)
        # LSyntax = lines
        i = 0
        filee = "".join(lines)

        # print(filee.replace("\n", ""))
        # print(repr(filee))

        for m in ActionType.START_END.finditer(filee):
            out += "".join((filee[i:m.start()], colors[1], filee[m.start():m.end()], colors[3]))
            i = m.end()

        if out != "":
            temp = "".join((out, temp[m.end():]))
        out = ""

        i = 0

        for m in ActionType.VARDICC.finditer(temp):
            out += "".join((temp[i:m.start()], colors[7], temp[m.start():m.end()], colors[3]))
            i = m.end()

        if out != "":
            temp = "".join((out, temp[m.end():]))
        out = ""

        i = 0

        for m in ActionType.VARASS.finditer(temp):
            out += "".join((temp[i:m.start()], colors[8], temp[m.start():m.end()], colors[3]))
            i = m.end()

        if out != "":
            temp = "".join((out, temp[m.end():]))
        out = ""

        i = 0

        for m in ActionType.LOOP.finditer(temp):
            out += "".join((temp[i:m.start()], colors[4], temp[m.start():m.end()], colors[3]))
            i = m.end()

        if out != "":
            temp = "".join((out,  temp[m.end():]))
        out = ""

        i = 0

        for m in ActionType.LOOPS.finditer(temp):
            out += "".join((temp[i:m.start()], colors[4], temp[m.start():m.end()], colors[3]))
            i = m.end()

        if out != "":
            temp = "".join((out, temp[m.end():]))
        out = ""

        i = 0

        for m in ActionType.COUNT.finditer(temp):
            out += "".join((temp[i:m.start()], colors[4], temp[m.start():m.end()], colors[3]))
            i = m.end()

        if out != "":
            temp = "".join((out, temp[m.end():]))
        out = ""

        i = 0

        for m in ActionType.OPERATORS.finditer(temp):
            out += "".join((temp[i:m.start()], colors[0], temp[m.start():m.end()], colors[3]))
            i = m.end()

        if out != "":
            temp = "".join((out, temp[m.end():]))
        out = ""

        i = 0

        for m in ActionType.CONDITIONALS.finditer(temp):
                out += "".join((temp[i:m.start()], colors[6], temp[m.start():m.end()], colors[3]))
                i = m.end()

        if out != "":
            temp = "".join((out, temp[m.end():]))

        print(temp)

        '''
        aux = 0
        for m in ActionType.iLOOP.finditer(line):
            aux += 1

        if aux == 1:
            if ActionType.iLOOP.search(line):
                # nombre loop, linea
                cLOOP.insert(0, (nLinea, ActionType.iLOOP.match(line).group().split()[-1], "i"))
                iLP.append(line[ActionType.iLOOP.match(line).end():])       # check

        aux = 0
        for m in ActionType.fLOOP.finditer(line):
            aux += 1

        if aux == 1:
            if ActionType.fLOOP.search(line):
                cLOOP.insert(0, (nLinea, ActionType.fLOOP.match(line).group().split()[-1], "f"))
                fLP.append(line[ActionType.fLOOP.match(line).end():])       # check
        '''

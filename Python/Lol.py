"""Tarea 1."""
import re


class regexx():
    """expresiones regulares -_-."""

    varT = r"^[A-Z|a-z][A-Z|a-z|\d]*$"
    dec = r"^I HAS A $" + varT
    fin = re.compile(r"^HAI\\n$" + """code""" + r"^\\nKTHXBYE$")


"""
variable terminal -> ([A-Z|a-z][A-Z|a-z|\d]*)

(match con re.IGNORECASE) - ([A-Z]+[A-Z|\d]*)

inicio - "HAI"+ \d
fin - "KTHXBYE"

declaracion -> "I HAS A"+
inicializacion -> "ITZ"+
asignacion -> + "R" + func

suma - "SUM OF"+ func +"AN"+ func
resta - "DIFF OF"+ func +"AN"+ func
multiplicacion - "PRODUKT OF"+ func +"AN"+ func
division - "QUOSHUNT OF"+ func +"AN"+ func
modulo - "MOD OF"+ func +"AN"+ func

mayor - "BIGGR OF"+ x +"AN"+ x
menor - "SMALLR OF"+ x +"AN"+ x

AND - "BOTH OF"+ x +"AN"+ x
OR - "EITHER OF"+ x +"AN"+ x
NOT - "NOT"+ x

igualdad - "BOTH SAEM"+ x +"AN"+ x
diferencia - "DIFFRINT"+ x +"AN"+ x

condicion - exp"\nORLY?"
if - "YA RLY\n"+
else - "NO WAI\n"+
fin condicion - "OIC"

until - "TIL" +
while - "WILE" +

"IM IN YR"+ x+ ("UPPIN"|"NERFIN")+ "YR"+ x'+ (until|while)+"\n"+cod+"\n
IM OUTTA YR"+ x

entrada - "GIMMEH" +
salida - "VISIBLE" +

exp - (mayor|menor|igualdad|diferencia)
func - (suma|resta|multiplicacion|division|modulo|not|var|func)
"""

varT = r"[A-Z|a-z][A-Z|a-z|\d]*"
dec = r"I HAS A "+varT

inicio = r"HAI+ [\d].[\d]"
fin = "KTHXBYE"


L = open("bla.lol", "r")
for l in L:
    print(l)
    # print(re.search(varT, L[0]).group(0))
L.close()

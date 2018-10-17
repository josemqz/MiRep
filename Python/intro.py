from supercardclass import Card, Webcam, Detection
webcam = Webcam()
detection = Detection()

def foto(l):
	while len(mano) < 5:
		image = webcam.read_image()
		for i in l:
			if detection.is_card_detected_in_image(i[0], image):
				conf = raw_input("Esta es su carta? (Yep/Nop)")
				if conf == "Yep":
	        		mano.add(i[1])
	        		break

mano = set()

AC = (Card("01_C.xml",1, True, None, None, None, 'C.xml', 4, 1), "01_C")	#FALTA MODIFICAR
dC = (Card("02_C.xml",1, True, None, None, None, 'C.xml', 4, 2), "02_C")	#FALTA MODIFICAR
TC = (Card("03_C.xml",1, True, None, None, None, 'C.xml', 4, 3), "03_C")	#FALTA MODIFICAR
cC = (Card("04_C.xml",1, True, None, None, None, 'C.xml', 4, 4), "04_C")	#FALTA MODIFICAR
CC = (Card("05_C.xml",1, True, None, None, None, 'C.xml', 4, 5), "05_C")	#FALTA MODIFICAR
sC = (Card("06_C.xml",1, True, None, None, None, 'C.xml', 4, 6), "06_C")	#FALTA MODIFICAR
SC = (Card("07_C.xml",1, True, None, None, None, 'C.xml', 4, 7), "07_C")		#FALTA MODIFICAR
OC = (Card("08_C.xml",1, True, None, None, None, 'C.xml', 4, 8), "08_C")		#FALTA MODIFICAR
NC = (Card("09_C.xml",1, True, None, None, None, 'Cm.xml', 4, 1), "09_C")		#FALTA MODIFICAR
DC = (Card("10_C.xml",1, True, None, None, None, 'Cm.xml', 4, 1), "10_C")		#FALTA MODIFICAR
JC = (Card("11_C.xml",1, True, None, None, None, 'Cm.xml', 4, 1), "11_C")		#FALTA MODIFICAR
QC = (Card("12_C.xml",1, True, None, None, None, 'Cm.xml', 4, 1), "12_C")		#FALTA MODIFICAR
KC = (Card("13_C.xml",1, True, None, None, None, 'Cm.xml', 4, 1), "13_C")		#FALTA MODIFICAR
AD = (Card("01_D.xml",1, True, None, None, None, 'D.xml', 4, 1), "01_D")		#FALTA MODIFICAR
dD = (Card("02_D.xml",1, True, None, None, None, 'D.xml', 4, 2), "02_D")		#FALTA MODIFICAR
TD = (Card("03_D.xml",1, True, None, None, None, 'D.xml', 4, 3), "03_D")		#FALTA MODIFICAR
cD = (Card("04_D.xml",1, True, None, None, None, 'D.xml', 4, 4), "04_D")		#FALTA MODIFICAR#FALTA MODIFICAR#FALTA MODIFICAR
CD = (Card("05_D.xml",1, True, None, None, None, 'D.xml', 4, 5), "05_D")		#FALTA MODIFICAR#FALTA MODIFICAR#FALTA MODIFICAR#FALTA MODIFICAR
sD = (Card("06_D.xml",1, True, None, None, None, 'D.xml', 4, 6), "06_D")		#FALTA MODIFICAR
SD = (Card("07_D.xml",1, True, None, None, None, 'D.xml', 4, 7), "07_D")		#FALTA MODIF#FALTA MODIFICARICAR
OD = (Card("08_D.xml",1, True, None, None, None, 'D.xml', 4, 8), "08_D")		#FALTA MODIFICAR
ND = (Card("09_D.xml",1, True, None, None, None, 'Dm.xml', 4, 1), "09_D")		#FALTA MODIFICAR
DD = (Card("10_D.xml",1, True, None, None, None, 'Dm.xml', 4, 1), "10_D")		#FALTA MODIFICAR
JD = (Card("11_D.xml",1, True, None, None, None, 'Dm.xml', 4, 1), "11_D")		#FALTA MODIFICAR#FALTA MODIFICAR
QD = (Card("12_D.xml",1, True, None, None, None, 'Dm.xml', 4, 1), "12_D")		#FALTA MODIFICAR
KD = (Card("13_D.xml",1, True, None, None, None, 'Dm.xml', 4, 1), "13_D")		#FALTA MODIFICAR
AP = (Card("01_P.xml",1, False, None, None, None, 'P.xml', 4, 1), "01_P")		#FALTA MODIFICAR
dP = (Card("02_P.xml",1, False, None, None, None, 'P.xml', 4, 2), "02_P")		#FALTA MODIFICAR
TP = (Card("03_P.xml",1, False, None, None, None, 'P.xml', 4, 3), "03_P")		#FALTA MODIFICAR
cP = (Card("04_P.xml",1, False, None, None, None, 'P.xml', 4, 4), "04_P")		#FALTA MODIFICAR
CP = (Card("05_P.xml",1, False, None, None, None, 'P.xml', 4, 5), "05_P")		#FALTA MODIFICAR
sP = (Card("06_P.xml",1, False, None, None, None, 'P.xml', 4, 6), "06_P")		#FALTA MODIFICAR
SP = (Card("07_P.xml",1, False, None, None, None, 'P.xml', 4, 7), "07_P")		#FALTA MODIFICAR
OP = (Card("08_P.xml",1, False, None, None, None, 'P.xml', 4, 8), "08_P")		#FALTA MODIFICAR
NP = (Card("09_P.xml",1, False, None, None, None, 'Pm.xml', 4, 1), "09_P")		#FALTA MODIFICAR
DP = (Card("10_P.xml",1, False, None, None, None, 'Pm.xml', 4, 1), "10_P")		#FALTA MODIFICAR
JP = (Card("11_P.xml",1, False, None, None, None, 'Pm.xml', 4, 1), "11_P")		#FALTA MODIFICAR
QP = (Card("12_P.xml",1, False, None, None, None, 'Pm.xml', 4, 1), "12_P")		#FALTA MODIFICAR
KP = (Card("13_P.xml",1, False, None, None, None, 'Pm.xml', 4, 1), "13_P")		#FALTA MODIFICAR
AT = (Card("01_T.xml",1, False, None, None, None, 'T.xml', 4, 1), "01_T")		#FALTA MODIFICAR
dT = (Card("02_T.xml",1, False, None, None, None, 'T.xml', 4, 2), "02_T")		#FALTA MODIFICAR
TT = (Card("03_T.xml",1, False, None, None, None, 'T.xml', 4, 3), "03_T")		#FALTA MODIFICAR
cT = (Card("04_T.xml",1, False, None, None, None, 'T.xml', 4, 4), "04_T")		#FALTA MODIFICAR
CT = (Card("05_T.xml",1, False, None, None, None, 'T.xml', 4, 5), "05_T")		#FALTA MODIFICAR
sT = (Card("06_T.xml",1, False, None, None, None, 'T.xml', 4, 6), "06_T")		#FALTA MODIFICAR
ST = (Card("07_T.xml",1, False, None, None, None, 'T.xml', 4, 7), "07_T")		#FALTA MODIFICAR
OT = (Card("08_T.xml",1, False, None, None, None, 'T.xml', 4, 8), "08_T")		#FALTA MODIFICAR
NT = (Card("09_T.xml",1, False, None, None, None, 'Tm.xml', 4, 1), "09_T")		#FALTA MODIFICAR
DT = (Card("10_T.xml",1, False, None, None, None, 'Tm.xml', 4, 1), "10_T")		#FALTA MODIFICAR
JT = (Card("11_T.xml",1, False, None, None, None, 'Tm.xml', 4, 1), "11_T")		#FALTA MODIFICAR
QT = (Card("12_T.xml",1, False, None, None, None, 'Tm.xml', 4, 1), "12_T")		#FALTA MODIFICAR
KT = (Card("13_T.xml",1, False, None, None, None, 'Tm.xml', 4, 1), "13_T")

x = [AC,dC,TC,cC,CC,sC,SC,OC,NC,DC,JC,QC,KC,
	AD,dD,TD,cD,CD,sD,SD,OD,ND,DD,JD,QD,KD,
	AP,dP,TP,cP,CP,sP,SP,OP,NP,DP,JP,QP,KP,
	AT,dT,TT,cT,CT,sT,ST,OT,NT,DT,JT,QT,KT]

foto(x)
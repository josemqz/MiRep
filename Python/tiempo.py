s = "18:47:30"
print float(s[0:2]) + (float(s[3:5]))/100
y = ["18:47:30","18:48:30","18:49:30"]
x = []
for t in y:
		x.append(float(t[0:2]) + (float(t[3:5]))/100)
print x

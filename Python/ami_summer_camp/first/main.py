__author__ = 'Sergey Ivanychev'

s = input()
list = s.split()
l = len(list)
sum = 0
for i in range(l):
	sum += int(list[i])
med = sum/l
num = 0
raz = abs(med - int(list[0]))

for i in range(l):
	if (raz > (abs(int(list[i]) - med))):
		raz = abs(int(list[i]) - med)
		num = i
print(list[num])

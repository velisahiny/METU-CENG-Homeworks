import sys

err = 0.15

with open(sys.argv[1]) as f:
    content = f.readlines()

outasst =  content[0].split(' ')[2:-1]


with open(sys.argv[2]) as f:
    content2 = f.readlines()

outstu = content2[0].split(' ')[2:-1]

counter = 0

for i in range(0,len(outasst)):
	a = float(outasst[i])
	s = float(outstu[i])
	if s>=a*(1-err) and s<=a*(1+err):
		counter+=1

print counter == len(outasst)

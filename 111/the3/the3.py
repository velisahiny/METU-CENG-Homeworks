import random
from time import time
qqqq=time()
def hyphenate_(word):
	pivot = 0
        word1 = list(word)
	
	if word1[pivot] in ["a","e","i","o","u","A","E","I","O","U"]:
		pivot += 1
		if pivot > len(word1)-1: return word1
		elif word1[pivot] in ["a","e","i","o","u","A","E","I","O","U"]:				
			word1.insert(pivot,"-")
			pivot+=1
			return word1[:pivot] + hyphenate_(word1[pivot:])
		elif pivot == len(word1)-1:
			return word1	
		else:	
			pivot += 1
			if word1[pivot] in ["a","e","i","o","u","A","E","I","O","U"]:
				word1.insert(pivot-1,"-")
				pivot -= 1
				return word1[:pivot]+hyphenate_(word1[pivot:])
		 	else:
				while pivot != len(word)-1:	
					pivot +=1
					if word1[pivot] in ["a","e","i","o","u","A","E","I","O","U"]:
						word1.insert(pivot-1,"-")
						pivot -= 1
					else:continue
					return word1[:pivot+1]+hyphenate_(word[pivot:])	
				else: return word1		
	else :
		if pivot == len(word)-1:
			return word1
		else :
			pivot += 1
			return  word1[:pivot]+hyphenate_(word1[pivot:])		
	return word1
def hyphenate(s):
	res=hyphenate_(s)
	res_=''.join(res)
	res=res_.split('-')
	return res		




def index_finder(string,liste):
	x = 0
	indeksler=[]	
	while x < len(liste) :
		if string in liste[x:]:
			indeksler.append(liste[x:].index(string)+x)
			x =liste[x:].index(string)+x+1
		else: x +=1
		
	return indeksler
"""print index_finder("ve",['ve', 'li', ' ', 'to', 'pu', ' ', 'tut', '.', 'ay', 'se', ' ', 'ip', ' ', 'at', 'la', '.', 've', 'li', ' ', 'to', 'pu', ' ', 'tut', '.', 'ay', 'se', ' ', 'ip', 'at', 'la', '.'])"""

def counter(string,liste):
	count=[]
	indexer = index_finder(string,liste)
	#print indexer
	for i in range(len(indexer)):
		count.append(liste[indexer[i]+1])
	#print count
	dic= {}
	for i in count:		
		dic[i] =count.count(i)
	#print dic
	largestn = 0
	secondlargestn = 0
	largest={}		
	second_largest = {}
	for  i in count:		
		if dic[i] > largestn:
			secondlargestn = largestn
			second_largest.clear()
			second_largest.update(largest)			
			largestn = dic[i]
			largest.clear()
			largest[i] = largestn
	#		print largest
	#		print second_largest
	#		print "1"
		elif dic[i] > secondlargestn and dic[i] < largestn:
			secondlargestn = dic[i]
			second_largest.clear()
			second_largest[i] = secondlargestn			
	#		print second_largest	
	#		print "2"
	largest.update(second_largest)	
	return largest


def dicter(liste):
	dicindic = {}	
	for i in liste:
		if i == ".":
			continue 
		elif not dicindic.has_key(i):	
			dicindic[i] = counter(i,liste)		
	return dicindic
	


"""execute"""

def execute():
	x=''
	liste = []
	hece = []
	hece1= []
	hecele=[]
	hecele2=[]
	mapped=[]
	res=[]
	result=[]
	b=0
	import random
	while x != "=":
		x=raw_input()
		if x == "=": break
		liste.append(x)
	n_and_m = liste.pop(0)
	nandm = n_and_m.split(" ")
	nword = int(nandm[0])
	mchar= int(nandm[1])
	for i in liste:	
		hece.append(i.split(" "))
	#print hece
	 	
	for i in hece:
		r = range(len(i)) 		
		for a in r :		
			i.insert(2*a+1," ")
	hece.insert(0," ")
	#print hece
	for t in hece:
		for a in t:
			hecele.append(a)
	#print hecele
	for i in hecele:
		hecele2.append(i.split("."))
	#print hecele2
	for i in hecele2:
		if len(i) == 2:
			i.insert(1,".")
			if i[2] == "":
				i.pop()
	#print hecele2
	for i in hecele2:
		for j in i:
			res.append(j)
	#print res
	while b < len(res):
		
		if res[b]== ".":
			if b+1< len(res):
				if res[b+1] == " " :
					del res[b+1]
			b+=1
		else : 
			b+=1 
	mapped = map(hyphenate,res)
	#print mapped
	for i in mapped:
		for x in i:
			result.append(x)
	#print result
	noktavebosluk = []
	noktai = index_finder(".",result)
	bosluki = index_finder(" ",result)
	#print noktai
	#print bosluki
		
	for i in noktai:
		if i < len(result) -1:
			noktavebosluk.append(result[i+1])
	for i in bosluki:
		if i < len(result)-1:
			noktavebosluk.append(result[i+1])
	#print noktavebosluk
        dicindic=dicter(result)
	#print dicindic
	output =" "
	a = random.choice(noktavebosluk)
	output = a
	#print output
	#print noktavebosluk
	#print dicindic
	while True: 
		
		if a  == ".":
			a = random.choice(noktavebosluk)
			output = output + a
		else:	
			a = random.choice(list(dicindic[a]))
			output = output +a
		if len(output) == mchar or (len(output.split(" ")) + list(output).count(".")) == nword:break
	print output

#print hyphenate("afyonkarahisarlIlaStIramadIklarImIzdansInIzcasIna")

execute()
print time()-qqqq	

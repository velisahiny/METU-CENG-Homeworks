def query(liste,tuples):
	dic = {}
	for i in tuples:

		dic[i[0]] =i[1]
	if type(liste) == str:
		return liste
	if helper(liste,dic) :
		return query(liste[1],tuples)
	else:
		return query(liste[2],tuples)
def returner(dic,key):
	if dic.has_key(key):
		return dic[key]
	else:
		return key
def helper(liste,dic):
	if liste == True: return True
	elif liste == False: return False
	elif liste == []:
		return False
	elif len(liste) == 1:
		return True
	elif type(liste[0]) == list:
		liste1 = liste[0]
	else:
		liste1 = liste 
	if liste1[0] == "==":
		return returner(dic,liste1[1]) == returner(dic,liste1[2])		
	elif liste1[0] == "!=":		
		return returner(dic,liste1[1]) != returner(dic,liste1[2])
	elif liste1[0] == ">":
		return returner(dic,liste1[1]) > returner(dic,liste1[2])
	elif liste1[0] == "<":	
		return returner(dic,liste1[1]) < returner(dic,liste1[2])
	elif liste1[0] == "in":	
		return returner(dic,liste1[1]) in liste1[2]
	elif liste1[0] == "and":
		for i in liste1[1:]:
			if helper(i,dic) == False:	
				return False
		return True	
	elif liste1[0] == "or":	
		for i in liste1[1:]:
			if helper(i,dic) :
				return True
		return False
	elif liste1[0] == "not":	
		return  not helper(liste1[1],dic)




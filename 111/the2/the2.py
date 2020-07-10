 
sum = 0
ID = raw_input()
def question_true(ID):
	
	
	for n in range(6):
		if ID[n] != '?':
			if n != 5:
				continue
				 
			else :
				return False
					
		elif ID[n] == '?':
			return True
			
			break
def first_six_digit(ID):
	for n in  (0,2,4):
		if ID[n] == "?":
			deger1 = ID.index('?')
			ID = ID.replace("?","0") 
			sum = int(ID[0])+int(ID[2])+int(ID[4])
				
			for m in (1,3,5):
		
				if int(ID[m]) * 2 >= 10 :
					a = int(ID[m]) *2
					a = str(a)
			
		
					sum = sum+ int(a[0]) + int(a[1]) 	
			 
				else :
					sum = sum + int(ID[m])*2
			
			answer = (10 - (sum + int(ID[7]))%10)%10 
			a = list(ID)
			a[deger1] = str(answer)
			ID = ''.join(a)			
					
			print ID
		else :
			continue	
	for n in (1,3,5):
		if ID[n] == "?":
			deger2 = ID.index("?")
			ID = ID.replace("?","0")
			sum = int(ID[0]) + int(ID[2]) + int(ID[4])
				
			
			for m in (1,3,5):
		
				if int(ID[m]) * 2 >= 10 :
					a = int(ID[m]) * 2
					a = str(a)
			
		
					sum = sum + int(a[0]) + int(a[1]) 	
			
				else :
					sum = sum + int(ID[m]) * 2
			
			before_answer = (10 -(int(ID[7]) + sum) % 10)%10
			
			if before_answer % 2 == 0:
				a = list(ID)
				b = before_answer / 2
				a[deger2] =  str(b)
				ID = ''.join(a)
				print ID
		 	else :
				answer2 = (before_answer + 9) / 2
				a = list(ID)
				a[deger2] = str(answer2)
				ID = ''.join(a)
				print ID
	
if question_true(ID) is True: 
	
	first_six_digit(ID)
else :
	sum = int(ID[0])+int(ID[2])+int(ID[4])		
	   
	for n in (1,3,5):
	
		if int(ID[n])*2 >= 10 :
			a = int(ID[n]) *2
			     		
			a = str(a)
			
			b = int(a[0]) + int(a[1]) 
			
			sum = sum + b
					
		else :
			sum = sum + int(ID[n])*2
			
	
		check_digit = (10 - (sum % 10))%10
		

	if str(check_digit) == (ID[7]):
		print "VALID" 	
	elif ID[7] == "?":
		
		print ID[:7] + str(check_digit) 
	else : 
		print "INVALID"	

	
	



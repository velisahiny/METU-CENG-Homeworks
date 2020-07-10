for i in $(ls outputs/); do
	  a=$(python readout.py gt_outputs/$i outputs/$i 2> /dev/null | grep -i true) ;  
	  if [ "$a" = "True" ] 
	  then  
		echo -en "1 " 
	  else
		echo -en "0 " 
	  fi 	 
done 
echo 


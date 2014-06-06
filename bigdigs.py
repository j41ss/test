#!/usr/bin/python
import sys

Zero= [" **** ",
       " *  * ",
       " *  * ",
       " *  * ",
       " *  * ",
       " *  * ",
       " **** "]
One= [ " ***  ",
       "   *  ",
       "   *  ",
       "   *  ",
       "   *  ",
       "   *  ",
       " **** "]
Two= [ " **** ",
       " *  * ",
       "    * ",
       "   *  ",
       "  *   ",
       " *    ",
       " **** "]
Three=[" **** ",
       "    * ",
       "    * ",
       "  *** ",
       "    * ",
       "    * ",
       " **** "]
Four=[ " *  * ",
       " *  * ",	
       " *  * ",
       " **** ",
       "    * ",
       "    * ",
       "    * "]
Five=[ " **** ",
       " *    ",		
       " *    ",		
       " **** ",		
       "    * ",		
       "    * ",		
       " **** "]
Six=[  " **** ",
       " *    ",
       " *    ",
       " **** ",
       " *  * ",
       " *  * ",
       " **** "]
Seven=[" **** ",
       "    * ",
       "   *  ",
       "  *   ",
       "  *   ",
       "  *   ",
       " ***  "]
Eith=[ " **** ",
       " *  * ",
       " *  * ",
       " **** ",
       " *  * ",
       " *  * ",
       " **** " ]
Nine=[ " **** ",
       " *  * ",
       " *  * ",
       " **** ",
       "    * ",
       "    * ",
       " **** "]
def fun1(msg,y):
	#print msg 
	source=""
	s=str(y);
	#print source
	for i in range(len(msg)):
		if msg[i]=='*':
			source+=s
		else:
			source+=msg[i]
	return source		
	#for i in xrange(len(msg)):
		#print i
	#	if msg[i]=='*':
	#		msg[i]=s[0]
		#print msg[i]
ArDig=[Zero,One,Two,Three,Four,Five,Six,Seven,Eith,Nine ]

try:
	#print sys.argc
	digit=sys.argv[1]
	tr=int(digit);
	count=0;
	for s in sys.argv:
		count+=1
	#if count==3:
	#	tr=int(sys.argv[1])+int(sys.argv[2]);
	um=0
	for i in range(1,count):
		um+=int(sys.argv[i])
	digit=str(um);	

except IndexError:
	print("Usage:",sys.argv[0],"number")
	sys.exit(1)	
except ValueError:
	digit=str("1")
for e in range(7):	
	i=0	
	st=""
	while i<len(digit):
		a1=int(digit[i]);
		st+=ArDig[a1][e]
		i+=1
		st=fun1(st,a1)
	print(st) 
	
	
	i+=1

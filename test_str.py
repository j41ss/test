#!/usr/bin/python

import os

a="////teset/////testtt/////////////////////aaaaaaaaaaaaa//////////////sssssssssss///wwwwwwww"
#print(a.replace('//','/',a.count("//")))
while a.find("//") != -1:
   a = a.replace('//','/')
#while True:
#  b = a.find("//") 
  #b = a.find("//");
#  if b == -1:
#      break
#  d = a[1:b] 
#  c = a[b:]
#  a = a[0:b] + a[b:]    
#  print(a)



print(a)  

#!/usr/bin/python

def dio():
 x = 1L
 while 1:
  for y in xrange(1, x):
   for z in xrange(1, y):
    if x*x == y*y + 12752041*z*z:
     return "Found it"
    x = x + 1
dio();    

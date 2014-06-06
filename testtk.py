#!/usr/bin/python
from tkinter import *
import random
import sys

class Application(Frame):
    matr = [];
    #minval = -(2**sys.int_info.bits_per_digit);
    minval = -4;
    maxval = abs(minval);


    def say_hi(self):
       print("hi there, everyone!")

    def createWidgets(self):
       self.QUIT = Button(self)
       self.QUIT["text"] = "QUIT"
       self.QUIT["fg"]   = "red"
       self.QUIT["command"] =  self.quit

       self.QUIT.pack({"side": "left"})

       self.hi_there = Button(self)
       self.hi_there["text"] = "Hello",
       self.hi_there["command"] = self.say_hi
       self.hi_there.pack({"side": "left"})
       self.MATRIX= Button( self )
       self.MATRIX["text"] = "MATRIX"
       self.MATRIX["command"] = self.matrix_gen
       self.MATRIX.pack({"side": "left"})


    def __init__(self, master=None):
       Frame.__init__(self, master)
       self.pack()
       self.createWidgets()
    def matrix_gen( self, columns=2, cols=2 ):
       matr = [ [ random.randint( self.minval, self.maxval) for i in range(columns) ] for j in range(cols) ];
       print(matr)
       print( self.translate(matr ));
    def translate( self, matr ):
       print(matr.count);
       if len(matr) == 2:
         print("test");
         return matr[0][0]*matr[1][1]-matr[1][0]*matr[0][1]


root = Tk()
app = Application(master=root)
app.mainloop()
root.destroy()

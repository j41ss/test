#!/usr/bin/python2
import Tkinter
from Tkinter import *
import tkMessageBox
import random
import numpy

class matrix:
  def __init__( self, data=None ):
    if data :
     self.data = data
     self.obj = numpy.matrix( self.data )
     #self.rank = numpy.linalg.matrix_rank( self.obj.getA ) 
     #self.det = numpy.linalg.det( self.obj.getA )
  @property  
  def rank( self ):
     return self.rank
  @property  
  def get( self ):
     return self.obj.getA()
  @property
  def det( self ):
     return self.obj.det

class window_init:
  def __init__( self ):
    self.top = Tkinter.Tk()
    self.text = Tkinter.Text( self.top )
    self.button1 = Tkinter.Button( self.top, text='Renerate Matrix')
    self.button2 = Tkinter.Button( self.top, text='Submit Matrix' )
    self.button3 = Tkinter.Button( self.top, text='Clear Text' )
    self.__bindbuttons()
    self.button1.pack()
    self.button2.pack()
    self.button3.pack()
    self.text.pack()
    self.top.mainloop()
  def __bindbuttons(self):
    #self.button1.bind('<Button-1>', lambda event, arg=self.text: self.test( event, arg) )
    #self.button2.bind('<Button-1>', lambda event, arg=self.text: self.show_text(  event, arg) )
    self.button1.bind('<Button-1>',  self.gen_matrix )
    self.button2.bind('<Button-1>', self.show_text )
    self.button3.bind('<Button-1>', self.clear )
    self.top.bind_all('<F1>', self.help );
    self.top.bind('<Q>', self.destr )
    self.top.bind('<q>', self.destr )
  #def test( self, event, canvas, width=3, height=3):
  def clear( self, event):
    self.text.delete('1.0', END)
    #choice = random.choice( ['0', '0','1'] )
    #if choice:
    # self.smile();
  def gen_matrix( self, event,  width=3, height=3):
   digits = [ i for i in range( 0,10 ) ]
   a = [ [random.choice( digits ) for i in range(width)] for j in range( height ) ]
   for i in range( height ):
    string = str(a[i]) +'\n'
    self.text.insert( INSERT, string )
   self.text.pack()
  def destr( self, event ):
   self.top.destroy()
  def show_text( self, event ):
   cont_len = float( self.text.index('end') )
   cont_len = int(cont_len)
   content = []
   for i in range( cont_len+1 ):
    digits =  self.text.get( float(i), str(i) + '.end')
    if digits != '':
     content += [ i for i in digits.split( ',') ]
   if len(content): 
    cont = matrix(content)
    print content  
    #print(cont.get)
    #print( cont.rank )
  def help( self, event ):
    tkMessageBox.showinfo('Test', 'hello')
  def smile(self):
    cv = Canvas( height=30, width=30)
    cv.create_oval(1, 1, 29, 29, fill="yellow" )
    cv.create_oval(9, 10, 12, 12)
    cv.create_oval(19, 10, 22, 12)
    cv.create_polygon( 9, 20, 15, 24, 22, 20)
    self.text.window_create( CURRENT, window=cv )

 
test = window_init()


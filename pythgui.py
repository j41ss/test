#!/usr/bin/python2
import fltk 
import sys
import os
#from __future__ import print_function
def open_cb():
    x = 1    
def quit_cb(widget, data):
   sys.exit(0)
def genmenuitems():
    menuitems = (( "&File",              0, 0, 0, fltk.FL_SUBMENU ),
      #( "&New File",        0, new_cb ),
      #( "&Open File...",    fltk.FL_CTRL + ord('o'), open_cb ),
      ( "&Open File...",    fltk.FL_CTRL + ord('o'), None ),
      #( "&Insert File...",  fltk.FL_CTRL + ord('i'), insert_cb, 0, fltk.FL_MENU_DIVIDER ),
      #( "&Save File",       fltk.FL_CTRL + ord('s'), save_cb ),
      ( "&Save File",       fltk.FL_CTRL + ord('s'), None ),
      #( "Save File &As...", fltk.FL_CTRL + fltk.FL_SHIFT + ord('s'), saveas_cb, 0, fltk.FL_MENU_DIVIDER ),
      ( "Save File &As...", fltk.FL_CTRL + fltk.FL_SHIFT + ord('s'), None, 0, fltk.FL_MENU_DIVIDER ),
      #( "New &View", FL_ALT + ord('v'), view_cb, 0 ),
      #( "&Close View", FL_CTRL + ord('w'), close_cb, 0, fltk.FL_MENU_DIVIDER ),
      #( "&Exit", fltk.FL_CTRL + ord('q'), quit_cb, 0 ),
      ( "&Exit", fltk.FL_CTRL + ord('q'), quit_cb, 0 ),
      ( None, 0 ),

     # ( "&Edit", 0, 0, 0, FL_SUBMENU ),
     # ( "Cu&t",        FL_CTRL + ord('x'), cut_cb ),
     # ( "&Copy",       FL_CTRL + ord('c'), copy_cb ),
     # ( "&Paste",      FL_CTRL + ord('v'), paste_cb ),
     # ( "&Delete",     0, delete_cb ),
     # ( None, 0 ),

     # ( "&Search", 0, 0, 0, FL_SUBMENU ),
     # ( "&Find...",       FL_CTRL + ord('f'), find_cb ),
     # ( "&Find Again",    FL_CTRL + ord('g'), find2_cb ),
     # ( "&Replace...",    FL_CTRL + ord('r'), replace_cb ),
     # ( "Re&place Again", FL_CTRL + ord('t'), replace2_cb ),
     # ( None, 0 ),

     # ( None, 0 ) )
    )
    return menuitems
def dataparse( i, data, fl_data ):
    #if i.find("</data>") == -1 :
    #    print("BAD")
    #    fl_data = False
    #    return
    #else :
        for j in i.split() :
            #print(j)
            if j.isdigit() :
                data.append( int(j))
            elif j.find("</data") != -1:
                data.append( int(j[0:j.find("</data>")]) )
            else:
                fl_data = False
       
def xmlparse( xml):
    offstx, offsty, fl_offst, fl_data, size_x, size_y  = 0, 0, 0, 0, 0, 0
    ar = []
    for i in open(xml):
         if not fl_offst and i.find("<x>") != -1:
             offstx = int(i[i.find("<x>") + 3:i.find("</x>")]) 
             continue
         if not fl_offst and i.find("<y>") != -1:
             offsty = int(i[i.find("<y>") + 3:i.find("</y>")] )
             fl_offst = True
             continue
         if fl_data: 
             dataparse(i, ar, fl_data) 
             continue
         if not fl_data and i.find("<data>") != -1:
            fl_data = True
         if i.find("<width>") != -1:
            sizex = int(i[ i.find("<width>") + 7 :i.find("</width>")])
            continue
         if i.find("<height>") != -1:
            sizey = int(i[ i.find("<height>") + 8 :i.find("</height>")])

    for i in range(len(ar)):
        if i % 2 :
            ar[i] = ar[i] - offsty
        else:
            ar[i] = ar[i] - offstx
    mat = [ ['-' for x in range(sizex) ] for i in range(sizey) ]
    for i in range(0, len(ar)-2,2):
       #mat[ar[i]][ar[i+1]] = 1
       mat[ar[i+1]][ar[i]] = 1
      
    return sizex, sizey, mat
def main():   
    x , y , mat= xmlparse(sys.argv[1])
    print x,y
    for i in mat:
        for j in i:
            if j == '-':
              #print j,
               print u'\x1b[1m\x1b[38;5;28m#\x1b[39m\x1b[22m',
            else:
               print u'\x1b[1m\x1b[38;5;196m*\x1b[39m\x1b[22m',    
        print '\n',       
        #print(u'j') 
        #for j in mat(i):
            

    #x11_init(mat)
    x11_init(mat, x, y )



def x11_init( val, x, y ):
#def x11_init():
     #box.box(fltk.FL_UP_BOX)
     #image = fltk.Fl_Bitmap( 
     #textbuf = fltk.Fl_Text_Buffer()
     #box.labelsize(100)
     #box.labelfont( fltk.FL_BOLD + fltk.FL_ITALIC)
     #box.labeltype( fltk.FL_SHADOW_LABEL)
     #input.value( "Now is the time for all good men..." )
     menuitems = genmenuitems()
     window = fltk.Fl_Window( 1024, 800, os.name )
     m = fltk.Fl_Menu_Bar(0,0,1280,20)
     m.copy(menuitems)
     #fltk.Fl_Output ( 100, 200, 100, 200, "label" )
     #fltk.Fl_Button( 100,100,20,20)
     #box = fltk.Fl_Box(30,30,1000,600, "Hello World");
     #button = fltk.Fl_Button( 100, 100, 50, 20, "label" )
     #fl = fltk.Fl_Input( 100,200,20,20)
     #fl = fltk.Fl_Text_Display(100,100,20,20, "INPUT:")
     #fl.insert(val)
     #fl = fltk.Fl_Multiline_Input(50,50,x, y, "Input:" )
     #out = fltk.Fl_Multiline_Output(200,200,x,y, "Output:" )
     fl = fltk.Fl_Text_Editor( 20, 20, x, y ) 

     window.end()
     window.show(1,sys.argv)
     #fltk.fl_draw_image( val , 100, 200, 100, 200)
     fltk.Fl.run()
main()     

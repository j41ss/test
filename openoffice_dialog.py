# -*- coding: utf-8 -*-
import uno
import unohelper
from com.sun.star.text.ControlCharacter import PARAGRAPH_BREAK
from com.sun.star.text.TextContentAnchorType import AS_CHARACTER
from com.sun.star.style.ParagraphAdjust import CENTER
from com.sun.star.style.ParagraphAdjust import LEFT
from com.sun.star.text.ControlCharacter import APPEND_PARAGRAPH
from com.sun.star.awt import XActionListener
from com.sun.star.awt import XTextListener
from com.sun.star.awt import XItemListener
from com.sun.star.awt import Selection
DISC=u"Iсторiя української культури"
KURS=2
YEAR=2014
SURNAME=u"Twinker"
DEFFILE=u"test"
ZBOOK="18.13.0104"
def setchrproperty( obj, width, height ):
 if callable( getattr(obj, 'setPropertyValue' ) ):
  if width >= 0:
   obj.setPropertyValue( "CharWeight", width)  
  if height >= 0: 
   obj.setPropertyValue( "CharHeight", height)  
def appendcontrolchr( obj, obj2, symb, count ):
  if callable( getattr( obj, "insertControlCharacter") ):
   if count:
    for c in range(count):
     obj.insertControlCharacter( obj2, symb, 0 )
class actiontext( unohelper.Base, XTextListener ):
 def __init__( self, child=None ):
  self.child = child
 def textChanged( self, actionEvent):
  val = {
   'vectedit': 'disc', 
   'myedit': 'sfile',
   'myedit1': 'surname',
   'myedit2': 'zbook',
   'combo': 'kurs',
   'edittheme' : 'theme',
  }[self.child]    
  setattr( actionlist, val, actionEvent.Source.Text ) 
#class comboaction( unohelper.Base, XItemListener ):
# def ItemStateChanged( self, ItemEvent ):
#  actionlist.kurs = ItemEvent.Source.Text
#class comboaction( unohelper.Base, XActionListener, XItemListener ):
class comboaction( unohelper.Base, XActionListener ):
 def __init__( self ):
  pass
 #def ItemStateChanged( self, ItemEvent ):
 # actionlist.kurs = ItemEvent.Source.Text
 def actionPerformed( self, ItemEvent ):
  actionlist.kurs = ItemEvent.Source.Text
 
class actionlist( unohelper.Base, XActionListener ):
 zbook = ZBOOK
 disc  = DISC
 surname = SURNAME
 year = YEAR
 sfile = DEFFILE
 kurs = KURS
 theme = ''
 def __init__( self, zbook=ZBOOK, disc=DISC, surname=SURNAME, year=YEAR, sfile=DEFFILE, kurs=KURS, obj=None ):
  pass
 def actionPerformed( self, actionEvent):
  createhead(  zbook=self.zbook, disc=self.disc, surname=self.surname, year=self.year, sfile=self.sfile, kurs=self.kurs, theme=self.theme ) 
  #if self.obj:
  # self.obj.dispose()
#class comboactionlist( uno
def cdialog( smgr=None ):
 if not smgr:
  ct    = uno.getComponentContext()
  smgr  = ct.ServiceManager
 dm = smgr.createInstance( 'com.sun.star.awt.UnoControlDialogModel' )
 dm.Width = 240
 dm.Height = 150
 dm.Title = "Select parameters"
 but = dm.createInstance( 'com.sun.star.awt.UnoControlButtonModel' )
 but.PositionX, but.PositionY, but.Width, but.Height = 150, 100, 25, 15
 but.Label, but.Name, but.TabIndex = 'Submit', 'mybutt', 1
 static_text = dm.createInstance( 'com.sun.star.awt.UnoControlFixedTextModel' )
 static_text.PositionX, static_text.PositionY = 10, 10
 static_text.Width, static_text.Height =  70, 20
 static_text.Label = "Дисциплина:"
 static_text.Name = "myfio"
 vect_edit = dm.createInstance( 'com.sun.star.awt.UnoControlEditModel' )
 vect_edit.PositionX, vect_edit.PositionY = 50, 10
 vect_edit.Width, vect_edit.Height = 90, 10
 #vect_edit.Name, vect_edit.Text = "vectedit", DISC 
 vect_edit.Name = "vectedit"
 vect_edit.Text =  DISC 
 #vect_edit.Editable = uno.Bool(1)
 

 vect = dm.createInstance( 'com.sun.star.awt.UnoControlFixedTextModel' )
 vect.PositionX, vect.PositionY, vect.Width, vect.Height = 10, 20, 70, 20
 vect.Label, vect.Name = 'Фаил:', 'myvect'
 theme = dm.createInstance( 'com.sun.star.awt.UnoControlFixedTextModel' )
 theme.PositionX, theme.PositionY, theme.Width, theme.Height = 10, 30, 70, 20
 theme.Label, theme.Name = 'Тема:', 'mytheme'
 

 fio =  dm.createInstance( 'com.sun.star.awt.UnoControlFixedTextModel' )
 fio.PositionX, fio.PositionY, fio.Width, fio.Height = 10, 40, 70, 20
 fio.Label, fio.Name = 'ФИО:', 'myfio2'
 zbook = dm.createInstance( 'com.sun.star.awt.UnoControlFixedTextModel' )
 zbook.PositionX, zbook.PositionY, zbook.Width, zbook.Height = 10, 50, 70, 20
 zbook.Label, zbook.Name = 'Зачетка:', 'myzbook'

 curs = dm.createInstance( 'com.sun.star.awt.UnoControlFixedTextModel' )
 curs.PositionX, curs.PositionY, curs.Width, curs.Height = 10, 60, 20, 20
 curs.Label, curs.Name = 'Курс:', 'mycurs'

 msgb = dm.createInstance( 'com.sun.star.awt.UnoControlEditModel' )
 msgb.PositionX, msgb.PositionY = 50, 20
 msgb.Width, msgb.Height = 90, 10
 msgb.Name, msgb.Text = "myedit", DEFFILE

 msgb3 = dm.createInstance( 'com.sun.star.awt.UnoControlEditModel' )
 msgb3.PositionX, msgb3.PositionY = 50, 30
 msgb3.Width, msgb3.Height = 90, 10
 msgb3.Name, msgb3.Text = "edittheme", ''
 
 msgb1 = dm.createInstance( 'com.sun.star.awt.UnoControlEditModel' )
 msgb1.PositionX, msgb1.PositionY = 50, 40
 msgb1.Width, msgb1.Height = 90, 10
 msgb1.Name, msgb1.Text = "myedit1", SURNAME
 
 msgb2 = dm.createInstance( 'com.sun.star.awt.UnoControlEditModel' )
 msgb2.PositionX, msgb2.PositionY = 50, 50
 msgb2.Width, msgb2.Height = 90, 10
 msgb2.Name, msgb2.Text = "myedit2", ZBOOK

 #combobox = dm.createInstance( 'com.sun.star.awt.UnoControlComboBoxModel' )
 combobox = dm.createInstance( 'com.sun.star.awt.UnoControlEditModel' )
 combobox.PositionX, combobox.PositionY = 50, 60
 combobox.Width, combobox.Height = 40, 10
 #combobox.StringItemList =  ( "1", "2", "3", "4" )
 #combobox.Tabstop = uno.Bool(1)
 #combobox.Autocomplete = uno.Bool(1)
 #combobox.Dropdown = uno.Bool(1)
 #combobox.Enabled = uno.Bool(1)
 combobox.Name='combo'
 #combobox.ReadOnly = uno.Bool( 1 )
 combobox.Text= KURS 

 dm.insertByName( 'mybutt', but )
 dm.insertByName( 'myedit', msgb )
 dm.insertByName( 'myedit1', msgb1 )
 dm.insertByName( 'myedit2', msgb2 )
 dm.insertByName( 'edittheme', msgb3 )
 dm.insertByName( 'myfio', static_text )
 dm.insertByName( 'vect', vect )
 dm.insertByName( 'mycurs', curs )
 dm.insertByName( 'vectedit', vect_edit )
 dm.insertByName( 'myfio2', fio )
 dm.insertByName( 'mytheme', theme )
 dm.insertByName( 'myzbook', zbook )
 dm.insertByName( 'combo', combobox )

 odial = smgr.createInstance( "com.sun.star.awt.UnoControlDialog" )
 odial.setModel( dm )
 
 odial.getControl('mybutt').addActionListener( actionlist( obj=odial) )
 odial.getControl('myedit').addTextListener( actiontext(  child='myedit') )
 odial.getControl('myedit1').addTextListener( actiontext(  child='myedit1') )
 odial.getControl('myedit2').addTextListener( actiontext(  child='myedit2') )
 odial.getControl('vectedit').addTextListener( actiontext(  child='vectedit') )
 odial.getControl('edittheme').addTextListener( actiontext(  child='edittheme') )
 odial.getControl('combo').addTextListener( actiontext( child='combo' ) )
 toolkit = smgr.createInstanceWithContext( "com.sun.star.awt.ExtToolkit", ct)
 #if odial.getControl('vectedit').isEditable:
 #oSelection=Selection(0,22 )
 odial.setVisible( False )
 odial.createPeer( toolkit, None )
 odial.getControl('vectedit').Editable= uno.Bool(1)
 odial.getControl('myedit').Editable= uno.Bool(1)
 odial.getControl('myedit1').Editable= uno.Bool(1)
 odial.getControl('myedit2').Editable= uno.Bool(1)
 odial.getControl('combo').Editable= uno.Bool(1)
 odial.execute()
 odial.dispose()
def createhead( disc=DISC, surname=SURNAME, kurs=KURS, year=YEAR, zbook=ZBOOK, sfile=DEFFILE, theme='' ):
 """create header for control work"""
 ct    = uno.getComponentContext()
 smgr  = ct.ServiceManager
 deskt = smgr.createInstanceWithContext( 'com.sun.star.frame.Desktop', ct )
 new   = deskt.loadComponentFromURL( 'private:factory/swriter', 'blank', 0, () )
 new.Title = sfile
 tex   = new.Text
 curs  = tex.createTextCursor()
 setchrproperty( curs, 150, 20.0 )
 curs.ParaAdjust = CENTER
 tex.insertString( curs, u"Міністерство освіти і науки України", 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 curs.ParaTopMargin = 500
 setchrproperty( curs, -1 , 18.0 )
 tex.insertString( curs, u"Національний авіаційний університет", 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 setchrproperty( curs, -1 , 14.0 )
 tex.insertString( curs, u"Інститут заочного та дистанційного навчання", 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 3 )
 setchrproperty( curs, -1 , 20.0 )
 tex.insertString( curs, u"КОНТРОЛЬНА РОБОТА", 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 setchrproperty( curs, 0 , 13.5 )
 tex.insertString( curs, u"з дисципліни", 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 setchrproperty( curs, 150 , 16.0 )
 tex.insertString( curs,  "\"%s\"" % disc, 0 )
 if theme:
  appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
  setchrproperty( curs, 0 , 13.5 )
  tex.insertString( curs, u"на тему", 0 )
  #appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
  setchrproperty( curs, 150 , 16.0 )
  appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
  tex.insertString( curs, "\"%s\"" % theme, 0 )
  appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 4 )
 else: 
  appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 6 )
 curs.ParaAdjust = LEFT
 setchrproperty( curs, 150 , 13.5 )
 #if not theme:
 curs.ParaTopMargin = 0
 curs.ParaLeftMargin = 11000
 tex.insertString( curs, u"Виконав:", 0 )
 setchrproperty( curs, 0 , 13.5 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 if int(kurs) < 4 :
  tex.insertString( curs, u"студент %s курсу ІЗДН" % ('I'*int(kurs)), 0 )
 else :
  tex.insertString( curs, u"студент IV курсу ІЗДН",  0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 tex.insertString( curs, surname, 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 tex.insertString( curs, u"Спеціальність 6.050201", 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 tex.insertString( curs, u"Залік. Книжка № %s" % zbook, 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 tex.insertString( curs, u"Група № 1", 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 2 )
 setchrproperty( curs, 150 , 13.5 )

 curs.ParaTopMargin = 400

 tex.insertString( curs, u"Перевірив:", 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 setchrproperty( curs, 0 , 13.5 )
 tex.insertString( curs, u"________________________", 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 1 )
 tex.insertString( curs, u"( П.І.Б  викладача )", 0 )
 appendcontrolchr( tex, curs, PARAGRAPH_BREAK, 5 )
 #test
 #appendcontrolchr( tex, curs, APPEND_PARAGRAPH, 4 )
 #tex.insertString( curs, u"test", 0 )
 #test
 curs.ParaAdjust = CENTER
 curs.ParaLeftMargin = 0
 curs.ParaTopMargin = 0
 setchrproperty( curs, 150 , 12.0 )
 tex.insertString( curs, u"Київ %s" % year, 0 )
 setchrproperty( curs, 0 , 14.0 )
 #cdialog( smgr )
 #cdialog( deskt )
 #cdialog( None )
 #createdialog()
 #save
 #new.storeAsUrl('file:///home/guileone/text.odt',() )
 #new.dispose()
 #sys.exit()
 
#createhead() 
#g_exportedScripts = createhead,
g_exportedScripts = cdialog,createhead

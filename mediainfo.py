#!/usr/bin/env python2

from pymediainfo import MediaInfo as Media
import os, sys, argparse, mimetypes, magic

class FileNotExistsError( Exception ): pass

class MediaObj :
    def __init__( self, basic ):
        self.verbose = basic.verbose
	self.mediafile = os.path.realpath( *(basic.mediafile) )
	self.__audio = basic.audio
	self.len = len( self.mediafile)
	self.dir = False
	self.video = False
	self.file = False
	self.bluray = False
	self.music = False
	self.__files_in_dir = False
	self.__iterable = 0
	exists = False
	if os.path.isfile( self.mediafile ): 
	  self.file = True
	  exists = True
	elif os.path.isdir( self.mediafile ):
	  self.dir = True
	  exists = True
        if not exists:
	  raise FileNotExistsError
	self.open( self.mediafile )  

    def __len__( self):
        return self.len
    def __iter__( self ):
        return self
    def next( self ):
        if self.__iterable <  self.__len__()   :
           val = self.mediafile[self.__iterable]
	   self.__iterable += 1
	   return val
	else :
	   raise StopIteration
    #def __test_	    
    def __test_music( self ):
       if self.file: 
          #mime = mimetypes.guess_type( self.mediafile )
	  #mime = magic.Magic( mime=True )
          #mime =  mime[0] 
	  #mime = mime.from_file(self.mediafile)
	  #print mim1
	  #mime = magic.open( magic.MAGIC_MIME)
	  #mime.load()
          mime = magic.from_file(self.mediafile)
	  #print mime
          if mime.count("audio") or mime.count("Audio") :
	     self.music = True
             self.__audio = True
	  elif mime.count("video"):
	     self.video = True
	  elif mime.count("data"):
	     self.bluray = True
       else :
          #add support for directory
          pass


       
    def open( self, fd ):
       self.__test_music()
       if self.file :
          a = Media.parse( fd ) 
          for track in a.tracks:
            if track.track_type  == 'General' and self.__audio == True and self.music:
          #print track.bit_rate, track.bit_rate_mode, track.codec, track.format
	     #print track.complete_name,
	     print str(track.performer)  + ' ' + str(track.album) + ' ' + str(track.recorded_date)
            if track.track_type  == 'Audio' and self.__audio == True:
	     print track.format , ' ' , track.bit_rate, ' ' , track.sampling_rate , ' ', track.channel_s    


def parseargs():
    
    parser = argparse.ArgumentParser( description = 'Mediainfo from file or Directories.' )
    parser.add_argument( '-a', '--audio', help= 'Just get audio parameters', action = 'store_true' )
    parser.add_argument( '-v', '--verbose', help = 'verbose output', action = 'store_true' )
    parser.add_argument( 'mediafile',  nargs=1 )	   
    args = parser.parse_args()
    if len( sys.argv ) == 1 :
       parser.print_help()
       exit() 
    #obj = MediaObj( args)  

    #print args.verbose   
    #print( dir(args) )   
    #print(args.accumulate(args.integers))
    return args 


def main():
    args = parseargs()
    try:
       obj = MediaObj( args )
    except FileNotExistsError:
       print 'object ' + os.path.realpath( args.mediafile[0] ) + ' not be found'
    exit()

    #if len(sys.argv) == 1:
    #print a
       
main()    

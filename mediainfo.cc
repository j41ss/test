#include <iostream>
#include <MediaInfo.h>
int main(int argc, char **argv)
{

        //using namespace MediaInfoLib;
        using namespace MediaInfoLib;
	using namespace std;
	if( argc == 1)
	     return 1;
	//String Handle;    
//	MediaInfoLib::Mediainfo Handle;
	MediaInfo Handle;
	String st(argv[1]);
	st = argv[1];
	//Handle = fo();
	//MediaInfoLib::String arg(st);
	Handle.Open(st);
  //      MediaInfo::Inform();
//	MediaInfo::Close();
	Handle.Close();
//
//
//
//        Handle.Menu_View_Text();
	return 0;
}	


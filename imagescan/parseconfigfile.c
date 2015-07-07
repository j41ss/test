#include "header.h"

int init_variables( const char *file, config *ar)
{
	std::fstream inpt;
	std::string st;
    int param=0;
	memset( ar, 0, sizeof( config));
	//std::cout<<sizeof(config)<<std::endl;
	//bzero( conf, sizeof( config));
	inpt.open(file, std::fstream::in);
	if( !inpt.is_open() ) {
          fprintf( stderr,"Cann't open %s\n", file);
	      return 1; }
	while( /*!inpt.eof() &&*/ std::getline( inpt, st) ) {
	   if( st[0] == '#' || st[0] == '/' || st == "" )
	      continue;
	   int count;   
	   if( (size_t) (count = st.rfind('=')) ==  std::string::npos || count == (int)(st.length() - 1)) {
	      std::cout<<"Unknown string: "<<st<<std::endl;
	      return 1; }
       std::string val; 
       //printf("%s\n", st.c_str());
	   val = &st[count+1];   
	   if( ! st.compare( 0, count  , "prefix")) {
              if( ! (*ar->prefix) )
                  param++;
              val.copy(ar->prefix,MIDDLELEN); }
	   if( ! st.compare( 0, count  , "template")) {
              if( ! (*ar->templates) )
                  param++;
              val.copy(ar->templates,MIDDLELEN); }
	   if( ! st.compare( 0, count  , "user")) {
              if( ! (*ar->user) )
                  param++;
              val.copy(ar->user, TINYLEN); }
	   if( ! st.compare( 0, count  , "host")) {
              if( ! (*ar->host) )
                  param++;
              val.copy(ar->host, TINYLEN); }
	   if( ! st.compare( 0, count  , "pwd")) {
              if( ! (*ar->pwd) )
                  param++;
              val.copy(ar->pwd, TINYLEN); }
	   if( ! st.compare( 0, count  , "number_dir")) {
              if( ! (*ar->numdir) )
                  param++;
              val.copy(ar->numdir, MIDDLELEN); }
	   if( ! st.compare( 0, count  , "repeat_dir")) {
              if( ! (*ar->repdir) )
                  param++;
              val.copy(ar->repdir, MIDDLELEN); }
	   if( ! st.compare( 0, count  , "report_file")) {
              if( ! (*ar->report_file) )
                  param++;
              val.copy(ar->report_file, MIDDLELEN); }
	   if( ! st.compare( 0, count  , "delay")) {
              if( ! ar->delay )
                  param++;
              ar->delay = atoi(val.c_str()); } 
	   /*std::cout<<st<<std::endl;*/ }
    inpt.close();
    if( param < 9 ) {
        fprintf( stderr, "%s\n", "Config file not contain all variables"); 
        return  1; }   
	return 0;
}	

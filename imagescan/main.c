#include "header.h"
#include <signal.h>

extern list_memb *head;

void sigcaller( int signum)
{

    if( head != NULL ) {
          fprintf( stderr, "Calling delete for dynamic memory\n");
          delete(head);
          head = head->next; }
    kill( getpid(), SIGINT );
}    

int main( int argc, char **argv)
{
    struct sigaction sign;
    config vars;
    int fd, sd, count = 1, index, scan;
    char  resp[MIDDLELEN], shotname[MIDDLELEN], rbuf[BUFSIZ], cand1[MIDDLELEN];
    if( argc == 1) 
        fprintf( stderr, "%s configfile \n", argv[0]), exit(EXIT_FAILURE);
    if( sigaction( SIGINT, NULL, &sign ) == -1 )
        fprintf( stderr, "Calling sigaction() for getting settings failed"), exit(EXIT_FAILURE);
    sign.sa_handler = sigcaller;
    sign.sa_flags |= SA_RESETHAND;
    if( sigaction( SIGINT,&sign, NULL ) == -1 )
        fprintf( stderr, "Calling sigaction() for create new settings failed"), exit(EXIT_FAILURE);

    if( init_variables( argv[1], &vars) ) 
        fprintf( stderr, "Error parse configfile %s\n", argv[1]),exit(EXIT_FAILURE); 
    memset( cand1, 0, sizeof(cand1));
    int co=0;
    if( count == 1) {
       count = 0;
       create_techinfo( vars.host, vars.user, vars.pwd, resp, sizeof(resp), IMG); }

    for( ;; )  {
         fd = init_connection( vars.host, 80, 0, &sd);
	 fprintf( stderr, "%d\n", co++);
         if( fd < 0) {
           fprintf( stderr, "%s\n", "init connection failed");
	       memset( cand1, 0, sizeof(cand1));
           close(sd);
	       sleep(vars.delay);
           continue; }
         snprintf( shotname, sizeof(shotname), "%s%lld.jpg", vars.prefix, get_time());
	     /*diffence*/
	     count = write_shot( sd, rbuf, sizeof(rbuf), shotname, resp, sizeof(resp) ); 
	     /**/
	     //memset( rbuf, 0, sizeof(rbuf));
	     /**/
         if( count  == 1) {
	       close(sd);
           fprintf( stderr, "cannot write shot %s\n", shotname);
	       sleep( vars.delay);
	       continue; }
        //else {
	       if( *cand1 ) {
                  if( compare_init( cand1, shotname, &index) == 1) {
		              fprintf( stderr,"Compare %s vs %s failed\n", cand1, shotname); 
	                  memset( cand1, 0, sizeof(cand1));
	                  close(sd);
                      /**/
                      continue;
                      /**/
                       }

	              else {
		                  //       memset( cand1, 0, sizeof(cand1)); 
                         if( index == 1 ) {
                           
                                  scan = cvmain( shotname, vars.templates, vars.numdir, vars.repdir, vars.report_file );
                            
                                  fprintf( stderr, "Scan image  %s  have status %d\n", shotname, scan);  
                                  if( scan == 1 ) 
                                       memset( shotname, 0, sizeof(shotname));
                                   }

                          //else {
                         unlink( cand1);
                               //memset( cand1, 0, sizeof(cand1));
                               /*continue;*/ //} 
                              
                     }}
         //else 
	     // memcpy( cand1, shotname, sizeof( cand1 )); 
//         if ( index != 1)
	       memcpy( cand1, shotname, sizeof( cand1 )); 
//}

	close(sd);     
        sleep(vars.delay); }
      /*  count++;
        if( count == 60 )
            break; }
            */
    return 0;
}

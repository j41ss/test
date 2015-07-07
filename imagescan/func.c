#include "header.h"

//quit for dynamic memory
long long get_time( void )
{
    time_t ct;
    char buf[ 15 ];
    struct tm *ptr;
    const char *format = "%Y%m%d%H%M%S";// format for strftime 
    ct = time( NULL );
    ptr = localtime( &ct );
    strftime( buf, sizeof(buf), format, ptr );
    return atoll( buf );
}    
void concat_str( char *buf,const char *user, const char *pwd, size_t len)
{
   strncpy( buf, user, len );
   strncat( buf, ":", len - strlen(buf) );
   strncat( buf, pwd, len - strlen(buf) );
}	       	
int create_http_request( char *buf, size_t len, const char *host, const char *url, const char *user, const char *pwd)
{
   char *userpwd;
   //for in crypt contain crypt
   static char crypt[MIDDLELEN];
   int code;
   void delete_double_symb( char *param );
   code = strlen( user ) + strlen( pwd ) + 2;
   userpwd = (char *)malloc( code  );
   if( userpwd == NULL )
       fprintf( stderr, "%s\n", "malloc() failed"),exit(EXIT_FAILURE);
   if( crypt[0] == 0 ) {    
          concat_str( userpwd, user, pwd, code );
         //printf("%s\n", userpwd);
         base64encode( (const unsigned char *)userpwd, strlen(userpwd) /* code  - 2 */,(unsigned char *) crypt, sizeof(crypt));
         if( userpwd == NULL  ){
            fprintf( stderr, "%s\n", "realloc() failed"); exit(EXIT_FAILURE); } 
         free(userpwd); }  
   code = snprintf( buf, len, "GET /%s HTTP/1.0\r\nHost: %s\r\nAuthorization: Basic %s\r\n\r\n", url, host, crypt);      
   return code;
}

int init_connection( const char *url, int port, int bind_port, int *sockf )
{
     int sock;
     struct sockaddr_in saddr;
     struct hostent *hp;
     sock = socket( AF_INET, SOCK_STREAM, 0);
     if ( sock == -1)
         return sock;
     *sockf = sock;    
     if( bind_port ) {
         memset( (void *) &saddr, 0, sizeof(saddr) ); 
         saddr.sin_addr.s_addr = INADDR_ANY;
         saddr.sin_port = htons(bind_port);
         saddr.sin_family = AF_INET; 
         if( bind( sock, (struct sockaddr *)&saddr, sizeof(saddr)) != 0)
             return -1 ; }
     hp=gethostbyname(url);
     if( hp == NULL )
         return -1;
     memset( (void *)&saddr, 0, sizeof(saddr) ); 
     memcpy( (void *)&saddr.sin_addr.s_addr, (void *) hp->h_addr, hp->h_length );
     saddr.sin_family = AF_INET;
     saddr.sin_port = htons( port );
     return connect( sock, (struct sockaddr *)&saddr, sizeof(saddr));
}     

int create_techinfo( const char *host, const char *usr, const char *pwd, char *buf, size_t bufsiz, int choice)
{
    char *url;
    if( choice == INFO) 
        url = (char *)"common/info.cgi";
    else if( choice == SINFO)
        url = (char *)"config/stream_info.cgi";
    else 
        url = (char *)"image/jpeg.cgi";
    return  create_http_request(buf, bufsiz, host, url, usr, pwd);
}
int write_shot( int sd, char *buf, size_t len, const char *filename, const char *reply, size_t reply_len )
{
    FILE *fp;
    size_t siz;
    int pos = 1;
    char *sh;
    if( send( sd, reply, reply_len, 0) == -1) {
        perror("send");return 1; }
    fp = fopen( filename, "wt");
    if( fp == NULL) {
        fprintf( stderr, "open %s failed\n", filename); return 1; }
    while( (siz = recv( sd, buf, len, 0) ) > 0) {
        if( pos == 1) {
            pos = 0;
            sh = strstr( buf,"\xff\xd8\xff\xe0");
            if(sh) {
                fwrite( sh , /*siz*/ siz - (sh - buf)  , 1, fp); }
            }
        else    
            fwrite( buf, siz, 1, fp); }
    fclose(fp); 
    convert_grayscale(filename);
    return 0;
}    

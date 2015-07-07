//#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cv.h>
#include <highgui.h>
#define TINYLEN 100
#define MIDDLELEN 300
//#define PREFIX "/Volume_1/shot/"
#define err(x) { perror(x);exit(EXIT_FAILURE); }
#define INFO 0
#define SINFO 1
#define IMG 2

struct list_memb {
        std::string sh;
        list_memb *next; };
                
//enum { INFO, SINFO, IMG } ret;

typedef struct {
    /*char host[TINYLEN], user[TINYLEN], pwd[TINYLEN];
    int delay;
    char share_prefix[MIDDLELEN], shabl_prefix[MIDDLELEN];
    char snapshot_dir[MIDDLELEN], end_dir[MIDDLELEN]; }*/
     char  prefix[MIDDLELEN], templates[MIDDLELEN], numdir[MIDDLELEN], repdir[MIDDLELEN], report_file[MIDDLELEN], user[TINYLEN], host[TINYLEN], pwd[TINYLEN] ;
     int delay; }
config;
typedef struct {
     int sizx,sizy,*pbuf;
} act_pixel;     
//extern "C++" void convert_grayscale( const char *file); 

int create_http_request( char *buf, size_t len, const char *host, const char *url, const char *user, const char *pwd);
long long get_time( void );
int init_connection( const char *url, int port, int bind_port, int *sockf );
int base64encode(const unsigned char *input, int input_length, unsigned char *output, int output_length);
//int init_imagebuf( gdImagePtr *in1, gdImagePtr *in2, const char *file1, const char *file2);
//int cross_scan( /*struct*/ act_pixel *source, gdImagePtr im);
//int wmemcmp_compare(  int *buf1, int *buf2, size_t siz, int procent);
int create_techinfo( const char *host, const char *usr, const char *pwd, char *buf, size_t bufsiz, int choice);
int write_shot( int sd, char *buf, size_t len, const char *filename, const char *reply, size_t reply_len );
int compare_init( const char *file1, const char *file2, int *status);
void convert_grayscale( const char *file);
int init_variables( const char *file, config *ar);
int cvmain( char *shotname, char *templates, char *numbers, char *numbers1, char *report_txt );

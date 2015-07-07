#include "header.h"

int getDiffenceHash( uint64_t val1, uint64_t val2);
uint64_t create_hash( const char *file);

void convert_grayscale( const char *file)
{
      IplImage *gray=0;
      gray = cvLoadImage( file, CV_LOAD_IMAGE_GRAYSCALE);
      cvSaveImage( file, gray);
      cvReleaseImage( &gray);
}            




int compare_init( const char *file1, const char *file2, int *status)
{
/*    
    gdImagePtr in1, in2;
    //struct act_pixel s1, s2;
    act_pixel s1, s2;
    if( init_imagebuf( &in1, &in2, file1, file2) == 1 ) {
         fprintf( stderr, "Compare failed\n"); return 1; }
   // ImageCompare( in1, in2 );
    printf("%s %s\n",file1, file2); 
    if( cross_scan( &s1, in1  ) == -1) {
        fprintf( stderr, "%s\n", "malloc() failed");
        return 1; }
    if( cross_scan( &s2, in2  ) == -1) {
        free( s1.pbuf );
        fprintf( stderr, "%s\n", "malloc() failed");
        return 1; }
    if( compare_image( &s1, &s2) == 0 ) {
        st = unlink(file1);
    	fprintf( stderr, "Deleting %s have status %d\n", file1, st ); 
        }
    if( s1.pbuf != NULL)
       free(s1.pbuf);
    if( s2.pbuf != NULL)
       free(s2.pbuf);
    flush_imagebuf( &in1, &in2);
    return 0;
    */
    uint64_t count, index;
    int result,st;
    *status = 0;
    count = create_hash(file1);
    index = create_hash(file2);
    if( !count || !index)
        return 1;
    result = getDiffenceHash( count, index);
    if( result <= 5  ) {
        st = unlink(file1);
    	fprintf( stderr, "Deleting %s have status %d\n", file1, st ); }
    else {
        *status = 1;
        fprintf( stderr, "File %s  %s have diffence\n", file1, file2); }
    return 0;

}
/*
int init_imagebuf( gdImagePtr *in1, gdImagePtr *in2, const char *file1, const char *file2)
{
    FILE *fp;
    fp = fopen( file1, "rb");
    if( fp == NULL) {
        fprintf( stderr, "Failed to open %s\n", file1);return 1; }
    *in1 = gdImageCreateFromJpeg( fp);
    fclose(fp);
    fp = fopen( file2, "rb");
    if( fp == NULL) {
        fprintf( stderr, "Failed to open %s\n", file1);return 1; }
    *in2 = gdImageCreateFromJpeg( fp);
    fclose(fp);
    return 0;
}*/
/*void flush_imagebuf( gdImagePtr *in1, gdImagePtr *in2 )
{
    gdImageDestroy( *in1);
    gdImageDestroy( *in2);
} */
/*
void ImageCompare( gdImagePtr in1, gdImagePtr in2 )
{
    int code;
    //char *ch;
    code = gdImageCompare( in1, in2 );
    if( !code ) {
       fprintf( stderr, "images haven't difference\n");return; }
    else {
        if( code & GD_CMP_NUM_COLORS ) 
            fprintf( stderr, "images have diffence of pallette color\n");
        if( code & GD_CMP_COLOR )   
            fprintf( stderr, "images have diffence of color\n");
        if( code & GD_CMP_SIZE_X )    
            fprintf( stderr, "images have diffence of width\n");
        if( code & GD_CMP_SIZE_Y )
            fprintf( stderr, "images have diffence of height\n");
        if( code & GD_CMP_TRANSPARENT ) 
            fprintf( stderr, "images have transparent color\n");
        if( code & GD_CMP_BACKGROUND )
            fprintf( stderr, "images have diffence of background color\n");
        if( code & GD_CMP_INTERLACE )
            fprintf( stderr, "images have diffence of interlaced setting\n");
        if( code & GD_CMP_TRUECOLOR )    
            fprintf( stderr, "images have diffence of truecolor vs pallette\n"); }
} 
*/
/*add support of offset */

//int cross_scan( /*struct*/ act_pixel *source, gdImagePtr im)
/*
{
    int begin, count, index;
    memset( source, 0, sizeof(act_pixel ) );
    source->sizx = gdImageSX( im );
    source->sizy = gdImageSY( im );
    
    source->pbuf =  (int *)calloc( (source->sizx + source->sizy), sizeof( int ) );
    //div image /2 
    if( source ->pbuf == NULL )
       return -1;
    for( begin = source->sizy/2, count = 0; count < source->sizx; count++ ) 
           source->pbuf[count] = gdImageGetPixel( im, count, begin );
    //printf( "%d %d %d\n", count, begin, source ->sizx+ source->sizy );
    for( begin = source->sizx/2, index = 0; index < source->sizy; index++, count++) {
           source->pbuf[count] = gdImageGetPixel( im, begin, index  ); }
    return 0;
}
*/
/*
int compare_image( const act_pixel *s1, const act_pixel *s2 )
{
    int count;
    if( s1->sizx != s2->sizx || s1->sizy != s2->sizy ) {
        fprintf( stderr, "%s\n", "Images have diffence of size" );
        return 1; }
    //
  //  count = wmemcmp( (int *)s1->pbuf, (int *)s2->pbuf, s1->sizx + s1->sizy ); 
    count = wmemcmp_compare( (int *)s1->pbuf, (int *)s2->pbuf, s1->sizx + s1->sizy, PRO ); 
    if( count == 0 ) 
        fprintf( stderr, "%s\n", "images pixels haven't diffence");
    else     
        fprintf( stderr, "%s\n", "images pixels have  diffence");
    return count; 	
} 
*/
//int wmemcmp_compare( wchar_t *buf1, wchar_t *buf2, size_t siz, int procent)
/*
int wmemcmp_compare(  int *buf1, int *buf2, size_t siz, int procent)
{
   long valid_pixels, valid_pixels1;
   if(procent < 100 )  valid_pixels = siz/100 * procent;
   else valid_pixels=siz;
   valid_pixels1=siz;
   size_t count;
   int *pt = buf1, *pt2 = buf2;
   printf("%zd %ld\n", siz, valid_pixels);
   for( count = 0 ; count < siz && valid_pixels >= 0l ; count++, pt++, pt2++  ) 
       if( *pt == *pt2)
          valid_pixels --;

   printf("%ld %ld\n", valid_pixels1 - valid_pixels, valid_pixels);	     
   if( valid_pixels < 0)
       return 0;
   return 1;
}   
*/
uint64_t create_hash( const char *file)
{
        IplImage *dst, *in;
        const int size_ar=8;
        long double sum=0;
        uint64_t val=0;
        double array[size_ar][size_ar];
        in = cvLoadImage( file);
        if( in == NULL)
             return 0;
        CvSize siz = cvSize(size_ar,size_ar);
        dst =  cvCreateImage(siz,in->depth, in->nChannels );
        cvResize( in, dst, CV_INTER_LINEAR);
        cvReleaseImage(&in);

        for( int i=0;i<dst->width;i++)
           for( int j = 0; j<dst->height;j++) {
               CvScalar scal = cvGet2D( dst, i, j);
               array[i][j] = (double)*scal.val;
               sum += (long double)array[i][j];
             /*printf( "(%.f,%.f,%.f,%.f)\n ", scal.val[0], scal.val[1], scal.val[2], scal.val[3] );*/ }
        sum /= dst->width * dst->height;
        for( int i=0;i<dst->width;i++)
           for( int j = 0; j<dst->height;j++) {
              val <<= 1;
              if( sum > array[i][j] )
                  val |= 0;
              else                                                                                                                                                                                                                     val |= 1; }
       // std::cout<<std::bitset<64>(val)<<std::endl;
        //printf("\n%.Lf\n", sum);        
        cvReleaseImage(&dst);
        return val;
}
int getDiffenceHash( uint64_t val1, uint64_t val2)
{
        int i, j;
        for( i = 0, j=0; i < (int)sizeof(val1)*8; i++, val1>>=1, val2>>=1 ) {
             bool v1,v2;
             v1 = val1 & 0x1;
             v2 = val2 & 0x1;
             if( v1 !=  v2)
                     j++; }
        return j;
}
                                

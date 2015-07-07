//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
//#include <io.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h> 

//#define DEBUG
#define max_file_size 512
#define max_number_size 12
#define min_number_size 4
#define posi_default_value 2000
#define symbol_default_value '?'
#define MIN_AREA 1000
#define MAX_AREA 40000
#define bublik_lenght 10
#define for_kvant_avg 10

const char* way_to_template;
const char* way_to_save_numbers1;
const char* way_to_save_numbers2;
const char* report_file;

IplImage* image = 0;
IplImage* img = 0;
IplImage* templ = 0;

IplImage* roiB = 0;
IplImage* roiK = 0;
IplImage* roiL = 0;

CvMoments moments;
//CvFileStorage* fs = cvOpenFileStorage( "example.xml", 0, CV_STORAGE_READ|CV_STORAGE_WRITE);
int num=0;
int num2=0;
int diff=0;
double min_match;
double d_moment;
char symbol;

//char file_number[max_file_size];

char symb[max_number_size];
int posi[max_number_size];

double match1[sizeof(symb)];
double match2[sizeof(symb)];
double match3[sizeof(symb)];

char symb1[sizeof(symb)];
char symb2[sizeof(symb)];
char symb3[sizeof(symb)];

IplImage* pict1 = 0;
IplImage* pict2 = 0;
IplImage* pict3 = 0;

char fin_numb [max_number_size];

int id;

using namespace std;

struct list_memb {
	std::string sh;
    	list_memb *next; };

list_memb *head;
// перевірка чи є символ буквою
bool isLetter(char lt)
{
	char letters[12] ={'A','B','C','E','H','I','K','M','O','P','T','X'};
	for (int i=0; i<sizeof(letters); i++)
		if (lt==letters[i])
			return true;
	return false;
}

//перевірка чи є символ цифрою
bool isCipher(char cp)
{
	char letters[12] ={'1','2','3','4','5','6','7','8','9','0'};
	for (int i=0; i<sizeof(letters); i++)
		if (cp==letters[i])
			return true;
	return false;
}

// сортування масивів
void sort(int imas[], char cmas[], int version=0)
{
	if ((id>4)&&(id<12)){//cout<<"size= "<<sizeof(cmas);
	//char* sortsymb;
	//double* sortciph;

	int size=sizeof(symb);
	int i, j;
	int itempl;
	char ctempl;
	//char stempl;
	//double dtemple;
	for(i=0; i<size; i++)
		for(j=size-1; j>i; j--)
		{
			if (imas[j-1]>imas[j])
			{
				itempl=imas[j-1];
				ctempl=cmas[j-1];

				imas[j-1]=imas[j];
				cmas[j-1]=cmas[j];

				
				imas[j]=itempl;
				cmas[j]=ctempl;
			}
		}
	}
}

//правильне розташування букв і цифр
void pos_let_num()
{
	if (id==8)
	{
		for(int i=0; i<sizeof(symb); i++)
		{
			if (((i==0)||(i==1)||(i==6)||(i==7))&&(isCipher(symb[i])))
				symb[i]='O';
			if (((i==2)||(i==3)||(i==4)||(i==5))&&(isLetter(symb[i])))
			{
				symb[i]='_';
			}
			if (((i==0)||(i==1)||(i==6)||(i==7))&&(isCipher(symb[i])))
			{
				symb[i]='_';
			}		
		}
	}
	if ((isLetter(symb[1]))&&(isLetter(symb[2]))&& (isCipher(symb[0])))
	{
		symb[0]=symbol_default_value;
		posi[0]=posi_default_value;
		id--;
		sort(posi, symb);
		
	}
	if ((isLetter(symb[6]))&&(isLetter(symb[7]))&& (isCipher(symb[8])))
	{
		symb[8]=symbol_default_value;
		posi[8]=posi_default_value;
		id--;
		sort(posi, symb);

	}
}


//пропускання "бубликів" від нуля
void bublic()
{
	for(int i=0; i<(int)(sizeof(symb)-1); i++)
		if((symb[i+1]!=symbol_default_value) && ((posi[i]+bublik_lenght)>posi[i+1]))
		{
			#ifdef DEBUG			
				cout<<"bublic on pozition "<<posi[i+1]<<endl;
			#endif
			symb[i+1]=symbol_default_value;
			posi[i+1]=posi_default_value;
			id--;
			sort(posi, symb);
		}
	pos_let_num();
}

void SaveNumber(char file_number[])
{
	
	sprintf(file_number, way_to_save_numbers1,fin_numb);
    
	while (access(file_number,0)!=-1) //if exists
	{
		num++;
		sprintf(file_number, way_to_save_numbers2,fin_numb, num);
	}

	if (pict1!=0)
		cvSaveImage(file_number, pict1);
	else if (pict2!=0)
		cvSaveImage(file_number, pict2);
	else cvSaveImage(file_number, pict3);
}

char* parse (char* temp_mas)
{	
    /*
	int i = strlen(temp_mas)-1;
	bool flag=false;
	while(!flag && i>0)
	{
		if(temp_mas[i]=='/') {flag=true; break;}
		i--;
	}
	if(i!=0) 
	{
	char* mas;
    
	mas = new char[len];
	cout<<"strlen(mas)= ";
	cout<<strlen(mas)<<endl;				
		for(int j=0; j<i; j++)
			mas[j]=temp_mas[i+j+1];	
		return mas;		
	}
	else
		return temp_mas;		
        */
    char *result;
    result = strrchr( temp_mas, '/');
    //if( temp_mas[strlen(temp_mas) - 1]='/' )
    if( result == NULL)
        return temp_mas;
    else if( result != &temp_mas[ strlen(temp_mas) - 1] )
         result++;
    return result;
}
const char *parsename( const char *st)
{
    const char *ptr, *p;
    p = st;
    int index = 0;
    while( (ptr = strchr(p, '/') )  )  {
         if( *ptr ) {
           p = ++ptr;
           index++; }
         }
    if( index > 2 ) {
       p = st;
       index = index - 1;
       while( index && (ptr = strchr( p, '/') ))
         if( *ptr ) {
           p = ++ptr;
           index--; }
           }
    else
       p = st;
    return p;    
}

//запис в report.txt
bool writeReport(char* filename)
{
	ofstream f;
	time_t t=time(NULL);
	struct tm *t_m=localtime(&t);
	char file_number[max_file_size];
	
	//FILE *f=fopen("report.html","w"); // !!!поменять на report_file

	if(symb1[0]!=0) {
		if(symb2[0]!=0) {
			//**************************111
			if(symb3[0]!=0) 
			{
				for(int i=0; (symb1[i]!=0)&&(i<sizeof(symb1)); i++)
				{
					//110
					if ((symb2[i]==symb1[i])&&(symb2[i]!=symb3[i])&&(symb1[i]!=symbol_default_value)&&(symb1[i]!=0))
					{
						f.put(symb1[i]);
						fin_numb[i]=symb1[i];
						#ifdef DEBUG
						cout<<symb1[i];
						#endif
					}
					//101
					else if ((symb1[i]==symb3[i])&&(symb2[i]!=symb1[i])&&(symb1[i]!=symbol_default_value)&&(symb1[i]!=0))
					{
						f.put(symb1[i]);
						fin_numb[i]=symb1[i];
						#ifdef DEBUG
						cout<<symb1[i];
						#endif
					}
					//011
					else if ((symb2[i]==symb3[i])&&(symb2[i]!=symb1[i])&&(symb2[i]!=symbol_default_value)&&(symb2[i]!=0))
					{
						f.put(symb2[i]);
						fin_numb[i]=symb2[i];
						#ifdef DEBUG
						cout<<symb2[i];
						#endif
					}
					//111
					else 
					{
						f.put(symb1[i]);
						fin_numb[i]=symb1[i];
						#ifdef DEBUG
						cout<<symb1[i];
						#endif
					}
				}
			}
			//**************************110
			if(symb3[0]==0) 
			{
				for(int i=0; (symb1[i]!=0)&&(i<sizeof(symb1)); i++)
				{
					if (symb2[i]==symb1[i])
					{
						f.put(symb1[i]);
						fin_numb[i]=symb1[i];
						#ifdef DEBUG
						cout<<symb1[i];
						#endif
					}
					else
					{
						f.put('_');
						fin_numb[i]='_';
						#ifdef DEBUG
						cout<<'_';
						#endif
					}			
				}
			}
		}
		if(symb2[0]==0) {
			//**************************101
			if(symb3[0]!=0) 
			{
				for(int i=0; (symb1[i]!=0)&&(i<sizeof(symb1)); i++)
				{
					if (symb3[i]==symb1[i])
					{
						f.put(symb1[i]);
						fin_numb[i]=symb1[i];
						#ifdef DEBUG
						cout<<symb1[i];
						#endif
					}
					else
					{
						f.put('_');
						fin_numb[i]='_';
						#ifdef DEBUG
						cout<<'_';
						#endif
					}			
				}
			}
			//**************************100
			if(symb3[0]==0) 
			{
				for(int i=0; (symb1[i]!=0)&&(i<sizeof(symb1)); i++)
				{
					f.put(symb1[i]);
					fin_numb[i]=symb1[i];
					#ifdef DEBUG
					cout<<symb1[i];
					#endif
				}
			}
		}
	}

	if(symb1[0]==0) {
		if(symb2[0]!=0) {
			//**************************011
			if(symb3[0]!=0) 
			{
				for(int i=0; (symb2[i]!=0)&&(i<sizeof(symb2)); i++)
				{
					if (symb3[i]==symb2[i])
					{
						f.put(symb2[i]);
						fin_numb[i]=symb2[i];
						#ifdef DEBUG
						cout<<symb2[i];
						#endif
					}
					else
					{
						f.put('_');
						fin_numb[i]='_';
						#ifdef DEBUG
						cout<<'_';
						#endif
					}				
				}
			}
			//**************************010
			if(symb3[0]==0) 
			{
				for(int i=0; (symb2[i]!=0)&&(i<sizeof(symb2)); i++)
				{
					f.put('_');
					fin_numb[i]='_';
					#ifdef DEBUG
					cout<<'_';
					#endif
				}
			}
		}
		if(symb2[0]==0) {
			//**************************001
			if(symb3[0]!=0) 
			{
				for(int i=0; (symb3[i]!=0)&&(i<sizeof(symb3)); i++)
				{
					f.put('_');
					fin_numb[i]='_';
					#ifdef DEBUG
					cout<<'_';
					#endif
				}
			}
			//**************************000
			if(symb3[0]==0) 
			{
				#ifdef DEBUG				
				cout<<"Numbers not found"<<endl; 
				#endif
				//system("pause");
                		return 0;
			}
		}
	}

	f.open(report_file, ios::app);
	f.seekp(0,ios::end);
	f<<"<ul>";
	f<<'\t'<<t_m->tm_mday<<"."<<t_m->tm_mon<<"."<<(1900+t_m->tm_year)<<" "<<t_m->tm_hour<<":"<<t_m->tm_min<<":"<<t_m->tm_sec;
	SaveNumber(file_number);
	//f<<'\t'<<filename;
	//f<<'\t'<<file_number;
    //file_name = 
	f<<'\t'<<"<a href="<<filename<<">";
	f<<parse(filename);
	f<<"</a>";
	f<<'\t'<<"<a href="<<file_number<<">";
	//for(int j=0; j<sizeof(fin_numb); j++)
	//	f<<fin_numb[j];
	f<<parse(file_number);	
	f<<"</a>";
	if (id!=8)
		f<<'\t'<<"[!] Bad recognition. Check image please";
	f<<'\n';
	f<<"</ul>";
	f.close();
	//for(int i=0; i<(int)sizeof(fin_numb); i++)
	//	if(fin_numb[i]!=0) { break;} 

	//cout<<endl;
	return 1;

}

//виведення розпізнаного номера на екран
void printNumb(int version=NULL)
{
	if ((id>4)&&(id<12))
	{
		/*ofstream f;
		time_t t=time(NULL);;
		struct tm *t_m=localtime(&t);
	
		if(symb[0]!='?')
		{
			f.open("report.txt", ios::app);
			f.seekp(0,ios::end);
			cout<<"[i] Write nuber:";
		}*/
		#ifdef DEBUG
		cout<<"[i] Write number:";
		#endif
		for(int i=0; i<sizeof(symb); i++)
			if(symb[i]!=symbol_default_value)
			{
				//f.put(symb[i]);
				#ifdef DEBUG
				cout<<symb[i];
				#endif
				if (version==1){symb1[i]=symb[i]; }
				if (version==2){symb2[i]=symb[i]; }
				if (version==3){symb3[i]=symb[i]; }
			}
		/*if(symb[0]!='?')
		{
			f<<'\t'<<t_m->tm_mday<<"."<<t_m->tm_mon<<"."<<(1900+t_m->tm_year)<<" "<<t_m->tm_hour<<":"<<t_m->tm_min<<":"<<t_m->tm_sec;
			f<<'\t'<<file_number;
			if (id!=8)
				f<<'\t'<<"[!] Bad recognition. Check image please";
			f<<'\n';
			f.close();
			cout<<endl;
		}*/
	}
}

//переформування контура на jpg файлі в xml
void to_countur(string way)
{
	int t =way.size();
	//cout<<t<<endl;
	char* name= new char[t+1];
	name[t]=0;
	memcpy(name,way.c_str(), t);
	//cout<<name<<endl;
	templ = cvLoadImage(name,1);
	name[t-3]='x';
	name[t-2]='m';
	name[t-1]='l';
	#ifdef DEBUG
	cout<<"[i] Load: "<<name<<endl;
	#endif
	IplImage* binTempl =0;
	//	cout<<"yes"<<endl;
	binTempl = cvCreateImage(cvGetSize(templ), 8, 1);
	cvCanny(templ, binTempl, 50, 200);
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* contoursTempl=0;
		
	int contoursMatchT = cvFindContours( binTempl, storage, &contoursTempl, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

    CvSeq* seqTempl=0;
    double perimT = 0;
    if(contoursTempl!=0)
	{
		// находим самый длинный контур 
        for(CvSeq* seq0 = contoursTempl;seq0!=0;seq0 = seq0->h_next)
		{
			double perim = cvContourPerimeter(seq0);
            if(perim>perimT)
			{
				perimT = perim;				
                seqTempl = seq0;								
            }			
        }
    }
	cvSave(name,seqTempl,0,0,cvAttrList(0,0));
	delete [] name;	
}
/*
// пошук шаблонів jpg
void find_template()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	string way;
  
	hFind = FindFirstFile(L"Templates\\*.jpg", &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		printf ("FindFirstFile failed (%d)\n", GetLastError());
		system("PAUSE");
	}
	do 
	{		 
		char ch[100];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP,0,FindFileData.cFileName,-1, ch,260,&DefChar, NULL);
		way=way_to_template+(string)ch;
		to_countur(way);
	}
	while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);
}
*/
//порівняння контурів
void contour_match(CvSeq* seqI, string way)
{
	int t =way.size();
	char* name= new char[t+1];
	name[t]=0;
	memcpy(name,way.c_str(), t);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* templates=0;
	templates=(CvSeq* )cvLoad(name,storage,0,0);
	
	for(CvSeq* seqTER = templates;seqTER!=0;seqTER = seqTER->h_next)
	{
		double match=cvMatchShapes(seqI, seqTER, CV_CONTOURS_MATCH_I3);
		if(match<min_match)
		{
			symbol=name[t-5];
			cvMoments( seqI, &moments);
			min_match=match;
		}
	}
	delete[] name;
}
/*
//пошук та завантаження xml шаблонів
void find_xml(CvSeq* seqI, int posx, int posy,  double height)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	string way;

	min_match=1;
	hFind = FindFirstFile(L"Templates\\*.xml", &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		printf ("[!] FindFirstFile failed (%d)\n", GetLastError());
		system("PAUSE");
	}
	do 
	{		 
		char ch[100];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP,0,FindFileData.cFileName,-1, ch,260,&DefChar, NULL);
		way=way_to_template+(string)ch;
		contour_match(seqI, way);
	}
	while (FindNextFile(hFind, &FindFileData));

	//розпізнавання 6 та 9, 5 та 2
	if((symbol=='9')&&(((moments.m01/moments.m00)-posy)>(height/2)))
	{
		cout<<"change";
		symbol='6';
	}
	if((symbol=='6')&&(((moments.m01/moments.m00)-posy)<(height/2)))
	{
		cout<<"change";
		symbol='9';
	}
	if((symbol=='5')&&(((moments.m01/moments.m00)-posy)>(height/2)))
	{
		cout<<"change";
		symbol='2';
	}
	if((symbol=='2')&&(((moments.m01/moments.m00)-posy)<(height/2)))
	{
		cout<<"change";
		symbol='5';
	}
	if(min_match!=1)
	{
		cout<<symbol<<" "<<min_match<<" "<<endl;
		posi[id]=posx;
		symb[id]=symbol;
		id++;
	}
	FindClose(hFind);
}
*/
//function for linux

void find_xml(CvSeq* seqI, int posx, int posy,  double height)
{
	//WIN32_FIND_DATA FindFileData;
	//HANDLE hFind;
	list_memb  *cur, *prev;

	string way;
	DIR *dfd;
    struct dirent *dp;
	//head=NULL;
	min_match=1;
    if( head == NULL) {
	       dfd=opendir(way_to_template);
	       while( (dp=readdir(dfd)) != NULL )
	         {
	         if( (strlen(dp->d_name)>4) && (dp->d_name[strlen(dp->d_name)-1]=='l') && (dp->d_name[strlen(dp->d_name)-2]=='m') && (dp->d_name[strlen(dp->d_name)-3]=='x') )
		     {	
            //printf("%s\n", dp->d_name);
	           cur = ( list_memb *) new(list_memb);
               if( ! head )
                 head = cur;
      	       else 
               	 prev->next=cur;
			   way=way_to_template+(string)dp->d_name;
               cur->sh  = way;
			   contour_match(seqI, way);
               cur->next = NULL;
           	   prev = cur;	
		      }
	          //cur->sh = dp->d_name;
	        } 
            closedir(dfd);
            }
    else {
        cur = head;
        while( cur != NULL ) {
           contour_match(seqI, cur->sh);
           cur = cur->next; }
    }
	//cur = head;

   	//while( cur ) {
     		//std::cout<<cur->sh<<" "<<cur->next<<std::endl;
    // 		delete cur;
    // 		cur = cur->next; }

   	//cur = head;
    
	
	if((symbol=='9')&&(((moments.m01/moments.m00)-posy)>(height/2)))
	{
		#ifdef DEBUG		
		cout<<"change";
		#endif
		symbol='6';
	}
	if((symbol=='6')&&(((moments.m01/moments.m00)-posy)<(height/2)))
	{
		#ifdef DEBUG
		cout<<"change";
		#endif
		symbol='9';
	}
	if((symbol=='5')&&(((moments.m01/moments.m00)-posy)>(height/2)))
	{
		#ifdef DEBUG
		cout<<"change";
		#endif
		symbol='2';
	}
	if((symbol=='2')&&(((moments.m01/moments.m00)-posy)<(height/2)))
	{
		#ifdef DEBUG
		cout<<"change";
		#endif
		symbol='5';
	}
	#ifdef DEBUG
	cout<<symbol<<" "<<min_match<<" "<<endl;
	#endif	
	posi[id]=posx;
	symb[id]=symbol;
	id++;
}
//визначення чи є контур номерним знаком
void isNumber(IplImage* pict, double hg, double wd, int method)
	{
		string name_to_save;
		bool ok=false;

		IplImage* grayNum = 0;
		IplImage* kvantNum = 0;
		IplImage* fin = 0;
		IplImage* fin2 = 0;
		//IplImage* dst3 = 0;
		//IplImage* dst4 = 0;
		IplImage* img_for = 0;
		bool sv=0;
		int t=0;
		char* name_char;

		grayNum = cvCreateImage( cvGetSize(pict), IPL_DEPTH_8U, 1 );
		fin = cvCloneImage(pict);
		fin2 = cvCreateImage( cvGetSize(pict), IPL_DEPTH_8U, 1 );
		img_for = cvCreateImage( cvGetSize(pict), IPL_DEPTH_8U, 1 );
		kvantNum = cvCreateImage( cvGetSize(pict), IPL_DEPTH_8U, 1 );

		cvCvtColor(pict, grayNum, CV_RGB2GRAY);
		CvScalar averageNum = cvAvg(grayNum);
		#ifdef DEBUG
       		printf("[i] averageNum: %.2f \n", averageNum.val[0]);
		#endif
		//cvNamedWindow("Numbers1",CV_WINDOW_AUTOSIZE);

		cvThreshold(grayNum, kvantNum, (averageNum.val[0]-for_kvant_avg), 255, CV_THRESH_BINARY);
		IplConvKernel* element = cvCreateStructuringElementEx(2, 2, 1, 1,CV_SHAPE_CROSS);
		IplImage* Temp = cvCreateImage( cvGetSize(pict), IPL_DEPTH_8U, 1 );
		cvMorphologyEx(kvantNum, fin2, Temp, element, 3, 1);
		//cvShowImage("Numbers1", kvantNum);
		CvMemStorage* storageNum = cvCreateMemStorage(0);
        	CvSeq* contoursNum=0;
		IplImage* kvantT = cvCloneImage(kvantNum);
		int contoursContNum = cvFindContours( kvantNum, storageNum,&contoursNum,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));
		#ifdef DEBUG
		cvNamedWindow("Numbers",CV_WINDOW_AUTOSIZE);
		cvShowImage("Numbers",pict);
		#endif
		id=0;
		for(int i=0; i<sizeof(symb); i++)
		{
			posi[i]=posi_default_value;
			symb[i]=symbol_default_value;
		}

		for(CvSeq* seq0 = contoursNum;seq0!=0;seq0 = seq0->h_next)
		{
			// вычисляем площадь и периметр контура		52x11.2
			double area = fabs(cvContourArea(seq0));
			double perim = cvContourPerimeter(seq0);

            	cvDrawContours(fin, seq0, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8); // рисуем контур
			CvRect rectNum = cvBoundingRect(seq0);
			//cout<<"areaNum="<<area<<" perimetrNum="<<perim<<endl;
			if (rectNum.height>rectNum.width && (area<(hg*wd)*0.6) && rectNum.height*3>hg )//*6 && area>(rect.height*rect.width)*0.6)
			{
				//cv2("Numbers",CV_WINDOW_AUTOSIZE);
				#ifdef DEBUG
				cout<<"areaNum="<<area<<" perimetrNum="<<perim<<endl;
				#endif				
				cvRectangle(fin, cvPoint(rectNum.x, rectNum.y), cvPoint(rectNum.x+rectNum.width, rectNum.y+rectNum.height), CV_RGB(0,255,0), 0);
				cvSetImageROI(kvantT, cvRect(rectNum.x,rectNum.y,rectNum.width,rectNum.height));
				#ifdef DEBUG
				cvNamedWindow("pict",CV_WINDOW_AUTOSIZE);
				cvShowImage("pict", fin);
				cvWaitKey(100);
				#endif
				find_xml(seq0, rectNum.x, rectNum.y, rectNum.height);
				#ifdef DEBUG
				cout<<"would you like to save contour?"<<endl<<"1 yes"<<endl<<"0 no"<<endl;
				cin>>sv;				
				if (sv==1)

				{							
					cout<<"enter name"<<endl;
					cin>>name_to_save;
					name_to_save=way_to_template+name_to_save+".xml";
					t =name_to_save.size();
					name_char= new char[t+1];
					name_char[t]=0;
					memcpy(name_char,name_to_save.c_str(), t);

					while (access(name_char,0)==0)
					{
						cout<<"File exist. Enter new name"<<endl;
						cin>>name_to_save;
						name_to_save=way_to_template+name_to_save+".xml";
						t =name_to_save.size();
						name_char= new char[t+1];
						name_char[t]=0;
						memcpy(name_char,name_to_save.c_str(), t);
					}	
							
					cvSave(name_char,seq0,0,0,cvAttrList(0,0));
					cout<<"[i] File saved: "<<name_to_save<<endl<<endl;
					delete []name_char;
				}
				#endif
				ok=true;
			}
		}
		

		if ((ok==true)&&(id>4))
		{
			if (method==1) pict1=cvCloneImage(pict);
			if (method==2) pict2=cvCloneImage(pict);
			if (method==3) pict3=cvCloneImage(pict);
		}
	}


//int main(int argc, char* argv[])
int cvmain( char *filename, char *templates, char *numbers, char *numbers1, char *report) 
{
	IplImage* gray = 0;
	IplImage* bin = 0;
	IplImage* dst = 0;
	IplImage* dst2 = 0;
	IplImage* dst3 = 0;
	IplImage* dst4 = 0;
/*
	if (argc >= 2)
		filename = argv[1];	
	else
	{
		int t=0;
		string name_jpg;
		#ifdef DEBUG
		cout<<"Enter name image to load"<<endl;
		#endif
		cin>>name_jpg;
		name_jpg=name_jpg+".jpg";
		t=name_jpg.size();
		filename= new char [t+1];
		filename[t]=0;
		memcpy(filename,name_jpg.c_str(), t);
		while (access(filename,0)==-1)
		{
			#ifdef DEBUG			
			cout<<"[!] No file with such name. Write correct name please."<<endl;
			#endif			
			cin>>name_jpg;
			name_jpg=name_jpg+".jpg";
			t=name_jpg.size();
			filename= new char [t+1];
			filename[t]=0;
			memcpy(filename,name_jpg.c_str(), t);
		}
	}
*/
    	image = cvLoadImage(filename,1);
/*
	way_to_template = argc >= 3 ? argv[2] : "Templates/";
	way_to_save_numbers1 = argc >= 4 ? argv[3] : "NUMBERS/%s.jpg";
	way_to_save_numbers2 = argc >= 5 ? argv[4] : "NUMBERS/%s(%d).jpg";
	report_file = argc >= 6 ? argv[5] : "report.txt";
*/
        way_to_template = templates;
        way_to_save_numbers1 = numbers;
        way_to_save_numbers2 = numbers1;
        report_file = report;
	#ifdef DEBUG	
	cout<<way_to_template<<endl;
    	printf("[i] image: %s\n", filename);
	#endif
    	assert( image != 0 );

    // создаём одноканальные картинки
    gray = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
    bin = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
	dst2 = cvCreateImage( cvSize(image->width, image->height), IPL_DEPTH_8U, 1);

	dst3 = cvCreateImage( cvGetSize(image), IPL_DEPTH_16S, 1);
    dst4 = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1);

    // клонируем
    dst = cvCloneImage(image);
	roiB = cvCloneImage(image);
	roiK = cvCloneImage(image);
	roiL = cvCloneImage(image);

    // окно для отображения картинки
	//cvNamedWindow("kvant",CV_WINDOW_AUTOSIZE);
    //cvNamedWindow("gray",CV_WINDOW_AUTOSIZE);
    //cvNamedWindow("binary",CV_WINDOW_AUTOSIZE);
    //cvNamedWindow("contours",CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("ROI", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("cvLaplace", CV_WINDOW_AUTOSIZE);

    // преобразуем в градации серого
    cvCvtColor(image, gray, CV_RGB2GRAY);
	//cvShowImage("gray",gray);
    // преобразуем в двоичное
	CvScalar average = cvAvg(gray);
	#ifdef DEBUG
    printf("[i] average: %.2f \n", average.val[0]);
	#endif
    cvInRangeS(gray, cvScalar(40), cvScalar(150), bin);
	//cvShowImage("binary",bin);
	cvThreshold(gray, dst2, average.val[0]-for_kvant_avg, 255, CV_THRESH_BINARY);
	//cvShowImage("kvant",dst2);

	// применяем оператор Лапласа
    cvLaplace(gray, dst3, 3); 		//int aperture =3;	
    // преобразуем изображение к 8-битному
    cvConvertScale(dst3, dst4);
	//cvShowImage("cvLaplace", dst4);

    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* contours=0;

    // знаходимо контури методом бінаризації
    int contoursCont = cvFindContours( bin, storage,&contours,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));
    //cvShowImage("binary",bin);
	// нарисуем контуры	
		
    for(CvSeq* seq0 = contours;seq0!=0;seq0 = seq0->h_next)
	{
			// вычисляем площадь и периметр контура		52x11.2
		double area = fabs(cvContourArea(seq0));
		double perim = cvContourPerimeter(seq0);
			//int i=0;

		if (area>MIN_AREA && area<MAX_AREA) //площа номерного знака в пікселях
		{
			// нарисуем контур
            //cvDrawContours(dst, seq0, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8); // рисуем контур

			CvRect rect = cvBoundingRect(seq0);
			// фільтрація по співвідношенню сторін прямокутника, яким можна обвести контур
			if (rect.height*3<rect.width && rect.width<rect.height*6 && area>(rect.height*rect.width)*0.6)
			{
				#ifdef DEBUG
				cout<<endl<<"areaGBin="<<area<<" perimetrGBin="<<perim<<endl;
				#endif
				cvRectangle(dst, cvPoint(rect.x, rect.y), cvPoint(rect.x+rect.width, rect.y+rect.height), CV_RGB(0,255,0), 0);
				cvSetImageROI(roiB, cvRect(rect.x,rect.y,rect.width,rect.height));
				isNumber(roiB, rect.height, rect.width,1);
				sort(posi, symb,1);
				bublic();
				printNumb(1);
			}
		}
	} 

	// знаходимо контури методом Лапласа
	int contoursCont2 = cvFindContours( dst4, storage,&contours,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));

    for(CvSeq* seq0 = contours;seq0!=0;seq0 = seq0->h_next)
	{
		// вираховуємо площу і периметр контурів
		double area = fabs(cvContourArea(seq0));
		double perim = cvContourPerimeter(seq0);

		if (area>MIN_AREA && area<MAX_AREA) //площа номерного знака в пікселях
		{
			//cvDrawContours(dst, seq0, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8); // рисуем контур
			CvRect rect = cvBoundingRect(seq0);
			// фільтрація по співвідношенню сторін прямокутника, яким можна обвести контур
			if (rect.height*3<rect.width && rect.width<rect.height*6 && area>(rect.height*rect.width)*0.6)
			{	
				#ifdef DEBUG				
				cout<<endl<<"areaRLapl="<<area<<" perimetrRLapl="<<perim<<endl;
				#endif
				cvRectangle(dst, cvPoint(rect.x, rect.y), cvPoint(rect.x+rect.width, rect.y+rect.height), CV_RGB(255,0,0), 0);
				cvSetImageROI(roiL, cvRect(rect.x,rect.y,rect.width,rect.height));
				isNumber(roiL,rect.height, rect.width,2);
				sort(posi, symb,2);
				bublic();
				printNumb(2);
			}
		}
	}

	// знаходимо контури методом бінарного квантування
    int contoursCont3 = cvFindContours( dst2, storage,&contours,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));
    //cvShowImage("binary",bin);
	// нарисуем контуры	
    for(CvSeq* seq0 = contours;seq0!=0;seq0 = seq0->h_next)
	{
		// вычисляем площадь и периметр контура		52x11.2
		double area = fabs(cvContourArea(seq0));
		double perim = cvContourPerimeter(seq0);
		//int i=0;

		if (area>MIN_AREA && area<MAX_AREA) //площа номерного знака в пікселях
		{
			// нарисуем контур
            //cvDrawContours(dst, seq0, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8); // рисуем контур
			CvRect rect = cvBoundingRect(seq0);
			// фільтрація по співвідношенню сторін прямокутника, яким можна обвести контур
			if (rect.height*3<rect.width && rect.width<rect.height*6 && area>(rect.height*rect.width)*0.6)
			{
				#ifdef DEBUG
				cout<<endl<<"areaBKvant="<<area<<" perimetrBKvant="<<perim<<endl;
				#endif
				cvRectangle(dst, cvPoint(rect.x, rect.y), cvPoint(rect.x+rect.width, rect.y+rect.height), CV_RGB(0,0,255), 0);
				cvSetImageROI(roiB, cvRect(rect.x,rect.y,rect.width,rect.height));
				isNumber(roiB, rect.height, rect.width,3);
				sort(posi, symb,3);
				bublic();
				printNumb(3);
				//cout<<roiB->height<<" ";
			}
		}
	}
	//if( roiB == 0 && roiK == 0 && roiL == 0 )
       //goto exitt;
	bool end = writeReport(filename);
	#ifdef DEBUG
	cout<<"\nend"<<endl;
	#endif

	// показываем картинки
    //cvShowImage("gray",gray);
	//cvShowImage("kvant",dst2);
    //cvShowImage("binary", bin);
    //cvShowImage("contours", dst);
		
    // ждём нажатия клавиши
    //cvWaitKey(0);
    //exitt:
    // освобождаем ресурсы
    cvReleaseImage(&image);
    cvReleaseImage(&gray);
    cvReleaseImage(&bin);
    cvReleaseImage(&dst);
	cvReleaseImage(&dst2);
	cvReleaseImage(&roiK);
	cvReleaseImage(&roiB);
	cvReleaseImage(&roiL);
	//cvReleaseFileStorage( &fs );
	//cvReleaseImage(&roiM);
    // удаляем окна
//    cvDestroyAllWindows();

	memset(symb1,0,sizeof(symb1));
	memset(symb2,0,sizeof(symb2));
	memset(symb3,0,sizeof(symb3));
	num=0;

   	return end;
}
/*
int main(int argc, char* argv[])
{
	int a = cvmain(argv[1], argv[2], argv[3], argv[4], argv[5]);	
	cout<<a<<endl;
	
	a = cvmain(argv[6], argv[7], argv[8], argv[9], argv[10]);	
	cout<<a<<endl;
	return 0;
}*/

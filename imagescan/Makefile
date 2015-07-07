LIBS := -lopencv_core -lopencv_highgui -lopencv_imgproc
INCLUDES := -I/usr/include/opencv/
#FLAGS := -Wall -O2 
FLAGS := -Wall -g 
NAME := cgi_fetcher
NAMEARM := cgi_afetcher
FILES := imagecompare.c main.c func.c base64.c parseconfigfile.c cvmain.cpp
COMPILER := armv5tel-softfloat-linux-gnueabi-g++
STRIP := armv5tel-softfloat-linux-gnueabi-strip
${NAME}: clean 
	g++  ${FILES} -o ${NAME} ${FLAGS} ${LIBS} ${INCLUDES}
	#strip ${NAME}
clean: 
	rm -fr cgi_fetcher
cleanarm:
	rm -fr cgi_afetcher

arm: cleanarm
	${COMPILER}  ${FILES} -o ${NAMEARM} ${FLAGS} ${LIBS} ${INCLUDES}
	${STRIP}  ${NAMEARM} 
main:	
	g++ cvmain.c -o cvmain ${FLAGS} ${LIBS} ${INCLUDES} -g -DCVMAIN

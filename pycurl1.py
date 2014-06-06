#!/usr/bin/python
import pycurl, urllib

c = pycurl.Curl()

#c.setopt( c.URL, "http://www.kinopoisk.ru/index.php?first=no&what=&kp_query=troubles+with+curves" )
c.setopt( c.URL, "http://www.kinopoisk.ru/index.php?first=no&what=&kp_query=walk+" )
c.setopt( c.USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.47 Safari/537.36")
c.setopt( c.COOKIEFILE, "/home/guileone/testcookie1" )
c.setopt( c.COOKIEJAR, "/home/guileone/testcookie1" )
c.setopt( c.HEADER, False )
c.setopt( c.VERBOSE, True )

a = c.perform()
print(a)





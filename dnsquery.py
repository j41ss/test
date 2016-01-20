#!/usr/bin/env python2
#for name deligate service who work through email
import os, optparse, pywhois
import collections, sys
import datetime, smtplib
from email.mime.text import MIMEText

class InputErr( Exception ): pass

class domain_record:
    def __init__( self, option, domainname ):
        self.__dname = domainname
        self.__sender = option.sender
        self.__send = option.send
        self.__operation = option.operation
        self.__year = option.year
        self.__destination = option.destination
#create header for subject ( ADD, RENEW, REDELEGATE, MODIFY )
        self.__header = self.__create_header(option, domainname)
#if not create dns record trying get info in  self.__data        
        if not self.__header.startswith( "ADD" )  :
            self.__rawdata_set()
        else:
            self.__call_dialog()
#if operation is redelegate or modify call __get_difference        
        if self.__header.startswith( "REDELEGATE" ) or self.__header.startswith("MODIFY") :
            self.__get_difference()
#if operation is renew in self.__data append end file for info renew            
        if self.__header.startswith("RENEW") :
            self.__epil( self.__year )
    def __call_dialog( self ) :
        self.__data = ""
        self.__data += "domain:   {domain}\n".format( domain=self.__dname)
        self.__data += "admin-c:  {adminc}\n".format( adminc=self.__get_line("EI1-UANIC",prompt="admin-c:").strip('\n'))
        i = 0
        while True :
            if i == 0:
                default = "TSNC1-UANIC"
            elif i == 1:
                default = "AK1391-UANIC"
            elif i == 2:
                default = "DW1-UANIC"
            line = self.__get_line(default,prompt="tech-c:").strip( '\n' )
            if line.startswith('exit') :
                break
            else :    
                self.__data += "tech-c:   {techc}\n".format( techc=line )
            i += 1    
        if i == 0:
                self.__data += "tech-c:   {techc}\n".format( techc="TSNC1-UANIC")
        i = 0          
        while True :
            if i == 0:
                default = "ns.example.ua"
            elif i == 1: 
                default = "ns2.example.ua"
            line = self.__get_line(default,prompt="nserver:").strip('\n')
            if line.startswith('exit') :
                break
            else :    
                self.__data += "nserver:  {ns}\n".format(ns=line)
            i += 1    
        if i == 0:
                self.__data += "nserver:  {techc}\n".format( techc=default )
        self.__data += "mnt-by:   UARR129-UANIC (ua.comstar)\n"
        i = 0
        while True:
            if i == 0 :
                default = "Example Ltd."
            if i == 1 :
                default = "Ukraine, Kiev"
            if i == 2 :
                default = "Primary av, 1, 1"
            line = self.__get_line(default,prompt="remark:").strip('\n')
            if line.startswith('exit') :
                break
            else :    
                self.__data += "remark:   {ns}\n".format(ns=line)
            i += 1
        if i == 0:
                self.__data += "remark:   {techc}\n".format( techc=default )
        date = str(datetime.datetime.now()).split(" ")[0]
        date = "".join( date.split('-'))
        self.__data += "changed:  UARR129-UANIC {date}\n".format( date = date )
        self.__data += "source:   UANIC\n"
    def __get_difference ( self ):
        while True:
            try:
                if self.__header.startswith("REDELEGATE"):
                    line = raw_input( "modify admin-c [{0}]:".format( self.__data.split("admin-c:")[1].split()[0] ) )
                    if not line:
                        raise InputErr()
                    self.__modify_data( line, "admin-c:"  )    
                else :
                    i = 1
                    for j in self.__data.split('\n'):
                        if j.startswith("tech-c:") or j.startswith("nserver:") or j.startswith("remark:") :
                            print("[{0}] {1} ".format(i,j))
                            i += 1   
                        else :
                            print("      {0} ".format(j))
                    x = self.__get_digital( i-1 )
                    self.__modify_data( x,None )
                    if x != 0:
                        print("admin-c not change;please change")
                        continue
                    break    
                        
                break

            except InputErr:
                continue
    def __get_digital( self, end=0 ):
        dig = raw_input("Choise digital [0-{0}] [0]:".format(end))
        try:
           dig = int(dig) 
           if dig > end :
               dig = 0
        except ValueError:
            return 0
        return dig
    def __get_line ( self, default, prefix=None, prompt=None ) :
        fr = default.strip('\n')
        if prompt == None : 
            invite = "input string [{0}]:".format(fr)
        else:   
            invite = "{0} [{1}]:".format(prompt,fr)
        x = raw_input(invite)
        if not x:
            return default
        else :
            if prefix is not None:
                x = prefix + x
            return x + '\n'

    def __modify_data( self, line, column ) :
        if column == "admin-c:":
            chunk1 = self.__data.split( column )[0]
            chunk2 = self.__data.split( column )[1][self.__data.split( column )[1].index('\n'):] 
            self.__data = chunk1 + "admin-c:" +" "*4 + line + chunk2
            return True
        else:
            if line == 0 :
                return False
            i = 0
            result = ""
            fl =0 
            for j in self.__data.splitlines(True):
                if j.startswith("tech-c:") or j.startswith("nserver:") or j.startswith("remark:") :
                    i += 1
                if i == line and not fl:
                    x = self.__get_line(j)
                    if not j.startswith("remark:"):
                        spaces = " " * j.count( " " )
                    else :
                        spaces = " " * 5

                    result += j.split(':')[0] + ":" + spaces

                    result += x
                    fl = True
                else:    
                    result += j
            print(result)    
            self.__data = result
            return True

    @property
    def data ( self ):
        return self.__data
    @property
    def destination( self ):
        return self.__destination
    @property
    def sender( self ):
        return self.__sender
    @property
    def valid( self ):
        return self.__valid
    @property 
    def send( self ):
        return self.__send
    @property
    def header( self ):
        return self.__header
    def __epil( self, year) :
        if year  <=  0:
            year = 1
        result = "\n#[RENEW_SECTION]\n+{year} year\n#[END]\n".format(year=year)
	self.__data = str( self.__data)
        self.__data +=  result 
        return True
    def __rawdata_set( self ) :
        domain_rec = ""
        self.__rawdata = pywhois.whois( self.__dname )   
        fl = False
        for i in self.__rawdata.text.split("\n"):
            if fl and not i.startswith("%") and i != "" and not i.startswith("created") \
                and not i.startswith("status") and not i.startswith("dom-"):
               domain_rec += i + "\n"
            if i.startswith("% % .UA whois"):
                fl = True
            if fl and i == "":
                break
            
        if len(domain_rec) > 0:
            self.__data = domain_rec
            self.__valid = True
        else:
            self.__data = None
            self.__valid = False
        return  self.__valid
    def __create_header( self, option, domain ) :
        op = option.operation
        result = ""
        if op == "r" or op == "renew" :
            result = "RENEW"
        elif op == "d" or op == "delete" :
            result = "DEL"
        elif op == "a" or op == "add" :
            result = "ADD"
        elif op == "m" or op == "modify":
            result = "MODIFY"
        else :
            result = "REDELEGATE"
        return "{op} {domain}".format(op=result,domain=domain)    
class InputErro(Exception): pass

def main():
    options, args = parse_options()
    if len(args) :
        a = domain_record( options, *args ) 
    else:
        raise SystemExit
         
    print_record( a )
    if a.send :
        while True:
            try:
                x = raw_input("send[Yes No][no]:" )
                if not x:
                    x = "no"
                x = x.lower()
                if not  x in ("yes","y","n","no" ) :
                    raise InputErro
            except InputErro:
                print("bad choise valid is ( \"yes\" or \"no\" ) " )
                continue
            else:
                break
        if x.startswith("yes") :
            msg = MIMEText(a.data)
            msg[ 'Subject' ] = a.header
            msg[ 'From' ] = a.sender
            msg[ 'To' ] = a.destination
            s = smtplib.SMTP('mail.example.com')
            s.sendmail(a.sender, a.destination, msg.as_string())
            s.quit()
            print("message send: OK")
            
def print_record( obj ):
    if obj.send :
        print("Sender      : {sender}".format( sender = obj.sender))
        print("Destination : {dest}".format( dest = obj.destination) )
        print("Subject     : {subj}".format( subj = obj.header,end="\n\n\n") )
    print(obj.data)



def parse_options():
    valid_operation=("renew", "r", "delete", "d", "add", "a", "modify", "m", "redelegate", "re")
    parser = optparse.OptionParser(usage="usage: %prog [option] domainname", description=
                      "redelegate( change admin-c ), add(adding new domain name), del(delete domain name) , modify(modify nameserver, tech-c and other),\
                      renew( renew domain name )")
    parser.add_option("-o", "--operation", dest="operation", action="store",
                      help="operation {0} [default: \"r\" ] ".format(valid_operation),
                      type="choice", choices=valid_operation, default="r")
    parser.add_option("-s", "--send", dest="send", action="store_true", default=False,
                        help="send message for address")    
    parser.add_option("-S", "--sender", dest="sender", help= " sender mail address [default: hostmaster@example.ua] ",
                      default="hostmaster@example.ua",type=str )

    parser.add_option("-d", "--destination", dest="destination", help= "destination mail address [default: hostmaster@exaple.com] ",
                      default="hostmaster@exaple.com",type=str )
    parser.add_option("-y", "--year", dest="year", default=1, help="for renew how much renew domain name [default: 1 year]", type=int )
    return parser.parse_args()

#def get_record( option ):

    
if __name__ == "__main__":
    main()

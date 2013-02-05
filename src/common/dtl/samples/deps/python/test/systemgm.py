import sys,os,re,socket
def getEnternetInfo():
		filename = '/etc/sysconfig/network-scripts/ifcfg-eth0'
		f = file (filename)
		c = {}
		while True:
				line = f.readline()
				if len(line) == 0:
						break
				if '=' in line:
						if '#' not in line:
								i = 0
								while line[i] != '=':
										i = i + 1
								else:
										a = line[0:i]
										b = line[i+1:]
										c[a] = b
		return c


def getSystemRunTime():
        temp = os.popen("date -d \"$(awk -F. '{print $1}' /proc/uptime) second ago\" +\"%Y-%m-%d %H:%M:%S\" ").readlines()
        str = ''.join(temp)
	return str


def getSystemStartTime ():
        temp = os.popen("cat /proc/uptime| awk -F. '{run_days=$1 / 86400;run_hour=($1 % 86400)/3600;run_minute=($1 % 3600)/60;run_second=$1 % 60;printf(\"%dDay %dHours %dMin %dSec\",run_days,run_hour,run_minute,run_second)}' ").readlines()
        a = ''.join (temp)
	return a 


def getDNS():
        d = []
        i = 0
        line = os.popen("cat /etc/resolv.conf").readlines()
        a = ''.join(line)
        b = re.split(r'\s+',a)
        i = 0;
        while i < len(b):
                c = ''.join(b[i])
                i = i + 1
                if '.' in c:
                        d.append(c)
        e = ' '.join(d)
	return e


def getApacheListenPort ():
        d = []
        temp = os.popen("cat /usr/httpd.conf|grep Listen ").readlines ()
        i = 0
        while i < len(temp):
                c = ''.join(temp[i])
                if '#' in c:
                        i = i + 1
                else:
                        i = i + 1
                        j = 0
                        while True:
                                if c[j] == ' ':
                                        break
                                else:
                                        j = j + 1
                        d.append(c[j+1:])
        e = ' '.join(d)
	return e


def setServicesTime (iDate, iTime):
        str = "date -s \"%d\" &> /dev/null" %(iDate)
#       print str
        if os.system(str) != 0:
                return 0
#       print os.popen(r"date").readlines()

        str = "date -s %d:%d:%d &> /dev/null" %(iTime/10000,(iTime%10000)/100,iTime%100)
#       print str
        if os.system(str) != 0:
        	return 0
        return 1
#       print os.popen(r"date").readlines()


def getServicesName():
        hostname = socket.gethostname()
#       print hostname
        return hostname
        
        
def getCpuNum ():
        str = os.popen(r"cat /proc/cpuinfo | grep processor | wc -l").readlines ()
   #     print str
        return str
        
        
def getCpuType ():
        str = os.popen(r"cat /proc/cpuinfo | grep name | cut -f2 -d:").readlines ()
        str1 = ' '.join (str)
#       print str1
        return str1
        
        
def getCpuMHz ():
        str = os.popen(r"cat /proc/cpuinfo | grep MHz | cut -f2 -d:").readlines ()
        str1 = ' '.join (str)	
#       print str1
        return str1
        
        
def getCacheSize ():
        str = os.popen("cat /proc/cpuinfo | grep \"cache size\" | cut -f2 -d:").readlines()
        str1 = ' '.join (str)
 #       print str1
        return str1
        
        
def getMemTotal ():
        str = os.popen("cat /proc/meminfo | grep MemTotal | cut -f2 -d:").readlines()
        str1 = ' '.join (str)
#        print str1
        return str1
        
        
def getMemFree ():
        str = os.popen("cat /proc/meminfo | grep MemFree | cut -f2 -d:").readlines()
        str1 = ' '.join (str)
#        print str1
        return str1
        
        
def setServicesName (name):
        os.system("hostname " + name)
        str = "/etc/sysconfig/network"
        str1 = "/etc/hosts"
        str2 = "HOSTNAME"
        str3 = "127.0.0.1"
        tmp = os.popen("find " + str + "| xargs grep " + str2).readlines ()
        if len(tmp) == 0:
                os.system("echo " + str2 + "=" + name + " >> " + str)
        else:
                i = tmp[0].find("=")
#               print i
                tmp1 = tmp[0][i+1:-1]
#               print tmp1
#               print "sed 's/" + tmp1 + "/" + name +"/' " +str
                os.system("sed -i 's/" + tmp1 + "/" + name +"/' " +str)

        temp = os.popen("find " + str1 + "| xargs grep " + str3 + "|awk -F ' ' '{print $2}'").readlines ()
        if len(temp) == 0:
                os.system("echo " + str3 + " " + name + " >> " + str1)
        else:
#               print temp
                temp1 = temp[0][0:-1]
#               print "sed -i 's/" + temp1 + "/" + name +"/' " +str1
                os.system("sed -i 's/" + temp1 + "/" + name +"/g' " +str1)
                
                
def setServerPort (i):
        j = '%d'%(i)
        str = "Listen"
        str1 = "/usr/httpd.conf"
        tmp = os.popen("cat " + str1 + "| grep " + str + "| grep -v '#'|awk -F ' ' '{print $2}'").readlines ()
#       tmp = os.popen("cat /usr/httpd.conf | grep Listen |grep -v '#'| awk -F ' ' '{print $2}'").readlines ()
#        print tmp
        if len(tmp) == 0:
                os.system("echo " + str + " " + j + " >> " + str1)
        else:
#                print tmp
                tmp1 = tmp[0][0:-1]
#                print "sed -i 's/" + tmp1 + "/" + j +"/' " +str1
                os.system("sed -i 's/" + tmp1 + "/" + j +"/g' " +str1)
        os.system("service httpd restart &> /dev/null")
        
        
def setEarthnet (strIP, strMask, strGateway, strEarthName):
#        print strIP
        str = "/etc/sysconfig/network-scripts/ifcfg-%s" %(strEarthName)
        tmp = os.popen("cat " + str + "| grep IPADDR | awk -F '=' '{print $2}'").readlines ()
        if len(tmp) == 0:
                os.system("echo IPADDR = " + strIP + " >> " + str)
        else:
                tmp1 = tmp[0][0:-1]
#                print tmp1
                os.system("sed -i 's/" + tmp1 + "/" + strIP + "/' " + str)

        tmpM = os.popen("cat " + str + "| grep NETMASK | awk -F '=' '{print $2}'").readlines ()
        if len(tmpM) == 0:
                os.system("echo NETMASK = " + strMask + " >> " + str)
        else:
                tmpM1 = tmpM[0][0:-1]
#                print tmpM1
                os.system("sed -i 's/" + tmpM1 + "/" + strMask + "/' " + str)

        tmpG = os.popen("cat " + str + "| grep GATEWAY | awk -F '=' '{print $2}'").readlines ()
        if len(tmpG) == 0:
                os.system("echo GATEWAY = " + strGateway + " >> " + str)
        else:
                tmpG1 = tmpG[0][0:-1]
#                print tmpG1
                os.system("sed -i 's/" + tmpG1 + "/" + strGateway + "/' " + str)                                                        

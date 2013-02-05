import os,sys
def getMemTotal ():
        str = os.popen("cat /proc/meminfo | grep MemTotal | cut -f2 -d:").readlines()
        str1 = ' '.join (str)
#        print str1
        return str1


#getMemTotal ()
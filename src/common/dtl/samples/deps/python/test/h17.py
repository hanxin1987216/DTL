import os
def getMemFree ():
        str = os.popen("cat /proc/meminfo | grep MemFree | cut -f2 -d:").readlines()
        str1 = ' '.join (str)
#        print str1
        return str1


#getMemFree ()
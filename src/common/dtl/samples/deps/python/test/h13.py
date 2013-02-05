import os,sys
def getCpuType ():
        str = os.popen(r"cat /proc/cpuinfo | grep name | cut -f2 -d:").readlines ()
        str1 = ' '.join (str)
#       print str1
        return str1


#getCpuType ()
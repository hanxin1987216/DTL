import os
def getCpuMHz ():
        str = os.popen(r"cat /proc/cpuinfo | grep MHz | cut -f2 -d:").readlines ()
        str1 = ' '.join (str)	
#       print str1
        return str1


#getCpuMHz ()
import os
def getCacheSize ():
        str = os.popen("cat /proc/cpuinfo | grep \"cache size\" | cut -f2 -d:").readlines()
        str1 = ' '.join (str)
 #       print str1
        return str1


#getCacheSize ()
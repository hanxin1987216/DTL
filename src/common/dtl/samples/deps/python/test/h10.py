import os,sys,re
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
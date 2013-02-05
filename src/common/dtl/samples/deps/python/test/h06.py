import sys,os
def getSystemRunTime():
        temp = os.popen("date -d \"$(awk -F. '{print $1}' /proc/uptime) second ago\" +\"%Y-%m-%d %H:%M:%S\" ").readlines()
        str = ''.join(temp)
        return str
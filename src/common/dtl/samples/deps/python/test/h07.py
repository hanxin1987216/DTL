import sys,os
def getSystemStartTime ():
        temp = os.popen("cat /proc/uptime| awk -F. '{run_days=$1 / 86400;run_hour=($1 % 86400)/3600;run_minute=($1 % 3600)/60;run_second=$1 % 60;printf(\"%dDay %dHours %dMin %dSec\",run_days,run_hour,run_minute,run_second)}' ").readlines()
        a = ''.join (temp)
        return a           
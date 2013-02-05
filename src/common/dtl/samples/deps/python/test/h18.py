import os,re
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
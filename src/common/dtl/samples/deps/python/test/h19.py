import os,re
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

#setServerPort(80)
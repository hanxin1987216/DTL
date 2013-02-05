import os,re
def setEarthnet (strIP, strMask, strGateway, strEarthName):
#        print strIP
        str = "/etc/sysconfig/network-scripts/ifcfg-%s" %(strEarthName)
        tmp = os.popen("cat " + str + "| grep IPADDR | awk -F '=' '{print $2}'").readlines ()
        if len(tmp) == 0:
                os.system("echo IPADDR = " + strIP + " >> " + str)
        else:
                tmp1 = tmp[0][0:-1]
#                print tmp1
                os.system("sed -i 's/" + tmp1 + "/" + strIP + "/' " + str)

        tmpM = os.popen("cat " + str + "| grep NETMASK | awk -F '=' '{print $2}'").readlines ()
        if len(tmpM) == 0:
                os.system("echo NETMASK = " + strMask + " >> " + str)
        else:
                tmpM1 = tmpM[0][0:-1]
#                print tmpM1
                os.system("sed -i 's/" + tmpM1 + "/" + strMask + "/' " + str)

        tmpG = os.popen("cat " + str + "| grep GATEWAY | awk -F '=' '{print $2}'").readlines ()
        if len(tmpG) == 0:
                os.system("echo GATEWAY = " + strGateway + " >> " + str)
        else:
                tmpG1 = tmpG[0][0:-1]
#                print tmpG1
                os.system("sed -i 's/" + tmpG1 + "/" + strGateway + "/' " + str)


#setEarthnet ("192.168.0.134","255.255.255.0","192.168.1.1","eth0")
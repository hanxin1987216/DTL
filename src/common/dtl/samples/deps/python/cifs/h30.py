import os,h29
def addSambaUser(username):
        h29.refreshSambaTmpPasswdFile ("123456")
#        print username
        str = "/home/sambapasswd.tmp"
        tmp = "cat " + str
        tmp += "|"
        tmp += "/usr/local/samba/bin/smbpasswd -as "
        tmp += username
        tmp += " > /dev/null 2>&1"

        os.system(tmp)

#addSambaUser("fewf")
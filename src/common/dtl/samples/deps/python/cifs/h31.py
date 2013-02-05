import os,h29
def changeSambaPwd(username,passwd):
        h29.refreshSambaTmpPasswdFile (passwd)
        str = "/home/sambapasswd.tmp"
        tmp = "cat " + str
        tmp += "|"
        tmp += "/usr/local/samba/bin/smbpasswd -as "
        tmp += username
        tmp += " > /dev/null 2>&1"

        os.system(tmp)
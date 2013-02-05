import os
def delSambaUser (username):
        str = "rm -rf /sysvol/etc/samba/smb.conf." + username
        os.system(str)

        cmd = "/usr/local/samba/bin/smapasswd -x " + username
        cmd += " > /dev/null 2>&1"
        os.system(cmd)
import os
def restartSMB():
        str = "/etc/init.d/smb restart"
        os.system(str)
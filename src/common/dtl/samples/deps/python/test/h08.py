
import os,sys,re
def getDNS():
        d = []
        i = 0
        line = os.popen("cat /etc/resolv.conf").readlines()
        a = ''.join(line)
        b = re.split(r'\s+',a)
        i = 0;
        while i < len(b):
                c = ''.join(b[i])
                i = i + 1
                if '.' in c:
                        d.append(c)
        e = ' '.join(d)
        return e
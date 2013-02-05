import os,sys
def getApacheListenPort ():
        d = []
        temp = os.popen("cat /usr/httpd.conf|grep Listen ").readlines ()
        i = 0
        while i < len(temp):
                c = ''.join(temp[i])
                if '#' in c:
                        i = i + 1
                else:
                        i = i + 1
                        j = 0
                        while True:
                                if c[j] == ' ':
                                        break
                                else:
                                        j = j + 1
                        d.append(c[j+1:])
        e = ' '.join(d)
        return e
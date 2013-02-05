import h23,re
def getCifsShareDir():
        line = h23.getContent("/etc/samba/smb.conf")
        a = []
        i = 0

        while i < len(line):
                if line[i].find("path =") != -1:
                        j = line[i].find("=")
                        tmp = line[i][j+1:]
                        tmp = tmp.strip()
                        a.append(tmp)
                i += 1
#        print a
        return a
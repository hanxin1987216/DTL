import re,h23
def getShareInfo(origDirName):
        line = h23.getContent("/etc/samba/smb.conf")
#        print origDirName
        shIf = []
        shDN = "\0"
        rl = "\0"
        wl = "\0"
        ru = []
        wu = []
        i = 0
        while i < len(line):
                if line[i].find("path =") != -1:
                        j = line[i].find("=")
                        tmpd = line[i][j+1:]
                        tmpd = tmpd.strip()
#                       tmpd = tmpd[0:-1]
#                       print tmpd
                        if tmpd == origDirName:
                                i += 1
                                if line[i].find("veto files =") != -1:
                                        i -= 2
                                        shDN = line[i][1:-2]
                                        i += 4
                                        rl = line[i]
                                        i +=1
                                        wl = line[i]
                                else:
                                        i -= 2
                                        shDN = line[i][1:-2]
                                        i += 3
                                        rl = line[i]
                                        i += 1
                                        wl = line[i]
                i += 1

        j = rl.find("=")
        tmp = rl[j+1:]
        tmp = tmp.strip()
        if tmp != "\0":
                ru = re.split(r',',tmp)
#               print ru
        j = wl.find("=")
        tmp = wl[j+1:]
        tmp = tmp.strip()
        if tmp != "\0":
                wu = re.split(r',',tmp)

        k = 0
        while k < len(ru):
                a = []
                if ru[k].find("@") != -1:
                        a.append(ru[k])
                        a.append(0)
                        a.append(1)
                else:
                        a.append(ru[k])
                        a.append(0)
                        a.append(0)
                shIf.append(a)
                k += 1
        k = 0
        while k < len(wu):
                a = []
                if wu[k].find("@") != -1:
                        a.append(wu[k])
                        a.append(1)
                        a.append(1)
                else:
                        a.append(wu[k])
                        a.append(1)
                        a.append(0)
                shIf.append(a)
                k += 1
        Info = []
        Info.append(shDN)
        Info.append(shIf)
#        print Info
        return Info
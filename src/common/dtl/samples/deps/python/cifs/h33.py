import re,h23,h24,h26,h25
def removeCifsShare (origDirName):
        hasfind = False
        hasfilt = False
        #print origDirName
        line = h23.getContent("/etc/samba/smb.conf")
        i = 0

        while i < len(line):
                if line[i].find("path =") != -1:
                        j = line[i].find("=")
                        tmpd = line[i][j+1:]
                        tmpd = tmpd.strip()
                        #print tmpd
                        if tmpd == origDirName:
                                hasfind = True
                                i += 1
                                if line[i].find("veto files") !=-1:
                                        hasfilt = True
                                break
                i += 1

        if hasfind == False:
                return 0

        if hasfind == True:
                i -= 2
                k = 7
                if hasfilt == True:
                        k = 8
                del line[i:i+k]

        h24.fileWriteLines("/etc/samba/smb.conf",line)
        h25.cpSmbConfig ()
        h26.restartSMB ()
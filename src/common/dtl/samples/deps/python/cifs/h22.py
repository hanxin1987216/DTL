import os,h23,re
def hasFind (shareName, sharePath, readlist, writelist, validusers, origDirName, shareDirName):
        hasfind = 0
        findfilter = 0
        line = h23.getContent("/etc/samba/smb.conf")
        i = 0
        while i < len (line):
                if line[i].find("path =") != -1:
                        j = line[i].find('=');
                        tmp = line[i][j+1:]
                        tmp = tmp.strip()
                        if tmp == origDirName:
                                hasfind = 1
                                i = i + 1
                                if line[i].find("veto files =") != -1:
                                        findfilter = 1
                                break
                i = i + 1

        k = 0
        #print line[k]
        tmp2 = shareName
        tmp2 = tmp2.lower()
        while k < len (line):
                if line[k].find("[") == 0:
                        tmp1 = line[k]
                        tmp1 = tmp1.strip()
                        if tmp1 == tmp2:
                                #print line[k+1][0:-1]
                                #print sharePath
                                if line[k+1][0:-1] != sharePath:
                                        return 0
                k = k + 1

        #print line
        if hasfind == 1:
                i = i - 2
                line[i] = shareName
                if findfilter == 1:
                        i = i + 4
                else:
                        i = i + 3
                line[i] = readlist
                i = i + 1
                line[i] = writelist
                i = i + 1
                line[i] = validusers
#               print line
        else:
                line.append("\n")
                line.append(shareName)
                line.append(sharePath)
                line.append("\tpublic = no")
                line.append(readlist)
                line.append(writelist)
                line.append(validusers)
        return line
#       print line
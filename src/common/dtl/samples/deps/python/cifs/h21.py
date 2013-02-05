import os,re,h22,h24,h25,h26
def editDirShare (origDirName,shareDirName,*shareInfo):
        shareName = "[" +shareDirName + "]"
        shareName.lower ()
        sharePath = "\tpath = " + origDirName
        i = 0
        writelist = "\0"
        readlist = "\0"

#        print shareInfo
        while i < len(shareInfo[0]):
                if shareInfo[0][i][1] == 0:
                        if shareInfo[0][i][2] == 1:
                                readlist += ",@"
                                readlist += shareInfo[0][i][0]
                        else:
                                readlist += ","
                                readlist += shareInfo[0][i][0]
                        i = i + 1
                else:
                        if shareInfo[0][i][2] == 1:
                                writelist += ",@"
                                writelist += shareInfo[0][i][0]
                        else:
                                writelist = writelist + ","
                                writelist += shareInfo[0][i][0]
                        i = i + 1

        if len(readlist)!=0:
                readlist = readlist[2:]

        if len(writelist) != 0:
                writelist = writelist[2:]

        validusers = "\tvalid users = " + readlist

        if len(readlist) != 0:
                if len(writelist) != 0:
                        validusers += "," + writelist

        readlist = "\tread list = " + readlist
        writelist = "\twrite list = " + writelist
        #print readlist
        #print writelist

        line = h22.hasFind (shareName, sharePath, readlist, writelist, validusers, origDirName, shareDirName)
        #print line
        if line == 0:
                return 0
        if line != 0:
                h24.fileWriteLines("/etc/samba/smb.conf", line)
                h25.cpSmbConfig ()
                h26.restartSMB ()
        return 1
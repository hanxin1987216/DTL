import os,h23,re,h24
def cpSmbConfig ():
        a = []
        line = h23.getContent("/etc/samba/smb.conf")
        i = 0
        while i < len(line):
                if line[i].find("valid users =") != -1:
                        j = line[i].find("=")
                        tmp = line[i][j+1:]
                        tmp = tmp.strip ()
                        tmp1 = re.split(r',',tmp)
                        j = 0
                        while j < len(tmp1):
                                a.append(tmp1[j])
                                j = j + 1
                i = i + 1
        os.system("rm -rf /sysvol/etc/samba/smb.conf.*")
        #print a

        k = 0
        while k < len(a):
                str = "\\cp /sysvol/etc/samba/smb.conf /sysvol/etc/samba/smb.conf." + a[k].strip ()
                os.system(str)
                #print str
                k = k + 1

        k = 0
        while k < len(a):
                filepath = "/sysvol/etc/samba/smb.conf." + a[k].strip ()
                tmp2 = h23.getContent(filepath)
                #print len(tmp2)
                j = 0
                while j < len(tmp2):
                        if tmp2[j].find('valid users =') != -1:
                                b = []
                                hasfind = 0
                                #print j
                                #print len(tmp2)
                                l = tmp2[j].find("=")
                                tmp3 = tmp2[j][l+1:]
                                #print tmp3
                                tmp3 = tmp3.strip()
                                tmp4 = re.split(r',',tmp3)
                                #print tmp4
                                n = 0
                                while n < len(tmp4):
                                        b.append(tmp4[n])
                                        n = n + 1
                                m = 0
                                while m < len(b):
                                        #print b[m]
                                        #print a[k]
                                        if b[m] == a[k]:
                                                hasfind = 1
                                                break
                                        m = m + 1
                                if hasfind == 1:
                                        #print "GGGGGGGG"
                                        #print tmp2
                                        tmp2[j-1:0] = ["\tbrowseable = no\n"]
                                        #print tmp2
                                        #print j
                                        j = j + 1
                                        #print j
                                else:
                                        j = j + 1
                                j = j + 1
                        else:
                                j = j + 1
                #print filepath
                #print tmp2
                h24.fileWriteLines(filepath, tmp2)
                k = k + 1
        #print a
import h24
def refreshSambaTmpPasswdFile(pwd):
        a = []

        a.append(pwd)
        a.append(pwd)

        h24.fileWriteLines("/home/sambapasswd.tmp",a)
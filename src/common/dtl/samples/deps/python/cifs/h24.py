import os
def fileWriteLines(filepath, *line):
        rf = open (filepath, "w")
        i = 0
        while i < len (line[0]):
                rf.write(line[0][i])
                if line[0][i][-1] != "\n":
                        rf.write("\n")
                i = i + 1
        rf.close()
#       rf = open (filepath, "a+")
#       print rf.read()
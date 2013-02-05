import os
def getContent(filepath):
        f = file(filepath)
        a = []
        i = 0
        while True:
                line = f.readlines()
                if len(line) == 0:
                        break
                else:
                        a = line
        return a
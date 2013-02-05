import os
def getCpuNum ():
        str = os.popen(r"cat /proc/cpuinfo | grep processor | wc -l").readlines ()
  #      print str
        return str


#getCpuNum ()
import sys
def getEnternetInfo():
  filename = '/etc/sysconfig/network-scripts/ifcfg-eth0'
  f = file (filename)
  c = {}
  while True:
   line = f.readline()
   if len(line) == 0:
     break
   if '=' in line:
     if '#' not in line:
       i = 0
       while line[i] != '=':
         i = i + 1
       else:
         a = line[0:i]
         b = line[i+1:]
         c[a] = b

  return c

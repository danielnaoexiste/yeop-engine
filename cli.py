import sys, os
import subprocess

TOOLS_DIR = "tools"

def runCommand(cmd):
  script = "{}/{}.py".format(TOOLS_DIR, cmd)
  ret = 0

  if os.path.exists(script):
    ret = subprocess.call(["python3", script])
  else:
    print("Invalid command:", cmd)
    ret = -1
  
  return ret

for i in range(1, len(sys.argv)):
  cmd = sys.argv[i]
  if runCommand(cmd) != 0:
    break
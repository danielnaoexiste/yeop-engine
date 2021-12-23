import globals
import sys, subprocess

if globals.isWindows():
  ret = subprocess.call(["cmd.exd", '/c', "premake\\premake5", "vs2019"])

if globals.isLinux():
  ret = subprocess.call(["premake/premake5.linux", "gmake2"])

if globals.isMac():
  ret = subprocess.call(["premake/premake5", 'gmake2'])
  ret = subprocess.call(["premake/premake5", 'xcode4'])

sys.exit(ret)
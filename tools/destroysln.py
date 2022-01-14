import globals
import os, sys, subprocess

args = globals.ProcessArguments(sys.argv)
CONFIG = globals.GetArgumentValue(args, "config", "debug")

print("Building config: " + CONFIG)
ret = 0

if globals.isWindows():
    VS_BUILD_PATH = os.environ["VS_BUILD_PATH"][8:-1]
    VS_BUILD_PATH = "C:\\\\" + VS_BUILD_PATH

    ret = subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, "{}.sln".format(globals.ENGINE_NAME), "/property:Configuration={}".format(CONFIG)])

if globals.isLinux():
    ret = subprocess.call(["make", "config={}".format(CONFIG)])

if globals.isMac():
    ret = subprocess.call(["make", "config={}".format(CONFIG)])

sys.exit(ret)
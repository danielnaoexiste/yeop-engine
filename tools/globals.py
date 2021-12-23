import sys, platform

V_MAJOR = '0'
V_MINOR = '01'

ENGINE_NAME = "yeop"
PROJECT_NAME = "yeop-editor"
TOOLS_DIR = "tools"

PLATFORM = sys.platform
for x in platform.uname():
    if "microsoft" in x.lower():
        PLATFORM = "windows"
        break

def isWindows():
    return PLATFORM == "windows" or PLATFORM == "win32"

def isLinux():
    return PLATFORM == "linux"

def isMac():
    return PLATFORM == "darwin"

def ProcessArguments(argv):
    ret = {} # return a key:value dict
    for arg in argv:
        try:
            k = arg[0:arg.index("=")]
            v = arg[arg.index("=")+1:]
        except:
            k = arg
            v = 0
        ret[k] = v
    return ret

def GetArgumentValue(args, name, default):
    return args[name] if name in args else default
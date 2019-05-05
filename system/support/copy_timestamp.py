import os
import sys

ts = os.stat(sys.argv[1]).st_mtime
os.utime(sys.argv[2], (ts-100000000, ts-100000000))

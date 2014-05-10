#!/usr/bin/python

import sys
import os, os.path
import subprocess
import datetime
import shutil
import shlex

# src tmx path - sys.argv[1]
# dst folder path - sys.argv[2]
# extension - sys.argv[3]

def run():
	if len(sys.argv) != 4:
		print 'Usage: ' + os.path.basename(os.path.realpath(__file__)) + ' src_tmx_path dst_folder extension'
		sys.exit(1)

	if os.path.isfile(sys.argv[1]):
		dstTMXPath = os.path.join(sys.argv[2], os.path.basename(sys.argv[1]))
		
		flag = False
		if os.path.isfile(dstTMXPath):
			srcModDate = datetime.datetime.fromtimestamp(os.path.getmtime(sys.argv[1]))
			dstModDate = datetime.datetime.fromtimestamp(os.path.getmtime(dstTMXPath))
			if srcModDate > dstModDate:
				flag = True
		else:
			flag = True
			
		if flag:
			shutil.copyfile(sys.argv[1], dstTMXPath)
			scriptDir = os.path.dirname(os.path.realpath(__file__))
			subprocess.call([os.path.join(scriptDir, '../Tools/tmxExt'), dstTMXPath, sys.argv[3]])
			

# -------------- main --------------
if __name__ == '__main__':
    run()

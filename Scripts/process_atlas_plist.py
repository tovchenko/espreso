#!/usr/bin/python

import sys
import os, os.path
import subprocess
import datetime
import shutil
import shlex

# src plist path - sys.argv[1]
# dst folder path - sys.argv[2]
# extension - sys.argv[3]

def callStdOut(cmd):
    args = shlex.split(cmd)
 
    proc = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = proc.communicate()
    return out

def run():
	if len(sys.argv) != 4:
		print 'Usage: ' + os.path.basename(os.path.realpath(__file__)) + ' src_plist_path dst_folder extension'
		sys.exit(1)

	if os.path.isfile(sys.argv[1]):
		dstPlistPath = os.path.join(sys.argv[2], os.path.basename(sys.argv[1]))
		
		flag = False
		if os.path.isfile(dstPlistPath):
			srcModDate = datetime.datetime.fromtimestamp(os.path.getmtime(sys.argv[1]))
			dstModDate = datetime.datetime.fromtimestamp(os.path.getmtime(dstPlistPath))
			if srcModDate > dstModDate:
				flag = True
		else:
			flag = True
			
		if flag:
			filename = callStdOut('/usr/libexec/PlistBuddy -c \"Print :metadata:realTextureFileName\" ' + sys.argv[1])
			filename = filename.replace('.png', '.' + sys.argv[3])
			if filename[-1] == '\n':
				filename = filename[:-1]
			shutil.copyfile(sys.argv[1], dstPlistPath)
			subprocess.call(['/usr/libexec/PlistBuddy', '-c', 'Set :metadata:realTextureFileName ' + filename, dstPlistPath])
			subprocess.call(['/usr/libexec/PlistBuddy', '-c', 'Set :metadata:textureFileName ' + filename, dstPlistPath])
			

# -------------- main --------------
if __name__ == '__main__':

    run()

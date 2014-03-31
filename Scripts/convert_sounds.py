#!/usr/bin/python

import sys
import os, os.path
import subprocess


def run():
	if len(sys.argv) != 4:
		print 'Usage: ' + os.path.basename(os.path.realpath(__file__)) + ' app_root dst_path format(caf, ogg, mp3)'
		sys.exit(1)
	
	scriptDir = os.path.dirname(os.path.realpath(__file__))
	appRoot = sys.argv[1]
	
	srcPath = os.path.join(appRoot, 'Assets/Sounds')
	intermediatesPath = os.path.join(os.path.join(appRoot, 'runtime/Intermediates/Sounds'), sys.argv[3])
	
	if sys.argv[3] == 'caf':
		if not os.path.exists(intermediatesPath):
			os.makedirs(intermediatesPath)
					
		converter = os.path.join(scriptDir, '../Tools/smart_wav2caf.py')
		subprocess.call([converter, srcPath, intermediatesPath])
	elif sys.argv[3] == 'ogg':
		if not os.path.exists(intermediatesPath):
			os.makedirs(intermediatesPath)
			
		converter = os.path.join(scriptDir, '../Tools/smart_wav2ogg.py')
		subprocess.call([converter, srcPath, intermediatesPath])
	elif sys.argv[3] == 'mp3':
		if not os.path.exists(intermediatesPath):
			os.makedirs(intermediatesPath)
			
		converter = os.path.join(scriptDir, '../Tools/smart_wav2mp3.py')
		subprocess.call([converter, srcPath, intermediatesPath])
	else:
		print 'Unknown sound type: ' + sys.argv[3]
		sys.exit(1)
		
	xcopy = os.path.join(scriptDir, '../Tools/xcopy')
	subprocess.call([xcopy, os.path.join(intermediatesPath, '*.*'), sys.argv[2]])

# -------------- main --------------
if __name__ == '__main__':

    run()

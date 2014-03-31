#!/usr/bin/python
# smart_wav2caf.py
# Convert sounds


import sys
import os, os.path
import datetime
import subprocess
import re


def convert(srcPath, dstPath, subPath):	
	fullSrcPath = os.path.join(srcPath, subPath)
	
	for filename in os.listdir(fullSrcPath):
		srcFilePath = os.path.join(fullSrcPath, filename)
		if os.path.isdir(srcFilePath):
			convert(srcPath, dstPath, os.path.join(subPath, filename))
		elif os.path.isfile(srcFilePath):
			ext = re.search(r'\.(.*)', filename).groups()[0].lower()
			if ext == 'wav':
				dstPath = os.path.join(dstPath, subPath)
				dstFilePath = os.path.join(dstPath, filename.replace('.wav', '.caf'));
			
				if os.path.isfile(dstFilePath):
					srcModDate = datetime.datetime.fromtimestamp(os.path.getmtime(srcFilePath))
					dstModDate = datetime.datetime.fromtimestamp(os.path.getmtime(dstFilePath))
					if srcModDate <= dstModDate:
						continue
					
				if not os.path.exists(dstPath):
					os.makedirs(dstPath)
				
				print 'Convert ' + filename + ' to caf file.'
				subprocess.call(['afconvert', '-f', 'caff', '-d', 'ima4@22050', srcFilePath, dstFilePath])
		else:
			print 'ERROR: File or directory doesn\'t exist.'
			sys.exit(1)


def run():
	if len(sys.argv) != 3:
		print 'Usage: ' + os.path.basename(os.path.realpath(__file__)) + ' src_folder dst_folder'
		sys.exit(1)
	
	convert(sys.argv[1], sys.argv[2], '')

# -------------- main --------------
if __name__ == '__main__':

    run()

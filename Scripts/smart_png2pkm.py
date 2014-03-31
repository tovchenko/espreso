#!/usr/bin/python

import sys
import os, os.path
import subprocess
import datetime
import re

# $1 - source dir
# $2 - destination dir
# $3 - has alpha (yes,no)
# $4 - scale
# $5 - max size

def convert(srcPath, dstPath, subPath, format, scale, maxSize):	
	fullSrcPath = os.path.join(srcPath, subPath)
	
	for filename in os.listdir(fullSrcPath):
		srcFilePath = os.path.join(fullSrcPath, filename)
		if os.path.isdir(srcFilePath):
			convert(srcPath, dstPath, os.path.join(subPath, filename), format, scale, maxSize)
		elif os.path.isfile(srcFilePath):
			ext = re.search(r'\.(.*)', filename).groups()[0].lower()
			if ext == 'png':
				dstPath = os.path.join(dstPath, subPath)
				dstFilePath = os.path.join(dstPath, filename.replace('.png', '.pkm') if format != 'yes' else filename.replace('.png', '.pvr.ccz'));
			
				if os.path.isfile(dstFilePath):
					srcModDate = datetime.datetime.fromtimestamp(os.path.getmtime(srcFilePath))
					dstModDate = datetime.datetime.fromtimestamp(os.path.getmtime(dstFilePath))
					if srcModDate <= dstModDate:
						continue
					
				if not os.path.exists(dstPath):
					os.makedirs(dstPath)
				
				print 'Convert ' + filename + (' to pkm file.' if format != 'yes' else ' to pvr.ccz file.')
				scriptPath = os.path.dirname(os.path.realpath(__file__))
				
				tmpPath = dstFilePath if format == 'yes' else os.path.join(scriptPath, filename)
				packer = os.path.join(scriptPath, '../Tools/TexturePacker.app/Contents/MacOS/TexturePacker')
				subprocess.call([packer, srcFilePath,
					'--quiet',
					'--sheet', tmpPath,
					'--algorithm', 'Basic',
			 		'--allow-free-size',
			 		'--border-padding', '0',
			 		'--shape-padding', '0',
					'--inner-padding', '0',
			 		'--no-trim',
			 		'--opt', 'RGBA8888' if format == 'yes' else 'RGB888',
				 	'--scale', scale,
			 		'--max-size', maxSize,
			 		'--dither-fs'])
			 		
			 	if format != 'yes':
			 		compressor = os.path.join(scriptPath, '../Tools/etc1tool')
			 		subprocess.call([compressor, tmpPath, '-o', dstFilePath])
			 		os.remove(tmpPath)
					
				plistPath = os.path.join(fullSrcPath, filename.replace('.png', '.plist'))
				if os.path.isfile(plistPath):
					processor = os.path.join(scriptPath, 'process_atlas_plist.py')
					subprocess.call([processor, plistPath, dstPath, 'pkm' if format != 'yes' else 'pvr.ccz'])
						
		else:
			print 'ERROR: File or directory doesn\'t exist.'
			sys.exit(1)
			

def run():
	if len(sys.argv) != 6:
		print 'Usage: ' + os.path.basename(os.path.realpath(__file__)) + ' src_folder dst_folder has_alpha(yes,no) scale max_size'
		sys.exit(1)
	
	convert(sys.argv[1], sys.argv[2], '', sys.argv[3], sys.argv[4], sys.argv[5])
	
	outfile = os.path.join(os.getcwd(), 'out.plist')
	if os.path.isfile(outfile):
		os.remove(outfile)
			

# -------------- main --------------
if __name__ == '__main__':

    run()

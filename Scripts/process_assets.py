#!/usr/bin/python

import sys
import os, os.path
import subprocess
import re

# app root - sys.argv[1]
# dst path - sys.argv[2]
# texture format - sys.argv[3]

def processTMX(srcPath, dstPath):
	for filename in os.listdir(srcPath):
		srcFilePath = os.path.join(srcPath, filename)
		if os.path.isfile(srcFilePath):
			ext = re.search(r'\.(.*)', filename).groups()[0].lower()
			if ext == 'tmx':
				processor = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'process_tmx.py')
				subprocess.call([processor, srcFilePath, dstPath, sys.argv[3]])

def run():
	if len(sys.argv) != 4:
		print 'Usage: ' + os.path.basename(os.path.realpath(__file__)) + ' app_root dst_folder texture_format'
		sys.exit(1)
	
	scriptDir = os.path.dirname(os.path.realpath(__file__))
	appRoot = sys.argv[1]
	
	textureFolder = os.path.join(appRoot, 'runtime/Intermediates/Textures')
	textureFolder = os.path.join(textureFolder, sys.argv[3])
	if not os.path.exists(textureFolder): os.makedirs(textureFolder)
		
	texSD = os.path.join(textureFolder, 'SD')
	if not os.path.exists(texSD): os.makedirs(texSD)
	texHD = os.path.join(textureFolder, 'HD')
	if not os.path.exists(texHD): os.makedirs(texHD)
	texHDR = os.path.join(textureFolder, 'HDR')
	if not os.path.exists(texHDR): os.makedirs(texHDR)
	
	textool = os.path.join(scriptDir, 'smart_png2pkm.py' if sys.argv[3] == 'pkm' else ('smart_png2pvrccz.py' if sys.argv[3] == 'pvr.ccz' else 'smart_png2png.py'))
	srcTexsPath = os.path.join(appRoot, 'Assets/Textures')
	
	# Scales and converts RGBA images from Shared to HDR, HD, SD folders
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/Shared'), texSD, 'yes', '0.25', '1024'])
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/Shared'), texHD, 'yes', '0.5', '2048'])
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/Shared'), texHDR, 'yes', '1', '4096'])
	# Just converts RGBA images
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/SD'), texSD, 'yes', '1', '1024'])
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/HD'), texHD, 'yes', '1', '2048'])
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/HDR'), texHDR, 'yes', '1', '4096'])
	# Scales and converts RGB images from Shared to HDR, HD, SD folders
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/Shared'), texSD, 'no', '0.25', '1024'])
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/Shared'), texHD, 'no', '0.5', '2048'])
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/Shared'), texHDR, 'no', '1', '4096'])
	# Just converts RGB images
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/SD'), texSD, 'no', '1', '1024'])
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/HD'), texHD, 'no', '1', '2048'])
	subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/HDR'), texHDR, 'no', '1', '4096'])

	# Copy
	xcopy = os.path.join(scriptDir, '../Tools/xcopy')
	
	dstSD = os.path.join(sys.argv[2], 'SD')
	if not os.path.exists(dstSD): os.makedirs(dstSD)
	dstHD = os.path.join(sys.argv[2], 'HD')
	if not os.path.exists(dstHD): os.makedirs(dstHD)
	dstHDR = os.path.join(sys.argv[2], 'HDR')
	if not os.path.exists(dstHDR): os.makedirs(dstHDR)
	
	subprocess.call([xcopy, os.path.join(texSD, '*.*'), dstSD])
	subprocess.call([xcopy, os.path.join(texHD, '*.*'), dstHD])
	subprocess.call([xcopy, os.path.join(texHDR, '*.*'), dstHDR])
	
	processTMX(os.path.join(srcTexsPath, 'rgba/SD'), dstSD)
	processTMX(os.path.join(srcTexsPath, 'rgba/HD'), dstHD)
	processTMX(os.path.join(srcTexsPath, 'rgba/HDR'), dstHDR)
	processTMX(os.path.join(srcTexsPath, 'rgb/SD'), dstSD)
	processTMX(os.path.join(srcTexsPath, 'rgb/HD'), dstHD)
	processTMX(os.path.join(srcTexsPath, 'rgb/HDR'), dstHDR)

	srcBundlePath = os.path.join(appRoot, 'Assets')
	subprocess.call([xcopy, os.path.join(srcBundlePath, 'Data/*.*'), sys.argv[2]])
	subprocess.call([xcopy, os.path.join(scriptDir, '../Sources'), sys.argv[2]])
	subprocess.call([xcopy, os.path.join(appRoot, 'src/*.*'), os.path.join(sys.argv[2], 'Sources')])
	

# -------------- main --------------
if __name__ == '__main__':

    run()

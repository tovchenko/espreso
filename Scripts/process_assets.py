#!/usr/bin/python

import sys
import os, os.path
import subprocess
import re
import argparse


def processTMX(srcPath, dstPath, fmt):
	for filename in os.listdir(srcPath):
		srcFilePath = os.path.join(srcPath, filename)
		if os.path.isfile(srcFilePath):
			ext = re.search(r'\.(.*)', filename).groups()[0].lower()
			if ext == 'tmx':
				processor = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'process_tmx.py')
				subprocess.call([processor, srcFilePath, dstPath, fmt])

def run():
	parser = argparse.ArgumentParser(prog='PROCESS RESOURCES')
	parser.add_argument('-appRoot')
	parser.add_argument('-dst')
	parser.add_argument('-fmt')
	parser.add_argument('-lods', nargs='*', default=['HDR', 'HD', 'SD'])
	parser.add_argument('-skipSrc', action='store_true', default=False)
	args = parser.parse_args()
	
	scriptDir = os.path.dirname(os.path.realpath(__file__))
	
	textureFolder = os.path.join(args.appRoot, 'runtime/temp/Textures')
	textureFolder = os.path.join(textureFolder, args.fmt)
	if not os.path.exists(textureFolder): os.makedirs(textureFolder)
	
	texSD = texHD = texHDR = dstSD = dstHD = dstHDR = None
	for lod in args.lods:
		if lod == 'SD':
			texSD = os.path.join(textureFolder, 'SD')
			dstSD = os.path.join(args.dst, 'SD')
		elif lod == 'HD':
			texHD = os.path.join(textureFolder, 'HD')
			dstHD = os.path.join(args.dst, 'HD')
		elif lod == 'HDR':
			texHDR = os.path.join(textureFolder, 'HDR')
			dstHDR = os.path.join(args.dst, 'HDR')
			
	textool = os.path.join(scriptDir, 'smart_png2pkm.py' if args.fmt == 'pkm' else ('smart_png2pvrccz.py' if args.fmt == 'pvr.ccz' else 'smart_png2png.py'))
	srcTexsPath = os.path.join(args.appRoot, 'assets/Textures')
	xcopy = os.path.join(scriptDir, '../Tools/xcopy')
		
	if texSD:
		if not os.path.exists(texSD): os.makedirs(texSD)
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/Shared'), texSD, 'yes', '0.25', '1024'])
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/SD'), texSD, 'yes', '1', '1024'])
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/Shared'), texSD, 'no', '0.25', '1024'])
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/SD'), texSD, 'no', '1', '1024'])
		if not os.path.exists(dstSD): os.makedirs(dstSD)
		subprocess.call([xcopy, os.path.join(texSD, '*.*'), dstSD])
		processTMX(os.path.join(srcTexsPath, 'rgba/SD'), dstSD, args.fmt)
		processTMX(os.path.join(srcTexsPath, 'rgb/SD'), dstSD, args.fmt)
		
	if texHD:
		if not os.path.exists(texHD): os.makedirs(texHD)
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/Shared'), texHD, 'yes', '0.5', '2048'])
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/HD'), texHD, 'yes', '1', '2048'])
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/Shared'), texHD, 'no', '0.5', '2048'])
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/HD'), texHD, 'no', '1', '2048'])
		if not os.path.exists(dstHD): os.makedirs(dstHD)
		subprocess.call([xcopy, os.path.join(texHD, '*.*'), dstHD])
		processTMX(os.path.join(srcTexsPath, 'rgba/HD'), dstHD, args.fmt)
		processTMX(os.path.join(srcTexsPath, 'rgb/HD'), dstHD, args.fmt)
		
	if texHDR:
		if not os.path.exists(texHDR): os.makedirs(texHDR)
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/Shared'), texHDR, 'yes', '1', '4096'])
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgba/HDR'), texHDR, 'yes', '1', '4096'])
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/Shared'), texHDR, 'no', '1', '4096'])
		subprocess.call([textool, os.path.join(srcTexsPath, 'rgb/HDR'), texHDR, 'no', '1', '4096'])
		if not os.path.exists(dstHDR): os.makedirs(dstHDR)
		subprocess.call([xcopy, os.path.join(texHDR, '*.*'), dstHDR])
		processTMX(os.path.join(srcTexsPath, 'rgba/HDR'), dstHDR, args.fmt)
		processTMX(os.path.join(srcTexsPath, 'rgb/HDR'), dstHDR, args.fmt)

	srcBundlePath = os.path.join(args.appRoot, 'assets')
	if not args.skipSrc:
		subprocess.call([xcopy, os.path.join(scriptDir, '../Sources'), args.dst])
		subprocess.call([xcopy, os.path.join(args.appRoot, 'src/*.*'), os.path.join(args.dst, 'Sources')])
		
	subprocess.call([xcopy, os.path.join(srcBundlePath, 'Data/*.*'), args.dst])
	subprocess.call([xcopy, os.path.join(args.appRoot, 'frameworks/espreso/espreso.json'), args.dst])
	

# -------------- main --------------
if __name__ == '__main__':
    run()

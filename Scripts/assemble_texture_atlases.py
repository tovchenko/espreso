#!/usr/bin/python

import sys
import os, os.path
import subprocess
import datetime
import re
import argparse
#import tkMessageBox


def atlasValid(srcFolder, outTexture):
	if not os.path.isdir(srcFolder):
		print srcFolder + ' isn\'t a folder'
		sys.exit(1)
		
	if os.path.isfile(outTexture):
		srcModDate = datetime.datetime.fromtimestamp(os.path.getmtime(srcFolder))
		dstModDate = datetime.datetime.fromtimestamp(os.path.getmtime(outTexture))
		if srcModDate <= dstModDate:
			return True
	return False


def assemble(srcFolder, outTexture, scale, maxSize, hasAlpha):
	scriptDir = os.path.dirname(os.path.realpath(__file__))
	packer = os.path.join(scriptDir, '../Tools/TexturePacker.app/Contents/MacOS/TexturePacker')
	texSize = os.path.join(scriptDir, '../Tools/getTextureSize')
	plist = os.path.join(scriptDir, 'process_atlas_plist.py')
	
	texName = os.path.basename(outTexture)
	extension = re.search(r'\.(.*)', texName).groups()[0].lower()
	outPlist = os.path.join(os.path.dirname(outTexture), texName.replace('.' + extension, '.plist'))
	tmpPlist = outPlist
	
	filename = os.path.basename(outTexture).replace('.' + extension, '.png')
	tmpPath = outTexture
	isExtPkm = extension == 'pkm'
	isPkm = isExtPkm and not hasAlpha
	isPvrTc = not hasAlpha and extension == 'pvr.ccz'
	
	if isPkm or isPvrTc:
		tmpPath = os.path.join(os.path.dirname(outTexture), filename)
		tmpPlist = os.path.join(scriptDir, os.path.basename(outPlist))
	elif isExtPkm:
		tmpPath = os.path.join(os.path.dirname(outTexture), filename.replace('.png', '.pvr.ccz'))
		
	if atlasValid(srcFolder, outTexture if isPkm or isPvrTc else tmpPath):
		return
	
	subprocess.call([packer, srcFolder,
		'--quiet',
		'--sheet', tmpPath,
		'--data', tmpPlist,
		'--opt', 'RGBA8888' if hasAlpha else 'RGB888',
		'--scale', scale,
		'--max-size', maxSize])
		
# 	tkMessageBox.showinfo("Info", tmpPath)		

	if isPvrTc:
		proc = subprocess.Popen([texSize, tmpPath], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		proc.wait()
		out = proc.stdout.read()
		if int(out) > 2048:
			isPvrTc = False
			subprocess.call([packer, tmpPath,
				'--quiet',
				'--sheet', outTexture,
				'--algorithm', 'Basic',
				'--allow-free-size',
				'--border-padding', '0',
				'--shape-padding', '0',
				'--inner-padding', '0',
				'--no-trim',
				'--opt', 'RGB888',
				'--max-size', maxSize,
				'--dither-fs'])
			os.remove(tmpPath)
			subprocess.call([plist, tmpPlist, os.path.dirname(outPlist), 'pvr.ccz'])
			os.remove(tmpPlist)
		
	if isPkm:
		compressor = os.path.join(scriptDir, '../Tools/etc1tool')
		subprocess.call([compressor, tmpPath, '-o', outTexture])
		os.remove(tmpPath)
		subprocess.call([plist, tmpPlist, os.path.dirname(outPlist), 'pkm'])
		os.remove(tmpPlist)
	elif isPvrTc:
		makeSquare = os.path.join(scriptDir, '../Tools/makeTextureSquare')
		squareTexPath = os.path.join(scriptDir, filename)
		subprocess.call([makeSquare, tmpPath, squareTexPath])
		os.remove(tmpPath)
		subprocess.call([packer, squareTexPath,
			'--quiet',
			'--sheet', outTexture,
			'--algorithm', 'Basic',
			'--allow-free-size',
			'--border-padding', '0',
			'--shape-padding', '0',
			'--inner-padding', '0',
			'--no-trim',
			'--opt', 'PVRTC4',
			'--max-size', maxSize,
			'--dither-fs'])
		os.remove(squareTexPath)
		subprocess.call([plist, tmpPlist, os.path.dirname(outPlist), 'pvr.ccz'])
		os.remove(tmpPlist)
	
	
def assembleFolder(srcDirPath, dstDirPath, scale, maxSize, hasAlpha, fmt):
	for name in os.listdir(srcDirPath):
		srcPath = os.path.join(srcDirPath, name)
		if os.path.isdir(srcPath):
			assemble(srcPath, os.path.join(dstDirPath, name + '.' + fmt), scale, maxSize, hasAlpha)
		

def run():
	parser = argparse.ArgumentParser(prog='ASSEMBLE TEXTURE ATLASES')
	parser.add_argument('-appRoot')
	parser.add_argument('-fmt')
	parser.add_argument('-lods', nargs='*', default=['HDR', 'HD', 'SD'])
	args = parser.parse_args()
		
	scriptDir = os.path.dirname(os.path.realpath(__file__))
	
	textureFolder = os.path.join(args.appRoot, 'runtime/temp/Textures')
	textureFolder = os.path.join(textureFolder, args.fmt)
	if not os.path.exists(textureFolder): os.makedirs(textureFolder)
	
	texSD = texHD = texHDR = None
	for lod in args.lods:
		if lod == 'SD':
			texSD = os.path.join(textureFolder, 'SD')
		elif lod == 'HD':
			texHD = os.path.join(textureFolder, 'HD')
		elif lod == 'HDR':
			texHDR = os.path.join(textureFolder, 'HDR')
			
	srcDir = os.path.join(args.appRoot, 'assets/Atlases')
	
	if texSD:
		if not os.path.exists(texSD): os.makedirs(texSD)
		assembleFolder(os.path.join(srcDir, 'rgba/Shared'), texSD, '0.25', '1024', True, args.fmt)
		assembleFolder(os.path.join(srcDir, 'rgba/SD'), texSD, '1', '1024', True, args.fmt)
		assembleFolder(os.path.join(srcDir, 'rgb/Shared'), texSD, '0.25', '1024', False, args.fmt)
		assembleFolder(os.path.join(srcDir, 'rgb/SD'), texSD, '1', '1024', False, args.fmt)
		
	if texHD:
		if not os.path.exists(texHD): os.makedirs(texHD)
		assembleFolder(os.path.join(srcDir, 'rgba/Shared'), texHD, '0.5', '2048', True, args.fmt)
		assembleFolder(os.path.join(srcDir, 'rgba/HD'), texHD, '1', '2048', True, args.fmt)
		assembleFolder(os.path.join(srcDir, 'rgb/Shared'), texHD, '0.5', '2048', False, args.fmt)
		assembleFolder(os.path.join(srcDir, 'rgb/HD'), texHD, '1', '2048', False, args.fmt)
			
	if texHDR:
		if not os.path.exists(texHDR): os.makedirs(texHDR)
		assembleFolder(os.path.join(srcDir, 'rgba/Shared'), texHDR, '1', '4096', True, args.fmt)
		assembleFolder(os.path.join(srcDir, 'rgba/HDR'), texHDR, '1', '4096', True, args.fmt)
		assembleFolder(os.path.join(srcDir, 'rgb/Shared'), texHDR, '1', '4096', False, args.fmt)
		assembleFolder(os.path.join(srcDir, 'rgb/HDR'), texHDR, '1', '4096', False, args.fmt)
	
	outfile = os.path.join(os.getcwd(), 'out.plist')
	if os.path.isfile(outfile):
		os.remove(outfile)
	

# -------------- main --------------
if __name__ == '__main__':
    run()

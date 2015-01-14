#!/usr/bin/python

import sys
import os, os.path
import subprocess
import re
import argparse

def run():
	parser = argparse.ArgumentParser(prog='PROCESS RESOURCES')
	parser.add_argument('-src')
	parser.add_argument('-dst')
	parser.add_argument('-lods', nargs='*', default=['HDR', 'HD', 'SD'])
	args = parser.parse_args()

	dstSD = dstHD = dstHDR = None
	for lod in args.lods:
		if lod == 'SD':
			dstSD = os.path.join(args.dst, 'SD')
		elif lod == 'HD':
			dstHD = os.path.join(args.dst, 'HD')
		elif lod == 'HDR':
			dstHDR = os.path.join(args.dst, 'HDR')

	scriptDir = os.path.dirname(os.path.realpath(__file__))
	tool = os.path.join(scriptDir, '../Tools/GDCL')

	glyphFiles = []
	for file in os.listdir(args.src):
		if os.path.splitext(file)[1] == '.GlyphProject':
			glyphFiles.append(os.path.splitext(file)[0])

	print 'Publish bmFont: ', glyphFiles

	for file in glyphFiles:
		print '  ', file
		if dstSD:
			if not os.path.exists(dstSD): os.makedirs(dstSD)
			cmd = [tool, os.path.join(args.src, file), os.path.join(dstSD, file), '-fo', 'PlainText-fnt', '-rfs', '0.25']
			subprocess.call(cmd)
		if dstHD:
			if not os.path.exists(dstHD): os.makedirs(dstHD)
			cmd = [tool, os.path.join(args.src, file), os.path.join(dstHD, file), '-fo', 'PlainText-fnt', '-rfs', '0.5']
			subprocess.call(cmd)
		if dstHDR:
			if not os.path.exists(dstHDR): os.makedirs(dstHDR)
			cmd = [tool, os.path.join(args.src, file), os.path.join(dstHDR, file), '-fo', 'PlainText-fnt', '-rfs', '1.0']
			subprocess.call(cmd)


# -------------- main --------------
if __name__ == '__main__':
	run()

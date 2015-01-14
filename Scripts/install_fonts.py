#!/usr/bin/python

import sys
import os, os.path
import subprocess
import argparse
from os.path import expanduser

def run():
	parser = argparse.ArgumentParser(prog='PROCESS RESOURCES')
	parser.add_argument('-src')
	args = parser.parse_args()

	fontFiles = []
	for file in os.listdir(args.src):
		if os.path.splitext(file)[1] == '.ttf':
			fontFiles.append(file)

	print 'Install fonts: ', fontFiles

	home = expanduser("~")

	scriptDir = os.path.dirname(os.path.realpath(__file__))
	xcopy = os.path.join(scriptDir, '../Tools/xcopy')
	fontInstallPath = os.path.join(expanduser("~"), 'Library/Fonts')

	for file in fontFiles:
		print '  ', file
		fullFontPath = os.path.join(args.src, file)
		cmd = [xcopy, fullFontPath, fontInstallPath]
		subprocess.call(cmd)


# -------------- main --------------
if __name__ == '__main__':
	run()

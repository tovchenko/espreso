#!/usr/bin/python

import sys
import os, os.path
import subprocess


def run():
	if len(sys.argv) != 3:
		print 'Usage: ' + os.path.basename(os.path.realpath(__file__)) + ' app_root dst_path'
		sys.exit(1)
	
	scriptDir = os.path.dirname(os.path.realpath(__file__))
	appRoot = sys.argv[1]
	
	srcPath = os.path.join(appRoot, 'assets/Sounds')
	tempPath = os.path.join(os.path.join(appRoot, 'runtime/temp/Sounds'), "sprites")
	
 	if not os.path.exists(tempPath):
 		os.makedirs(tempPath)
 		
	nodejs = os.path.join(scriptDir, '../Tools')
	ffmpeg = os.path.join(scriptDir, '../Tools/ffmpeg')
	
	os.environ["PATH"] = os.environ["PATH"] + ":" + nodejs + ":" + ffmpeg;
	
 	converter = os.path.join(scriptDir, '../Tools/audiosprite/audiosprite.js')
 	os.chdir(tempPath);

	callArray = [converter, "-o", "sounds", "-e", "ogg,mp3"];
	empty = 1;

	for file in os.listdir(srcPath):
		if file.endswith(".wav"):
			callArray.append(os.path.join(srcPath, file))
			empty = 0;
		elif file.endswith(".mp3"):
			callArray.append(os.path.join(srcPath, file))
			empty = 0;
		elif file.endswith(".ogg"):
			callArray.append(os.path.join(srcPath, file))
			empty = 0;
	
	if empty == 0:
 		subprocess.call(callArray)
		
		xcopy = os.path.join(scriptDir, '../Tools/xcopy')
		subprocess.call([xcopy, os.path.join(tempPath, '*.*'), sys.argv[2]])

# -------------- main --------------
if __name__ == '__main__':
    run()

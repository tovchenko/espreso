#!/usr/bin/python

import sys
import os, os.path
import subprocess


def run():
	scriptDir = os.path.dirname(os.path.realpath(__file__))
	packer = os.path.join(scriptDir, '../Tools/TexturePacker.app/Contents/MacOS/TexturePacker')
	subprocess.call([packer, '--install-license', os.path.join(scriptDir, '../Tools/texturepacker-license.tpkey')])

# -------------- main --------------
if __name__ == '__main__':
    run()

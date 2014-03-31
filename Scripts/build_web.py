#!/usr/bin/python
# build_web.py
# Build Web


import sys
import os, os.path
import shutil
import subprocess


def copy_files(src, dst):
    for item in os.listdir(src):
        path = os.path.join(src, item)
        if not item.startswith('.') and os.path.isfile(path):
            shutil.copy(path, dst)
        if os.path.isdir(path):
            new_dst = os.path.join(dst, item)
            os.mkdir(new_dst)
            copy_files(path, new_dst)

def copy_resources(app_root):
    res_dir = os.path.join(app_root, 'res')
    if os.path.isdir(res_dir):
        shutil.rmtree(res_dir)

    # copy resources
    os.mkdir(res_dir)
    scripts_dir = os.path.join(app_root, 'frameworks/espreso/Scripts')
    if os.path.isdir(scripts_dir):
		subprocess.call([os.path.join(scripts_dir, 'activate_texturepacker.py')])
		subprocess .call([os.path.join(scripts_dir, 'assemble_texture_atlases.py'), app_root, res_dir, 'png'])
		subprocess.call([os.path.join(scripts_dir, 'process_assets.py'), app_root, res_dir, 'png'])
		subprocess.call([os.path.join(scripts_dir, 'create_audiosprite.py'), app_root, res_dir])
		subprocess.call( [os.path.join(scripts_dir, 'convert_sounds.py'), app_root, res_dir, 'ogg'])
		subprocess.call([os.path.join(scripts_dir, 'convert_sounds.py'), app_root, res_dir, 'mp3'])


def run():
    current_dir = os.path.dirname(os.path.realpath(__file__))
    copy_resources(os.path.join(current_dir, '../../../'))
    

# -------------- main --------------
if __name__ == '__main__':
    run()

#!/usr/bin/env python2.7
import os
import sys
import subprocess
import shlex

def run(sourcePath):
    targetPath = sourcePath.replace('.cpp', '').replace('.cc', '').replace('.lyt', '')
    targetExists = os.path.exists(targetPath)
    build(sourcePath)
    command = "./" + targetPath
    proc = subprocess.Popen(shlex.split(command), stdout=subprocess.PIPE)
    outs, errs = proc.communicate()
    if not targetExists:
        os.remove(targetPath)

def build(sourcePath):
    targetPath = sourcePath.replace('.cpp', '').replace('.cc', '').replace('.lyt', '')
    command = 'clang++ --std=c++11 -lsndfile -llyt -o "' + targetPath + '" "' + sourcePath + '"'
    print command
    proc = subprocess.Popen(shlex.split(command), stdout=subprocess.PIPE)
    outs, errs = proc.communicate()
    return targetPath

def printUsage():
    print('lyt <command> <args>')
    quit()

if __name__ == '__main__':
    if len(sys.argv) < 3:
        printUsage() 

    command = sys.argv[1]

    if command == 'build':
        build(sys.argv[2])
    elif command == 'run':
        run(sys.argv[2])

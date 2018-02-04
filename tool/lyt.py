#!/usr/bin/env python2.7
import os
import sys
import subprocess
import shlex

def getTargetPath(sourcePath):
    return sourcePath.replace('.cpp', '').replace('.cc', '').replace('.lyt', '')
    
def run(sourcePath):
    targetPath = getTargetPath(sourcePath)
    targetExists = os.path.exists(targetPath)
    buildState = build(sourcePath)

    if buildState != 0:
        return

    command = "./" + targetPath
    proc = subprocess.Popen(shlex.split(command), stdout=subprocess.PIPE)
    outs, errs = proc.communicate()
    if not targetExists:
        os.remove(targetPath)

def build(sourcePath):
    targetPath = getTargetPath(sourcePath)
    command = 'clang++ --std=c++11 -lsndfile -llyt -o "' + targetPath + '" "' + sourcePath + '"'
    print command
    proc = subprocess.Popen(shlex.split(command), stdout=subprocess.PIPE)
    outs, errs = proc.communicate()
    return proc.returncode

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

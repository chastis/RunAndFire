import os
from os import listdir
from os.path import isfile, join, splitext
import sys

dir = "../Data/Maps"

files = []
for f in listdir(dir):
    if isfile(join(dir, f)):
        f_name, f_ext = splitext(f)
        if f_ext.lower() == '.json':
            files.append(join(dir, f))

for file_name in files:
    orig_chars = ""
    with open(file_name, "r") as file:
        for line in file:
            for char in line:
                orig_chars += char

        orig_chars = orig_chars.replace('"image":"..\/Content\/', '"image":"Content\/')
        #file.seek(0)
        #file.write(orig_chars)
        print('readed ' + file_name)
    with open(file_name, "w") as file:
        file.write(orig_chars)
        print('modified ' + file_name)

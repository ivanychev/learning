#!/usr/bin/env python3
"""
Current version of Jupyter doesn't support pdf exporting when it comes to 
russian language in the document. To fix this, current script has born.
It requires nbconvert as long as jupyter to be installed.


Author:     Sergey Ivanychev
Email:      sergeyivanychev@gmail.com
Revision:   1
"""

import sys
import os
import subprocess

FORMAT = ".ipynb"
"""
TODO:   What if user has ___o.tex in current folder?
"""
TEMP_TEX = "___o.tex"
TEMP_FOLDER = "/tmp"
TRASH_EXTENSIONS = [".aux", ".out", ".log"]
OLD1 = r"\usepackage[utf8x]{inputenc}"
NEW1 = r"""
    \usepackage[utf8x]{inputenc}
    \usepackage[T1,T2A]{fontenc}
    \usepackage[russian,english]{babel}
"""
REPLACE = [(OLD1, NEW1)]
HELP = """
This script is aimed at correctly converting .ipynb to .pdf files.
You may use it via 

# ipynb2pdf Solution.ipynb

To get .pdf in the same directory
"""

def check_args(argv):
    if (len(argv) > 2):
        print("Please, type .ipynb filename as argument")
        return -1
    if (len(argv) == 1):
        print(HELP)
        return -1
    script, filename = argv
    if not is_ipynb(filename):
        print("Please, type .ipynb filename as argument")
        return -1

def remove_extention(string, extention):
    """
    Removes argumented extention from the end of the string
    """
    if extention[0] != '.':
        extention = "." + extention
    if string.endswith(extention):
        string = string[0:-len(extention)]
    return string

def is_ipynb(filename):
    if not filename.endswith(".ipynb"):
        return False
    return True

def tex2pdf(filename, desired_name):
    """
    Converts filename (which is tex document) to desired_name (which is pdf)
    leaving no trash in current folder
    """
    base = remove_extention(filename, "tex")
    output = base + ".pdf"
    ret = subprocess.call("pdflatex %s" % filename , 
                                        shell=True, stdout=subprocess.PIPE)
    for ext in TRASH_EXTENSIONS:
        os.unlink(base + ext)
    os.rename(output, desired_name)
    return ret

def main(argv):
    if check_args(argv) == -1:
        return -1
    script, filename = argv
    ret = subprocess.call("jupyter nbconvert %s --to latex --output %s" % 
                                            (filename, TEMP_TEX), shell=True,
                                            stdout=subprocess.PIPE)
    if (ret != 0):
        print("ret = %d" % ret)
        os.unlink(TEMP_TEX)
        print("Converting to LaTeX failed. Return code: %d" % ret)
        return -1
    tex_file = open(TEMP_TEX, "r")
    tex = tex_file.read()
    for old, new in REPLACE:
        tex = tex.replace(old, new)
    tex_file.close()
    os.unlink(TEMP_TEX)
    tex_file = open(TEMP_TEX, "w+")
    tex_file.write(tex)
    tex_file.close()
    ret = tex2pdf(TEMP_TEX, remove_extention(filename, ".ipynb") + ".pdf")
    tex_file.close()
    os.unlink(TEMP_TEX)
    print(remove_extention(filename, ".ipynb") + ".pdf - DONE")
    return 0

if __name__ == "__main__":
    exit(main(sys.argv))

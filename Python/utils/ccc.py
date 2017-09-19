#!/usr/bin/env python
"""Making C++ compilation easy.

  Examples:
    ccc.py temp.cc  # compile with clang++
    ccc.py temp.cc -gcc  # compile with g++
    ccc.py temp.cc -x  # compile and execute immediately
"""

from __future__ import print_function

import argparse
import logging
import re
import subprocess
import sys

PARSER = argparse.ArgumentParser(description='Process the script flags.')
PARSER.add_argument('filename', action='store', help='File to compile')
PARSER.add_argument('-gcc', action='store_const', const=True,
                    help='Specify if we prefer gcc to clang.')
PARSER.add_argument('-x', action='store_const', const=True,
                    help='Execute immediately')

CLANG_CALL = ('clang++ {source_file} -fsanitize=address,undefined -x c++ '
              '-std=c++14 -O2 -Wall -Werror -Wsign-compare -o {output_file}')
GCC_CALL = ('g++-7 {source_file} -x c++ -std=c++14 -O2 -Wall -Werror '
            '-Wsign-compare -o {output_file}')
CC_SOURCE_REGEX = re.compile(
    r'(?P<name>.*)(?P<extention>(\.cc|\.cpp|\.c|\.h|\.hpp))$')
EXECUTABLE_EXTENTION = '.o'


def _GetOutputFileName(base_name):
  return base_name + EXECUTABLE_EXTENTION

def _GetNameFromCCFilename(filename):
  '''Parses a C++ source file name and extracts the part before the extention.

  Args:
    filename: str. C++ file name. E.g. 'hello.cc'

  Returns:
    str or None. The part before the extentin of None if the filename is
      incorrect.
  '''
  matched = CC_SOURCE_REGEX.match(filename)
  return matched and matched.group('name')

def _CompileWithClang(args, base_name):
  command = CLANG_CALL.format(source_file=args.filename,
                              output_file=_GetOutputFileName(base_name))
  subprocess.check_call(command.split())

def _CompileWithGCC(args, base_name):
  command = GCC_CALL.format(source_file=args.filename,
                            output_file=_GetOutputFileName(base_name))
  subprocess.check_call(command.split())

def main(argv):
  args = PARSER.parse_args(argv[1:])
  if not args.filename:
    logging.error('File name is not provided')
    return 0
  base_name = _GetNameFromCCFilename(args.filename)
  if not base_name:
    logging.error('Invalid file name specified: %s', args.filename)
    return 0
  if args.gcc:
    _CompileWithGCC(args, base_name)
  else:
    _CompileWithClang(args, base_name)
  if args.x:
    subprocess.call('./' + _GetOutputFileName(base_name))


if __name__ == "__main__":
  sys.exit(main(sys.argv))

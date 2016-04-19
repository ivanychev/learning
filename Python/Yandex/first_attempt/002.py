import sys

string = sys.stdin.readline()
nums = map(lambda x: int(x), string.split())
sys.stdout.write(str(sum(nums)))

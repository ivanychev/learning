import sys
from functools import reduce
from math import factorial
from fractions import gcd


def main(argv):
    inp = open("input.txt")
    num = int(inp.readline())
    num_list = list(map(lambda x: int(x), inp.readline().split(" ")))

    if num == 1:
        denominator = 2
        numerator = num_list[0]
        gcd_val = gcd(denominator, numerator)
    else:
        denominator = reduce(lambda x, y: x*y, num_list) * (num + 1)
        numerator = (min(num_list)**(num + 1))
        gcd_val = gcd(denominator, numerator)
    sys.stdout.write("%d/%d" % (numerator // gcd_val, denominator // gcd_val))
    inp.close()

if __name__ == "__main__":
    sys.exit(main(sys.argv))

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
        t_min = min(num_list)
        t_prod = reduce(lambda x, y: x*y, num_list)
        denominator = t_prod * (num + 1)
        numerator = t_min**(num + 1) + (num + 1) * t_min * (t_prod - t_min**(num))
        gcd_val = gcd(denominator, numerator)
    sys.stdout.write("%d/%d" % (numerator // gcd_val, denominator // gcd_val))
    inp.close()

if __name__ == "__main__":
    sys.exit(main(sys.argv))

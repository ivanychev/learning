__author__ = 'Sergey Ivanychev'

import string
import math

def main():
    xes = []
    dx = 0.0001
    x = 2
    while x <= 4:
        xes.append(x)
        x += dx
    y = 29.2
    y0 = 29.2
    print(y)
    for x in xes:
        y += math.exp(x)*(2*x + x * x) * dx
        y0 += dx * 2 * (x)
    print(y,y0)
    return 0

main()
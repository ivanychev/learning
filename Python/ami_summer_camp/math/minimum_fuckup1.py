__author__ = 'Sergey Ivanychev'

__author__ = 'Sergey Ivanychev'


def f(x):
    return x * x - 5

def main():
    x0 = -3
    dx = 100
    dy = f(x0+dx) - f(x0)
    x = x0
    if dy < 0:
        while dy < 0:
         x_last = x
         x += dx
         dy = f(x) - f(x_last)


    print(x_last)

    return 0
main()

"""
x0 = x_last - dx
    x1 = x_last + dx
    x = x0
    dx = (x1 - x0) / 100000
    while x < x1:

        x_last = x
        x += dx
        dy = f(x) - f(x_last)
        if dy > 0 :
            break
            """
__author__ = 'Sergey Ivanychev'

def integral(x):
    return x ** 2

def main():
    x1 = 0
    x2 = 2
    dx = 1
    s1 = 0
    s2 = 0
    while x1 < x2:
        #s1 += ((x1 + dx) ** 3) * dx
        # метод трапеций s2 += (integral(x1) + (integral(x1+dx))) / 2 * dx
        s2 += dx/6 * ((x1 ** 3) + ((x1 + dx) ** 3) + 4 * (((x1 + x1 + dx)/2) ** 3))
        x1 += dx
    #print(s1, 4 - s1)
    print(s2)

main()
import math

def f(x):
    return (x * x - 4*x + 4) *( math.sin(3*3.1415926/2 + x - 2) + 2)
def sign(x):
    if x >= 0:
        return 1
    else:
        return -1

def main():
    x0 = -18
    dx0 = 1.1
    dx = dx0
    x = x0
    dy = -1
    count = 0
    mins = []
    while x < 100:
        x_last = x
        x += dx
        dy = f(x) - f(x_last)

        if sign(dy) != sign(f(x0+dx) - f(x0)):
            x = x - 2*dx
            dx /= 3
        count += 1
        if abs(dy) <= 0.00001:
            mins.append([x_last, f(x_last)])
            dx = dx0


    print(x_last, " f(x)=",f(x_last)," count=", count)

    return 0

main()
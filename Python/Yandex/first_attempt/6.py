import sys

def read_ints(f):
    return tuple(map(lambda x: int(x), f.readline().split()))

def read_int(f):
    return int(f.readline())


def main(argv):
    inp = open("input.txt")
    nsell, nbuy = read_ints(inp)
    if nsell > nbuy:
        noffers = nbuy
    else:
        noffers = nsell
    sells = read_ints(inp)
    buys = read_ints(inp)
    sells = sorted(sells)
    buys = sorted(buys, reverse=True)
    money = 0
    for i in range(noffers):
        val = buys[i] - sells[i]
        if (val <= 0):
            break
        money += val
    sys.stdout.write(str(money))
    inp.close()

if __name__ == "__main__":
    sys.exit(main(sys.argv))

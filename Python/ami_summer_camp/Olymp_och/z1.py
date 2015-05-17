__author__ = 'Sergey Ivanychev'

def main():
    inp = input().split()
    n = int(inp[0])

    inp = list(map(int, input().split()))
    l = 0
    posl = []
    flag = 0

    while flag + l < len(inp) - 1:
        if inp[flag:flag + l + 1] == sorted(inp[flag:flag + l + 1]):
            posl = inp[flag:flag + l + 1]
            l += 1
        else:
            flag += l

    print(posl)

    return 0

main()


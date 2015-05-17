__author__ = 'Sergey Ivanychev'

def main():
    inp = list(map(int, input().split()))
    n = inp[0]
    m = inp[1]

    stolb = {}
    for i in range(27):
        stolb[i] = 0

    chars = []
    for i in range(m):
        chars.append(stolb.copy())
    str = []
    for i in range(n):
        str = input()
        for j in range(m):
            chars[j][ord(str[j]) - 97] += 1
    for i in range(m):
        for j in range (26):
            if chars[i][j] % 2 == 1:
                print(chr(j+97),end="")

    return 0

main()

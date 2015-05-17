__author__ = 'Sergey Ivanychev'

def main():
    inp = list(map(int, input().split()))
    n = inp[0]
    det = []

    for i in range(3):
        inp = list(map(int, input().split()))
        inp.sort()
        det.append(inp)
    l = n-1
    done = []
    for i in range(n):
        if det[0][l-i] >= 20 and det[1][l-i] >= 20 and det[2][l-i] >= 20:
            done.append(det[0][l-i] + det[1][l-i] + det[2][l-i])
        else:
            break
    count = 0
    for i in done:
        if i < 100:
            count += 1
    print(count)

    return 0

main()


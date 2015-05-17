__author__ = 'Sergey Ivanychev'

def main():
    x = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7]
    p = [-3.999, -3.992, -3.973, -3.936, -3.875, -3.784]
    last_raz = []
    last_raz.append(-3.784)
    st = 0



    while (len(set(p))) != 1:
        dub_p = p.copy()
        p = []
        for x in range(len(dub_p) - 1):
            p.append(dub_p[x+1] - dub_p[x])
        print(p)
        last_raz.append(p[len(dub_p)-2])

        st += 1

    print(st)
    s = 0
    for x in last_raz:
        s += x
    print(s)
    print(last_raz)

    return 0

main()
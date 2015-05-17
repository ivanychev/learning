__author__ = 'Sergey Ivanychev'

def main():
    inp = input().split()
    n = int(inp[0])
    tps = []
    acts = []
    dict = {}
    emp = 0
    for x in range(n):
        tps.append(0)

    count = 0

    st = input()
    if st[0] == "+":
        cool = 0
        if emp < n:
                tps[emp] = st[1:]
                acts.append([st[1:],x+1])
                dict[st[1:]] = x
                emp += 1
                cool = 1

        if cool == 0:
            print(cool," ", st[1:])
            return 0
    while 1:
        try:
            st = input()
        except EOFError:
            st = ""
        if st == "":
            break

        if st[0] == "+":
            cool = 0
            if emp < n:
                tps[emp] = st[1:]
                acts.append([st[1:],x+1])
                dict[st[1:]] = x
                cool = 1
                emp += 1
                while tps[emp % n] != 0 and emp < n:
                    emp += 1

            if cool == 0:
                print(cool," ", st[1:])
                return 0
            continue
        if st[0] == "-":
            tps[dict[st[1:]]] = 0
            if emp < dict[st[1:]]:
                emp = dict[st[1:]]
            continue
    for x in acts:
        print(x[0], x[1])

    return 0

main()


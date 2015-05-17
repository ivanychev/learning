def main():
    line = input()

    if line =="0":
        print("YES")
        return 0

    l = len(line)
    for x in range(l):
        if line[x] =="0":
            print("NO")
            return 0
    x = 0
    route = set()

    while len(route) < l:
        forw = int(line[x]) % l
        if (x + forw) % l in route:
            print("NO")
            return 0
        route.add((x + forw) % l)
        x = (x + forw) % l

        print("YES")


    return 0

main()
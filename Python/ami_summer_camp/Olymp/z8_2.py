__author__ = 'Sergey Ivanychev'

def main():
    inp = input().split()
    line = inp[0]
    l = len(line)

    if line == "0":
        print("YES")
        return 0

    for x in range(len(line)):
        if line[x] == "0":
            print("NO")
            return 0

    route = []
    now = 0
    while 1:
           if now != 0:
               route.append(now)
           forward = int(line[now]) % l
           if ((now + forward) % l) in route:
               print("NO")
               return 0
           if ((now + forward) % l) == 0 and len(route) != l-1:
               print("NO")
               return 0
           if ((now + forward) % l) == 0 and len(route) == l-1:
               print("YES")
               return 0
           now = ((now + forward) % l)
    return 0

main()
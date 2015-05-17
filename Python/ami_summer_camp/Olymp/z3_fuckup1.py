__author__ = 'Sergey Ivanychev'
def search(list, thing):
    for x in range(len(list)):
        if x == thing:
            return x
    return 0

def main():
    act = input().split()
    pairs = []
    pair = []
    open = []
    close = []
    num = []
    count = 0
    while 1 :
        pair = input().split()
        if pair == []:
            break
        pairs.append(pair)

        open.append(pair[0])
        close.append(pair[1])
        num.append(int(pair[2]))

    stack = []

    for x in act:
        if x in open:
            stack.append(x)
        else:
            c = stack.pop()
            if search(close,x) == search(open, c):
                num[search(close, x)] -= 1
            else:
                print("0")
                return 0
    done = 1

    for x in num:
        if num != 0:
            done = 0


    print(done)

    return 0

main()


__author__ = 'Sergey Ivanychev'

def search(list, thing):
    for x in range(len(list)):
        if x == thing:
            return x
    return 0

def check (list, num, open, close, num):
    now = list[num]
    if num + 1 > len(list) - 1:
        return 0
    next = list[num + 1]

    if search(open, now) == search(close, next):



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

    done = check(act, 0, open, close, num)
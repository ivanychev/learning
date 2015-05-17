__author__ = 'Sergey Ivanychev'
def search(list, thing):
    for x in range(len(list)):
        if list[x] == thing:
            return x
    return -1

def check(list, open, close):
    out = []
    x = 0
    while x < len(list) - 1:
        so = search(open, list[x])
        sc = search(close, list[x + 1])
        if (so == sc) and (so != -1):
            op = open[so]
            del list[x+1]
            del list[x]
            out = [list, op]
            return out
        x += 1
    out = [list, "thisiser"]
    return out


def main():

    act = input().split()
    mn1 = set(act)
    mn2 = set()
    pairs = []
    pair = []
    open = []
    close = []
    num = []
    count = 0
    while len(mn1) > len(mn2):
        pair = input().split()
        if pair[0] not in mn2:
            mn2.add(pair[0])
        if pair[1] not in mn2:
            mn2.add(pair[1])

        pairs.append(pair)

        open.append(pair[0])
        close.append(pair[1])
        num.append(int(pair[2]))

    past_act = []
    catch_list = []
    while (act != []) and (past_act != act):
        past_act = act[:]
        catch_list = check(act, open, close)
        act = catch_list[0]
        catch_name = catch_list[1]

        if catch_name == "thisiser":
            print("0")
            return 0

        num_name = search(open, catch_name)

        if num_name == -1:
            print("0")
            return 0

        num[num_name] -= 1
    done = 0

    for x in num:
        if x != 0:
            done = 1

    if (act == []) and (done == 0):
        print("1")
    else:
        print("0")

    return 0

main()




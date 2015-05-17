__author__ = 'Sergey Ivanychev'

def main():
    list = []
    while 1:
        in_list = input().split()
        if in_list == []:
            break
        list.append(in_list)

    print(list)

    return 0

main()




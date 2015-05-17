def search(list, thing):
    for x in range(len(list)):
        if list[x] == thing:
            return x
    return -1

def main():
    vertices = input().split()
    dict_vert = {}
    files = []
    i = 0
    for x in vertices:
        dict_vert[x] = i
        files.append({"name":x, "to":[], "from":[]})
        i += 1


    pair = input().split()
    files[dict_vert[pair[0]]]["to"].append(pair[1])
    files[dict_vert[pair[1]]]["from"].append(pair[0])
    while pair != []:
        try:
            pair = input().split()
        except EOFError:
            pair = []
        if pair == []:
            continue
        files[dict_vert[pair[0]]]["to"].append(pair[1])
        files[dict_vert[pair[1]]]["from"].append(pair[0])

    flag = 1
    outfiles = []
    while (files != []) and (flag == 1):
        flag = 0
        for x in files:
            if x["to"] == []:
                outfiles.append(x["name"])
                flag = 1
                for y in x["from"]:
                    ser = search(files[dict_vert[y]]["to"],x)
                    del files[dict_vert[y]]["to"][ser]
                del files[search(files,x)]
                break

    for x in outfiles:
        print(x, end = " ")

    return 0

main()

with open("input.txt") as f:
    string = f.readline()
    nums = map(lambda x: int(x), string.split(" "))
    with open("output.txt", "w") as out:
        out.write(str(sum(nums)))

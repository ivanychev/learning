__author__ = 'Sergey Ivanychev'

"""
def cross(f1, f2):
    x1 = []
    y1 = []
    x2 = []
    y2 = []

    while f1 != []:
        x1.append(f1[0])
        y1.append(f1[1])
        del f1[1]
        del f1[0]
    while f2 != []:
        x2.append(f2[0])
        y2.append(f2[1])
        del f2[1]
        del f2[0]
    @for x in range(len(x1)):
        flag = 0
        for y in range(len(x2)):

            if x == len(x1) - 1:
                xx == 0
            else:
                xx = x + 1
            if y == len(x2) - 1:
                yy == 0
            else:
                yy = y + 1 @

    flag = 0
    for y in range(len(x2)):
        sign = []
        for x in range(len(x1)):
            if x == len(x1) - 1:
                xx == 0
            else:
                xx = x + 1
            sign_now = vector(x1[xx] - x1[x], y1[xx] - y1[x], x2[y] - x1[xx], y2[y] - y1[xx])
            if (sign_now >=0) and 1 not in sign:
                sign.append(1)
            if (sign_now < 0) and -1 not in sign:
                sign.append(-1)
        if (1 in sign and -1 not in sign) or (1 not in sign and -1 in sign):
            return 1
    return 0 """

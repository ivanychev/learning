__author__ = 'Sergey Ivanychev'

def gcd_xtended(a, b):

    if a >= b:
        r1, r2 = a, b
    else:
        r1, r2 = b, a
    q = dict()
    q.append([r1, 0])
    q.append([r2, 0])

    rr = r1 % r2

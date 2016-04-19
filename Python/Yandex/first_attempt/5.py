import sys

def read_ints(f):
    return tuple(map(lambda x: int(x), f.readline().split()))

def read_int(f):
    return int(f.readline())

def get_sum(N):
    return N * (N + 1) // 2

def get_squares(N):
    return N * (N + 1) * (2*N + 1) // 6

def get_cubes(N):
    return N** 2 * (N + 1) ** 2 // 4

def get_ssc(s1, s2, s3, N):
    return get_sum(N) - s1, get_squares(N) - s2, get_cubes(N) - s3

def find_max_num(sumv, squarev, cubev):
    return min([sumv - 2, round(squarev**(1/2)), round(cubev**(1/3))])

def find_triple(sumv, squarev, cubev):
    max_num = find_max_num(sumv, squarev, cubev)
    for x in range(1, max_num + 1):
        sum1 = x
        square1 = x**2
        cube1 = x**3
        for y in range(x, max_num + 1):
            sum2 = sum1 + y
            if sum2 >= sumv:
                break
            square2 = square1 + y**2
            if square2 >= squarev:
                break
            cube2 = cube1 + y**3
            if cube2 >= cubev:
                break
            z = y
            while z <= max_num:
                sum3 = sum2 + z
                if sum3 > sumv:
                    break
                square3 = square2 + z**2
                if square3 > squarev:
                    break
                cube3 = cube2 + z**3
                if cube3 > cubev:
                    break
                if sum3 == sumv and square3 == squarev and cube3 == cubev:
                    return x, y, z
                z += 1
            y += 1
        x += 1
        # sorry for that piece of junk
    return None



def main(argv):
    inp = open("input.txt")
    number_of_cards = read_int(inp)
    all_sumv, all_squarev, all_cubev = read_ints(inp)
    sumv, squarev, cubev = get_ssc(all_sumv, all_squarev, all_cubev, number_of_cards)
    x, y, z = find_triple(sumv, squarev, cubev)
    sys.stdout.write("%d %d %d" % (x, y, z))
    inp.close()

if __name__ == "__main__":
    sys.exit(main(sys.argv))

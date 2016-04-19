import sys

def read_ints(f):
    return tuple(map(lambda x: int(x), f.readline().split()))

def read_int(f):
    return int(f.readline())

def get_edges(f, num):
    edges = []
    for i in range(num):
        edges.append(read_ints(f))
    return edges

def get_data(f):
    nvertexes, nedges = read_ints(f)
    edges = get_edges(f, nedges)
    num_cutting = read_int(f)
    cutting = read_ints(f)


def main(argv):
    inp = open("input.txt")
    print(nvertexes, nedges, edges, num_cutting, cutting)

if __name__ == "__main__":
    sys.exit(main(sys.argv))

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
    return nvertexes, nedges, edges, num_cutting, cutting

def form_graph(nvertexes, edges):
    graph = dict.fromkeys(range(1, nvertexes + 1))
    for vertex in range(1, nvertexes + 1):
        graph[vertex] = list()
    for edge in edges:
        graph[edge[0]].append(edge[1])
        graph[edge[1]].append(edge[0])
    return graph

def get_component(starting_vertex_in_list, graph):
    old_vertexes = None
    vertexes = set(starting_vertex_in_list)
    while vertexes != old_vertexes:
        old_vertexes = vertexes
        vertexes = set(old_vertexes)
        for vertex in old_vertexes:
            vertexes |= set(graph[vertex])
    return vertexes

def get_n_components(graph, nvetexes):
    graph_copy = graph.copy()
    num = 0
    while graph_copy:
        vertexes = [list(graph_copy)[0]]
        component = get_component(vertexes, graph)
        for vertex in component:
            graph_copy.pop(vertex)
        num += 1
    return num


def remove_edge(graph, edges, cut):
    graph[edges[cut - 1][0]].remove(edges[cut - 1][1])
    graph[edges[cut - 1][1]].remove(edges[cut - 1][0])
    return graph

def was_bridge(graph, edges, cut):
    starting = edges[cut - 1][0]
    ending = edges[cut - 1][1]
    if ending not in get_component([starting], graph):
        return True
    return False

def main(argv):
    inp = open("input.txt")
    nvertexes, nedges, edges, num_cutting, cutting = get_data(inp)
    graph = form_graph(nvertexes, edges)
    ncomponents = get_n_components(graph, nvertexes)
    components = []
    for cut in cutting:
        remove_edge(graph, edges, cut)
        if was_bridge(graph, edges, cut):
            ncomponents += 1
        components.append(ncomponents)
    sys.stdout.write(" ".join(map(lambda x: str(x), components)))
    inp.close()


if __name__ == "__main__":
    sys.exit(main(sys.argv))

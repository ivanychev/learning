__author__ = 'Sergey Ivanychev'

class Graph:

    vertices = [] #вершина
    intend_dict = dict()
    def add_vert(self, name):
        if name in self.vertices:
            return
        self.vertices.append(name)
        self.intend_dict[name] = list()
        return

    def add_edge(self, v1, v2):
        if v2 == v1:
            return 0

        self.intend_dict[v1].append(v2)
        return 0

    def __repr__(self): #теперь можно вызывать print(переменная), если переменная = graph()
        return str(self.vertices)

    def __len__(self): #можем использовать len()
        return len(self.vertices)

    def find_route(self):
        lenv = len(self.vertices)

        def go(self,route, v, lenv):
            dub_route = route[:] + [v]
            if len(dub_route) == lenv:
                return dub_route
            flag_go = 0
            for x in self.intend_dict[v]:
                if x not in route:
                    flag_go = 1
                    ret = go(self, dub_route, x, lenv)
                    """if ret == []:
                        out = []
                        return out"""
                    if len(ret) == lenv:
                        return ret


            out = []
            return out
        for x in self.vertices:
            route = go(self, [], x, lenv)
            if route == []:
                continue
            if len(route) == lenv:
                return route
        return ["0"]

def main():
    vertices = input().split()

    g = Graph()

    for x in vertices:
        g.add_vert(x)

    try:
        pair = input().split()
    except EOFError:
        pair = []
    if pair == []:
            pair = []
            print("0")
    g.add_edge(pair[1],pair[0])

    while pair != []:
        try:
            pair = input().split()
        except EOFError:
            pair = []
        if pair == []:
            pair = []
        if pair == []:
            break
        g.add_edge(pair[1],pair[0])

    list = g.find_route()

    for x in range(len(list)):
        print(list[x], end = " ")

    return 0

main()
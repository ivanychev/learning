import random
#import networkx хорошая реализация графов

class Graph:
    """class  Vert:
        pass
    class Edge:
        pass можно зафигачить класс внутри класса"""

    vertices = [] #вершина
    intend_dict = dict()
    def add_vert(self, name):
        if name in self.vertices:
            return
        self.vertices.append(name)
        self.intend_dict[name] = list() # кортеж
        return

    def add_edge(self, v1, v2):
        if v2 == v1:
            return

        if v1 not in self.verticles:
            self.add_vert(v1)
        if v2 not in self.vertices:
            self.add_vert(v2)

        self.intend_dict[v1].append(v2)
        self.intend_dict[v2].append(v1)
        return

    def __repr__(self): #теперь можно вызывать print(переменная), если переменная = graph()
        return str(self.vertices)

    def __len__(self): #можем использовать len()
        return len(self.vertices)

    def __next__(self):
        pass

def gen_graph(n):
    out = Graph()
    for i in range(n):
        out.add_vert(i)
    for i in range(n):
        x = random.randint(0,n-1);
        while x>=0:
            out.add_edge(i,random.randint(0,n-1))
    return out

def search_width(gr):
    def neib(gr,name,flag)
        
    flag = []
    x = 0
    y = 0
    for x in gr.vertices[]:
        if x in flag:
            break
        flag.append(x)
        for y in gr.intend_dic[x]:





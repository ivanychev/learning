import random

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
            return 0
        if v2 in self.intend_dict[v1]:
            return 0
        if v1 not in self.vertices:
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

    def search_width(self):
        """
        Поиск в ширину, полная хрень.
        В самой функции есть две подфункции.
        1 - neib(self, имя вершины, лист помеченных вершин) метит непомеченных соседей и возвращает их список
        2 - level(self, список вершин одного уровня, лист помеченных вершин) - для каждого элемента слоя последовательно
        выполняет функцию neib, формируя лист нового уровня. В конце вызывает рекурсивно саму себя. Постепенно формируе-
        тся список помеченных вершин путем наращивания flag. Когда функция дойдет до нулегого слоя, она возвратит полный
        список помеченных вершин
        Главная функция последовательно рассматривает вершины графа, проверяя, помечены ли они. Если вершина не помечена
        , то исполняется функция level с аргументом [name], где name - имя рассматриваемой вершины. Так как функция
        level вызывает себя рекурсивно, цельный граф, содержащий в себе вершину name проходится и метится полностью, то
        есть следующая найденная непомеченная вершина будет принадлежать другому цельному графу. Таким образом,
        анализируя все вершины, мы осуществляем поисr по всему графу
        """
        flag = []

        def neib(self,name, flag):
            list = []
            for y in self.intend_dict[name]:
                if y not in flag:
                    list.append(y)
                    print(y)

            return list

        def level(self,list,flag):
            if (list == []):
                return flag
            out = []
            time = 0
            for x in list:
                out += neib(self, x, flag + out)

            flag += out

            return(level(self, out, flag))

        x = 0
        for x in self.vertices:
            if x in flag:
                continue
            flag.append(x)
            print(x)
            flag = level(self, [x], flag)

        return flag

    def search_depth(self):


        flagin = []
        flagout = []

        """
        flagin - список с вершинами, в которые мы "входили"
        flagout - список с вершинами, из которых мы вышли
        in_apex() - функция, конфигурирующее наше поведение, находясь в какой-либо вершине. Мы по очереди заходим в те соседние
        вершины, которые не находятся в списке flagin, т.е. не пройденные нами ранее. зайдяв дальнейшую вершину, мы рекурсивно
        вызываем ту же функцию. Она возвращает списки flagin и flagout, дополняя их вершинами по мере необходимости
        """
        def in_apex(self,name,flagin,flagout):
            for i in self.intend_dict[name]:
                if (i not in flagin):
                    flagin += [i]
                    print("to",i)
                    flagin, flagout = in_apex(self, i, flagin, flagout)
            print("out",name)
            flagout += [name]
            return flagin, flagout

        x = 0

        for x in self.vertices:
            if x in flagout:
                continue
            flagin.append(x)
            print("to",x)
            flagin, flagout = in_apex(self, x, flagin, flagout)
        return flagin, flagout







def gen_graph(n): #генерирует граф длины n, названиями вершин 0..n-1, каждая из которых произвольно соединена с другими
    out = Graph()
    for i in range(n):
        out.add_vert(i)
    for i in range(n):
        x = random.randint(0,n-1);
        while x>=0:
            out.add_edge(i,random.randint(0,n-1))
            x -= 1
    return out

def main():
    #g = gen_graph(10);
    g = Graph()
    """
    g.add_vert(1)
    g.add_vert(2)
    g.add_vert(3)
    g.add_vert(4)

    g.add_edge(1,2)
    g.add_edge(3,4)
    """
    g.add_vert(1)
    g.add_vert(2)
    g.add_vert(3)
    g.add_vert(4)
    g.add_vert(5)
    g.add_vert(6)
    g.add_vert(7)
    g.add_vert(8)

    g.add_edge(1,2)
    g.add_edge(1,3)
    g.add_edge(2,4)
    g.add_edge(3,6)
    g.add_edge(4,5)
    g.add_edge(6,5)
    g.add_edge(7,8)

    print(g)
    flag = g.search_width() #формат вывода - номера вершин в последовательности прохода, связность графа не обязательна
    listin, listout = g.search_depth() #формат вывода - траектория прохода по графу, связность графа не обязательна
    #по прохождении вершины обе функции сами выводят информацию
    #print(flag, listin, listout)
    return 0

main()
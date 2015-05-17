class myFirstClass:
    def method(self):
        pass

    pass

class Figure:
    def __init__(self): #метод создания объекта собственного класса
        print("first")
        pass

    surface = 0
    perim = 0
    pass

class Triangle(Figure):
    x1  = 0
    y1 = 0
    height = 0
    length = 0
    def __init__(self, h, l):
        Figure.__init__(self)
        print("Second")
        self.height = h
        self.length = l
    def getSurface(self):
        return self.height * self.length / 2
    pass



obj = myFirstClass()
obj.k = 10
obj.method()

tri = Triangle(5, 10)
print(tri.getSurface())

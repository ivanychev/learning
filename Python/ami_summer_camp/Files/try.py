__author__ = 'Sergey Ivanychev'


"""f = open(filename, mode(w,r,rw))
f.write()
f.read()
f.readline()
f.close()

или

with f = open(file):
    pass

после этого файл автоматически закрывается

PRINT

print(shit,shit2,end = "замена \n по умолчанию")
file = sys.stdout - ???

OS


import os импортирует стандартные инструменты с файловой системой

os.listfir()

и так далее

PICKLE

import pickle

pickle.dump(obj) принимает на вход любой объект (или класс), возвращает строчку. Можно записать в файл
pickle.load(str) - возвращает объект, зафигаченный ранее в строку

PRETTYPRINT

pprint() - в каком-то модуле (может в textwarp)

ФОРМАТИРОВАННЫЙ ВЫВОД

str.format(x,a,b) карочи в учебнике есть


КАК УЗНАТЬ, КАКИЕ МОДУЛИ МОЖНО ИМПОРТИРОВАТЬ?

import inspect

в этом модуле есть функция ismodule(), isclass(), isfunction()


КАК РАБОТАЕТ ФУНКЦИЯ НА МАШИННОМ УРОВНЕ

sys.currentframe() - возвращает содержимое текущего кадра стека
inspect.getframe(number) - или что-то вроде этого :D

ВСТРОЕННЫЙ ОТЛАДЧИК

import pdb - дебаггер карочи

pdb.pm() - начинает отладку на месте смерти скрипта


ИСКЛЮЧЕНИЯ!!!!


"""

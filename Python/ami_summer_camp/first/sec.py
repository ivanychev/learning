#!/usr/bin/python
# hashbang, для исполнения скрипта в *nix - системах, указывает интерпретатор
# -*- coding: utf-8 -*-
# Кодировка файла, необходимо для правильного отображения не англ. строк в интерпретаторе
""" Программа реализует примитивный метод шифрования - шифр Цезаря.
	Сам алгоритм прост - циклициски сдвигаем буквы алфавита в строке на k позиций
	Между тем, это - многострочный коментарий, он же docstring"""

import sys # используем чтобы подключить сторонний модуль. В момент подключения он интерпретируется.
# В таком виде, содержимое модуля sys доступно через точку - sys.exit() - функция exit() из модуля sys.
# Можно также использовать такой видм импорта:
from math import *
# Теперь все содержимое модуля datetime доступно напрямую. Вместо * можно указать конкетные функции\классы\т.д.


def encrypt(k): # функция, которая принимает один аргумент
	plaintext = input('Введите сообщение: ') # Самый простой пользовательский ввод через клавиатуру. Аргумент input - приглашение, которое увидит пользователь
	cipher = '' # объявили переменную-строку, учтите - строки неизменяемы.

	for each in plaintext: # пример цикла for по _строке_ plaintext
		c = (ord(each)+k) % 126 # ord - возвращает ASKII код символа

		if (c < 32):
			c += 31

		cipher += chr(c)  # Не смотря на то, как это выглядит, мы не расширяем строку, а каждый раз создаем новую

	print('Шифротекст: ' + cipher)


def decrypt(k):
	cipher = input('Введите шифротекст: ')
	plaintext = ''

	for each in cipher:
		p = (ord(each)-k) % 126

		if (p < 32):
			p+=95

		plaintext += chr(p)

	print('Ваше сообщение: ' + plaintext)


def math_example(first_positional_arg, second_positional_arg = 100, *unamed_args_list, **named_args_dict):
	""" Функция n переменных.
		Первый аргумент обычный,
		второй - со значением по умолчанию,
		третий - там будет список всех безымянных лишних аргументов,
		четвертый - словарь всех лишних именованных аргументов. См приминение
						Подробности - http://docs.python.org/3.3/library/math.html"""
	assert type(first_positional_arg) is int
	a = first_positional_arg
	result = factorial(a)
	print(result)
	print("Exponent: " + str(exp(second_positional_arg)))
	print(log(a) + log2(a) )
	print(sqrt(result))
	for x in unamed_args_list:
		print(str(x) + ' ', end='') # именованный аргумент end - строка, которую припишут к концу, по умолчанию - символ перевода
	for key, value in named_args_dict.items():
		print("Key: {}, value: {}".format(key, value))
	return a, result


def main(argv):
	if (len(sys.argv) != 3):
		sys.exit('Порядок запуска: ceaser.py <k> <mode>')

	if sys.argv[2] == 'e':
		encrypt(int(sys.argv[1]))
	elif sys.argv[2] == 'd':
		decrypt(int(sys.argv[1]))
	elif sys.argv[2] == 'b':
		math_example(3, 1, 3, 4 ,5, 6, gg=4, aa= 1, bb= 6)
	else:
		sys.exit('Несуществующий режим')


if __name__ == "__main__":
	main(sys.argv[1:])


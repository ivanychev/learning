"""
y(x) = y(x0) + y'(x0)/1 * dx + y''(x0)/2! * d^2x + y'''(x0)/3! * d^3 * x ... - ряд Тейлора

Наглядный пример - температура стержня

y(t) = y(t0) + y'(t0)/1 * dt + y''(t0)/2! * d^2t + y'''(t0)/3! * d^3 * t ...

Создается сетка. Одна ось - время, другая - координата. Точка (узел) на сетке, температура в данное время, в данной координате

Пусть удалось померить температуру только первые три секунды в x0.

2Y't = Y'x - закон распределения температуры в стержне (учебник физики)


"""


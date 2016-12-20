
# coding: utf-8

# # Задача
#
# Для $t=1\ldots T$, $d_t$ – спрос на продукцию в период $t$; $c_t$, $p_t$ и $h_t$ – заданные предельные расходы на подготовку, производство и хранение продукции соответственно в период $t$.
#
# Цель: минимизация суммарных расходов на подготовку, производство и хранение продукции при условии удовлетворения спроса $d_t$ в каждый из $T$ периодов. Введем непрерывные переменные:
#
# * $y_t$ – запас продукции в период $t$
# * $s_t$ – остаток продукции в период $t$
#
# и бинарные решающие переменные $x_t$
#
# $$
# x_t = \begin{cases}
#     1, & \text{ if } y_t > 0 \\
#     0, & \text{ otherwise }
# \end{cases}
# $$
#
# $$
# \min \sum_{t=1}^{T} (p_ty_t+h_ts_t+c_tx_t)
# $$
# при ограничениях
# $$
# \begin{align*}
#     & y_1 = d_1 + s_1 & \\
#     & s_{t-1} + y_t = d_t + s_t & t=1\ldots T\\
#     & s_t, y_t \geq 0 & \\
#     & x_t \in \{0, 1\} & t=1\ldots T\\
#     & s_T = 0 & \\
#     & y_t \leq \omega x_t & t=1\ldots T \\
# \end{align*}
# $$
# Где $\omega = \sum_{t=1}^T d_t$
#

# # Решаем задачу

# In[1]:

import pyomo.environ as po
EPS = 10e-5


# ## Определяем параметры и переменные
model = po.AbstractModel()

model.T = po.Param(within=po.NonNegativeIntegers)
model.I = po.RangeSet(1, model.T)
model.I1 = po.RangeSet(2, model.T)
model.C = po.Param(model.I, within=po.NonNegativeReals)
model.P = po.Param(model.I, within=po.NonNegativeReals)
model.H = po.Param(model.I, within=po.NonNegativeReals)
model.D = po.Param(model.I, within=po.NonNegativeIntegers)
model.X = po.Var(model.I, within=po.IntegerSet(0, 1), initialize=1)
model.Y = po.Var(model.I, within=po.NonNegativeIntegers, initialize=1)
model.S = po.Var(model.I, within=po.NonNegativeIntegers)


# ## Определяем целевую функцию

# In[3]:

def objective(model):
    return po.summation(model.P, model.Y) + po.summation(model.H, model.S) + po.summation(model.C, model.X)

model.OBJ = po.Objective(rule=objective, sense=po.minimize)


# ## Определяем ограничения

# $$
# \begin{align*}
#     & y_1 = d_1 + s_1 & \\
#     & s_{t-1} + y_t = d_t + s_t & t=1\ldots T\\
#     & s_t, y_t \geq 0 & \\
#     & x_t \in \{0, 1\} & t=1\ldots T\\
#     & s_T = 0 & \\
#     & y_t \leq \omega x_t & t=1\ldots T \\
# \end{align*}
# $$

# In[4]:

def constraint1(model):
    return model.Y[1] == model.D[1] + model.S[1]

def constraint2(model, i):
    return model.S[i - 1] + model.Y[i] == model.D[i] + model.S[i]

def constraint3(model, i):
    return (model.X[i] == 0 and model.Y[i] == 0) or (model.X[i] == 1 and model.Y[i] >= EPS)

def constraint4(model):
    return model.S[model.T] == 0

def constraint5(model, i):
    return model.Y[i] <= model.X[i]*sum(model.D)

model.Constraint1 = po.Constraint(rule=constraint1)
model.Constraint2 = po.Constraint(model.I1, rule=constraint2)
model.Constraint3 = po.Constraint(model.I, rule=constraint3)
model.Constraint4 = po.Constraint(rule=constraint4)
model.Constraint5 = po.Constraint(model.I, rule=constraint5)

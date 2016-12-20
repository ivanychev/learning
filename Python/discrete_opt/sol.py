"""
Pyomo script for solving production task. Formulation is contained
in formulation.JPG and Production.ipynb. Data is provided in prod.dat

To launch it via glpk solver:

pyomo solve --solver=glpk sol.py prod.dat

Author: Sergey Ivanychev
Revision: 1
"""
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

def objective(model):
    return po.summation(model.P, model.Y) + po.summation(model.H, model.S) + po.summation(model.C, model.X)

model.OBJ = po.Objective(rule=objective, sense=po.minimize)


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

## Production problem

Pyomo script for solving production task. Formulation is contained
in `formulation.JPG` and `Production.ipynb`. Data is provided in `prod.dat`. Output
is provided in `results.yml`.

To launch it via glpk solver:

```bash
pyomo solve --solver=glpk sol.py prod.dat
```

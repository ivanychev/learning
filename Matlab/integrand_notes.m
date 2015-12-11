% example of integrand
syms r a e_0
I = int(-e_0/(pi*a^3)*exp(-2*r/a)*e_0/r*4/3*pi*r^3, r, 0, +Inf)

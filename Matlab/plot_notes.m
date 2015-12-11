% Source: http://www.exponenta.ru/soft/matlab/potemkin/book2/chapter10/plot.asp
%
% plot(y)
% plot(x, y)
% plot(x, y, s)
% plot(x1, y1, s1, x2, y2, s2, ...)

% array of points from -pi to pi with the step of pi/500
% row!
x = -pi:pi/500:pi
y = sin(x)

% argument --- number of element
plot(y)
% argument --- x
plot(x, y)

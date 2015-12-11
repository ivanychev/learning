% Sources
%
%   http://life-prog.ru/view_zam.php?id=53
%   http://www.exponenta.ru/soft/matlab/potemkin/book2/chapter7/eig.asp


% Matrix creation
A = [1 2; 3 4]

% Matrix transpose
A_T = a'

% Matrix inverse
A_inv = inv(A)
A*A_inv

% Eigenvalues
temp = eig(A)
temp(1) + temp(2)


% Eigenvectors and eigenvalues
[eigVec, eigVal] = eig(A)
A * eigVec - eigVec * eigVal


P = [1 2 0 2; 4 10 12 5; 0 11 10 5; 9 2 3 5]
P(2, 3)         % 2th row, 3rd column
P1 = P(2:3,2:3) % middle submatrix example
p  = P(2, :)    % second row
p2 = P(:, 2)    % second column

I  = eye(4)      % Identity matrix
Z  = zeros(3)
Z2 = zeros(3, 5)
Z2 = ones(3, 5)
I  = eye(4, 7)

d = [1; 2; 3; 4];
D = diag(d)     % diagonal matrix from vector
d = diag(D)     % extract diagonal of matrix to vector


% Norms
A = [5 -2 6; -2 11 0; 6 0 11]

n1 = norm(A, Inf)         % (1st in lectures) Maximum norm
                          % max of sums of rows absolute values
n2 = norm(A, 1)           % (2nd in lectures)
                          % first norm, max of sums of columns absolute values
n3 = norm(A, 2)           % (3rd in lectures) Euclidean norm
% n4 = norm(A, 'fro')     % Frobenius norm

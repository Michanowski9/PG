clc
N = 7;       %tyle bo tyle mamy w sieci
d = 0.85;    %wspolczynnik

Edges = sparse([1,1,2,2,2,3,3,3,4,4,5,5,6,6,7; ...
                4,6,3,4,5,5,6,7,5,6,4,6,4,7,6]);

B = sparse(Edges(2,:), Edges(1,:), 1, N, N);

L = sum(B)';

A = sparse(diag(1./L));

I = speye(N);

b = zeros(N,1);
for i = 1:N
    b(i) = (1-d)/N;
end
b;

M = sparse(I - d*B*A);

r = M \ b;

bar(r)
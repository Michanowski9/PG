% Zadanie B
%------------------
% generacja macierzy I, A, B i wektora b
% ...
d = 0.85;
B = sparse(Edges(2,:), Edges(1,:), 1, N, N);
L = sum(B)';
A = sparse(diag(1./L));
I = speye(N);

b = zeros(N,1);
for i = 1:N
   b(i) = (1-d)/N;
end
% b

issparse(B)
% macierze A, B i I muszą być przechowywane w formacie sparse (rzadkim)

save zadB_175793 A B I b
%-----------------
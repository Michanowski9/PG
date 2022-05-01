% Zadanie D
%------------------
clc
clear all
close all

density = 10;
N = [500, 1000, 3000, 6000, 12000];
d = 0.85;

czas_Gauss = zeros(size(N));

for i = 1:5
    [Edges] = generate_network(N(i), density);
    
    B = sparse(Edges(2,:), Edges(1,:), 1, N(i), N(i));
    L = sum(B)';
    A = sparse(diag(1./L));
    I = speye(N(i));
    
    b = zeros(N(i),1);
    for j = 1:N(i)
       b(j) = (1-d)/N(i);
    end

    M = sparse(I - d*B*A);

    tic
    % obliczenia
    r = M \ b;
    czas_Gauss(i) = toc;
end

plot(N, czas_Gauss)
ylabel("Czas w sekundach");
xlabel("rozmiar macierzy N")
title("Czas rozwiązania układu równań metodą bezpośrednią");
saveas(gcf, 'zadD_175793.png')
%------------------
% Zadanie E
%------------------
clc
clear all
close all

% przykład działania funkcji tril, triu, diag:
% Z = rand(4,4)
% tril(Z,-1) 
% triu(Z,1) 
% diag(diag(Z))

d = 0.85;
density = 10;
N = [500, 1000, 3000, 6000, 12000];
breakValue = 10^(-14);

iterations = zeros(size(N));
czas_Gauss_Seidl = zeros(size(N));

for i = 1:5
    [Edges] = generate_network(N(i), density);
    
    B = sparse(Edges(2,:), Edges(1,:), 1, N(i), N(i));
    A = sparse(diag(1./(sum(B)')));
    I = speye(N(i));
    
    b = zeros(N(i),1);
    for j = 1:N(i)
       b(j) = (1-d)/N(i);
    end

    M = sparse(I - d*B*A);

    tic
    % obliczenia
    D = diag(diag(M));
    U = triu(M,1);
    L = tril(M,-1);
    r = ones(N(i),1);
    
    iterations(i) = 0;

    while(true)
        iterations(i) = iterations(i) + 1;
        r = (-(D + L))\(U*r) + ((D + L) \ b);
        res = M*r - b;
        resNorm(i, iterations(i)) = norm(res);
        if(norm(res) <= breakValue || isnan(norm(res)))
            break
        end
    end
    czas_Gauss_Seidl(i) = toc;
end

figure('Name', 'Zadanie F - czas');
plot(N, czas_Gauss_Seidl)
title("Zadanie F - czas");
ylabel("Czas");
xlabel("Rozmiar macierzy");
saveas(gcf, 'zadF_175793_1.png');

figure('Name', 'Zadanie F - liczba iteracji');
plot(N, iterations)
title("Zadanie F - liczba iteracji");
ylabel("Liczba iteracji");
xlabel("Rozmiar macierzy");
saveas(gcf, 'zadF_175793_2.png');

figure('Name', 'Zadanie F - norma z residuum dla N = 1000');
semilogy(resNorm(2, 1:iterations(2)));
title('Zadanie F - norma z residuum dla N = 1000')
ylabel("Norma z residuum");
xlabel("iteracja");
saveas(gcf, 'zadF_175793_3.png');
%------------------
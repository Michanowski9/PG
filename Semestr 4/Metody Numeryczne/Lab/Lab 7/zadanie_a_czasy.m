clc
clear all
close all

load P_ref

a = 0;
b = 5;
N = 10^7;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%               prostokaty              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
tic

suma = 0;
dx = b / N;
for i = 1:N
    arg = ((i - 1) * dx + i * dx) / 2;
    suma = suma + dx * funkcja_awarii(arg);
end

time_p = toc;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                trapezy                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
tic

suma = 0;
dx = (b - a) / N;
for i = 1:N
    temp = funkcja_awarii(a + (i - 1) * dx);
    temp = temp + funkcja_awarii(a + i * dx);
    temp = temp * dx / 2;
    suma = suma + temp;
end

time_t = toc;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%               Simpsona                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
tic

suma = 0;
dx = (b - a) / N;
for i = 1:N
    suma = suma + funkcja_awarii(a + (i - 1) * dx);
    suma = suma + 4 * funkcja_awarii((a + (i - 1) * dx + a + i*dx) / 2);
    suma = suma + funkcja_awarii(a + i * dx);
end
suma = suma * dx / 6;

time_s = toc;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%              Monte Carlo              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
tic

fmin = 0;
fmax = funkcja_awarii(10);

N_1 = 0;
for i = 1:N
    x = rand() * b;
    y = rand() * fmax;
    if y >= fmin && y <= funkcja_awarii(x)
        N_1 = N_1 + 1;
    end
end
suma = (N_1/N)*b*fmax;

time_mc = toc;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                wykres                 %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure();
y = [time_p; time_t; time_s; time_mc];
bar(y); 
title('Czas wykonania metod');
xlabel('Metoda');
ylabel('Czas [s]');
saveas(gcf, "czas_wykonywania.png");


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%            funckja awarii             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function f = funkcja_awarii(t)
    f = (1/(3 * sqrt(2 * pi))) * exp(-(t - 10)^2 /(2 * 3^2));
end

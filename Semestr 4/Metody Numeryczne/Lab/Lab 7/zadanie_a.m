clc
clear all
close all

load P_ref.mat

a = 0;
b = 5;
x = 5:50:10^4;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%               prostokaty              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
err = [];
n_arr = [];

for N = 5:50:10^4
    suma = 0;
    dx = b / N;
    for i = 1:N
        arg = ((i - 1) * dx + i * dx) / 2;
        suma = suma + dx * funkcja_awarii(arg);
    end
    err = [err, abs(suma - P_ref)];
end

figure();
loglog(x, err);
title('Błąd - prostokąty');
xlabel('Liczba przedziałów');
ylabel('Wartość błędu');
saveas(gcf, 'prostokaty_blad.png')


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                trapezy                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
err = [];

for N = 5:50:10^4
    suma = 0;
    dx = (b - a) / N;
    for i = 1:N
        temp = funkcja_awarii(a + (i - 1) * dx);
        temp = temp + funkcja_awarii(a + i * dx);
        temp = temp * dx / 2;
        suma = suma + temp;
    end
    err = [err, abs(suma - P_ref)];
end

figure();
loglog(x, err);
title('Błąd - trapezy');
xlabel('Liczba przedziałów');
ylabel('Wartość błędu');
saveas(gcf, 'trapezy_blad.png')


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%               Simpsona                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

err = [];

for N = 5:50:10^4
    suma = 0;
    dx = (b - a) / N;
    for i = 1:N
        suma = suma + funkcja_awarii(a + (i - 1) * dx);
        suma = suma + 4 * funkcja_awarii((a + (i - 1) * dx + a + i*dx) / 2);
        suma = suma + funkcja_awarii(a + i * dx);
    end
    suma = suma * dx / 6;
    err = [err, abs(suma - P_ref)];
end
figure();
loglog(x, err);
title('Błąd - Simpson');
xlabel('Liczba przedziałów');
ylabel('Wartość błędu');
saveas(gcf, 'simpson_blad.png')


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%              Monte Carlo              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

err = [];
fmin = 0;
fmax = funkcja_awarii(5);

for N = 5:50:10^4
    N_1 = 0;
    for i = 1:N
        x_loc = rand() * b;
        y = rand() * fmax;
        if y >= fmin && y <= funkcja_awarii(x_loc)
            N_1 = N_1 + 1;
        end
    end
    P = (N_1 / N) * b * fmax;
    err = [err, abs(P - P_ref)];
end

figure();
loglog(x, err);
title('Błąd - Monte Carlo');
xlabel('Liczba przedziałów');
ylabel('Wartość błędu');
saveas(gcf, 'monte_carlo_blad.png')


close all


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%            funckja awarii             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function f = funkcja_awarii(t)
    f = (1/(3 * sqrt(2 * pi))) * exp(-(t - 10)^2 /(2 * 3^2));
end

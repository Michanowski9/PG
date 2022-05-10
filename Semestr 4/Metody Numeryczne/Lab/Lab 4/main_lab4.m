clc
clear all
close all


%zadanie 1
a = 1
b = 60000
eps = 10^-3

% zadanie 1 - bisekcja
[xvect, xdif, fx, it_cnt] = bisect(a, b, eps, @compute_time)

semilogy(1:it_cnt, xvect)
title("Zadanie 1. Wartości kolejnych przybliżeń (bisekcja)");
ylabel("Liczba parametrów wejściowych");
xlabel("Nr iteracji");
saveas(gcf, 'zad1_przyblizenia_bisekcja.png');

semilogy(1:it_cnt, xdif)
title("Zadanie 1. Różnice pomiędzy wartościami (bisekcja)");
ylabel("Różnica");
xlabel("Nr iteracji");
saveas(gcf, 'zad1_roznice_bisekcja.png');

% zadanie 1 - sieczne
[xvect, xdif, fx, it_cnt] = sieczne(a, b, eps, @compute_time)

semilogy(1:it_cnt, xvect)
title("Zadanie 1. Wartości kolejnych przybliżeń (sieczne)");
ylabel("Liczba parametrów wejściowych");
xlabel("Nr iteracji");
saveas(gcf, 'zad1_przyblizenia_sieczne.png');

semilogy(1:it_cnt, xdif)
title("Zadanie 1. Różnice pomiędzy wartościami (sieczne)");
ylabel("Różnica");
xlabel("Nr iteracji");
saveas(gcf, 'zad1_roznice_sieczne.png');




%zadanie 2
a = 1
b = 50
eps = 1e-12

% zadanie 2 - bisekcja
[xvect, xdif, fx, it_cnt] = bisect(a, b, eps, @compute_impedance)

semilogy(1:it_cnt, xvect)
title("Zadanie 2. Wartości kolejnych przybliżeń (bisekcja)");
ylabel("Częstotliwość kątowa");
xlabel("Nr iteracji");
saveas(gcf, 'zad2_przyblizenia_bisekcja.png');

semilogy(1:it_cnt, xdif)
title("Zadanie 2. Różnice pomiędzy wartościami (bisekcja)");
ylabel("Różnica");
xlabel("Nr iteracji");
saveas(gcf, 'zad2_roznice_bisekcja.png');

% zadanie 2 - sieczne
[xvect, xdif, fx, it_cnt] = sieczne(a, b, eps, @compute_impedance)

semilogy(1:it_cnt, xvect)
title("Zadanie 2. Wartości kolejnych przybliżeń (sieczne)");
ylabel("Częstotliwość kątowa");
xlabel("Nr iteracji");
saveas(gcf, 'zad2_przyblizenia_sieczne.png');

semilogy(1:it_cnt, xdif)
title("Zadanie 2. Różnice pomiędzy wartościami (sieczne)");
ylabel("Różnica");
xlabel("Nr iteracji");
saveas(gcf, 'zad2_roznice_sieczne.png');



%zadanie 3
a = 1
b = 50
eps = 1e-12

% zadanie 3 - bisekcja
[xvect, xdif, fx, it_cnt] = bisect(a, b, eps, @compute_velocity)

semilogy(1:it_cnt, xvect)
title("Zadanie 3. Wartości kolejnych przybliżeń (bisekcja)");
ylabel("Przybliżony czas");
xlabel("Nr iteracji");
saveas(gcf, 'zad3_przyblizenia_bisekcja.png');

semilogy(1:it_cnt, xdif)
title("Zadanie 3. Różnice pomiędzy wartościami (bisekcja)");
ylabel("Różnica");
xlabel("Nr iteracji");
saveas(gcf, 'zad3_roznice_bisekcja.png');

% zadanie 3 - sieczne
[xvect, xdif, fx, it_cnt] = sieczne(a, b, eps, @compute_velocity)

semilogy(1:it_cnt, xvect)
title("Zadanie 3. Wartości kolejnych przybliżeń (sieczne)");
ylabel("Przybliżony czas");
xlabel("Nr iteracji");
saveas(gcf, 'zad3_przyblizenia_sieczne.png');

semilogy(1:it_cnt, xdif)
title("Zadanie 3. Różnice pomiędzy wartościami (sieczne)");
ylabel("Różnica");
xlabel("Nr iteracji");
saveas(gcf, 'zad3_roznice_sieczne.png');


options = optimset('Display','iter')
fzero(@tan,6,options)
fzero(@tan,4.5,options)




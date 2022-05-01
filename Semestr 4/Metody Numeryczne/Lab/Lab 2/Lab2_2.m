clc

program(10, 100, 1, "wykres1.png");

pause(2);

program(10, 100, 2, "wykres2.png");



function program(a,n_max,r_max,filename)
    fprintf(1, '----------START FUNKCJI----------\n ')
    figure('Name', 'Bąbelki');

    %utworzenie list do wszystkich kół
    x = zeros(1,n_max);
    y = zeros(1,n_max);
    r = zeros(1,n_max);
    areas = zeros(1,n_max);
    roundCounter = zeros(1,n_max);
 
    for n = 1:n_max
        while(1)
            %inkrementacja licznika losowań
            roundCounter(n) = roundCounter(n) + 1;
    
            %losowanie parametrów koła
            currentx = rand(1) * a;
            currenty = rand(1) * a;
            currentr = rand(1) * r_max;
                    
            %sprawdzenie czy poprawny
            if(currentx - currentr > 0 && ...
                    currentx + currentr < a && ...
                    currenty - currentr > 0 && ...
                    currenty + currentr < a && ...
                    checkFlag(currentx,currenty,currentr,x,y,r,n) == true)
                %jesli poprawny to zapisuje do listy
                x(n) = currentx;
                y(n) = currenty;
                r(n) = currentr;           
                areas(n) = pi * currentr * currentr;
                fprintf(1, ' %s%5d%s%.3g\r ', 'n =', n, ' S = ', sum(areas))
                break
            end
        end
    
        xlabel("x");
        ylabel("y");
        title('Bąbelki');

        axis([0 a 0 a])
        plot_circ(currentx,currenty,currentr);
        pause(0.01);
        hold on
    end

    %zapisanie do pliku wykresu
    saveas(gcf, filename);
    
    %wyswietlenie wykresów
    figure('Name', 'Powierzchnia całkowita');
    semilogx(1:n, cumsum(areas));
    xlabel("n");
    title('Powierzchnia całkowita');
    
    figure('Name', 'Średnia liczba losowań');
    loglog(cumsum(roundCounter)./(linspace(1,n_max,n_max)));
    xlabel("n");
    title('Średnia liczba losowań');
end

function result = checkFlag(X,Y,R,x,y,r,n)
    for i = 1:n
        tempx = (x(i) - X) .^ 2;
        tempy = (y(i) - Y) .^ 2;
        if(sqrt(tempx + tempy) < r(i) + R)
            result = false;
            return
        end
    end
    result = true;
end

function plot_circ(X, Y, R)
    theta = linspace(0,2*pi);
    x = R*cos(theta) + X;
    y = R*sin(theta) + Y;
    plot(x,y)
end
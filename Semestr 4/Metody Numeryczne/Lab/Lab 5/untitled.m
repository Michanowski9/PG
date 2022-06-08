[XX,YY] = meshgrid(linspace(0,100,101),linspace(0,100,101));

divp = [];
divt = [];
FFpp = [];
FFtp = [];

for i = 5:45

    [x,y,f,xp, yp] = lazik(i);

    [p] = polyfit2d(x,y,f);
    [FFp] = polyval2d(XX,YY,p);
    [p] = trygfit2d(x,y,f);
    [FFt] = trygval2d(XX,YY,p);
  
  if i == 5
    FFpp = FFp;
    FFtp = FFt;
  else
    divp = [divp, max(max(abs(FFp - FFpp)))];
    divt = [divt, max(max(abs(FFt - FFtp)))];

    FFpp = FFp;
    FFtp = FFt;
  end
end

plot(6:45, divp);
title("Zbieżność interpolacji wielomianowej");
ylabel("Maksymalna różnica interpolowanych funkcji");
xlabel("Ilość punktów pomiarowych");
saveas(gcf, 'zad2_wielom.png');

plot(6:45, divt);
title("Zbieżność interpolacji trygonometrycznej");
ylabel("Maksymalna różnica interpolowanych funkcji");
xlabel("Ilość punktów pomiarowych");
saveas(gcf, 'zad2_tryg.png');

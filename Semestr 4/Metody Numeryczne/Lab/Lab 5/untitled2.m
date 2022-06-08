K = [4, 15, 25, 35];
[XX,YY] = meshgrid(linspace(0,100,101),linspace(0,100,101));
  
for i = K
  [x, y, f, xp, yp] = lazik(i);

  subplot(2, 2, 1)
  plot(xp, yp, '-o', 'linewidth', 3);
  title(strcat("Tor ruchu łazika K = ", num2str(i)));
  ylabel("y [km]");
  xlabel("x [km]");
  
  subplot(2, 2, 2);
  plot3(x, y, f, 'o');
  title(strcat("Zebrane wartości próbek K = ", num2str(i)));
  ylabel("y [km]");
  xlabel("x [km]");
  zlabel("f (x,y)");
  
  [p] = polyfit2d(x, y, f);
  [FF] = polyval2d(XX, YY, p);
  subplot(2, 2, 3);
  surf(YY, XX, FF);
  shading flat;
  title(strcat("Interpolacja wielomianowa K = ", num2str(i)));
  ylabel("y [km]");
  xlabel("x [km]");
  zlabel("f (x,y)");
  
  [p] = trygfit2d(x, y, f);
  [FF] = trygval2d(XX, YY, p);
  subplot(2, 2, 4);
  surf(YY, XX, FF);
  shading flat;
  title(strcat("Interpolacja trygonometryczna K = ", num2str(i)));
  ylabel("y [km]");
  xlabel("x [km]");
  zlabel("f (x,y)");

  saveas(gcf, strcat("zad1_K_", num2str(i),".png"));
end

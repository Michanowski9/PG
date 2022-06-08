clc
clear all
close all

warning('off','all')

load trajektoria2

N = 60;
[ wsp, xa ] = aproksymacjaWiel(n,x,N);
[ wsp, ya ] = aproksymacjaWiel(n,y,N); 
[ wsp, za ] = aproksymacjaWiel(n,z,N); 

plot3(x,y,z,'o')
grid on
axis equal
hold on

plot3(xa, ya, za, 'lineWidth', 4);

title("Trajektoria zmierzona i aproksymowana N = 60");
xlabel("x");
ylabel("y");
zlabel("z");

saveas(gcf,'175793_Soja_zad5.png')

close all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                   zadanie 5 b)                        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

err = [];
M =size(n,2);

for i = 1:71
    xsum = 0;
    ysum = 0;
    zsum = 0;
    
    [ wsp, xa ] = aproksymacjaWiel(n,x,i);
    [ wsp, ya ] = aproksymacjaWiel(n,y,i); 
    [ wsp, za ] = aproksymacjaWiel(n,z,i); 
    
    for j = i:M
        xsum = xsum + (x(j)- xa(j)).^2;
        ysum = xsum + (x(j)- xa(j)).^2;
        zsum = xsum + (x(j)- xa(j)).^2;
    end
    xerr = sqrt(xsum)/M;
    yerr = sqrt(ysum)/M;
    zerr = sqrt(zsum)/M;
    err(i) = xerr+yerr+zerr;

end

semilogy(err)

title("Błąd aproksymacji wielomianowej.");
xlabel("N");
ylabel("błąd");

saveas(gcf,'175793_Soja_zad5b.png')

close all



clc
clear all
close all

warning('off','all')

load trajektoria2

N = 60;
[ xa ] = aprox_tryg(n,x,N);
[ ya ] = aprox_tryg(n,y,N); 
[ za ] = aprox_tryg(n,z,N); 

plot3(x,y,z,'o')
grid on
axis equal
hold on

plot3(xa, ya, za, 'lineWidth', 4);

title("Trajektoria zmierzona i aproksymowana N = 60");
xlabel("x");
ylabel("y");
zlabel("z");

saveas(gcf,'175793_Soja_zad7.png')

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
    
    [ xa ] = aprox_tryg(n,x,i);
    [ ya ] = aprox_tryg(n,y,i); 
    [ za ] = aprox_tryg(n,z,i); 
    
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

saveas(gcf,'175793_Soja_zad7b.png')

close all



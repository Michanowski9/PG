clc
clear all
close all

warning('off','all')

load trajektoria1

N = 50;
[ wsp, xa ] = aproksymacjaWiel(n,x,N);
[ wsp, ya ] = aproksymacjaWiel(n,y,N); 
[ wsp, za ] = aproksymacjaWiel(n,z,N); 

plot3(x,y,z,'o')
grid on
axis equal
hold on

plot3(xa, ya, za, 'lineWidth', 4);

title("Trajektoria zmierzona i aproksymowana N = 50");
xlabel("x");
ylabel("y");
zlabel("z");
saveas(gcf,'175793_Soja_zad4.png')



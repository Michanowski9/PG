clc
clear all
close all

warning('off','all')

load trajektoria1

plot3(x,y,z,'o')
grid on
axis equal

title("Trajektoria zmierzona");
xlabel("x");
ylabel("y");
zlabel("z");

saveas(gcf,'175793_Soja_zad2.png')
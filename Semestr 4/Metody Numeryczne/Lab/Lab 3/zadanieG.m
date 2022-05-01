load("Dane_Filtr_Dielektryczny_lab3_MN.mat");

metoda = "Gaussa"
r =  M\b;
save wynik_Gauss r



metoda = "Jacobi"
breakValue = 10^(-14);
r = ones(size(b));

D = diag(diag(M)); 
U = triu(M, 1); 
L = tril(M, -1);

while(true) 
    r = (-D \(L + U))*r + (D \ b); 
    res = M*r - b; 
    if(norm(res) <= breakValue || isnan(norm(res)))
      break 
    end 
end 
save wynik_Jacobi r



metoda = "Gaussa-Seidla"
breakValue = 10^(-14);
r = ones(size(b));

D = diag(diag(M)); 
U = triu(M, 1); 
L = tril(M, -1);

i = 0;
while(i < 1000) 
    i = i + 1;
    r = (-(D + L))\(U*r) + ((D + L) \ b);
    res = M*r - b; 
    if(norm(res) <= breakValue || isnan(norm(res)))
      break 
    end 
end 
save wynik_Gauss_Seidl r


%Rozwiązanie problemu metodą gradientu:

x = -2:0.1:7;
y = x.^3 -7*x.*x + 8*x +1;
plot(x,y)

k = 1;
tau2 = 2;
tau1 = 0.5;
f0 = 1;
fp0 = 8;

beta = 0.5;




ftau1 = tau1.^3 - 7.*tau1^2 + 8 *tau1 +1;
ftau2 = tau2.^3 - 7*tau2.^2 + 8*tau2 +1;


while(ftau1 > f0 + (1/2)*fp0*tau1) && (ftau2 < f0 + (1/2)*fp0*tau2)
    disp("jestem w while1")
  if(ftau1 < f0 + (1/2)*fp0*tau1)
      disp("jestem w if1")
tau1=tau1*(1/k);
  end
   if  (ftau2 < f0 + (1/2)*fp0*tau2)
       disp("jestem w if2")
    tau2=tau2*k
  end

    k = k+1;
    tau1 = k*tau2;
    ftau1 = tau1.^3 - 7.*tau1^2 + 8 *tau1 +1;
    ftau2 = tau2.^3 - 7*tau2.^2 + 8*tau2 +1;
end


tau1 = tau1;
tau2 = tau2;
alfa = ( sqrt( 5 ) - 1 ) / 2;
xl = tau2 - alfa.* ( tau2 - tau1 );
xr = tau1 + alfa.* ( tau2 - tau1 );







alfa = ( sqrt( 5 ) - 1 ) / 2;
%punkty próbek
x1 = tau2 - alfa.* ( tau2 - tau1 );
x2 = tau1 + alfa.* ( tau2 - tau1 );

%współczynnik próbkowania
epsilon = 0.001;

%for i = 1:5 <---test

%pierwsze wyznaczenie wartosci probek
fx1 =  x1.^3 -7*x1.*x1 + 8*x1 +1;
fx2 =  x2.^3 -7*x2.*x2 + 8*x2 +1;
%petla zmniejszajaca zakres sprawdzania do epsilona
while ((tau1-tau2)>epsilon)
    disp("jestem w while2")
    %jezeli wartosc 1<wartosci 2 - zmienia sie zakres
    if fx1 < fx2
        disp("jestem w if3")
%duzy zakres zmienia sie z prawej z x2 tau1 x2 przesowa sie w lewo na x1 
        tau2 = x2;
        x2 = x1;
        %przez przesuniecie tau2 x1 z rownania rowniez sie przesunie w lewo
        % (tau1 zostaje bez zmian)
        x1 = tau2 - alfa.*(tau2-tau1);
        fx1 =  x1.^3 -7*x1.*x1 + 8*x1 +1;
        fx2 =  x2.^3 -7*x2.*x2 + 8*x2 +1;
        %^^trzeba ponownie wyznaczyc wartosci probek 
    else 
        disp("jestem w else")
        %duzy zakres przesuwa sie w prawo (tau1 na x1)
        tau1 = x1;
        x1 = x2;
        %maly zakres w prawo (x1 na miejsce x2, gdzie x2 nowo wyznaczone z
        %przesunietego tau1. Tu tau2 nie zmienia miejsca
        x2 = tau1 + alfa.*(tau2-tau1);
        fx1 =  x1.^3 -7*x1.*x1 + 8*x1 +1;
        fx2 =  x2.^3 -7*x2.*x2 + 8*x2 +1;
        %^^trzeba ponownie wyznaczyc wartosci probek 
    end
end
%wyswietlenie srodka nowego przedzialu w ktorym jest min
 disp((tau2+tau1)/2);


%Algorytm obliczający minimum lokalne funkcji jednej zmiennej: 
x = -2:0.01:7;
y = x.^3 -7*x.*x + 8*x +1;
plot(x,y)

a = 2;
b = 8;
alfa = ( sqrt( 5 ) - 1 ) / 2;
%punkty próbek
x1 = b - alfa.* ( b - a );
x2 = a + alfa.* ( b - a );

%współczynnik próbkowania
epsilon = 0.001;

%for i = 1:5 <---test

%pierwsze wyznaczenie wartosci probek
fx1 =  x1.^3 -7*x1.*x1 + 8*x1 +1;
fx2 =  x2.^3 -7*x2.*x2 + 8*x2 +1;
%petla zmniejszajaca zakres sprawdzania do epsilona
while ((b-a)>epsilon)
    %jezeli wartosc 1<wartosci 2 - zmienia sie zakres
    if fx1 < fx2
%duzy zakres zmienia sie z prawej z x2 a x2 przesowa sie w lewo na x1 
        b = x2;
        x2 = x1;
        %przez przesuniecie b x1 z rownania rowniez sie przesunie w lewo
        % (a zostaje bez zmian)
        x1 = b - alfa.*(b-a);
        fx1 =  x1.^3 -7*x1.*x1 + 8*x1 +1;
        fx2 =  x2.^3 -7*x2.*x2 + 8*x2 +1;
        %^^trzeba ponownie wyznaczyc wartosci probek 
    else 
        %duzy zakres przesuwa sie w prawo (a na x1)
        a = x1;
        x1 = x2;
        %maly zakres w prawo (x1 na miejsce x2, gdzie x2 nowo wyznaczone z
        %przesunietego a. Tu b nie zmienia miejsca
        x2 = a + alfa.*(b-a);
        fx1 =  x1.^3 -7*x1.*x1 + 8*x1 +1;
        fx2 =  x2.^3 -7*x2.*x2 + 8*x2 +1;
        %^^trzeba ponownie wyznaczyc wartosci probek 
    end
end
%wyswietlenie srodka nowego przedzialu w ktorym jest min
 disp((b+a)/2);

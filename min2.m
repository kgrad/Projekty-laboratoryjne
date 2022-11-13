clc
clear all
close all
format short

f=@(x)1280*x(1)*x(2) - 10240*x(2) - 327718*x(1) - 40*x(1)^2*x(2) + 30721*x(1)^2 - 1280*x(1)^3 + 20*x(2)^2 + 20*x(1)^4 + 1311090;
X = [ 1;...
      1];
F = f(X);
disp(['k = 0 | x'' = [',num2str(X'),'] | f(x) = ',num2str(F)]);
eps=0.0001;
Xopt = zeros(2,2);  
Xopt=[1,0];
k=1;

while  abs( sqrt( (Xopt(k,1))^2 + (Xopt(k,2))^2 )-sqrt( (X(1,1))^2+(X(2,1))^2 ))>= eps   
    if(mod(k,2)==0)
        D=[0,;...
            1];
    else
        D=[1,;...
            0];
    end


    fa = @(a)f( D*a +X ); 

    [a,y] = fminsearch(fa,0);

        
    Xopt(k+1,1) = X(1,1);
    Xopt(k+1,2) = X(2,1);
    X = D*a +X;

    disp(['k = ',num2str(k),' | x'' = [',num2str(X'),'] | f(x) = ',num2str(y)]);
 
k=k+1;
end
plotMOO_2D(f,Xopt)

%-------------------------------------------------------------------------%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%-------------------------------------------------------------------------%



function plotMOO_2D(F,X)
    n = size(X,1);
    X1 = X(1:n,1);
    X2 = X(1:n,2);

    x1p = min(X1) -(max(X1)-min(X1))/10; x1k = max(X1) +(max(X1)-min(X1))/10; x1 = linspace(x1p,x1k);
    x2p = min(X2) -(max(X2)-min(X2))/10; x2k = max(X2) +(max(X2)-min(X2))/10; x2 = linspace(x2p,x2k);
    [XX1,XX2] = meshgrid(x1,x2);

    [nx1,nx2] = size(XX1);  Y = zeros(nx1,nx2);

    for i = 1:nx1
        for j = 1:nx2
            x = [XX1(i,j) XX2(i,j)];    Y(i,j) = F(x);
        end
    end
%%%---------------------------------------------------------------------%%%
    figure(100)
    contour(XX1,XX2,Y,30); hold on;
    plot(X1,X2,'*-k');
    plot(X1(1),X2(1),'ok',X1(end),X2(end),'sk','MarkerFaceColor','w','Markersize',8);
    xlabel('x_1');ylabel('x_2'); grid on;
    title('funkcja nieliniowa');
    legend('f(x)','x^i','x^0','x^{opt}');
%%%---------------------------------------------------------------------%%%
end

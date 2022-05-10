function [xvect,xdif,fx,it_cnt]=sieczne(a,b,eps,fun)

    xvect = [];
    xdif = [];
    fx = [];
    
    for i=1:1000
        ya = feval(fun, a);
        yb = feval(fun, b);
        newx = b - (yb * (b - a)) / (yb - ya);
        ynew = feval(fun, newx);
       
        xvect(i) = newx;
        fx(i) = ynew;
        xdif(i) = abs(b - newx);
        
        if abs(ynew) < eps
            it_cnt = i;
            break    
        end
        a = b;
        b = newx;
    
    end
end
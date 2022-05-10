function [xvect,xdif,fx,it_cnt]=bisect(a,b,eps,fun)

    lastx = 0;
    xvect = [];
    xdif = [];
    fx = [];
    
    for i = 1:1000
        x = (a + b)/2;
        y = feval(fun, x);
    
        xvect(i) = x;
        xdif(i) = abs(lastx - x);
        fx(i) = y;
        lastx = x;
    
        if abs(y) < eps
            it_cnt = i;
            return;
        elseif feval(fun, a) * y < 0
            b = x;
        else
            a = x;
        end
    end
end


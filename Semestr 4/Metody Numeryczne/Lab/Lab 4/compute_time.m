function [value] = compute_time( N )
    t = 5000;
    
    value = (N ^ 1.43 + N ^1.14) / 1000 - t;

end


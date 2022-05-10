function [value] = compute_velocity( t )

    v = 750;

    g = 9.81;
    m0 = 150000;
    q = 2700;
    u = 2000;

    value = u * log(m0 / (m0 - q*t)) - g*t - v;
end


function [value] = compute_impedance( omega )
    Z = 75;

    R = 725;
    C = 8e-5;
    L = 2;
    value = 1 / sqrt(1 / (R^2) + (omega*C - (1 / (omega*L)))^2) - Z;
end


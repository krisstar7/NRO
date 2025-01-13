clc;
clear all;

strong_scaling_time = [
1, 677.013204;
2, 401.265077;
3, 328.981320;
4, 259.952736;
5, 227.214689;
6, 204.000442;
7, 203.314041]

strong_scaling_ideal = strong_scaling_time;

strong_scaling_ideal(2, 2) = strong_scaling_ideal(1, 2)/2;
strong_scaling_ideal(3, 2) = strong_scaling_ideal(1, 2)/3;
strong_scaling_ideal(4, 2) = strong_scaling_ideal(1, 2)/4;
strong_scaling_ideal(5, 2) = strong_scaling_ideal(1, 2)/5;
strong_scaling_ideal(6, 2) = strong_scaling_ideal(1, 2)/6;
strong_scaling_ideal(7, 2) = strong_scaling_ideal(1, 2)/7;

N_threads = strong_scaling_time(:, 1);
time = strong_scaling_time(:, 2);
ideal_time = strong_scaling_ideal(:, 2);

plot(N_threads, time)
hold on;
plot(N_threads, ideal_time)
xlabel("N (stevilo niti)")
ylabel("t[s]")
title("Graf 'strong scaling'")
grid on;
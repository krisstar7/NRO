clc;
clear all;

tic;
n = 10000000;
[x1_notri, y1_notri, x1_zunaj, y1_zunaj, notri] = mcc_pi(n);

[pi_izrac, napaka]=area_pi(notri, n);

figure();
hold on;
plot(x1_notri, y1_notri, 'r.')
plot(x1_zunaj, y1_zunaj, 'b+')
axis square;
xlabel('x os');
ylabel('y os');
hold off;

toc


function[pi_izrac, napaka]=area_pi(notri, n)
    pi_izrac = (4*sum(notri))/n;
    napaka = abs(pi - pi_izrac);
end


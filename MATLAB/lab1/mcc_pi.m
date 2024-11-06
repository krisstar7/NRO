function[x1_notri, y1_notri, x1_zunaj, y1_zunaj, notri]=mcc_pi(n)

% n=1000;
xn=rand(n, 1);
yn=rand(n, 1);

x1=xn*2-1;
y1=yn*2-1;

r=sqrt(x1.^2+y1.^2);

notri=r<=1;
zunaj=r>1;

x1_notri=x1(notri);
y1_notri=y1(notri);

x1_zunaj=x1(zunaj);
y1_zunaj=y1(zunaj);

% figure();
% hold on;
% plot(x1_notri, y1_notri, 'r.')
% plot(x1_zunaj, y1_zunaj, 'b+')

end
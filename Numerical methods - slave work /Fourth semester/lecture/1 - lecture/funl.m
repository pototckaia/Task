r1 = [1; 2.0; 3.0; 4.0; 5.0; 6.0; 7.0; 8.0; 9.0; 10.0; 11.0; 12.0; 13.0; 14.0; 15.0; 16.0; 17.0; 18.0; 19.0; 20.0];
d = poly(r1);
d(0) = d(0) - 0.0000001;
r = roots(d);
for i=1:length(r)
    plot(real(r(i)), imag(r(i)), 'or', 'linewidth', 2); hold on;
end
title('Комплексная плоскость'); xlabel('Re(z)'); ylabel('Im(z)');
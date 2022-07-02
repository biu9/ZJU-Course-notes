%画出x[n] = 1 (-N=<n<=N)的离散傅里叶变换在一个周期内的图像。
%第一种画法，直接做图。
N = 50;
w = [-pi:0.001:pi];
y = zeros(1,length(w));
for i = 1:length(w)
    if abs(w(i))==0
        y(i) = 2*N+1;
    else
        y(i) = sin((N+0.5)*w(i))/sin(0.5*w(i));
    end;
end;
subplot(2,1,1);
plot(w,y);

%第二种画法，利用离散傅里叶级数FFT
N = 50;
x  = [ones(1,2*N+1),zeros(1,length(w)-2*N-1)];
y = fft(x);
for i = 1:length(y)
    y(i) = y(i)*exp(j*2*pi*(i-1)*N/length(y));
end;
y =fftshift(y);
y = real(y);
subplot(2,1,2);
plot(w,y);
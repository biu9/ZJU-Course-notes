[x1,fs] = audioread('voice3.mp3');
x1 = x1(:,1);
figure(1);
y1 = fft(x1);
y1 = fftshift(y1);
N = length(x1);
derta_fs = fs/N;

N1 = floor(fs/(2*derta_fs));
w = [-N1*derta_fs:derta_fs:(N-N1-1)*derta_fs];
plot(w,abs(y1)/fs);
title('原始语音信号的频谱');
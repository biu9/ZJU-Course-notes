function result = convNew2(X,Y)
%��FFT��IFFTʵ��������һά�źŵľ��
len = length(X)+length(Y) - 1;
result  = zeros(1, len);

N = 2^(1+floor(log2(len)));
X = [X,zeros(1, N-length(X))];
Y = [Y,zeros(1, N-length(Y))];
result = ifftNew(fftNew(X).*fftNew(Y));
result = real(result(1:len));
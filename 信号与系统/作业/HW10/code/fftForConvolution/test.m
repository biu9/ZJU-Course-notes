clear all;
N = 2^16;
X = randn(1,N);
Y = randn(1,N);
N
tic
%�þ���Ķ���ʵ�ֵ������źŵľ�����������������ġ�
Z1 = convNew(X,Y);
toc

tic
%�������Լ���FFTNEW��IFFTNEW��������ʵ�ֵľ�����������һ�㣬���䵱���г��Ⱥܳ���ʱ��
Z2 = convNew2(X,Y);
toc

tic
%�������ģ���Ϊ�õ���MATLAB�Դ��ľ�����������FFT, IFFTģ�龭���Ż�
Z3 = conv(X,Y);
toc



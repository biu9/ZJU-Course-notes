function C = convNew(A,B)
% �þ���Ķ���ʵ��������һά�źŵľ����
C = zeros(1,length(A) + length(B)-1);
for i = 1:length(A) 
    C = C + [zeros(1,i-1),A(i)*B, zeros(1,length(A)-i)];%�б�
end;
    
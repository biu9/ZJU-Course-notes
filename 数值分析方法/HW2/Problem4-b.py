import math
a=0.3955950485
x1=0.9722034681*a
x2=0.1749966243*a
x3=0.1555525549*a
f1=10*x1-2*pow(x2,2)+x2-2*x3-5
f2=8*pow(x2,2)+pow(x3,2)-9
f3=8*x2*x3+4
res=pow(f1,2)+pow(f2,2)+pow(f3,2)
print(res)
print(x1)
print(x2)
print(x3)
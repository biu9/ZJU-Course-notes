# HW 7

### Problem 1

> 自由空间中的平面波以波导半空间$\theta$角入射；对于足够大的$\sigma / w\epsilon_0$，通过证明$\theta_t = tan^{-1}k_x/k_{zR}$来证明透射波垂直于边界

$$
\frac{sin\theta_i}{sin\theta_t} = \frac{k_t}{k_0}\\
tan\theta_t = \frac{k_0sin\theta_0}{\sqrt{k_t^2-k_0^2sin^2\theta_0}} = \frac{k_x}{k_z} = \frac{k_x}{k_{zr}}\\
由于\frac{\sigma}{w\epsilon_0}>>1\\
k_x = \sqrt{\frac{w\epsilon}{2\sigma}}k(i-1)\\
k_x^2+k_z^2 = k^2\\
tan\theta_t = \frac{k_x}{\sqrt{k^2-k_x^2}} = \frac{i-1}{\sqrt2 \sqrt{\frac{\sigma}{w\epsilon}+i}} = 0\\
$$

 

### Problem 2

$$
对于TE波，R_{TE} = \frac{1-p_{0t}}{1+p_{0t}}\\
T_{TE} = \frac{2}{1+p_{0t}}\\
p_0t = \frac{u_0k_{tz}}{u_tk_z}\\
对于TM波，R_{TM} = \frac{1-p_{0t}}{1+p_{0t}}\\
T_{TM} = \frac{2}{1+p_{0t}}\\
p_{0t} = \frac{\epsilon k_{tz}}{\epsilon_t k_x}\\
由于TE、TM波入射的是相同介质，得到的TEM波反射率、透射率相同
$$

### Problem 3

$$
E_i = (\frac{1}{\sqrt2}x+\frac{1}{\sqrt2}z+iy)e^{i\frac{1}{\sqrt2}k_0x-i\frac{1}{\sqrt2}k_0z}\\
 = (\frac{1}{\sqrt2}x+\frac{1}{\sqrt2}z+iy)[cos(\frac{1}{\sqrt2}k_0(x-z))+isin(\frac{1}{\sqrt2}k_0(x-z))]\\
 E_x = \frac{1}{\sqrt2}[cos(\frac{1}{\sqrt2}k_0(x-z))+isin(\frac{1}{\sqrt2}k_0(x-z))]x\\
 E_y = \frac{1}{\sqrt2}[cos(\frac{1}{\sqrt2}k_0(x-z))+isin(\frac{1}{\sqrt2}k_0(x-z))]iy\\
 由于入射方向是z方向，电场方向在x，z平面内，入射波是TM波，\\对于TM波，E_r = R^{TM}E_i\\
R_{TM} = \frac{1-p_{0t}}{1+p_{0t}},T_{TM} = \frac{2}{1+p_{0t}},p_{0t} = \frac{\epsilon k_{tz}}{\epsilon_t k_x}\\
 由于是从+z入射到-z方向，入射波是左旋的\\又由于(\frac{1}{\sqrt 2})^2+(\frac{1}{\sqrt 2})^2 = 1.入射波是圆极化波\\
=>反射波是右旋圆极化波
$$


# HW 4

### Problem 1

(a)

$$
f = 2.5G,\epsilon=40\epsilon_0,\sigma=2\\
K_I = w\sqrt{u\epsilon}[\frac{1}{2}\sqrt{1+\frac{\sigma^2}{\epsilon^2w^2}}-1]^{0.5}\\
d_p = \frac{1}{K_I} ≈\frac{2}{\sigma}(\frac{\epsilon}{u})^{0.5} = 0.167m\\
当\sigma=4\times10^{-6},\epsilon=1.03\epsilon_0时\\
d_p = \frac{1}{K_I} = 1346.97m
$$
(b)
$$
\frac{w\epsilon}{\sigma}<<1\\
由于\frac{w\epsilon}{\sigma}<0.1\\
w<0.1\frac{\sigma}{\epsilon}\\
f = \frac{w}{2\pi} = 898755hz
$$
(c)
$$
\epsilon=\epsilon_0,u=u_0,\sigma=3.54\times10^{7}\\
d_p=\sqrt{\frac{2}{wu\sigma}} = 8.45\times10^{-6}\\
5d_p=4.23\times10^{-5}>10^{-3}(inch)\\
不够厚
$$
(d)
$$
由于\frac{\sigma}{w\epsilon}>>1\\
f=100Hz时
\\
d_p=\sqrt{\frac{2}{wu\sigma}}=25.16m\\
f=5MHz时\\
d_p=\sqrt{\frac{2}{wu\sigma}}=0.1125m
$$
(e)
$$
d_p=\sqrt{\frac{2}{wu\sigma}} = \frac{1}{K_I}\\
e^{-2K_Iz} = -109.1dB
$$

### Problem 2

(a)
$$
\epsilon=40(1+i0.3)\epsilon_0,f=2.5GHz\\
K_I = w\sqrt{u\epsilon}[\frac{1}{2}\sqrt{1+\frac{\sigma^2}{\epsilon^2w^2}}-1]^{0.5}\\
d_p = \frac{1}{K_I} ≈\frac{2}{\sigma}(\frac{\epsilon}{u})^{0.5} = 0.167m\\
$$
(b)
$$
f=60Hz,\sigma=4,\epsilon=80\epsilon_0,u=u_0\\
K_I = w\sqrt{u\epsilon}[\frac{1}{2}\sqrt{1+\frac{\sigma^2}{\epsilon^2w^2}}-1]^{0.5}\\
由于\frac{\sigma}{w\epsilon}>>1\\
d_p=\frac{1}{K_I}≈\sqrt{\frac{2}{wu\sigma}} = 32.487m\\loss~~tangent=\frac{\sigma}{wRe(\epsilon)-Im(\epsilon)}=1.5\times10^7\\
f=10MHz时，d_p=0.079577m\\
loss~~tangent=\frac{\sigma}{wRe(\epsilon)-Im(\epsilon)}=90
$$
(c)
$$
E_0=1V/m\\
k=\frac{w}{c}\sqrt{1-\frac{w_p^2}{w^2}}\\
E = E_0e^{ikz}\\
z=100时，E=0.019V/m\\
<S>=\frac{k}{wu}|E|^2\\
z=0时，E=1V/m,<S>=25W/m^2\\
z=100时，E=0.019V/m，<S>=8.39\times10^{-3}W/m^2
$$

### Problem 3

(a)
$$
d_p=\sqrt{\frac{m}{Ne^2u_0}}\\
proof:d_p=\frac{1}{K_I}\\
K_I=\frac{w}{c}\sqrt{\frac{w_p^2}{w^2}-1}\\
w_p=\sqrt{\frac{Nq^2}{m\epsilon_0}}\\
=>d_p=\frac{1}{K_I} = \frac{c}{w\sqrt{\frac{Nq^2}{m\epsilon_0w^2}-1}}\\
d_p=\sqrt{\frac{mc^2\epsilon w^2}{w^2Nq^2-m\epsilon w^2}} = \sqrt{\frac{m}{\frac{Nq^2}{c^2\epsilon}-\frac{m}{c^2}}} = \sqrt{\frac{m}{Ne^2u_0}}
$$
(b)
$$
N=7\times10^{28}m^{-3}\\
d_p=\sqrt{\frac{m_e}{Ne^2u_0}} = 2.008\times10^{-8}
$$
(c)
$$
对于good ~conductor，d_p=\delta=\sqrt{\frac{2}{wu\sigma}}\\
对于superconductor，d_p=\delta=\sqrt{\frac{m}{Ne^2u_0}}\\
当磁场强度变化慢时，\sqrt{\frac{2}{wu\sigma}}增大；d_p增加\\
但\sqrt{\frac{m}{Ne^2u_0}}与频率无关，因此不能穿透
$$

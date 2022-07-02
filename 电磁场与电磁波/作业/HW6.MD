# HW 6

### Probelm 1

$$
对于ordinary~ wave,\theta_1 = \theta_2\\
对于extraordinary~ wave,\theta_2>\theta_1
$$

### Problem 2

(a)

$$
由于\sigma_z = 0.2\epsilon_0 >0且足够厚\\
把z变换到u或v都能满足条件
$$
(b)
$$
等价于求d_p\\
K_I=w\sqrt{u\epsilon}[\frac{1}{2}(\sqrt{1+\frac{\sigma^2}{\epsilon^2w^2}}-1)]^{0.5}\\
d_p = \frac{1}{K_I} = 3.18\lambda
$$
(c)
$$
z->w,x->u,y->v\\
E_{inc} = \frac{E_o}{\sqrt2}(x-y)cos(k_0z-wt)\\
z = d时，由于是circularly~polarized\\
(2\sqrt3-1)k_0d = \frac{\pi}{2}\\
d = \frac{\lambda}{4(2\sqrt3-1)};此时是右旋的
$$

### Problem 3

(a)
$$
\overline {\overline z} = [\begin{matrix}
0&-1&0\\
1&0&0\\
0&0&0\\
\end{matrix}]
$$
(b)
$$
\frac{dM}{dt} = gu_0M\times H = gu_0[(\vec zM_0+M_1)\times (\vec zH_0+H_1)]\\
由于M_1\times H_1可忽略\\
上式等于gu_0(M_0\vec z\times H_1-H_0\vec z\times M_1) \\
 = gu_0(M_0\overline {\overline z}·H_1-H_0\overline {\overline z}·M_1)\\
 B = u_0(H+M)\\
 B_1 = u_0(H_1+M_1) =\overline {\overline u}·H_1\\
 可以得到\overline {\overline u} = [\begin{matrix}
u&iu_g&0\\
-iu_g&u&0\\
0&0&u_z\\
\end{matrix}]
$$
(c)

$$
\overline {\overline v} = [\begin{matrix}
v&iv_g&0\\
-iv_g&u&0\\
0&0&v_z\\
\end{matrix}]\\
=>[\begin{matrix}
u^2-kv&-ikv_gcos\theta\\
ikv_gcos\theta&u^2-k(vcos^2\theta+v_zsin^2\theta)
\end{matrix}]·[\begin{matrix}
B_1\\
B_2
\end{matrix}] = 0\\
\frac{D_2}{D_1} = -\frac{B_1}{B_2} = \frac{(v-nu_0)sin^2\theta_0±\sqrt{(v-v_0)^2sin^4\theta+4v_g^2cos^2\theta^2}}{2iv_gcos\theta}
$$
(d)
$$
定义cos2\phi = \frac{2v_gcos\theta}{(v-v_z)sin^2\theta}\\
\frac{D_2}{D_1} = itan\phi 或icot\phi,是椭圆极化波\\
 =>Faraday~~ rotation~~ exists
$$

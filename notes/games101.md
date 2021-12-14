### Shear Matrix

![image-20210819122935150](hw1.assets/image-20210819122935150.png)

### Rotation Matrix

![image-20210819123116311](hw1.assets/image-20210819123116311.png)

### Panning Matrix(vector)

![image-20210819172309495](hw1.assets/image-20210819172309495.png)

Remembre there is a `T`, so it is a vertical vector.

Notice, 2d vector has `translation invariance`, so the last number is `0`

![image-20210819172830731](hw1.assets/image-20210819172830731.png)

point + point = the mid point of these two point

![image-20210819173729756](hw1.assets/image-20210819173729756.png)

![image-20210819174256654](hw1.assets/image-20210819174256654.png)

### Viewing transformation

#### 3D rotation

![image-20210819203724149](hw1.assets/image-20210819203724149.png)

rotation formula

![image-20210819213820228](hw1.assets/image-20210819213820228.png)

camera

![image-20210819232700298](hw1.assets/image-20210819232700298.png)

![image-20210820192855462](hw1.assets/image-20210820192855462.png)

正交投影：符合事实但是不符合现实

透视投影：符合人眼

正交投影

![image-20210821100425728](hw1.assets/image-20210821100425728.png)
$$
M_{ortho}
=
\begin{bmatrix}
    \frac{2}{r-l} & 0 & 0 & -\frac{r+l}{r-l} \\
    0 & \frac{2}{t-b}& 0 & -\frac{t+b}{t-b} \\
    0 & 0 & \frac{2}{n-f} & -\frac{n+f}{n-f} \\
    0 & 0 & 0 & 1 \\
\end{bmatrix}
$$
透视投影

![image-20210821163945373](hw1.assets/image-20210821163945373.png)
$$
M_{persp\to ortho}
=
\begin{bmatrix}
    n & 0 & 0 & 0 \\
    0 & n & 0 & 0 \\
    0 & 0 & n+f & -nf \\
    0 & 0 & 1 & 0 \\
\end{bmatrix}
$$
![image-20210821233601100](hw1.assets/image-20210821233601100.png)

标准化

![image-20210821181729053](hw1.assets/image-20210821181729053.png)

视距推导边界

![image-20210821204310983](hw1.assets/image-20210821204310983.png)

### 离散化和采样

![image-20210827114751725](games101.assets/image-20210827114751725.png)

首先判断是否在三角形内部
$$
P0P1 \cross P0Q\\
P1P2 \cross P1Q\\
P2P0 \cross P2Q
$$
三者同号说明在内部

![image-20210827115107120](games101.assets/image-20210827115107120.png)

寻找上下界划分`Bounding Box`

### 抗锯齿

傅立叶变换

![image-20210827224419478](games101.assets/image-20210827224419478.png)

滤波后采样 不能采样后滤波

![image-20210828181746815](games101.assets/image-20210828181746815.png)

注意前面是**WRONG！**

### MSAA

时域上进行卷积

![image-20210828224930366](games101.assets/image-20210828224930366.png)

现代抗锯齿

![image-20210828224940248](games101.assets/image-20210828224940248.png)

### Z-buffer

用于判断前后着色器的

### 着色(Shading)

![image-20210829205858651](games101.assets/image-20210829205858651.png)

入射光 法线 反射光 -> viewpoint

着色有局部性，only focus on shading instead of shadowing

### 漫反射(Diffuse Reflection)

会反射到各个地方去

![image-20210829210425131](games101.assets/image-20210829210425131.png)

#### 能量衰减

![image-20211102224943167](games101.assets/image-20211102224943167.png)

![image-20211102224927331](games101.assets/image-20211102224927331.png)

漫反射系数决定了颜色/亮度

### 高光

![image-20211102234354178](games101.assets/image-20211102234354178.png)

判断半程向量是否接近，就是$n$和$h$是否接近，经验模型，判断是否能看到高光，主要是半程向量好算。指数$p$代表reflection lobe，用于快速下降高光值。

![image-20211102235724402](games101.assets/image-20211102235724402.png)

#### 环境光照

![image-20211103000556564](games101.assets/image-20211103000556564.png)

环境光其实是一个常数，是一个大概，为了保证没有一个地方是完全黑的，真正计算需要全局光照的知识。

![image-20211103002723451](games101.assets/image-20211103002723451.png)

合并光简化模型。

![image-20211103010651292](games101.assets/image-20211103010651292.png)

求每个三角形法线的情况

![image-20211103010742726](games101.assets/image-20211103010742726.png)

定点+插值判断每个三角形

![image-20211103010807569](games101.assets/image-20211103010807569.png)

Phong是着色频率

![image-20211103031706816](games101.assets/image-20211103031706816.png)

法线平均->点的法线

![image-20211103044129429](games101.assets/image-20211103044129429.png)

定义UV坐标系

### 图形渲染管线(pipeline)

个人认为这是一个很重要的概念，便于理解渲染的整个流程

![image-20211107161911696](games101.assets/image-20211107161911696.png)

#### 双线性插值

![image-20211109195952063](games101.assets/image-20211109195952063.png)

#### Mipmap

没懂 需要过后面再看





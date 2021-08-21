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












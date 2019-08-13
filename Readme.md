CirclesDectect

OpenCV霍夫变换 霍夫圆变换识别图像中圆

霍夫变换的相关内容
https://blog.csdn.net/poem_qianmo/article/details/26977557

霍夫变换一般步骤：
1、读入图像
2、平滑滤波
3、转成灰度图
4、边缘检测
5、Hough圆检测
6、在原图中绘圆并显示

核心函数：
void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1=100, double param2=100, int minRadius=0, int maxRadius=0 )

HoughCircles函数可以利用霍夫变换算法检测出灰度图中的圆。它和之前的HoughLines和HoughLinesP比较明显的一个区别是它不需要源图是二值的，而HoughLines和HoughLinesP都需要源图为二值图像。

第一个参数，InputArray类型的image，输入图像，即源图像，需为8位的灰度单通道图像。
第二个参数，InputArray类型的circles，经过调用HoughCircles函数后此参数存储了检测到的圆的输出矢量，每个矢量由包含了3个元素的浮点矢量(x, y, radius)表示。
第三个参数，int类型的method，即使用的检测方法，目前OpenCV中就霍夫梯度法一种可以使用，它的标识符为CV_HOUGH_GRADIENT，在此参数处填这个标识符即可。
第四个参数，double类型的dp，用来检测圆心的累加器图像的分辨率于输入图像之比的倒数，且此参数允许创建一个比输入图像分辨率低的累加器。上述文字不好理解的话，来看例子吧。例如，如果dp= 1时，累加器和输入图像具有相同的分辨率。如果dp=2，累加器便有输入图像一半那么大的宽度和高度。
第五个参数，double类型的minDist，为霍夫变换检测到的圆的圆心之间的最小距离，即让我们的算法能明显区分的两个不同圆之间的最小距离。这个参数如果太小的话，多个相邻的圆可能被错误地检测成了一个重合的圆。反之，这个参数设置太大的话，某些圆就不能被检测出来了。
第六个参数，double类型的param1，有默认值100。它是第三个参数method设置的检测方法的对应的参数。对当前唯一的方法霍夫梯度法CV_HOUGH_GRADIENT，它表示传递给canny边缘检测算子的高阈值，而低阈值为高阈值的一半。
第七个参数，double类型的param2，也有默认值100。它是第三个参数method设置的检测方法的对应的参数。对当前唯一的方法霍夫梯度法CV_HOUGH_GRADIENT，它表示在检测阶段圆心的累加器阈值。它越小的话，就可以检测到更多根本不存在的圆，而它越大的话，能通过检测的圆就更加接近完美的圆形了。
第八个参数，int类型的minRadius,有默认值0，表示圆半径的最小值。
第九个参数，int类型的maxRadius,也有默认值0，表示圆半径的最大值。
 

需要注意的是，使用此函数可以很容易地检测出圆的圆心，但是它可能找不到合适的圆半径。我们可以通过第八个参数minRadius和第九个参数maxRadius指定最小和最大的圆半径，来辅助圆检测的效果。或者，我们可以直接忽略返回半径，因为它们都有着默认值0，单单用HoughCircles函数检测出来的圆心，然后用额外的一些步骤来进一步确定半径。


不同的opencv版本，标识符略有不同。
OPENCV3 命名空间等变化
http://blog.leanote.com/post/zhaoxingniu/OPENCV3-%E5%91%BD%E5%90%8D%E7%A9%BA%E9%97%B4%E7%AD%89%E5%8F%98%E5%8C%96

具体信息可以查看opencv文档

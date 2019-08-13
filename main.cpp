#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
//#include <boost/concept_check.hpp>

using namespace std;
using namespace cv;

#define g_nGaussianBlurValue  15 //高斯滤波参数
#define miniDist 400 //圆心之间的最小距离
#define param1 100  //传递给canny边缘检测算子的高阈值
#define param2 35  //检测阶段圆心的累加器阈值。它越小的话，就可以检测到更多根本不存在的圆
#define miniRadius 60 //圆半径的最小值。
#define maxRadius  150  //圆半径的最大值。

int main(int argc, char** argv) {

	Mat src = imread("source\\014.jpg");
	
	if (src.empty())
	{
		cout << "can not open " << endl;
		return -1;
	}

	Mat cimg;

	//中值滤波
	medianBlur(src, src, 5);

	//转成灰度图并存在cimg
	cvtColor(src, cimg, COLOR_BGR2GRAY);
	cout <<"原图的大小："<< cimg.size() << endl;
	imshow("原图", cimg);
	//高斯滤波
	GaussianBlur(cimg, cimg, Size(g_nGaussianBlurValue, g_nGaussianBlurValue),2,2);
	imshow("高斯滤波", cimg);
    //边缘检测
	Canny(cimg, cimg, 10, 250, 5);
	imshow("canny", cimg);

	//Hough圆检测
	vector<Vec3f> circles;
	HoughCircles(cimg, circles, HOUGH_GRADIENT , 1,miniDist,param1,param2,miniRadius,maxRadius);
	cout << "检测出圆形的数量："<<circles.size() << endl;

	//绘图
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		cout <<"圆心："<< center << endl;
		cout << "半径："<<radius << endl;
		//绘制圆心  
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓  
		circle(src, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}
	imshow("图片", src);
	cv::waitKey(0);
	return 0;
}

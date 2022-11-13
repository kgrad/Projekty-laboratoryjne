#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


using namespace cv;


int main() {

	Mat img = cv::imread("F:/Projekty/Grafika/Grafika/original.jpg");

	Mat reverse;
	bitwise_not(img, reverse);
	imshow("reverse", reverse);
	
	imwrite("F:/Projekty/Grafika/Grafika/netagive.jpg", reverse);

	Mat smooth_img;
	blur(img, smooth_img, Size(10, 10));
	imshow("blur", smooth_img);
	imwrite("F:/Projekty/Grafika/Grafika/blur.jpg", smooth_img);



Mat edge;
Mat img_gray;
cvtColor(img, img_gray, COLOR_BGR2GRAY);
Mat img_blur;
GaussianBlur(img_gray, img_blur, Size(3, 3), 0);
Sobel(img_blur, edge, CV_64F, 1, 1, 5);
imshow("krawedzie metoda Sobel", edge);
imwrite("F:/Projekty/Grafika/Grafika/edge_det_1.jpg", edge);


Canny(img_blur, edge, 100, 200, 3, false);
imshow("krawedzie metoda Canny (mniej szczegolow)", edge);
imwrite("F:/Projekty/Grafika/Grafika/edge_det_2.jpg", edge);

Mat histo;
equalizeHist(img_gray, histo);
imshow("szary image", img_gray);
imshow("wyrownany image", histo);
imwrite("F:/Projekty/Grafika/Grafika/histogram.jpg", histo);
	cv::waitKey(0);
	cv::destroyAllWindows();
} 
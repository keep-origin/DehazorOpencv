#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "dehazor.h"
#include "LyhDehazor.h"

using namespace cv;

int main()
{
	unsigned char* MatToRGBA(const Mat *mat);
	Mat img = imread("pic2.jpg",1);   

	LyhDehazor *lyhdehazor = new LyhDehazor(img.cols, img.rows, 3);
	lyhdehazor->Dehazor(MatToRGBA(&img), img.cols, img.rows);


	Dehazor *dehazor = new Dehazor();
	dehazor->setEpsilon(0.0001f);
	dehazor->setFog_factor(0.95f);
	dehazor->setWindowsize(7);
	dehazor->setLocalWindowsize(21);
	Mat deh = dehazor->process(img);

	Mat refine = dehazor->getRefinedMap();
	cv::imwrite("refine.jpg", refine);

	namedWindow("lyh", CV_WINDOW_AUTOSIZE);  
	imshow("lyh", img);  
	imshow("dehazor", deh);  
	imshow("refine", refine);
	delete dehazor;
	waitKey();  

}

unsigned char* MatToRGBA(const Mat *mat)
{
	int width = mat->cols * mat->channels();
	int height = mat->rows;
	int len  = width * height;
	unsigned char *rgba = (unsigned char*)malloc(mat->cols * mat->rows * 4);
	unsigned char * p = mat->data;
	for(int i = 0, j = 0; i < len; i +=3, j+=4)
	{
		rgba[j] = p[i];
		rgba[j+1] = p[i+1];
		rgba[j+2] = p[i+2];
		rgba[j+3]=255;
	}

	cv::Mat img(mat->rows, mat->cols, CV_8UC4, rgba);
	cv::imwrite("rgba.jpg",img);
	return rgba;
}
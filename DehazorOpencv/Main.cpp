#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "dehazor.h"
#include "LyhDehazor.h"

using namespace cv;

int main()
{
	cv::Mat boxfilter(cv::Mat &im, int r);
	unsigned char* MatToRGBA(const Mat *mat);
	unsigned char* GetMatChannel(const Mat *mat, const int );
	//unsigned char* GetMatChannel(const Mat *mat, const int chal);
	Mat img = imread("pic2.jpg",1);   


	LyhDehazor *lyhdehazor = new LyhDehazor(img.cols, img.rows, 3);
	Dehazor *dehazor = new Dehazor();
	dehazor->setEpsilon(0.0001f);
	dehazor->setFog_factor(0.95f);
	dehazor->setWindowsize(15);
	dehazor->setLocalWindowsize(21);


	unsigned char * channel = GetMatChannel(&img, 0);
	unsigned char * channel1 = (unsigned char *)malloc(sizeof(char) * img.rows * img.cols);
	lyhdehazor->BoxFilter(channel,channel1, 7,img.cols, img.rows, 1);

	cv::Mat mych(img.rows, img.cols, CV_8UC1, channel1);
	cv::imwrite("myboxfilter.jpg",mych);
	cv::Mat ch(img.rows, img.cols, CV_8UC1, channel);
	cv::Mat ch2 = boxfilter(ch,7);
	cv::imwrite("hisboxfilter.jpg",ch2);

	lyhdehazor->Dehazor(MatToRGBA(&img), img.cols, img.rows);




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

unsigned char* GetMatChannel(const Mat *mat, const int chal)
{
	int width = mat->cols * mat->channels();
	int height = mat->rows;
	int len  = width * height;
	unsigned char *rgba = (unsigned char*)malloc(mat->cols * mat->rows);
	unsigned char * p = mat->data;
	p += chal;
	for(int i = 0, j = 0; i < len; i +=3, ++j)
	{
		rgba[j] = p[i];
	}

	cv::Mat img(mat->rows, mat->cols, CV_8UC1, rgba);
	cv::imwrite("channel.jpg",img);
	return rgba;
}



cv::Mat boxfilter(cv::Mat &im, int r)
{
	//im is a CV_32F type mat [0,1] (normalized)
	//output is the same size to im;

	int hei=im.rows;
	int wid=im.cols;
	cv::Mat imDst;
	cv::Mat imCum;


	imDst=cv::Mat::zeros(hei,wid,CV_8UC1);
	imCum.create(hei,wid,CV_8UC1);

	//cumulative sum over Y axis
	for(int i=0;i<wid;i++){
		for(int j=0;j<hei;j++){
			if(j==0)
				imCum.at<unsigned char>(j,i)=im.at<unsigned char>(j,i);
			else
				imCum.at<unsigned char>(j,i)=im.at<unsigned char>(j,i)+imCum.at<unsigned char>(j-1,i);
		}
	}


	//difference over Y axis
	for(int j=0;j<=r;j++){
		for(int i=0;i<wid;i++){
			imDst.at<unsigned char>(j,i)=imCum.at<unsigned char>(j+r,i);
		}
	}
	for(int j=r+1;j<=hei-r-1;j++){
		for(int i=0;i<wid;i++){
			imDst.at<unsigned char>(j,i)=imCum.at<unsigned char>(j+r,i)-imCum.at<unsigned char>(j-r-1,i);
		}
	}
	for(int j=hei-r;j<hei;j++){
		for(int i=0;i<wid;i++){
			imDst.at<unsigned char>(j,i)=imCum.at<unsigned char>(hei-1,i)-imCum.at<unsigned char>(j-r-1,i);
		}
	}


	//cumulative sum over X axis
	for(int j=0;j<hei;j++){
		for(int i=0;i<wid;i++){
			if(i==0)
				imCum.at<unsigned char>(j,i)=imDst.at<unsigned char>(j,i);
			else
				imCum.at<unsigned char>(j,i)=imDst.at<unsigned char>(j,i)+imCum.at<unsigned char>(j,i-1);
		}
	}
	//difference over X axis
	for(int j=0;j<hei;j++){
		for(int i=0;i<=r;i++){
			imDst.at<unsigned char>(j,i)=imCum.at<unsigned char>(j,i+r);
		}
	}
	for(int j=0;j<hei;j++){
		for(int i=r+1;i<=wid-r-1;i++){
			imDst.at<unsigned char>(j,i)=imCum.at<unsigned char>(j,i+r)-imCum.at<unsigned char>(j,i-r-1);
		}
	}
	for(int j=0;j<hei;j++){
		for(int i=wid-r;i<wid;i++){
			imDst.at<unsigned char>(j,i)=imCum.at<unsigned char>(j,wid-1)-imCum.at<unsigned char>(j,i-r-1);
		}
	}

	return imDst;
}
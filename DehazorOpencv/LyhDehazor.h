#pragma once

//#include <jni.h>
#include <stdio.h>
//#include <string>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv.hpp>
//#include <android/log.h>
#include <time.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types_c.h>
#define MINT(a,b,c) (a<b?(a<c?a:c):(b<c?b:c))
//#define MAX(a,b) (a>b?a:b)
//#define MIN(a,b) (a<b?a:b)
#define MUL(a,b,c) (a[c] * b[c])
#define CLAM(a) ((a) > 255 ? 255 : ((a) < 0 ? 0 : (a)))
//#define unsigned char unsigned char
class LyhDehazor
{

private:
    const static int RADIUS = 7;
    int * mDivN;
    int mRadius;
    void Normalized(unsigned char *data, float *out, int len);
    void AirlightEsimation(unsigned char *oriImage, unsigned char *oriDark, unsigned char *out, int len, int low, int heigh);
    void ImageDivAir(unsigned char *oriImage, int len, float *out, unsigned char *air);
    void MeanFilter(unsigned char *data, unsigned char *outdata, int r, int widht, int height);
    template<class T1, class T2>void BoxFilter(T1 *data, T1 *outdata, int r, int width, int height , T2 cumtype);
    template<class T1, class T2, class T3> void MulMeanFilter(T1 *data1, T2 *data2, T3 *outdata, int r, int width, int height);
    template<class T1, class T2, class T3> void ArrayMul(T1 *input1, T2 *input2, int len, T3 *out);
    template<class T1, class T2, class T3> void Variance(T1 *exy, T2 *ex, T3 ey, int len);
    void GuidedFilter(unsigned char *guidedImage, float *data, int width, int height, int size, int e);
    void GuidedFilter(unsigned char *ori_r, unsigned char *ori_g,unsigned char *ori_b, float *data, int width, int height,int size,float e);
    void BoxDivN(int *out, int width, int height, int r);
    template<class T1, class T2> void MeanFilter(T1 *data, T1 *outdata, int r, int width, int height , T2 cumtype);

    void MinFilter(unsigned char *data, int width, int height, int boxWidth, int boxHeight, unsigned char *out);
    void GetTrans(float *data, int width, int height, int boxsize, float *out, float w);
    unsigned char MinLine(unsigned char *data, int width, int line, int left, int right);
public:
    LyhDehazor(int width, int height, int r);
    ~LyhDehazor(void);    
    float MinLine(float *data, int width, int line, int left, int right);
    void Dehazor(unsigned char *imageDataRGBA, int width, int height);
	static void writeImg(int width, int height, unsigned char *data, std::string name)
	{
		cv::Mat img(height, width, CV_8UC1, data);
		cv::imwrite(name, img);
	}
	static void writeImgF(int width, int height, float *data, std::string name)
	{
		cv::Mat img(height, width, CV_32FC1, data);
		cv::imwrite(name, img);
	}
};


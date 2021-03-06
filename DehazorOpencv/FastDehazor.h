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
#define MINT(a,b,c) ((a)<(b)?((a)<(c)?(a):(c)):((b)<(c)?(b):(c)))
//#define MAX(a,b) (a>b?a:b)
//#define MIN(a,b) (a<b?a:b)
#define MUL(a,b,c) (a[c] * b[c])
#define CLAM(a) ((a) > 255 ? 255 : ((a) < 0 ? 0 : (a)))


#define INPUT_NULL -1

class FastDehazor
{
public:
	FastDehazor(int width, int height);
	~FastDehazor();
	int process(unsigned char * rgba, int width, int height);
protected:
private:
	int * mDivN;
	int mWinSize;
	float mUpper;
	float mP;
	unsigned char * mResultTable;
	void InitResultTable();
	//在算法中，air的三个通道的值都是一样的
	unsigned char mAir;
	void MeanFilter(unsigned char *data, int * outdata, int r, int width, int height);
	void BoxDivN(int *out, int width, int height, int r);
	template<class T1, class T2> void BoxFilter(T1 *data, T2 *outdata, int r, int width, int height, T2 t);
};
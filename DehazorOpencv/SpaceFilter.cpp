#include "SpaceFilter.h"
#include "Utils.h"
using namespace cv;

//直方图均衡化 src为0-255的单通道数的图像
void SpaceFilter::Histeq(Mat & src)
{
	long len[256];
	GenHist(src, len);
	//得到每一级像素个数的累加
	for(int i = 1; i < 256; ++i)
	{
		len[i] += len[i - 1];
	}
	const double  N = src.cols * src.rows;
	uchar r[256];
	for(uchar i = 1; i < 256; ++i)
	{
		r[i] = (uchar)((len[i] / N) * 255);
	}

	for (int i = 0; i < src.rows; i++)
	{
		uchar * ptr = src.ptr<uchar>(i);
		for (int j = 0; j < src.cols; j++)
		{
			ptr[j] = r[ptr[j]];
		}
	}

}

//获取直方图，src单通道 0 - 255
bool SpaceFilter::GenHist(Mat &src, long hist[256], int n = 256)
{
	long len;
	GET_ARRAY_LENGTH(hist, len);
	if(len != n)
		return false;
	for (int i = 0; i < n; i++)
	{
		hist[i] = 0;
	}
	for (int i = 0; i < src.rows; ++i)
	{
		uchar *ptr = src.ptr<uchar>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			++hist[ptr[j]];
		}
	}
}
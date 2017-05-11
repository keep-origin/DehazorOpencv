#include "SpaceFilter.h"
#include "Utils.h"
using namespace cv;

//ֱ��ͼ���⻯ srcΪ0-255�ĵ�ͨ������ͼ��
void SpaceFilter::Histeq(Mat & src)
{
	long len[256];
	GenHist(src, len);
	//�õ�ÿһ�����ظ������ۼ�
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

//��ȡֱ��ͼ��src��ͨ�� 0 - 255
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
#pragma once

#include "BaseHeader.h"

using namespace cv;

class SpaceFilter{
public:

	/************************************************************************/
	/* max:the max value of type T                                         */
	/************************************************************************/
	template<class T>
	static void Grama(Mat &imgIn, Mat &imgOut, float r, double max){
		int channel  = imgIn.channels();

		for(int h = 0; h < imgIn.rows; ++h)
		{
			const T *ptr1 = imgIn.ptr<T>(h);
			T *ptr2 = imgOut.ptr<T>(h);
			for(int w = 0; w < imgIn.cols; w += channel)
			{
				for(int i = 0; i < channel; ++i)
				{
					double v = ptr1[w + i] / max;
					v = pow(v, r) * max;
					ptr2[w + i] = CLAM(v);
				}
			}
		}
	}
};
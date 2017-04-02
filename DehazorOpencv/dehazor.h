#ifndef DEHAZOR_H
#define DEHAZOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
class Dehazor
{
private:

        // window size -General parameter
        int windowsize;

        // fog reservation factor-General parameter
        double fog_reservation_factor;

        // local window size -guided filter parameter
        int localwindowsize;

        // regularization eps filter parameter
        float eps;

        // output image
        cv::Mat output;

        // raw transmission map
        cv::Mat rawImage;

        // refined transmission map
        cv::Mat refinedImage;

        // inline private member function
        // Computes the distance from target color.
//        int getDistance(const cv::Vec3b& color) const {
//               // return static_cast<int>(cv::norm<int,3>(cv::Vec3i(color[0]-target[0],color[1]-target[1],color[2]-target[2])));
//                return abs(color[0]-target[0])+
//                                      abs(color[1]-target[1])+
//                                      abs(color[2]-target[2]);
//        }

public:

        // empty constructor
        Dehazor() {

                // default parameter initialization here

        }

        void setWindowsize(int px) {

                if (px<0)
                        px=0;
                windowsize= px;
        }
        void setFog_factor(double factor) {

                if (factor<0)
                        factor=0;
                fog_reservation_factor= factor;
        }
        void setLocalWindowsize(int lpx) {

                if (lpx<0)
                        lpx=0;
                localwindowsize= lpx;
        }
        void setEpsilon(float epsilon) {

                if (epsilon<0)
                        epsilon=0;
                eps= epsilon;
        }

        cv::Mat getRawMap()
        {
            return rawImage;
        }
        cv::Mat getRefinedMap()
        {
            return refinedImage;
        }

        cv::Mat process(const cv::Mat &image);
		cv::Mat boxfilter(cv::Mat &im,int r);

private:
        cv::Mat guildedfilter_color(const cv::Mat &Img,cv::Mat &p,int r,float &epsi);

};



#endif // DEHAZOR_H

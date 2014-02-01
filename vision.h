#ifndef _VISION_H
#define _VISION_H


#define WEBCAM



#ifdef WEBCAM
//webcam
#define BLURSIZE 3
#define MINVALUE 90
#define MINHUE 70
#define MAXHUE 110
#define MINSATURATION 90
#define MAXSATURATION 255
#else
//robotcam - TBD
#define BLURSIZE 3
#define MINVALUE 64
#define MINHUE 160
#define MAXHUE 200
#define MINSATURATION 50
#define MAXSATURATION 100
#endif

#define AREA_RATIO 0.8



#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

Mat FilterImage(const Mat& image);

void GetContours(Mat image, vector<vector<Point> >& out_contours, vector<Vec4i>& out_hierarchy);

vector<vector<Point> > GetTargetContours(const vector<vector<Point> >& all_contours, const vector<Vec4i>& hierarchy);



#endif

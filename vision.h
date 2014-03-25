#ifndef _VISION_H
#define _VISION_H


#define ROBOCAM



#ifdef BUILTINCAM
//built in webcam
#define BLURSIZE 3
#define MINVALUE 90
#define MINHUE 70
#define MAXHUE 110
#define MINSATURATION 90
#define MAXSATURATION 255
#elif defined(WEBCAM)
//webcam - NON FILTERED
#define BLURSIZE 3
#define MINVALUE 0
#define MINHUE 0
#define MAXHUE 255
#define MINSATURATION 0
#define MAXSATURATION 255
#else
//robotcam - Reflective
#define BLURSIZE 9
#define MINVALUE 150
#define MINHUE 60
#define MAXHUE 100
#define MINSATURATION 30
#define MAXSATURATION 255
#endif

#define AREA_RATIO 0.65



#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

Mat FilterImage(const Mat& image);

void GetContours(Mat image, vector<vector<Point> >& out_contours, vector<Vec4i>& out_hierarchy);

vector<vector<Point> > GetTargetContours(const vector<vector<Point> >& all_contours, const vector<Vec4i>& hierarchy);



#endif

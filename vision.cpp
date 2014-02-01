#include "vision.h"

#include <vector>


extern bool r1, r2, r3;

#define UINT8 unsigned char

Mat FilterImage(const Mat& image)
{
	Mat hsv;

	//convert to HSV
	cvtColor(image, hsv, CV_BGR2HSV);

	//get the channels;
	vector<Mat> v_channel(3);
	split(hsv,v_channel);
	//treshold
	for(int y = 0; y<hsv.rows; y++)
	{
		for(int x = 0; x<hsv.cols; x++){
			Point ref(x, y);
			UINT8 h, s, v;
			h = v_channel[0].at<UINT8>(ref);
			s = v_channel[1].at<UINT8>(ref);
			v = v_channel[2].at<UINT8>(ref);
			//treshold
			if(v < MINVALUE) //value is low
				hsv.at<Vec3b>(ref) = Vec3b();

			if(h < MINHUE || h > MAXHUE) //hue is not within limits
				hsv.at<Vec3b>(ref) = Vec3b();

			if(s < MINSATURATION || s > MAXSATURATION) //saturation not within limits
				hsv.at<Vec3b>(ref) = Vec3b();

		}
	}

	//convert back to BGR
	Mat backcvt;
	cvtColor(hsv, backcvt, CV_HSV2BGR);

	return backcvt;
}



bool contourAreaComparer(const vector<Point>& a, const vector<Point>& b) {
   return contourArea(a) > contourArea(b);
}


void GetContours(Mat image, vector<vector<Point> >& out_contours, vector<Vec4i>& out_hierarchy)
{
		findContours(image, out_contours, out_hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
}

vector<vector<Point> > GetTargetContours(const vector<vector<Point> >& all_contours, const vector<Vec4i>& hierarchy)
{
	//get the areas
	vector<double> areas;
	vector<vector<Point> > contours_poly;
	for(unsigned int i = 0; i < all_contours.size(); i++)
	{
		vector<Point> poly;
		approxPolyDP(all_contours[i], poly, 4, true);
		contours_poly.push_back(poly);
	}
	//get the biggest
	std::sort(contours_poly.begin(), contours_poly.end(), contourAreaComparer);

	vector<vector<Point> > ret;

	if(contours_poly.size() > 0)
	{
		double maxsize = contourArea(contours_poly[0]);
		for(unsigned int i = 0; i < contours_poly.size(); i++){
			if(contourArea(contours_poly[i]) >= maxsize * AREA_RATIO)
				ret.push_back(contours_poly[i]);
		}
	}

	return ret;
}




#include "vision.h"

#include <vector>


extern bool r1, r2, r3;

#define UINT8 unsigned char

Mat FilterImage(const Mat& image)
{

	Mat ret = Mat::zeros(image.size(), CV_8UC1);
	
	//convert to HSV
	Mat hsv;
	cvtColor(image, hsv, CV_BGR2HSV);
	//get the channels;
	//vector<Mat> v_channel(3);
	//split(hsv,v_channel);
	//treshold
	
	for(int y = 0; y<hsv.rows; ++y)
	{
		for(int x = 0; x<hsv.cols; ++x){
			Point ref(x, y);
			Vec3b color = hsv.at<Vec3b>(ref);
			UINT8 h = color[0];
			UINT8 s = color[1];
			UINT8 v = color[2];
			//treshold
			UINT8& cache = ret.at<UINT8>(ref);

			if(v >= MINVALUE && h >= MINHUE && h <= MAXHUE && s >= MINSATURATION && s <= MAXSATURATION){ //everything is within limits
				cache = v;
				
			}
			/*if(x == 60 && y == 60)
				printf("did st %u\n", ret.at<UINT8>(ref));*/

		}
	}
	

	return ret;
}



bool contourAreaComparer(const vector<Point>& a, const vector<Point>& b) {
   return contourArea(a) > contourArea(b);
}


void GetContours(Mat image, vector<vector<Point> >& out_contours, vector<Vec4i>& out_hierarchy)
{
	Mat copy = image.clone();
		findContours(copy, out_contours, out_hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
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
		int num = 0;
		double maxsize = contourArea(contours_poly[0]);
		for(unsigned int i = 0; i < contours_poly.size(); i++){
			if(contourArea(contours_poly[i]) >= maxsize * AREA_RATIO){
				ret.push_back(contours_poly[i]);
				if(++num >= 2)
					break;
				}
		}
	}

	return ret;
}




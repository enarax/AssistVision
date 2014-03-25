#include "vision.h"

#include <cstring>
#include <stdio.h>
#include <string>
#include <exception>
#include <sstream>
#include <unistd.h>
#include <iostream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define BUFFERLEN 1
#define REQUIRED 1

bool resultbuffer[BUFFERLEN];
int resultindex = 0;



bool averagebuffer()
{
	int num = 0;
	for(int i = 0; i < BUFFERLEN; i++)
		if(resultbuffer[i])
			num++;
	
	return num >= REQUIRED;
	
}




int main(void)
{
	//setup the gpio
	system("echo \"11\" > /sys/class/gpio/export");
	system("echo \"out\" > /sys/class/gpio/gpio11/direction");
	



	for(int i = 0; i < BUFFERLEN; i++)
		resultbuffer[i] = false;
	
	
	CvCapture* capture = cvCaptureFromCAM(0);
	if (! capture)
        {
            fprintf(stderr, "Cannot capture from webcam.\n");
            exit(0);
        }
        
    cvSetCaptureProperty(capture, CV_CAP_PROP_FPS, 30);
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 480 );
	cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 320 );
        
    int count = 0;
	while(1)
	{
		
		

		// create a window to display detected faces
		//cvNamedWindow("Sample Program", CV_WINDOW_AUTOSIZE);
	 	//printf("grabframe ret %d\n", cvGrabFrame(capture));
	 	//continue;
	 	if (!cvGrabFrame(capture))
            continue;
        
        Mat src = cvRetrieveFrame(capture);
        if (++count % 15 != 0)
            continue;
	 	if(src.empty())
	 		continue;
	 		
	 		//flash the LED
		if(count % 30 == 0)
			system("echo \"0\" > /sys/class/leds/led0/brightness");
		else
			system("echo \"1\" > /sys/class/leds/led0/brightness");
	 	
	 	
		
		Mat blurred;
		GaussianBlur(src, blurred, Size(BLURSIZE, BLURSIZE), 1.0);
		Mat filtered_grey = FilterImage(blurred);
		//contours
		
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		GetContours(filtered_grey, contours, hierarchy);
	
		vector<vector<Point> > target = GetTargetContours(contours, hierarchy);
		
		resultbuffer[resultindex%BUFFERLEN] = target.size() >= 2;
		resultindex++;
		
		
 
		int c = cvWaitKey(10);
		if( (char)c == 27 ) { printf("%u\n", filtered_grey.at<unsigned char>(Point(60,60))); }
		
		//imshow("Sample Program", filtered_grey);
		
		char buf[255];
		//sprintf(buf, "/shared/AssistVision/capture/frame%i.jpg", count);
		//imwrite(buf, src);
		
				if(averagebuffer()){
					printf("%i - hot\n", count);
					system("echo \"0\" > /sys/class/gpio/gpio11/value");	
				}
				else{
					printf("%i - nothot\n", count);
					system("echo \"1\" > /sys/class/gpio/gpio11/value");
				}
		
	}
	
		
}

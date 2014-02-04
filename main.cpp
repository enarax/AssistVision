#include "vision.h"
#include "network.h"
#include "message_targethot.h"
#include "message_requeststatus.h"

#include <cstring>
#include <stdio.h>
#include <string>
#include <exception>
#include <sstream>
#include <unistd.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define BUFFERLEN 10
#define REQUIRED 3


const char* robotaddr = "10.28.23.21";
const unsigned short robotport = 12869;
const unsigned short listenport = 12868;

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

	for(int i = 0; i < BUFFERLEN; i++)
		resultbuffer[i] = false;

	networkrobot robot(robotaddr, robotport, listenport);
	
	
	CvCapture* capture = cvCaptureFromCAM(0);
	if (! capture)
        {
            fprintf(stderr, "Cannot capture from webcam.\n");
            exit(0);
        }
	while(1)
	{
		// create a window to display detected faces
		cvNamedWindow("Sample Program", CV_WINDOW_AUTOSIZE);
	 
	 	IplImage* frame = cvQueryFrame( capture ); 
		Mat src(frame);
		Mat blurred;
		GaussianBlur(src, blurred, Size(BLURSIZE, BLURSIZE), 1.0);
		Mat filtered = FilterImage(blurred);
		Mat filtered_grey;
		cvtColor(filtered, filtered_grey, CV_BGR2GRAY);

		//contours
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		GetContours(filtered_grey, contours, hierarchy);
	
		vector<vector<Point> > target = GetTargetContours(contours, hierarchy);
		
		resultbuffer[resultindex%BUFFERLEN] = target.size() >= 2;
		resultindex++;
		
		Mat drawing = Mat::zeros(filtered_grey.size(), CV_8UC3);
		for(unsigned int i = 0; i < target.size(); i++){
			drawContours( drawing, target , i, Scalar(255,255,255,225), 2, 8, hierarchy, 0, Point() );
		}
		
		imshow("Sample Program", drawing);
 
		int c = cvWaitKey(10);
		if( (char)c == 27 ) { exit(0); }
		
		
		
			
		networkmessage* msg = robot.receivemessage(false);
		if(msg)
		{
			if(msg->getGuid() == MSGID_REQUESTSTATUS)
			{
				message_targethot response(averagebuffer());
				robot.sendmessage(&response);
				
				if(averagebuffer())
					printf("sent - hot\n");
				else
					printf("sent - nothot\n");
			}
			else
				printf("Weird message received. ID: %u\n", msg->getGuid());
		}
		deletemessage(&msg);
		
	}
	
	/*
	//sample sending code
	message_targethot msg(1);
	robot.sendmessage(&msg);
	
	//sample receiving code
	while(1)
	{
		printf("waiting...\n");
		networkmessage* msg = robot.receivemessage(true);
		printf("gotmessage\n");
		if(msg->getGuid() == MSGID_TARGETHOT)
		{
			message_targethot* targetmsg = (message_targethot*)msg;
			if(targetmsg->isHot())
				printf("hot\n");
			else
				printf("nothot\n");
		}
		else
			throw std::exception();
			
		deletemessage(&msg);
	}
	*/
	
		
}

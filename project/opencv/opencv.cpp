#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include<opencv2/opencv.hpp>
#include <fstream>
#include <stdlib.h>
using namespace cv;
using namespace std;
#define CAMNUM 0
 int main(int argc, char** argv)
{
	//VideoCapture cap("video2.AVI");
	VideoCapture cap;
	cap.open(CAMNUM);
	cap.set(CV_CAP_PROP_FRAME_WIDTH,480);
       
        cap.set(CV_CAP_PROP_FRAME_HEIGHT,360);
	Mat image1, image2;
	Mat grayscale1, grayscale2;
	Mat absOut, thresholdImg;
	 string time,date_time;
	int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH); 
  	int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); 
	int data;
	if (!cap.isOpened())
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}
	bool detect = false;
	//namedWindow("original", 1); // for edited video
	//namedWindow("threshold", 1); // threshold video
	//VideoWriter video("1.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height));
	while (true)
	{
		system("date +%H > date.txt");
		system("date \"+%H_%M_%S_%d_%m\" > datefull.txt");
		ifstream ftime("date.txt");
    	       
                getline(ftime, time );
		//cout <<"string"<<time<<endl;
                ftime.close();
		ifstream ftime2("datefull.txt");
    	       
                getline(ftime2, date_time );
		//cout <<"string"<<time<<endl;
                ftime2.close();
		 data= atoi(time.c_str());
		//cout <<"data"<<data<<endl;
		bool bSuccess1 = cap.read(image1); // read a new frame from video
   		
               // video.write(image1);
		if (!bSuccess1) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}
		if ( 1 /*data >=12 || data<=6*/ ){
		cvtColor(image1, grayscale1, COLOR_BGR2GRAY); // convert to gray scale

		bool bSuccess2 = cap.read(image2); // read a new frame from video bud need little bit wait for next frame

		if (!bSuccess2) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		cvtColor(image2, grayscale2, COLOR_BGR2GRAY); // convert to gray scale
		absdiff(grayscale1, grayscale2, absOut); //input need to be in grayscale

		blur(thresholdImg, thresholdImg, Size(200, 200));	//smooth effect
		threshold(absOut, thresholdImg, 30, 255, THRESH_BINARY);	//only black and white

		erode(thresholdImg, thresholdImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));	//noise reduction 
		dilate(thresholdImg, thresholdImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));	//noise reduction 

		Moments mome = moments(thresholdImg);
		double dM01 = mome.m01;
		double dM10 = mome.m10;
		double dArea = mome.m00;

		int posX = dM10 / dArea;
		int posY = dM01 / dArea;
		system("echo 0 > alarm.txt");
	//	VideoWriter *video; 
		 VideoWriter* video;
		if (posX > 0 && posY > 0)	//paint cross
		{
			
			line(image1, Point(posX + 30, posY), Point(posX - 30, posY), Scalar(255, 0, 0), 2); 
			line(image1, Point(posX, posY + 30), Point(posX, posY - 30), Scalar(255, 0, 255), 2);
			system("echo 1 > alarm.txt");
			
		       if(detect ==false ){
			//date_time ="vahid";
		   video=new  VideoWriter(date_time+".avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height));			
			///cout <<"dateae====  "<<date_time<<endl;			
			}			
			detect =true;
	 		 video->write(image1);
  
			//imwrite(date_time+".png",image1);		
		}
		else if (detect == true ){
		video->release();
		delete(video);
		detect =false;
		}

		}
		///cout << "vahoddd \n";
		//imshow("threshold", thresholdImg); 
	//	imshow("original", image1);
		 
		imwrite("1.png", image1);
		system("sudo cp 1.png /var/www/html/plot.png ");
		//imwrite("2.png",thresholdImg);
		
	}

	return 0;
}

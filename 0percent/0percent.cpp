#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>

using namespace cv;
using namespace std;

// output video info
double FPS;
int width;
int height;
int B = 20; // border

// video 1 info
double FPS1;
int movieWidth1;
int movieHeight1;

// video 2 info
double FPS2;
int movieWidth2;
int movieHeight2;

// CvCapture, not using
CvCapture* capture1 = 0;
CvCapture* capture2 = 0;
CvVideoWriter *videoWriter = 0;

// main function
int main(int argc, char* argv[])
{
	// open the left and right eye video
	//VideoCapture cap1("D:\\\2016暑假工讀\\\YiVideo\\\left\\\0712\\\YDXJ0462.mp4");
	//VideoCapture cap2("D:/2016暑假工讀/YiVideo/right/0712/YDXJ0005.mp4");
	VideoCapture cap1("YDXJ0529_distort10e7.avi");
	VideoCapture cap2("YDXJ0047_distort10e7.avi");

	/*IplImage* frame1;
	IplImage* frame2;
	IplImage* imageOut = 0;*/

	// if not success, exit program
	if(!cap1.isOpened())
	{
		cout << "Cannnot open the left eye video file" << endl;
		return -1;
	}
	cout << "open left eye video successfully" << endl;

	if(!cap2.isOpened())
	{
		cout << "Cannot open the right eye video file" << endl;
		return -1;
	}
	cout << "open right eye video successfully" << endl;

	// set the desired video file speed.
	FPS1 = cap1.get(CV_CAP_PROP_FPS);
	if(FPS1 <= 0 || FPS1 > 100)
		FPS1 = 30;

	FPS2 = cap2.get(CV_CAP_PROP_FPS);
	if(FPS2 <= 0 || FPS1 > 100)
		FPS2 = 30;

	FPS = max(FPS1, FPS2); // use the fastest video speed.
	cout << "got FPS, FPS: " << FPS << endl;

	// proper width
	movieWidth1 = static_cast<int>(cap1.get(CV_CAP_PROP_FRAME_WIDTH));
	movieWidth2 = static_cast<int>(cap2.get(CV_CAP_PROP_FRAME_WIDTH));
	//width = max(movieWidth1, movieWidth2);
	width = B + movieWidth1 + B + movieWidth2 + B;
	cout << "got total width, width: " << width << endl;

	// proper height
	movieHeight1 = static_cast<int>(cap1.get(CV_CAP_PROP_FRAME_HEIGHT));
	movieHeight2 = static_cast<int>(cap2.get(CV_CAP_PROP_FRAME_HEIGHT));
	//height = max(movieHeight1, movieHeight2);
	height = B + max(movieHeight1, movieHeight2) + B;
	cout << "got total height, height: " << height << endl;

	// open output video file (both eyes)
	VideoWriter out("YDJX0529+YDJX0047_distort10e7.avi", CV_FOURCC('m', 'p', '4', 'v'), FPS, Size(width, height));
	if(!out.isOpened())
	{
		cout << "cannot open output file" << endl;
		exit(-1);
	}
	cout << "open output file successfully" << endl;

	Mat image1, image2;
	cout << "image1 rows: " << image1.rows
		<< "image1 cols: " << image1.cols
		<< "image2 rows: " << image2.rows
		<< "image2 cols: " << image2.cols << endl;
	//Mat image = Mat::zeros(height, width*2+10, );

	// starts create the output file
    cout << "a" << endl;
	while(true)
	{
		cap1 >> image1;
		cap2 >> image2;
		Mat image = Mat::zeros(height, width, image1.type());

		cout << "assertion successfully" << endl;
		//cout << "b" << endl;
		// if no any image found
		if(image1.empty() || image2.empty())
		{
			cout << "can't read frames from both videos" << endl;
			break;
		}

        cout << "find both frames" << endl;

		/*image1.copyTo(image(Range(0, width), Range::all()));
		image2.copyTo(image(Range(width+10, width*2+10), Range::all()));*/
		//cout << "c" << endl;
		//image1.copyTo(image(Range::all(), Range(0, width)));
		//cout << "e" << endl;
		//image2.copyTo(image(Range::all(), Range(width+1000, width*2+1000)));
		//cout << "d" << endl;
		/*Rect leftROI = Rect(B, B, movieWidth1, movieHeight1);
		image = image(leftROI);
		image1.copyTo(image);*/
		image1.copyTo(image(Rect(B, B, movieWidth1, movieHeight1)));
		cout << "left frame copied successfully" << endl;

		/*Rect rightROI = Rect(B+movieWidth1+B, B, movieWidth2, movieHeight2);
		image = image(rightROI);
		image2.copyTo(image);*/
		image2.copyTo(image(Rect(B+movieWidth1+B, B, movieWidth2, movieHeight2)));
		cout << "right frame copied successfully" << endl;

		out << image;
		//imshow("modified video", image);

        cout << "modification succeed" << endl;
		//out.write(image);

		if(waitKey(1000.0/FPS) == 27)
			break;
	}

	cout << "complete" << endl; // end program successfully
	return 0;
}

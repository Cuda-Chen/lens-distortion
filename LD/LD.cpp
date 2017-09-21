// OpenCV accessing video camera and saving the result
#include <iostream>
#include <opencv2/opencv.hpp>

// function distort
// make barrel distortion on the frame
void distort(const IplImage* arr, float idx0, float idx1, CvScalar& res)
{
	if((idx0 < 0) || (idx1 < 0) || (idx0 > (cvGetSize(arr).height-1) || idx1 > (cvGetSize(arr).width-1)))
    {
        res.val[0] = 0;
        res.val[1] = 0;
        res.val[2] = 0;
        res.val[3] = 0;
        return;
    }

    float idx0_floor = floor(idx0);
    float idx0_ceil = ceil(idx0);
    float idx1_floor = floor(idx1);
    float idx1_ceil = ceil(idx1);

    CvScalar s1 = cvGet2D(arr, (int)idx0_floor, (int)idx1_floor);
    CvScalar s2 = cvGet2D(arr, (int)idx0_floor, (int)idx1_ceil);
    CvScalar s3 = cvGet2D(arr, (int)idx0_ceil, (int)idx1_ceil);
    CvScalar s4 = cvGet2D(arr, (int)idx0_ceil, (int)idx1_floor);
    float x = idx0 - idx0_floor;
    float y = idx1 - idx1_floor;
    res.val[0]= s1.val[0]*(1-x)*(1-y) + s2.val[0]*(1-x)*y + s3.val[0]*x*y + s4.val[0]*x*(1-y);
    res.val[1]= s1.val[1]*(1-x)*(1-y) + s2.val[1]*(1-x)*y + s3.val[1]*x*y + s4.val[1]*x*(1-y);
    res.val[2]= s1.val[2]*(1-x)*(1-y) + s2.val[2]*(1-x)*y + s3.val[2]*x*y + s4.val[2]*x*(1-y);
    res.val[3]= s1.val[3]*(1-x)*(1-y) + s2.val[3]*(1-x)*y + s3.val[3]*x*y + s4.val[3]*x*(1-y);
}
// end function distort

// variables used for barrel distortion
//float K = 0.0000001; /* 10e-7 */ // <--------------------------------------------------------------------------
float K = 0.000001; /* 10e-6 */
IplImage* src; // source frame
IplImage* dst; // source frame which has been modified
cv::Mat imageProcessed; // cast dst(type: IlpImage*) into Mat

float xscale;
float yscale;
float xshift;
float yshift;

// function getRadialX
float getRadialX(float x, float y, float cx, float cy, float k)
{
	x = (x * xscale + xshift);
	y = (y * yscale + yshift);
	float res = x+((x-cx)*k*((x-cx)*(x-cx)+(y-cy)*(y-cy)));
	return res;
}
// end function getRadialX

// function getRadialY
float getRadialY(float x, float y, float cx, float cy, float k)
{
	x = (x*xscale+xshift);
    y = (y*yscale+yshift);
    float res = y+((y-cy)*k*((x-cx)*(x-cx)+(y-cy)*(y-cy)));
    return res;
}
// end function getRadialY

float thresh = 1;

// function calc_shift
float calc_shift(float x1, float x2, float cx, float k)
{
	float x3 = x1 + (x2 - x1) * 0.5;
	float res1 = x1+((x1-cx)*k*((x1-cx)*(x1-cx)));
    float res3 = x3+((x3-cx)*k*((x3-cx)*(x3-cx)));

	if(res1 > -thresh and res1 < thresh)
		return x1;
	if(res3 < 0)
	{
		return calc_shift(x3, x2, cx, k);
	}
	else
	{
		return calc_shift(x1, x3, cx, k);
	}
}
// end function calc_shift

// main function
int main()
{
    // Open the input video
    cv::VideoCapture cap("YDXJ0469.mp4");
    if(!cap.isOpened()) // if intput video has any situation
    {
        std::cout << "Unable to open the camera\n";
        std::exit(-1);
    }

    cv::Mat image; // to capture frames from the video
    double FPS = cap.get(CV_CAP_PROP_FPS); // FPS

    // Get the width.height of the video
    int width = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT));

    // Open an output video file for writing (the MP4V codex works on OS X and Windows)
    cv::VideoWriter out("YDXJ0469_distort10e6.avi", CV_FOURCC('m', 'p', '4', 'v'), FPS, cv::Size(width, height));
    if(!out.isOpened()) // if output video has any situation
    {
        std::cout << "Error! Unable to open video file for output." << std::endl;
        std::exit(-1);
    }

	// while loop to modify the frames
    while(true)
    {
        cap >> image; // capture a frame from input video
        if(image.empty()) // if don't find a frame
        {
            std::cout << "Can't read frames from your camera\n";
            break;
        }

		src = new IplImage(image); // change image's type to IplImage* (and pass by reference)
		dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels); // initialize dst
		float centerX = (cvGetSize(src).width) / 2; // initialize centerX
		float centerY = (cvGetSize(src).height) / 2; // initialize centerY
		int width = cvGetSize(src).width; // initialize width
		int height = cvGetSize(src).height; // initialize height

		xshift = calc_shift(0, centerX-1, centerX, K);
		float newcenterX = width - centerX;
		float xshift_2 = calc_shift(0, newcenterX-1, newcenterX, K);

		yshift = calc_shift(0, centerY-1, centerY, K);
		float newcenterY = height - centerY;
		float yshift_2 = calc_shift(0, newcenterY-1, newcenterY, K);

		xscale = (width - xshift - xshift_2) / width;
		yscale = (height - yshift - yshift_2) / height;

		// start barrel distortion
		for(int j = 0; j < cvGetSize(dst).height; j++)
		{
			for(int i = 0; i < cvGetSize(dst).width; i++)
			{
				CvScalar s;
				float x = getRadialX((float)i, (float)j, centerX, centerY, K);
				float y = getRadialY((float)i, (float)j, centerX, centerY, K);
				distort(src, y, x, s);
				cvSet2D(dst, j, i, s);
			}
		}

		// set imageProcessed as dst's reference
		imageProcessed = cv::cvarrToMat(dst);

        // Save frame to video
        //out << image;
		out << imageProcessed;

        //cv::imshow("Camera feed", image);
		cv::imshow("Camera feed", imageProcessed);

		//cvReleaseImage(&src);
		cvReleaseImage(&dst);

        // Stop the program if the user presses the "ESC" key
        if(cv::waitKey(1000.0/FPS) == 27) break;
    }

    return 0;
}
// end main function

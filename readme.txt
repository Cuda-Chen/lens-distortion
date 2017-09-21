compile information of 0percent.cpp and LD.cpp:
language: C++
IDE: code::block 12.11
compiler: gcc ver. 4.7.1 (tdm-1) with MinGW
openCV ver.: 2.4.13
problem you may encounter: cannot search file using absolute path(both programs)

0percent.cpp:

	description:
	�o�ӵ{���O�ڥΨӧ��Ӽv���X���@�Ӽv����program

	how to run this program:
	��W�sĶ0percent.cpp�Y�i

	input 1:
	put the file represented left eye video into
	VideoCapture cap1("FILENAME"); (line 37)

	input 2:
	put the file represented right eye video into
	VideoCapture cap2("FILENAME"); (line 38)
	
	output:
	put the output file name you prefer into
	VideoWriter out("FILENAME", CV_FOURCC('m', 'p', '4', 'v'), FPS, Size(width, height)); (line 86)

LD.cpp:
	description:
	�o�ӵ{���O�ڥΨӹ�@�Ӽv���i��barrel distortion����A��X���@��.avi file��program
	
	how to run this program:
	��W�sĶLD.cpp�Y�i

	input:
	put the file you want to distort into
	cv::VideoCapture cap("FILENNAME"); (line 94)

	output:
	put the output file name you prefer into
	cv:VideoWriter output("FILENAME", CV_FOURCC('m', 'p', '4', 'v'), FPS, cv:Size(width, height)); (line 109)
	I recommend the file name plus "distort" and "N"(N for the value of K) with (ex. FILENAME_distort_N)

	parameter:
	distort coefficient K
	put the value of K you desire into
	float K = "your value"; (line 38)
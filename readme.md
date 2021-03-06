# Develop Environment of this work
* language: C++
* IDE: code::block 12.11
* compiler: gcc ver. 4.7.1 (tdm-1) with MinGW
* openCV ver.: 2.4.13

# problem you may encounter
* cannot search file using absolute path (both programs)

# Description of this work
* this work consists of two parts: 0percent and LD
* 0percent.cpp:
	* description:
		* put two videos side-by-side horizontally
then output one video
	* input 1:
		* put the file represented left eye video into
```VideoCapture cap1("FILENAME"); ```
	* input 2:
		* put the file represented right eye video into
```VideoCapture cap2("FILENAME");```	
	* output:
		* put the output file name you prefer into
```VideoWriter out("FILENAME", CV_FOURCC('m', 'p', '4', 'v'), FPS, Size(width, height)); ```

* LD.cpp:
	* description:
		* apply barrel distortion to input video with certain coefficient
then output the processed video
	* input:
		* put the file you want to distort into
```cv::VideoCapture cap("FILENNAME"); ```
	* output:
		* put the output file name you prefer into
```cv:VideoWriter output("FILENAME", CV_FOURCC('m', 'p', '4', 'v'), FPS, cv:Size(width, height));```
	* I recommend the file name plus "distort" and "N"(N for the value of K) with (e.g. FILENAME_distort_N)
	* parameter:
		* distort coefficient ```K```
		* put the value of K you desire into
```float K = "your value";```

# How to Compile and Run this Work
* for 0percent
```
$ cmake .
$ make
$ ./0percent
```
* for LD
```
$ cmake .
$ make
$ ./LD
```

# Reference
The work of barrel distortion is originated from 逍遙文工作室.
You can find his work in this link: https://cg2010studio.com/2012/01/03/opencv-%E6%A8%A1%E6%93%AC%E9%AD%9A%E7%9C%BC%E9%8F%A1%E9%A0%AD-simulate-fisheye-lens/

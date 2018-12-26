# Develop Environment of this work
* language: C++
* IDE: code::block 12.11
* compiler: gcc ver. 4.7.1 (tdm-1) with MinGW
* openCV ver.: 2.4.13

# problem you may encounter
* cannot search file using absolute path(both programs)

# Description of this work
* this work consists of two parts: 0percent and LD
* 0percent.cpp:
	* description:
		* put two videos side-by-side horizontally
then output one video

	* how to compile and run this program:
```
$ cmake .
$ make
$ ./0percent
```


	* input 1:
		* put the file represented left eye video into
```cpp=37
VideoCapture cap1("FILENAME"); 
```


	* input 2:
		* put the file represented right eye video into
```cpp=38
VideoCapture cap2("FILENAME");
```

	
	* output:
		* put the output file name you prefer into
```cpp=86
VideoWriter out("FILENAME", CV_FOURCC('m', 'p', '4', 'v'), FPS, Size(width, height));
```

* LD.cpp:
	* description:
		* apply barrel distortion to input video with certain coefficient
then output the processed video
	
	* how to run this program:
```
$ cmake .
$ make
$ ./LD
```


	* input:
		* put the file you want to distort into
```cpp=94
cv::VideoCapture cap("FILENNAME"); 
```


	* output:
		* put the output file name you prefer into
```cpp=109
cv:VideoWriter output("FILENAME", CV_FOURCC('m', 'p', '4', 'v'), FPS, cv:Size(width, height));
```
	* I recommend the file name plus "distort" and "N"(N for the value of K) with (e.g. FILENAME_distort_N)

	* parameter:
		* distort coefficient ```K```
		* put the value of K you desire into
```cpp=38
float K = "your value";
```

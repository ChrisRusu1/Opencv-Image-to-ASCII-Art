#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include<sstream>  
#include <vector>
#include <windows.h>
//#include <bits/stdc++.h>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	bool render = false;
	if (render) {


		Mat image;
		Mat grayImage;
		Mat resizeImage;
		string fileName;
		//int counter = m;
		stringstream ss;
		VideoCapture cap("Images/aladdin/aladdin.mp4");
		if (!cap.isOpened()) {
			cout << "Error opening video stream or file" << endl;
			cvWaitKey(0);
			return -1;
		}
		int counter = 0;
		while (true) {
			if (counter % 1 == 0) {
				Mat frame;
				cap >> frame;
				double resizeValue = 0.073;
				if (frame.empty())
					break;
				cvtColor(frame, grayImage, CV_BGR2GRAY);
				resize(grayImage, resizeImage, cv::Size(), resizeValue, resizeValue, INTER_AREA);
				string textfileName;
				textfileName = "aladdin";
				textfileName += to_string(counter);

				cout << textfileName << endl;
				ofstream myfile;
				myfile.open("textFile/aladdint/" + textfileName);
				char choicec;
				string asciiSelf;

				char standard[10] = { ' ','.','-',':','=','+','*','#','%','@' };
				int values[10];
				double runs = 255 / 10;
				for (int i = 0; i < 10; i++) {
					values[10 - (i + 1)] = runs * (i + 1);
				}
				values[0] = 255;
				int avg;
				for (int i = 0; i < resizeImage.rows; i++) {// 0 is start
					for (int j = 0; j < resizeImage.cols; j++) {//0 is start
						avg = resizeImage.at<uchar>(i, j);
						for (int l = 0; l < 10; l++) {
							if (l == 9) {
								if (avg <= values[l] && avg >= 0) {
									myfile << standard[l];
									break;
								}
							}
							else if (avg <= values[l] && avg >= values[l + 1]) {
								myfile << standard[l];
								break;
							}
						}
					}
					myfile << endl;
				}
				myfile.close();
				image.release();
				grayImage.release();
				//cvWaitKey(0);

			}
			counter++;
		}
	}
	int counter2 = 0;
	while (true) {
		if (counter2 % 6 == 0) {

			cout << string(50, '\n');
			string line;///make a string for the line
			string textfileName = "aladdin";
			textfileName += to_string(counter2);

			ifstream InFile(("textFile/aladdint/" + textfileName).c_str()); /// just a text file
			while (getline(InFile, line)) {

				string inputStr(line);
				string buf; /// Have a buffer string
				stringstream s(inputStr); /// Insert the string into a stream
				s << inputStr;///put the line into the stream
				string input;///string for the input

				while (getline(s, input)) {
					cout << input;
				}
				cout << '\n';
			}
			Sleep(500);
		}

		counter2++;
	}
	return 0;


}


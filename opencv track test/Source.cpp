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
	for (int m = 0; m < 25; m++) {


		Mat image;
		Mat grayImage;
		Mat resizeImage;
		string fileName;
		int counter = m;
		stringstream ss;

		ss << counter;
		ss >> fileName;
		fileName = fileName + "_delay-0.09s.jpg";
		if (counter >= 10) {
			fileName = "Images/gen/frame_" + fileName;
		}
		else {
			fileName = "Images/gen/frame_0" + fileName;
		}


		//cout << "input a file name(with extention)" << endl;
		//cin >> fileName;
		image = imread(fileName);
		if (!image.data) {
			cout << "Could not open the image file " << fileName << endl;
			cvWaitKey(0);
			return -1;
		}
		else {
			double resizeValue = 0.046;
			int height = image.rows;
			int width = image.cols;

			cvtColor(image, grayImage, CV_BGR2GRAY);
			resize(grayImage, resizeImage, cv::Size(), resizeValue, resizeValue, INTER_AREA);
			string textfileName;
			textfileName = "genie";
			textfileName += to_string(m);

			cout << textfileName << endl;
			ofstream myfile;
			myfile.open("textFile/genie/" + textfileName);
			//myfile << "Writing this to a file.\n";
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
	}
	while (true) {
		for (int n = 0; n < 25; n++) {
			
			cout << string(50, '\n');
			string line;///make a string for the line
			string textfileName = "genie";
			textfileName += to_string(n);

			ifstream InFile(("textFile/genie/" + textfileName).c_str()); /// just a text file
			while (getline(InFile, line)) /// getline returns false at EOF
			{

				string inputStr(line);
				string buf; /// Have a buffer string
				stringstream s(inputStr); /// Insert the string into a stream
				s << inputStr;///put the line into the stream
				string input;///string for the input

				while (getline(s, input))///gets a string from the stream up the next space
				{
					
						cout <<input;
					

				}
				cout << '\n';
			}
			Sleep(90);
		}
		

	}
	return 0;


}


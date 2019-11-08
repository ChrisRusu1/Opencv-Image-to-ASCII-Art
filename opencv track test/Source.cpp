#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	
		Mat image;
		Mat grayImage;

		image = imread("kenrith.jpg");
		if (!image.data) {
			cout << "Could not open the image file" << endl;
			return -1;
		}
		else {
			int height = image.rows;
			int width = image.cols;

			cvtColor(image, grayImage, CV_BGR2GRAY);


			namedWindow("Display window", WINDOW_NORMAL);
			imshow("Display window", image);

			namedWindow("Gray Image", WINDOW_NORMAL);
			imshow("Gray Image", grayImage);
			ofstream myfile;
			myfile.open("example2.txt");
			//myfile << "Writing this to a file.\n";
			int avg;
			int count = 0;
			for (int i = 0; i < grayImage.rows; ++i) {// 0 is start
				i++;
				const unsigned char* row = grayImage.ptr<unsigned char>(i);
				for (int j = 0; j < grayImage.cols; j++) {//0 is start
					j++;
					avg = grayImage.at<uchar>(i, j);
					if (avg < 29) myfile << '.';
					else if (avg < 58) myfile << ',';
					else if (avg < 87) myfile << ';';
					else if (avg < 116) myfile << '!';
					else if (avg < 145) myfile << 'v';
					else if (avg < 174) myfile << 'l';
					else if (avg < 203) myfile << 'L';
					else if (avg < 232) myfile << 'F';
					else if (avg < 255) myfile << 'E';
					else                      myfile << '$';
						
				}
				myfile << endl;
			}
			

			
			myfile.close();

			//cvWaitKey(0);
			image.release();
			grayImage.release();
			return 0;
		}

	}


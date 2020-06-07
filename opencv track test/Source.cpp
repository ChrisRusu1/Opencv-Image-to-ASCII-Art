#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;
int main(int argc, char *argv[]){
		Mat image;
		Mat grayImage;
		Mat resizeImage;
		string fileName;
		cout << "input a file name(with extention)" << endl;
		cin >> fileName;
		image = imread("Images/"+fileName);
		if (!image.data) {
			cout << "Could not open the image file" << endl;
			return -1;
		}
		else {
			cout << "please input a resizing factor(0-1)" << endl;
			double resizeValue;
			cin >> resizeValue;
			int height = image.rows;
			int width = image.cols;

			cvtColor(image, grayImage, COLOR_BGR2GRAY);
			resize(grayImage, resizeImage, cv::Size(), resizeValue, resizeValue*.6, INTER_AREA);
			cout << "please input a text file name to store he ascii art, with .txt at the end" << endl;
			string textfileName;
			cin >> textfileName;
			
			/*namedWindow("Display window", WINDOW_NORMAL);
			imshow("Display window", image);

			namedWindow("Gray Image", WINDOW_NORMAL);
			imshow("Gray Image", resizeImage);*/
			ofstream myfile;
			myfile.open("textFile/"+textfileName);
			//myfile << "Writing this to a file.\n";
			cout << "do you want standard ascii values, or input your own? (o for own, s for standard)" << endl;
			char choicec;
			cin >> choicec;
			string asciiSelf;
			if (choicec == 'o') {
				cout << "please input your ascii values (lighest to darkest)" << endl;
				cin >> asciiSelf;
				const int arraysize = asciiSelf.size();
				vector<int> values;
				double runs = 255 / arraysize;
				for (int i = 0; i < arraysize; i++) {
					values.push_back(runs * ((arraysize - (i + 1)) + 1));
				}
				values[0] = 255;
				int avg;
				for (int i = 0; i < resizeImage.rows; ++i) {// 0 is start
					for (int j = 0; j < resizeImage.cols; j++) {//0 is start
						avg = resizeImage.at<uchar>(i, j);
						for (int i = 0; i < arraysize; i++) {
							if (i == arraysize - 1) {
								if (avg <= values[i] && avg >= 0) {
									myfile << asciiSelf[i];
									break;
								}
							}
							else if (avg <= values[i] && avg >= values[i + 1]) {
								myfile << asciiSelf[i];
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
				return 0;
			}
			else {
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
				return 0;
			}
				

			// .'`^",:;Il!i><~+_-?][}{1)(\|?tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$ <<<white to black
			
		}

	}


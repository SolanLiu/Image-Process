#include "mycanny.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void MyCanny::on_canny_clicked()
{
    Mat img = imread("F://Qt5.8.0//myProcedure//test_Ostu//testImage.bmp", 1);
    Mat grey;
    cvtColor(img, grey,CV_BGR2GRAY);
    Mat edges(img.size(), CV_8U);
    double threshold = 50;

    Canny(img, edges, threshold, threshold * 3, 3);

    cvNamedWindow("img");
    cvNamedWindow("edges");
    imshow("img",img);
    imshow("edges",edges);

    cvWaitKey(0);
    cvDestroyWindow("img");
    cvDestroyWindow("edges");
}

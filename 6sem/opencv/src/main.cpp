#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include<iostream>

using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold = 9;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";

Mat CannyThreshold(Mat src, Mat dst)
{
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
    dst = Scalar::all(255);
    src.copyTo(dst, detected_edges);
    //imshow(window_name, dst);
    return dst;
}


int main()
{
    Mat image;
    image = imread("donov.jpg", CV_LOAD_IMAGE_COLOR);

    //if (!image.data)
    //{
    //    std::cout << "could not open or find image" << std::endl;
    //    return -1;
    //}

    Mat blured;
    GaussianBlur(image, blured, Size(15, 15), 0, 0);

    //if (!blured.data)
    //{
    //    std::cout << "could not open or find image" << std::endl;
    //    return -1;
    //}

    Mat grayScale;
    cvtColor(image, grayScale, COLOR_BGR2GRAY);

    Mat dX, dY;
    Sobel(grayScale, dX, CV_32F, 1, 0);
    Sobel(grayScale, dY, CV_32F, 0, 1);

    //if (!dY.data)
    //{
    //    std::cout << "could not open or find image" << std::endl;
    //    return -1;
    //}

    Mat mag, ang;
    cartToPolar(dX, dY, mag, ang);

    auto it = std::max_element(mag.begin<float>(), mag.end<float>());
    auto max_elem = mag.at<float>(it.pos());
    mag /= max_elem;

    //if (!mag.data)
    //{
    //    std::cout << "could not open or find image" << std::endl;
    //    return -1;
    //}

    //src = imread("donov.jpg", CV_LOAD_IMAGE_COLOR);
    //cvtColor(src, src_gray, COLOR_BGR2GRAY);

    //if (!src.data)
    //{
    //    std::cout << "could not open or find image" << std::endl;
    //    return -1;
    //}

    ////cvtColor(src, src_gray, COLOR_BGR2GRAY);
    //dst.create(src.size(), src.type());
    ////cvtColor(src, src_gray, COLOR_BGR2GRAY);

    //namedWindow(window_name, WINDOW_AUTOSIZE);

    ////createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
    //CannyThreshold(src);


    VideoCapture cap(0);
    if (!cap.isOpened())
        return -1;
    namedWindow("frame", CV_WINDOW_AUTOSIZE);
    while (true)
    {
        Mat frame, dst;
        cap >> frame;
        dst.create(frame.size(), frame.type());
        Mat final;
        flip(CannyThreshold(frame, dst), final, 1);
        imshow("frame", final);
        if (waitKey(30) == 27) break; //выходим на esc
    }

    //namedWindow("Display window", WINDOW_AUTOSIZE);
    //imshow("Display window", mag);

    waitKey(0);

    return 0;
}

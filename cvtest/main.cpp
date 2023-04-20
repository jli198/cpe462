#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    int   j, k, width, height;


    int** image_in, ** image_out;


    Mat image;
    Mat newImage;

    image = imread(argv[1], IMREAD_GRAYSCALE);
    if (!image.data) {
        cout << "Could not open the image file" << endl;
        return -1;
    }
    else {
        int height = image.rows;
        int width = image.cols;


        namedWindow("Display window", WINDOW_AUTOSIZE);
        imshow("Display window", image);

        newImage = image.clone();
        //negative (originally given code)

        for (j = 0; j < height; j++)
            for (k = 0; k < width; k++)
            {
                newImage.at<uchar>(j, k) = 255 - image.at<uchar>(j, k);
            }
        //pixel at (y,x)


        bool worked = imwrite("mynewimg.jpg", newImage);
        if (!worked)
            cout << "failure\n";
        else
            cout << "success\n";
        namedWindow("New Image", WINDOW_AUTOSIZE);
        imshow("New Image", newImage);
        waitKey(0);
        image.release();
        newImage.release();
    }
    return 0;

}
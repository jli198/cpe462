// myimgproc.cpp :  This file contains 'main' function. Program execution begins and ends there.
// Usage: myimgproc

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>
//#include <opecnv2/core/core.hpp>
//#include <opecnv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
  FILE* in, * out;
  int j, k, width, height;
  int** image_in, ** image_out;
  float sum1, sum2;
  float new_T, old_T, delta_T;
  long count1, count2;
  errno_t err;

  /*
  Some OpenCV here
  */

  //Open default video camera
  VideoCapture cap(0);

  // if not success, exit program
  if (cap.isOpened() == false)
  {
    cout << "Cannot open video camera" << endl;
    cin.get();  //wait for any key press
    return -1;
  }

  double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);  //get width of frames of video
  double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);  //get height of frames of video

  cout << "Resolution of video : " << dWidth << " x " << dHeight << endl;

  string window_name = "My Camera Feed";
  namedWindow(window_name); //create window called "My Camera Feed"

  Mat frame;

  while (true)
  {
    bool bSuccess = cap.read(frame);  // read new frame from video

    //Breaking while loop if frames cannot be captured
    if (bSuccess == false)
    {
      cout << "Video camera is disconnected" << endl;
      cin.get();  //Wait for any key press
      break;
    }

    //show frame in created window
    imshow(window_name, frame);

    //wait for 10 ms until any key is pressed
    //If 'Esc' key is pressed, break while loop
    //If any other key is pressed, continue loop
    //If any key is not pressed within 10 ms, continue loop
    if (waitKey(10) == 27)
    {
      cout << "Esc key is presssed by user. Stopping the video" << endl;
      break;
    }
  }

  //Mat M_in = imread(argv[1]);
  Mat M_in = frame;
  Mat_<uchar> M_in_g(M_in.rows, M_in.cols);
  cvtColor(M_in, M_in_g, COLOR_BGR2GRAY);
  //cout << "height" << M_in_g.rows << endl;

  String windowName1 = "Input Image"; //Name of window

  namedWindow(windowName1); // Create window

  imshow(windowName1, M_in_g);  // Show image inside created window

  waitKey(0); // Wait for any keystroke in window

  destroyWindow(windowName1); //destroy created window

  height = M_in_g.rows;
  width = M_in_g.columns;

  image_in = (int**)calloc(height, sizeof(int*));
  if (!image_in)
  {
    printf("Error: Can't allocate memory!\n");
    return(1);
  }

  image_out = (int**)calloc(height, sizeof(int*));
  if (!image_out)
  {
    printf("Error: Can't allocate memory!\n");
    return(1);
  }

  for (j = 0; j < height; j++)
  {
    image_in[j] = (int*)calloc(width, sizeof(int));
    if (!image_in[j])
    {
      printf("Error: Can't allocate memory!\n");
      return(1);
    }

    image_out[j] = (int*)calloc(width, sizeof(int));
    if (!image_out[j])
    {
      printf("Error: Can't allocate memory!\n");
      return(1);
    }
  }

  for (j=0; j < height; j++)
    for (k=0; k < width; k++)
      image_in[j][k] = M_in_g(j, k);

  /*
  Image Processing begins
  */

  for (j = 0; j < height; j++)
    for (k = 0; k < width; k++)
    {
      image_out[j][k] = 255 - image_in[j][k];
    }
  
  /*
  Image Processing ends
  */

  /*
  Some OpenCV here
  */

  Mat_<uchar> M_out(height, width);
  for (int ii = 0; ii < height; ii++)
    for (int jj = 0; jj < width; jj++)
      M_out(ii, jj) = image_out[ii][jj];

  String windowName2 = "Output Image";  //Name of window

  namedWindow(windowName2); // Create window

  imshow(windowName2, M_out); // Show image inside created window

  waitKey(0); // Wait for any keystroke in window

  destroyWindow(windowName2); //destroy created window

  bool isSuccess = imwrite("MyOutImage.jpg", M_out);  //write image to file as JPEG
  //bool isSuccess = imwrite("MyOutImage.png", M_out);  //write image to file as PNG
  if (isSuccess == false)
  {
    cout << "Failed to save image" << endl;
    //cin.get();  //wait for key press
    return -1;
  }

  for (j = 0; j < height; j++)
  {
    free(image_in[j]);
    free(image_out[j]);
  }
  free(image_in);
  free(image_out);

  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
/*
imageproc.c
Usage: imageproc in_file_name out_file_name width height
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#Include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
  FILE *in, *out;
  int j, k, width, height;
  int ** image_in, ** image_out;
  float sum1, sum2;
  float new_T, old_T, delta_T;
  long count1, count2;
  errno_t err;

  if(argc<5) { printf("ERROR: Insufficient parameter!\n"); return(1);}

  width = atoi(argv[3]);
  height = atoi(argv[4]);

  image_in = (int**) calloc(height, sizeof(int*));
  if(!image_in)
  {
    printf("Error: Can't allocate memory!\n");
    return(1);
  }

  image_out = (int**) calloc(height, sizeof(int*));
  if(!image_out)
  {
    printf("Error: Can't allocate memory!\n");
    return(1);
  }

  for (j=0; j<height; j++)
  {
    image_in[j] = (int *) calloc(width, sizeof(int));
    if(!image_in[j])
    {
      printf("Error: Can't allocate memory!\n");
      return(1);
    }

    image_out[j] = (int *) calloc(width, sizeof(int));
    if(!image_out[j])
    {
      printf("Error: Can't allocate memory!\n");
      return(1);
    }
  }

  if((err=fopen_s(&in, argv[1], "rb")) !=0)
  {
    printf("ERROR: Can't open in_file!\n");
    return(1);
  }

  if((err=fopen_s(&out, argv[2], "wb")) !=0)
  {
    printf("ERROR: Can't open out_file!\n");
    return(1);
  }

  for (j=0; j < height; j++)
    for (k=0; k<width; k++)
    {
      if((image_in[j][k]=getc(in))==EOF)
      {
        printf("ERROR: Can't read from in_file!\n");
        return(1);
      }
    }
  
  if(fclose(in)==EOF)
  {
    printf("ERROR: Can't close in_file!\n");
    return(1);
  }
  
  /*
  Image processing begins
  */
  for (j=0; j<height; j++)
    for (k=0; k<width; k++)
    {
      image_out[j][k]=255-image_in[j][k];
    }
  
  /*
  Image processing ends
  */
  
  /*
  Some OpenCV here
  */

  Mat_<uchar> M_out(height, width);
  for (int ii = 0; ii < height; ii++)
    for (int jj = 0; jj < width; jj++)
      M_out(ii, jj) = image_out[ii][jj];
  
  String windowName2 = "Output Image"; //Name of window

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

  /* save image_out into out_file in raw format */
  for (j=0; j < height; j++)
    for (k=0; k < width; k++)
    {
      if((putc(image_out[j][k],out))==EOF)
      {
        printf("ERROR: Can't write to outfile!\n");
        return(1);
      }
    }

  if(fclose(out)==EOF)
	{
		printf("ERROR: Can't close out_file!\n");
		return(1);
	}


	for (j=0; j<height; j++)
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
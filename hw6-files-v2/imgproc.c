/*
imageproc.c
Usage: imagproc in_file_name out_file_name width height
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "CImg.h"
using namespace cimg_library;

int main(int argc, char *argv[])
{
  FILE *in, *out;
  int j, k, width, height;
  int ** image_in, ** image_out;
  float sum1, sum2;
  long count1, count2;

  if(argc<5) { printf("ERROR: Insufficient parameters!\n"); return(1);} 

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

  for (j=0; j < height; j++)
  {
    image_in[j] = (int *) calloc(width, sizeof(int));
    if(!image_in[j])
    {
      printf("Error: Can't allocate memory!\n");
      return(1);
    }
    image_out[j] = (int *) calloc(width,sizeof(int));
    if(!image_out[j])
    {
      printf("Error: Can't allocate memory!\n");
      return(1);
    }
  }

  if((in=fopen(argv[1], "rb"))==NULL)
  {
    printf("ERROR: Can't open in_file!\n");
    return(1);
  }
  if((out=fopen(argv[2], "web"))==NULL)
  {
    printf("ERROR: Can't open out_file!\n");
    return(1);
  }

  for (j=0; j < height; j++)
    for (k=0; k<width; k++)
    {
      if((image_in[j][k] =getc(in)) == EOF) {
        printf("ERROR: Can't read file from in_file!\n");
        return(1);
      }
    }
  if(fclose(in)==EOF)
  {
    printf("ERROR: Can't close in_file!\n");
    return(1);
  }

  /* display image_in */
  CIMG<int> image_disp(width, height, 1, 1, 0);
  /* CIMG<type> image_name(width, height, temproral_frame_number, color_plane_number, initial)*/

  for (j=0; j<height; j++)
    for(k=0; k<width; k++)
    {
      image_disp(k, j, 0, 0) = image_in[j][k];
    }
  CImgDisplay disp_in(image_disp, "Image_In", 0);
  /*CImgDisplay display_name(image_displayed, "window title", normalization_factor) */

  /*
  Image Processing begins
  */
  
  for (j=0; j<height; j++)
    for (k=0; k<width; k++)
    {
      image_out[j][k]=255-image_in[j][k];
    }

  /*
  Image Processing ends
  */

  /* display image_out */
  for (j=0; j<height; j++)
    for (k=0; k<width; k++)
    {
      image_disp(k,j,0,0) = image_out[j][k];
    }
  CImgDisplay disp_out(image_disp,"Image_Out", 0);

  /* save image_out into out_file */
  for (j=0; j<height; j++)
    for (k=0; k<width; k++)
    {
      if((putc(image_out[j][k], out))==EOF)
      {
        printf("ERROR: Can't write to out_file!\n");
        return(1);
      }
    }

  if(fclose(out)==EOF)
  {
    printf("ERROR: Can't close out_file!\n");
    return(1);
  }

  /* closing */
  while (!disp_in.is_closed)
    disp_in.wait();
  while (!disp_out.is_closed)
    disp_out.wait();

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
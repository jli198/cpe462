/**********************************************************************************
* imageprocessing.c
* Usage: imageproc in_file_name out_file_name width height
* Modified to include HW7. Functionality will need tweaking
 **********************************************************************************/


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[])
{
	FILE  *in, *out;
	int   j, k, width, height;
	int ** image_in, ** image_out;
	float sum1, sum2;
	float new_T, old_T, delta_T;
	long count1, count2;
	errno_t err;

	if(argc<5) { printf("ERROR: Insufficient parameters!\n"); return(1);}

	width = atoi(argv[3]);
	height = atoi(argv[4]);

	image_in = (int**) calloc(height, sizeof(int*));
	if(!image_in)
	{
		printf("Error: Can't allocate memmory!\n");
		return(1);
	}

	image_out = (int**) calloc(height, sizeof(int*));
	if(!image_out)
	{
		printf("Error: Can't allocate memmory!\n");
		return(1);
	}

	for (j=0; j<height; j++)
	{
		image_in[j] = (int *) calloc(width, sizeof(int));
		if(!image_in[j])
		{
			printf("Error: Can't allocate memmory!\n");
			return(1);
		}

		image_out[j] = (int *) calloc(width, sizeof(int));
		if(!image_out[j])
		{
			printf("Error: Can't allocate memmory!\n");
			return(1);
		}

	}

	if((err=fopen_s(&in, argv[1],"rb"))!=0)
	{
		printf("ERROR: Can't open in_file!\n");
		return(1);
	}

	if((err=fopen_s(&out, argv[2],"wb"))!=0)
	{
		printf("ERROR: Can't open out_file!\n");
		return(1);
	}

	for (j=0; j<height; j++)
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



/********************************************************************/
/* Image Processing begins                                          */
/********************************************************************/

	for (j=0; j<height; j++)
		for (k=0; k<width; k++)
	  {
			image_out[j][k]=255-image_in[j][k];
		}




/********************************************************************/
/* Image Processing ends                                          */
/********************************************************************/

  //HW 7 code
  new_T = 200.0;  // initial threshold
  delta_T = 100.0;  // any big number to get into loop

  while (delta_T > 5.0 || delta_T < -5.0)
  {
    count1 = 0; count2 = 0;
    sum1 = 0.0; sum2 = 0.0;

    for (j=0; j<height; j++)
      for (k=0; k<width; k++)
      {
        if (image_in[j][k] >= new_T)
        {
          sum1 += image_in[j][k];
          count1++;
        }
        else
        {
          sum2 += image_in[j][k];
          count2++;
        }
      }
    
    old_T = new_T;
    new_T = ((sum1/count1) + (sum2/count2)) / 2;
    delta_T = new_T - old_T;
    printf("new threshold = %f \n", new_T);
  }

  // now do thresholding
  for (j=0; j<height; j++)
    for (k=0; k<width; k++)
    {
      image_out[j][k] = (image_in[j][k] >= new_T ? 255 : 0);
    }

	/* save image_out into out_file in RAW format */
	for (j=0; j<height; j++)
		for (k=0; k<width; k++)
	  {
	    if((putc(image_out[j][k],out))==EOF)
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


	for (j=0; j<height; j++)
	{
		free(image_in[j]);
		free(image_out[j]);
	}
	free(image_in);
	free(image_out);

  return 0;
}




/*
Func: histogram_specification
Desc: perform histogram specification on input image
Params: buffer - pointer to input image
        number_of_pixel - total number of pixels in image
        desired_histogram - desired histogram of output image
*/

void histogram_specification(image_ptr buffer, unsigned long number_of_pixels, unsigned long *desired_histogram) {
  float histogram[256];         // image histogram
  float sum_hist[256];          // normalized sum of histogram elements
  float scale_factor;           // scaling factor used to normalize hist
  float difference;             // usede to determine inverse transform
  unsigned long i;              // loop variable
  unsigned long sum;            // sum used to determine sum of hist
  unsigned char inv_hist[256];  // inverse histogram indices
  int j;                        // loop variable
  int min;                      // min difference computing inverse trans

  // clear histogram to 0
  for(i=0; i<256; i++)
    histogram[i]=0;
  
  // calculate histogram
  for(i=0; i<number_of_pixels; i++)
    histogram[buffer[i]]++;
  
  // calculate normalized sum of hist
  sum = 0.0;
  scale_factor = 255.0 / number_of_pixels;
  for(i=0; i <256; i++){
    sum += histogram[i];
    sum_hist[i] = sum * scale_factor;
  }

  // transform image using new sum_hist as LUT
  for(i=0; i<number_of_pixels; i++)
    buffer[i] = (unsigned char) sum_hist[buffer[i]];
  
  // calculate normalized sum of hist for desired histogram
  sum = 0;
  scale_factor = 255.0 / number_of_pixels;
  for(i=0; i<256; i++) {
    sum += desired_histogram[i];
    sum_hist[i] = sum * scale_factor;
  }

  // generate inverse transform
  for(i=0; i<256; i++){
    difference = fabs(i - sum_hist[0]);
    min = 0;
    for(j=0; j<256; j++) {
      if(fabs(i-sum_hist[j]) < difference) {
        difference = fabs(i - sum_hist[j]);
        min = j;
      }
    }
  inv_hist[i] = (unsigned char) min;
  }

  // transform final image using inv_hist
  for(i=0; i<number_of_pixels; i++)
    buffer[i] = inv_hist[buffer[i]];
}
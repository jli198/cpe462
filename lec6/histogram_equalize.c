/* 
Func: histogram_equalize
Desc: histogram equalize input image and write it out
Params: buffer - pointer to image in memory
        number_of_pixels - total number of pixels in image
*/

void histogram_equalize(image_ptr buffer, unsigned long number_of_pixels) {
  unsigned long histogram[256]; // image histogram
  unsigned long sum_hist[256];  // sum of histogram elements
  float scale_factor;           // normalized scale factor
  unsigned long i;              // index variable
  unsigned long sum;            // variable used to increment sum of hist

  // clear histogram to 0
  for(i=0; i<256; i++)
    histogram[i]=0;

  // calculate histogram
  for(i=0; i<number_of_pixels; i++)
    histogram[buffer[i]]++;
  
  // calculate normalized sum of hist
  sum = 0;
  scale_factor = 255.0 / number_of_pixels;
  for(i=0; i<256; i++) {
    sum += histogram[i];
    sum_hist[i] = (sum * scale_factor) + .5;
  }

  // transform image using new sum_hist as LUT
  for(i=0; i<number_of_pixels; i++)
    buffer[i] = sum_hist[buffer[i]];
}
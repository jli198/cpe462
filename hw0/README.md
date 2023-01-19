# Course Information

## Introduction to Signal Processing

* Fourier series (`xfourier`) and Fourier transform (`sigdemo1`)
* 1-D filtering (`filtdem`) and filter design (`filtdemo`)
* Signals and images ( `demo1`)
* Image filtering and filter design (`firdemo`)
* Image processing
  * Edge detection: high-pass (`edgedemo`)
  * Noise reduction: low-pass (`nrfiltdemo`)
  * Compression (`dctdemo`)
  * Enhancement (`imadjdemo`)

## Homework 0 (Do not submit)

* Warmup exercise with MATLAB. Follow the instructions carefully
  * Save following lines in new file named "hw0_1.m" in working directory
  * Open MATLAB and use "cd" command to change working directory in same directory
  * Type "hw0_1" in MATLAB
  * Print out plot
  * Understand all parameters, and find frequency of this signal
  * Change right parameter to double frequency value. Print out new function and its plot
  * Change right parameter to half frequency value. Print out new function and its plot

```matlab
% hw0_1.m
Fs = 256;
t = (1:256) / Fs;
s = sin(2*pi*10*t);
figure(1);
plot(t,s);
w=ones(256,1)*s;
figure(2);
image((w+1*256/2));
truesize;
colormap(gray(256));
```

% to find webcam name + details
% webcamlist

cam
cam = webcam('Webcam Name')
img = snapshot(cam)
image(img)
imwrite(img,"imageName.jpg","Comment","JPEG file")
A = imread('imageName.jpg')
r = img(:,:,1)
g = img(:,:,2)
b = img(:,:,3)
Y = r *.299 + g *.587 + b *.114
imshow(Y)
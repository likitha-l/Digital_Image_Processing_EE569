I = imread('Dogs.jpg');
I1=rgb2gray(I);
figure;
imshow(I1)
impixelinfo();
BW1 = edge(I1,'Canny',[0.15,0.45],1.4);
figure;
imshow(BW1)
%BW2 = edge(I1,'Sobel');
%figure;
%imshow(BW2)

function test_set=readtest()
width=128;
height=128;
test_set=zeros(12,15);
counter=1;
for i=1:12
InputImage=readrawimg("D:\dip\hw4\HW4_image\test\"+i+".raw",height,width);
 figure;
 imshow(InputImage/max(InputImage(:)));
 impixelinfo;
test_set(i,:)=feature_extraction(width,height,InputImage);
end
end
width=239;
height=372;
Imagedata=readrawimg('PCB.raw',height,width);

BW=imbinarize(Imagedata,128);
ComplementImage=imcomplement(BW);
figure;
imshow(Imagedata/max(Imagedata(:)));
   impixelinfo;
figure;
imshow(BW/max(BW(:)));
   impixelinfo;
figure;
imshow(ComplementImage/max(ComplementImage(:)));
   impixelinfo;

BW3 = bwmorph(BW,'shrink',Inf);
figure;
imshow(BW3/max(BW3(:)));
CC = bwconncomp(BW3,8);

numPixels = cellfun(@numel,CC.PixelIdxList);
noofholes=sum(numPixels==1);
disp('No of holes')
disp(noofholes)


BW2 = bwmorph(BW,'remove');
figure;
imshow(BW2/max(BW2(:)));
CC4 = bwconncomp(BW,8);
numPixels1 = cellfun(@numel,CC4.PixelIdxList);
noofsegments=size(numPixels1)
disp('No of line segment')
disp(noofsegments(1,2)/2)






   

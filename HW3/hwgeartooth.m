Imagedata=readrawimg('Geartooth.raw',250,250);
%imshow(Imagedata);
BW=imbinarize(Imagedata,128);
imshow(Imagedata/max(Imagedata(:)));
   impixelinfo;
figure;
imshow(BW/max(BW(:)));
   impixelinfo;

filled = imfill(BW,'holes');
figure;
imshow(filled/max(filled(:)));
impixelinfo;

ComplementImage=imcomplement(BW);
s=strel('disk',3);
h=imdilate(ComplementImage,s);
B = bwmorph(h,'thin',Inf);
figure;
imshow(B/max(B(:)));

[centers1,radii1] = imfindcircles(filled,[20 150])
N=250; M=250; %matrix dimensions
    cx=centers1(1,1); cy=centers1(1,2); %center
    radius=radii1;
    x=(1:N).'; y=1:M;
    binaryMap=(x-cx).^2+(y-cy).^2 <=radius^2;
    figure;
imshow(binaryMap/max(binaryMap(:)));
impixelinfo;

finalImg=filled-binaryMap;
    figure;
imshow(finalImg/max(finalImg(:)));
impixelinfo;
CC3= bwconncomp(finalImg,8);
bwq=bwlabel(finalImg,8);

numPixels = cellfun(@numel,CC3.PixelIdxList);
nooftooth=sum(numPixels>10);% selecting only the bigger connected components
if(nooftooth<12)
    disp('Defective')
    disp('No of missing teeth')
    disp(12-nooftooth)
else
    disp('Normal')
end

total=sum(numPixels>0);
for i=1:total
    mean(CC3.PixelIdxList{i},'all');  
    
end


   

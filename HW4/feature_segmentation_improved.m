height=600;
width=450;
InputImage=readrawimg("D:\dip\hw4\HW4_image\comp.raw",height,width);
figure;
imshow(InputImage/max(InputImage(:)));
impixelinfo
Mean=mean2(InputImage);
MeanImg=InputImage-Mean;

figure;
imshow(MeanImg/max(MeanImg(:)));
impixelinfo;

MeanImgExt=zeros(454,604);

% MeanImgExt(3:130,1)=MeanImg(:,2);
% MeanImgExt(3:130,2)=MeanImg(:,1);
% MeanImgExt(3:130,131)=MeanImg(:,128);
% MeanImgExt(3:130,132)=MeanImg(:,127);
 MeanImgExt(3:452,3:602)=MeanImg(:,:);
% 
% MeanImgExt(1,:)=MeanImgExt(4,:);
% MeanImgExt(2,:)=MeanImgExt(3,:);
% 
% MeanImgExt(131,:)=MeanImgExt(130,:);
% MeanImgExt(132,:)=MeanImgExt(129,:);


L5=[1 4 6 4 1];
E5=[-1 -2 0 2 1];
S5=[-1 0 2 0 -1];
W5=[-1 2 0 -2 1];
R5=[1 -4 6 -4 1];

law_filter{1}=L5;
law_filter{2}=E5;
law_filter{3}=S5;
law_filter{4}=W5;
law_filter{5}=R5;

filter25D={};
count=1;

filteredImage=zeros(width,height);
filteredImg=zeros(width,height,25);

for i=1:5
    for j=1:5
        filter25D{count}=law_filter{i}'*law_filter{j};
        count=count+1;
    end
end

for k=1:25
    for i=3:(width+2)
        for j=3:(height+2)
             image_patch=MeanImgExt(i-2:i+2,j-2:j+2);
             filteredImage(i-2,j-2)=sum((image_patch.*filter25D{k}),'all');
        end
    end
%Different window
%     filteredImageExt=zeros(454,604);
%     filteredImageExt(3:452,3:602)=filteredImage(:,:);
%     for i=3:(width+2)
%        for j=3:(height+2)
%             filteredImg(i-2,j-2,k)=sum(abs(filteredImageExt(i-2:i+2,j-2:j+2)),'all')/(25);
%        end
%     end

%     filteredImageExt=zeros(456,606);
%     filteredImageExt(4:453,4:603)=filteredImage(:,:);
%     for i=4:(width+3)
%        for j=4:(height+3)
%             filteredImg(i-3,j-3,k)=sum(abs(filteredImageExt(i-3:i+3,j-3:j+3)),'all')/(49);
%        end
%     end


% filteredImageExt=zeros(458,608);
% filteredImageExt(5:454,5:604)=filteredImage(:,:);
% for i=5:(width+4)
%     for j=5:(height+4)
%             filteredImg(i-4,j-4,k)=sum(abs(filteredImageExt(i-4:i+4,j-4:j+4)),'all')/(81);
%     end
% end

% filteredImageExt=zeros(460,610);
% filteredImageExt(6:455,6:605)=filteredImage(:,:);
% for i=6:(width+5)
%     for j=6:(height+5)
%             filteredImg(i-5,j-5,k)=sum(abs(filteredImageExt(i-5:i+5,j-5:j+5)),'all')/(121);
%     end
% end

% 
% filteredImageExt=zeros(462,612);
% filteredImageExt(7:456,7:606)=filteredImage(:,:);
% for i=7:(width+6)
%     for j=7:(height+6)
%             filteredImg(i-6,j-6,k)=sqrt(((sum(abs(filteredImageExt(i-6:i+6,j-6:j+6)),'all'))));

%     end
% end

% filteredImageExt=zeros(464,614);
% filteredImageExt(8:457,8:607)=filteredImage(:,:);
% for i=8:(width+7)
%     for j=8:(height+7)
%             filteredImg(i-7,j-7,k)=sqrt(((sum(abs(filteredImageExt(i-7:i+7,j-7:j+7)),'all'))));

%     end
% end

% filteredImageExt=zeros(466,616);
% filteredImageExt(9:458,9:608)=filteredImage(:,:);
% for i=9:(width+8)
%     for j=9:(height+8)
%             filteredImg(i-8,j-8,k)=sqrt(((sum(abs(filteredImageExt(i-8:i+8,j-8:j+8)),'all'))));
%             %filteredImg(i-7,j-7,k)=(((sum(abs(filteredImageExt(i-7:i+7,j-7:j+7)).^2,'all'))))./(169);
%             %reject
%     end
% end

%Window 19x19
filteredImageExt=zeros(468,618);
filteredImageExt(10:459,10:609)=filteredImage(:,:);
for i=10:(width+9)
    for j=10:(height+9)
            filteredImg(i-9,j-9,k)=sqrt(((sum(abs(filteredImageExt(i-9:i+9,j-9:j+9)),'all'))));
    end
end
end


%Selecting 14d feature

filteredImg15=zeros(width,height,14);
L5E5=filteredImg(:,:,1);
filteredImg15(:,:,1)=((filteredImg(:,:,2)+filteredImg(:,:,6))/2)./L5E5;
filteredImg15(:,:,2)=((filteredImg(:,:,3)+filteredImg(:,:,11))/2)./L5E5;
filteredImg15(:,:,3)=((filteredImg(:,:,4)+filteredImg(:,:,16))/2)./L5E5;
filteredImg15(:,:,4)=((filteredImg(:,:,5)+filteredImg(:,:,21))/2)./L5E5;
filteredImg15(:,:,5)=filteredImg(:,:,7)./L5E5;
filteredImg15(:,:,6)=((filteredImg(:,:,8)+filteredImg(:,:,12))/2)./L5E5;
filteredImg15(:,:,7)=((filteredImg(:,:,9)+filteredImg(:,:,17))/2)./L5E5;
filteredImg15(:,:,8)=((filteredImg(:,:,10)+filteredImg(:,:,22))/2)./L5E5;
filteredImg15(:,:,9)=filteredImg(:,:,13)./L5E5;
filteredImg15(:,:,10)=((filteredImg(:,:,14)+filteredImg(:,:,18))/2)./L5E5;
filteredImg15(:,:,11)=((filteredImg(:,:,15)+filteredImg(:,:,23))/2)./L5E5;
filteredImg15(:,:,12)=filteredImg(:,:,19)./L5E5;
filteredImg15(:,:,13)=((filteredImg(:,:,20)+filteredImg(:,:,24))/2)./L5E5;
filteredImg15(:,:,14)=filteredImg(:,:,25)./L5E5;


kmeansInput=zeros(width*height,14);

for k=1:14
    counter=1;
    for i=1:(width)
        for j=1:(height)
            kmeansInput(counter,k)=filteredImg15(i,j,k);
            counter=counter+1;
        end
    end
end

%In order to use pca uncomment this section
% [coeff,score,latent,tsquared,explained] = pca(kmeansInput);
% disp('The percentage of total variance explained by each principal component')
% disp(explained)
% %applying kmeans on three principal components
% [idx,C]=kmeans(score(:,1:3),6);



%apply k means algorithm to 14D feature image
[idx,C] = kmeans(kmeansInput,6);

counter=1;
for i=1:(width)
     for j=1:(height)
            kmeansOutput(i,j)=idx(counter,1);
            counter=counter+1;
     end
end

kmeansOutput(kmeansOutput==1)=0;
kmeansOutput(kmeansOutput==2)=51;
kmeansOutput(kmeansOutput==3)=102;
kmeansOutput(kmeansOutput==4)=153;
kmeansOutput(kmeansOutput==5)=204;
kmeansOutput(kmeansOutput==6)=255;

figure;
imshow(kmeansOutput/max(kmeansOutput(:)));
impixelinfo

se = strel('disk',7);
afterOpening = imclose(kmeansOutput,se);
figure;
imshow(afterOpening/max(afterOpening(:)));
title('After Closing');
impixelinfo

se = strel('disk',5);
afterOpening = imopen(afterOpening,se);
figure;
imshow(afterOpening/max(afterOpening(:)));
title('After Opening');
impixelinfo












             


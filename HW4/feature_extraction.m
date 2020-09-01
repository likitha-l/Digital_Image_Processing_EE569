function G=feature_extraction(width,height,InputImage)

Mean=mean2(InputImage);
MeanImg=InputImage-Mean;

%  figure;
%  imshow(InputImage/max(InputImage(:)));
%  impixelinfo;

MeanImgExt=zeros(132,132);

MeanImgExt(3:130,3:130)=MeanImg(:,:);



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
filteredImg=zeros(1,25);

for i=1:5
    for j=1:5
        filter25D{count}=law_filter{i}'*law_filter{j};
        count=count+1;
    end
end

for k=1:25
    for i=3:(130)
        for j=3:(130)
             image_patch=MeanImgExt(i-2:i+2,j-2:j+2);
             filteredImage(i-2,j-2)=sum((image_patch.*filter25D{k}),'all');
        end
    end
    filtered2D{k}=imfilter(MeanImgExt,filter25D{k});
    hh{k}=filteredImage;
    filteredImg(k)=(sum(abs(filteredImage),'all')/(width*height));
    %filteredImg(k)=(sum(abs(filteredImage).^2,'all')/(width*height));
    %filteredImg(k)=sqrt((sum(abs(filteredImage),'all')));
end

%Selecting 15d feature


filteredImg15=zeros(1,15);
filteredImg15(1)=filteredImg(1);
filteredImg15(2)=mean(filteredImg([2 6]));
filteredImg15(3)=mean(filteredImg([3 11]));
filteredImg15(4)=mean(filteredImg([4 16]));
filteredImg15(5)=mean(filteredImg([5 21]));
filteredImg15(6)=filteredImg(7);
filteredImg15(7)=mean(filteredImg([8 12]));
filteredImg15(8)=mean(filteredImg([9 17]));
filteredImg15(9)=mean(filteredImg([10 22]));
filteredImg15(10)=filteredImg(13);
filteredImg15(11)=mean(filteredImg([14 18]));
filteredImg15(12)=mean(filteredImg([15 23]));
filteredImg15(13)=filteredImg(19);
filteredImg15(14)=mean(filteredImg([20 24]));
filteredImg15(15)=filteredImg(25);

G=filteredImg15;

end


             


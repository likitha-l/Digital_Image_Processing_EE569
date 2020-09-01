InputImage=readrawimg('stars.raw',640,480);
figure;
imshow(InputImage/max(InputImage(:)));
   impixelinfo;
width=480;
height=640;
BinaryInput=zeros(width,height);

BinaryInput(InputImage>30)=1;
figure;
imshow(BinaryInput/max(BinaryInput(:)));
   impixelinfo;
%edges = unique(InputImage);
%[counts,bins] = histcounts(InputImage(:), edges);
%histogram(InputImage(:))
S=zeros(100000,2);
p=1;
count=2;
for i=2:(width-1)
    for j=2:(height-1)
        if(BinaryInput(i,j)~=0)
            flag=(BinaryInput(i-1,j-1)==0)&&(BinaryInput(i-1,j)==0)&&(BinaryInput(i-1,j+1)==0)&&(BinaryInput(i,j-1)==0);
            if (flag)
                BinaryInput(i,j)=count;
                count=count+1;
            end
            if((flag~=1)&&((BinaryInput(i-1,j-1)~=0)||(BinaryInput(i-1,j)~=0)||(BinaryInput(i-1,j+1)~=0)||(BinaryInput(i,j-1)~=0)))
                neighbourpixels=[BinaryInput(i-1,j-1) BinaryInput(i-1,j) BinaryInput(i-1,j+1) BinaryInput(i,j-1)];
                %disp(neighbourpixels)
                minvalue=min(neighbourpixels(neighbourpixels>0));
                BinaryInput(i,j)=minvalue;
                if(sum(neighbourpixels>0)>=2)
                    if(BinaryInput(i-1,j-1)~=0)
                        S(p,1)=minvalue;
                        S(p,2)=BinaryInput(i-1,j-1);
                        p=p+1;
                    end
                    if(BinaryInput(i-1,j)~=0)
                        S(p,1)=minvalue;
                        S(p,2)=BinaryInput(i-1,j);
                        p=p+1;
                    end
                    if(BinaryInput(i-1,j+1)~=0)
                        S(p,1)=minvalue;
                        S(p,2)=BinaryInput(i-1,j+1);
                        p=p+1;
                    end
                    if(BinaryInput(i,j-1)~=0)
                        S(p,1)=minvalue;
                        S(p,2)=BinaryInput(i,j-1);
                        p=p+1;
                    end
                end  
            end
        end
    end
end
uniqueset=unique(S,'rows'); %equivalence table
for i=2:width
    for j=2:height
        BinaryInput(i,j)=min(uniqueset((uniqueset(:,2)==BinaryInput(i,j)),1));
    end
end

noofstars=size(unique(BinaryInput(BinaryInput>0)));
disp("No of stars")
disp(noofstars(1,1)-1)

edges = unique(BinaryInput(BinaryInput>0));
counts = histcounts(BinaryInput(BinaryInput>0), edges);
noofdiffsize=size(unique(counts));
disp("No of different star sizes")
disp(noofdiffsize(1,2))

%coun = histcounts(counts, unique(counts));
%figure;
%histogram(coun)

figure;
histogram(counts)
title('Histogram of star size with respect to frequency');
xlabel('Star Size');
ylabel('Frequency');

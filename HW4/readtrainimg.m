function train_set=readtrainimg()
width=128;
height=128;
train_set=zeros(36,15);
counter=1;
for i=1:9
InputImage=readrawimg("D:\dip\hw4\HW4_image\train\blanket"+i+".raw",height,width);
train_set(counter,:)=feature_extraction(width,height,InputImage);
counter=counter+1;
end
for i=1:9
InputImage=readrawimg("D:\dip\hw4\HW4_image\train\brick"+i+".raw",height,width);
train_set(counter,:)=feature_extraction(width,height,InputImage);
counter=counter+1;
end
for i=1:9
InputImage=readrawimg("D:\dip\hw4\HW4_image\train\grass"+i+".raw",height,width);
train_set(counter,:)=feature_extraction(width,height,InputImage);
counter=counter+1;
end
for i=1:9
InputImage=readrawimg("D:\dip\hw4\HW4_image\train\rice"+i+".raw",height,width);
train_set(counter,:)=feature_extraction(width,height,InputImage);
counter=counter+1;
end
end


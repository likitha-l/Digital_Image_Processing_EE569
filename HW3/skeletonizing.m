width=558;
height=558;
InputImage=readrawimg('maze.raw',height,width);
figure;
imshow(InputImage/max(InputImage(:)));
impixelinfo;


unconditional_mask=[0 1 0 0 1 1 0 0 0;
                    0 1 0 1 1 0 0 0 0;
                    0 0 0 1 1 0 0 1 0;
                    0 0 0 0 1 1 0 1 0;
                    
                    0 0 1 0 1 1 0 0 1;
                    1 1 1 0 1 0 0 0 0;
                    1 0 0 1 1 0 1 0 0;
                    0 0 0 0 1 0 1 1 1;                
              
                    1 1 1 0 1 1 0 0 0;
                    0 1 1 0 1 1 0 0 1;
                    1 1 1 1 1 0 0 0 0;
                    1 1 0 1 1 0 1 0 0;
                    1 0 0 1 1 0 1 1 0;
                    0 0 0 1 1 0 1 1 1;
                    0 0 0 0 1 1 1 1 1;
                    0 0 1 0 1 1 0 1 1;
                    
                    1 1 1 0 1 1 0 0 1;
                    1 1 1 1 1 0 1 0 0;
                    1 0 0 1 1 0 1 1 1;
                    0 0 1 0 1 1 1 1 1;
                    
                    0 1 1 0 1 1 0 1 1;
                    1 1 1 1 1 1 0 0 0;
                    1 1 0 1 1 0 1 1 0;
                    0 0 0 1 1 1 1 1 1;
                    
                    1 1 1 0 1 1 0 1 1;
                    0 1 1 0 1 1 1 1 1;
                    1 1 1 1 1 1 1 0 0;
                    1 1 1 1 1 1 0 0 1;
                    1 1 1 1 1 0 1 1 0;
                    1 1 0 1 1 0 1 1 1;
                    1 0 0 1 1 1 1 1 1;
                    0 0 1 1 1 1 1 1 1;
                    
                    1 1 1 0 1 1 1 1 1;
                    1 1 1 1 1 1 1 0 1;
                    1 1 1 1 1 0 1 1 1;
                    1 0 1 1 1 1 1 1 1;
                    
                    1 1 1 1 1 1 0 1 1;
                    1 1 1 1 1 1 1 1 0;
                    1 1 0 1 1 1 1 1 1;
                    0 1 1 1 1 1 1 1 1; ];
                
Inputtostage1=zeros(width,height);
Inputtostage1(InputImage>30)=1;

flag=1;
iteration=1;

while(flag)
M=zeros(width,height);
for i=2:(width-1)
    for j=2:(height-1)
      if(Inputtostage1(i,j)~=0)
        box=[Inputtostage1(i-1,j-1) Inputtostage1(i-1,j) Inputtostage1(i-1,j+1) Inputtostage1(i,j-1) Inputtostage1(i,j) Inputtostage1(i,j+1) Inputtostage1(i+1,j-1) Inputtostage1(i+1,j) Inputtostage1(i+1,j+1)];
        if(ismember(box,unconditional_mask,'rows'))
           M(i,j)=1;
        end
      end
    end
end


%figure;
%imshow(M/max(M(:)));

result=secondstageskeleton(M,width,height);

resultingimg=Inputtostage1&(imcomplement(M)|result);
%resultingimg=Inputtostage1-M;
if(Inputtostage1==resultingimg)
    flag=0;
end
Inputtostage1=resultingimg;
iteration=iteration+1;
disp(iteration)
end

figure;
imshow(resultingimg/max(resultingimg(:)));
            
        

               
                    
                    
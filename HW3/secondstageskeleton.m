function SecondStageOutput=secondstageskeleton(M,width,height)
%A=2, B=3,C=4,D=5 in the mask
conditional_mask=[0 0 0 0 1 0 0 0 1;
                  0 0 0 0 1 0 1 0 0;
                  0 0 1 0 1 0 0 0 0;
                  1 0 0 0 1 0 0 0 0;
                  
                  0 0 0 0 1 0 0 1 0;
                  0 0 0 0 1 1 0 0 0;
                  0 0 0 1 1 0 0 0 0;
                  0 1 0 0 1 0 0 0 0;
                  
                  0 1 0 0 1 1 0 0 0;
                  0 1 0 1 1 0 0 0 0;
                  0 0 0 0 1 1 0 1 0;
                  0 0 0 1 1 0 0 1 0;
                  
                  1 1 5 1 1 5 5 5 5;
                  5 5 5 5 1 1 5 1 1;
                  
                  5 1 5 1 1 1 5 5 5;
                  5 1 5 1 1 5 5 1 5;
                  5 5 5 1 1 1 5 1 5;
                  5 1 5 5 1 1 5 1 5;
                  
                  1 5 1 5 1 5 2 3 4;
                  1 5 4 5 1 3 1 5 2;
                  4 3 2 5 1 5 1 5 1;
                  2 5 1 3 1 5 4 5 1;
                  
                  5 1 0 0 1 1 1 0 5;
                  0 1 5 1 1 0 5 0 1;
                  5 0 1 1 1 0 0 1 5;
                  1 0 5 0 1 1 5 1 0;];

SecondStageOutput=zeros(width,height);

                  
for i=2:(width-1)
    for j=2:(height-1)
        for k=1:26
          if(M(i,j)~=0)
            mask=zeros(1,9);
            neigh=[M(i-1,j-1) M(i-1,j) M(i-1,j+1) M(i,j-1) M(i,j) M(i,j+1) M(i+1,j-1) M(i+1,j) M(i+1,j+1)];
            if(ismember(2,conditional_mask(k,:))&&ismember(3,conditional_mask(k,:)))
                if(neigh(conditional_mask(k,:)==2)||neigh(conditional_mask(k,:)==3))
                    mask(conditional_mask(k,:)==2)=1;
                    mask(conditional_mask(k,:)==3)=1;
                end
            end
            if(ismember(2,conditional_mask(k,:))&&ismember(3,conditional_mask(k,:))&&ismember(4,conditional_mask(k,:)))
                if(neigh(conditional_mask(k,:)==2)||neigh(conditional_mask(k,:)==3)||neigh(conditional_mask(k,:)==4))
                    mask(conditional_mask(k,:)==2)=1;
                    mask(conditional_mask(k,:)==3)=1;
                    mask(conditional_mask(k,:)==4)=1;                    
                end
            end
          
          if(ismember(5,conditional_mask(k,:)))
               mask(conditional_mask(k,:)==5)=1;
          end
         
          mask(neigh==conditional_mask(k,:))=1;  
          if(sum(mask)==9)
                    SecondStageOutput(i,j)=1;
          end
         end
       end
    end
end

%figure;
%imshow(SecondStageOutput/max(SecondStageOutput(:)));

end
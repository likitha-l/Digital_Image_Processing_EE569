    feature_matrix=readtrainimg();
    test_matrix=readtest();
    meanoffeature=mean(feature_matrix);
    a=zeros([size(feature_matrix)]);
    for i=1:15
        a(:,i)=feature_matrix(:,i)-meanoffeature(i);
    end
    
   [U,S,V]=svds(a);
   Y=U*S*V';
   VR=V(:,1:3);
   YR=feature_matrix*VR;
   figure;
   scatter3(YR(:,1),YR(:,2),YR(:,3))
   
   %Testing Images
    meanoffeature=mean(test_matrix);
    a=zeros([size(test_matrix)]);
    for i=1:15
        a(:,i)=test_matrix(:,i)-meanoffeature(i);
    end
    
   [U,S,V]=svds(a);
   Y=U*S*V';
   VR=V(:,1:3);
   YR=test_matrix*VR;
   figure;
   scatter3(YR(:,1),YR(:,2),YR(:,3))

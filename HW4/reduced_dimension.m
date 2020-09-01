test_matrix=readtest();
feature_matrix=readtrainimg();

%Reducing the dimension to 3D
[coeff,score,latent,tsquared,explained] = pca(feature_matrix);
disp('The percentage of total variance explained by each principal component')
disp(explained)
%applying kmeans on three principal components
[idx,C]=kmeans(score(:,1:3),4);
figure;
scatter3(score(:,1),score(:,2),score(:,3),[],idx,'filled')


%Reducing the dimension to 3D
[coeff,score,latent,tsquared,explained] = pca(test_matrix);
disp('The percentage of total variance explained by each principal component')
disp(explained)
%applying kmeans on three principal components
[idx,C]=kmeans(score(:,1:3),4);
figure;
scatter3(score(:,1),score(:,2),score(:,3),[],idx,'filled')
figure;
str=string(1:12)
textscatter3(score(:,1),score(:,2),score(:,3),str);
%textscatter3(score(:,1:3),str,'ColorData',idx);
disp('Cluster 1: Following Images')
disp(find(idx==1))
disp('Cluster 2: Following Images')
disp(find(idx==2))
disp('Cluster 3: Following Images')
disp(find(idx==3))
disp('Cluster 4: Following Images')
disp(find(idx==4))


% %checking accuracy when pca is applied
%  test_labels=[3 1 1 2 4 3 2 4 4 2 1 3]';

%  
% applying kmeans on 25D
[idx_all,C_all]=kmeans(test_matrix,4);
disp('Cluster 1: Following Images')
disp(find(idx_all==1))
disp('Cluster 2: Following Images')
disp(find(idx_all==2))
disp('Cluster 3: Following Images')
disp(find(idx_all==3))
disp('Cluster 4: Following Images')
disp(find(idx_all==4))

    
 
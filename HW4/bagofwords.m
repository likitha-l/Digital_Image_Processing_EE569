
I1 = imread("D:\dip\hw4\HW4_image\Husky_3.jpg") ;
I2 = imread("D:\dip\hw4\HW4_image\Husky_2.jpg") ;
I3 = imread("D:\dip\hw4\HW4_image\Husky_1.jpg") ;
I4 = imread("D:\dip\hw4\HW4_image\Puppy_1.jpg") ;

% --------------------------------------------------------------------
%                      Extract features
% --------------------------------------------------------------------

[f1,d1] = vl_sift(im2single(rgb2gray(I1))) ;
[f2,d2] = vl_sift(im2single(rgb2gray(I2))) ;
[f3,d3] = vl_sift(im2single(rgb2gray(I3))) ;
[f4,d4] = vl_sift(im2single(rgb2gray(I4))) ;

data=d1;
numClusters=8;
[centers1, assignments1] = vl_kmeans(im2double(d1), numClusters);
[centers2, assignments2] = vl_kmeans(im2double(d2), numClusters);
[centers3, assignments3] = vl_kmeans(im2double(d3), numClusters);
[centers4, assignments4] = vl_kmeans(im2double(d4), numClusters);



figure;
histogram(assignments1,'Normalization','probability');
title('Husky 3')

figure;
histogram(assignments2,'Normalization','probability');
title('Husky 2')

figure;
histogram(assignments3,'Normalization','probability');
title('Husky 1')

figure;
histogram(assignments4,'Normalization','probability');
title('Puppy 1')
% 
% 

[N1,edges1] = histcounts(assignments1,8);
[N2,edges2] = histcounts(assignments2,8);
[N3,edges3] = histcounts(assignments3,8);
[N4,edges4] = histcounts(assignments4,8);

diff1=norm(abs(sort(N1/size(assignments1,2))-sort(N2/size(assignments2,2))));

diff2=norm(abs(sort(N1/size(assignments1,2))-sort(N3/size(assignments3,2))));


diff3=norm(abs(sort(N1/size(assignments1,2))-sort(N4/size(assignments4,2))));


 [D,I] = pdist2(centers1',centers2','euclidean','Smallest',8)
 x=centers2(:,2);
 
 kdtree = vl_kdtreebuild(centers1) ;
 [index1, distance1] = vl_kdtreequery(kdtree, centers1, centers2(:,1)) ;
 [index2, distance2] = vl_kdtreequery(kdtree, centers1, centers2(:,2)) ;
 [index3, distance3] = vl_kdtreequery(kdtree, centers1, centers2(:,3)) ;
 [index4, distance4] = vl_kdtreequery(kdtree, centers1,centers2(:,4)) ;
 [index5, distance5] = vl_kdtreequery(kdtree, centers1, centers2(:,5)) ;
 [index6, distance6] = vl_kdtreequery(kdtree, centers1, centers2(:,6)) ;
 [index7, distance7] = vl_kdtreequery(kdtree, centers1, centers2(:,7)) ;
 [index8, distance8] = vl_kdtreequery(kdtree, centers1, centers2(:,8)) ;
 
 [~, k] = min(vl_alldist(x, centers1)) ;

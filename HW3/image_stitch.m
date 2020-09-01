LeftImage=imread('l.jpg');
boxImage=rgb2gray(LeftImage);
figure;
imshow(LeftImage);
title('Left Image ');

MiddleImage = imread('m.jpg');
sceneImage=rgb2gray(MiddleImage);
figure;
imshow(MiddleImage);
title('Middle Image');

RightImage = imread('r.jpg');
rImage=rgb2gray(RightImage);
figure;
imshow(RightImage);
title('Right Image ');

boxPoints = detectSURFFeatures(boxImage);
scenePoints = detectSURFFeatures(sceneImage);
rightimagepoints= detectSURFFeatures(rImage);

figure;
imshow(LeftImage);
title('100 Strongest Feature Points from Box Image');
hold on;
plot(selectStrongest(boxPoints, 3));

figure;
imshow(MiddleImage);
title('300 Strongest Feature Points from Scene Image');
hold on;
plot(selectStrongest(scenePoints, 3));

figure;
imshow(RightImage);
title('300 Strongest Feature Points from Scene Image');
hold on;
plot(selectStrongest(rightimagepoints, 3));

[boxFeatures, boxPoints] = extractFeatures(boxImage, boxPoints);
[sceneFeatures, scenePoints] = extractFeatures(sceneImage, scenePoints);
[rFeatures, rightimagepoints] = extractFeatures(rImage, rightimagepoints);



boxPairs = matchFeatures(boxFeatures, sceneFeatures);
boxPairs2 = matchFeatures(sceneFeatures,rFeatures);

matchedBoxPoints = boxPoints(boxPairs(:, 1), :).Location;
matchedScenePoints = scenePoints(boxPairs(:, 2), :).Location;
figure;
showMatchedFeatures(LeftImage, MiddleImage, matchedBoxPoints, ...
    matchedScenePoints, 'montage');
title('Putatively Matched Points (Including Outliers)');

matchedBoxPoints1 = scenePoints(boxPairs2(:, 1), :).Location;
matchedScenePoints1 = rightimagepoints(boxPairs2(:, 2), :).Location;
figure;
showMatchedFeatures(MiddleImage, RightImage, matchedBoxPoints1, ...
    matchedScenePoints1, 'montage');
title('Putatively Matched Points (Including Outliers)');


%%%%%%%%%%%%geo%%%%%%%%%%

gte=vision.GeometricTransformEstimator;
gte.Method= 'Random Sample consensus (RANSAC)';
[tform_matrix,inlierIdx]= step(gte,matchedBoxPoints,matchedScenePoints);
inlierBoxPoints= matchedBoxPoints(inlierIdx,:);
inlierScenePoints=matchedScenePoints(inlierIdx,:);

gte=vision.GeometricTransformEstimator;
gte.Method= 'Random Sample consensus (RANSAC)';
[tform_matrix,inlierIdx]= step(gte,matchedBoxPoints1,matchedScenePoints1);
inlierBoxPoints1= matchedBoxPoints1(inlierIdx,:);
inlierScenePoints1=matchedScenePoints1(inlierIdx,:);


figure;
showMatchedFeatures(LeftImage, MiddleImage, inlierBoxPoints, ...
    inlierScenePoints, 'montage');
title('Matched Points (Inliers Only)');

figure;
showMatchedFeatures(MiddleImage,RightImage, inlierBoxPoints1, ...
    inlierScenePoints1, 'montage');
title('Matched Points (Inliers Only)');
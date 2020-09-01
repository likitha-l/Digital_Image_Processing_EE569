%feature_matrix=readtrainimg();
%test_matrix=readtest();
[coeff,score,latent,tsquared,explained] = pca(feature_matrix);
disp('The percentage of total variance explained by each principal component')
disp(explained)

%Random Forest Classifier
nTrees=500;

%training the classifier
Tr=score(:,1:3);
train_label=[1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4]';
B = TreeBagger(nTrees,Tr,train_label, 'Method', 'classification'); 
Ts=test_matrix;

%testing
[coeff_test,score_test,latent_test,tsquared_test,explained_test] = pca(Ts);

test_label=[3 1 1 2 4 3 2 4 4 2 1 3]';
predtest_label = B.predict(score_test(:,1:3));  % Predictions is a char though. We want it to be a number.
c = str2double(predtest_label);
accuracy_RF=sum(c==test_label)/length(test_label);

disp("Random Forest Classifier Accuracy:")
disp(accuracy_RF*100)


%SVM Classifier
t = templateSVM('Standardize',true,'SaveSupportVectors',true);
%SVMModel = fitcecoc(Tr,train_label,'FitPosterior',true);
SVMModel = fitcecoc(Tr,train_label,'Learners',t,'FitPosterior',true);
[label_testSVM,score] = predict(SVMModel,score_test(:,1:3));

accuracy_SVM=sum(label_testSVM==test_label)/length(test_label);
%disp(SVMModel.ClassNames)


disp("SVM Classifier Accuracy:")
disp(accuracy_SVM*100)

accuracy_SVM_gaussian=svm_gaussian(Tr,train_label,test_label,score_test);
disp("SVM Classifier Gaussian Accuracy:")
disp(accuracy_SVM_gaussian*100)


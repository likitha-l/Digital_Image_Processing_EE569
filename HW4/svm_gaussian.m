function accuracy_SVM=svm_gaussian(Tr,train_label,test_label,score_test)
t = templateSVM('Standardize',true,'KernelFunction','gaussian');
SVMModel = fitcecoc(Tr,train_label,'Learners',t,'FitPosterior',true);
[label_testSVM,score] = predict(SVMModel,score_test(:,1:3));
accuracy_SVM=sum(label_testSVM==test_label)/length(test_label);


disp("SVM Classifier Gaussian Accuracy:")
disp(accuracy_SVM*100)
end

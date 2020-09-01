data=csvread('histogramresults.csv'); % reading csv file 
x=data(:,1); % reading its first column
y=data(:,2); % reading its second column of csv file
z=data(:,3);
a=data(:,4);
figure;
plot(x,y);title('Histogram of R channel');
figure;
plot(x,z);title('Histogram of G channel');
figure;
plot(x,a);title('Histogram of B channel');
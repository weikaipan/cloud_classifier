clear all
close all

file = fopen('/home/C.b01209041/matlab_read/DARDAR/one_file_test/20130610.txt' , 'r');
format = '%lf %lf %lf %lf %lf';
sizeA = [5 inf];
raw_data = fscanf(file, format, sizeA);
raw_data = raw_data';

figure(1)
hist(raw_data(:,1), 400);

figure(2)
hist(raw_data(:,5));

figure(3)
plot(raw_data(:,1), raw_data(:,5));

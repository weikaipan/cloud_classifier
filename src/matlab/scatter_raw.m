clear all
close all
%read file
%for i = 26193:26404;
%s = 'data/data_2011*';

file = fopen('/home/C.b01209041/matlab_read/DARDAR/one_file_test/26194.txt' , 'r');
file2 = fopen('/home/C.b01209041/matlab_read/DARDAR/one_file_test/a26194.txt' , 'r');
file3 = fopen('/home/C.b01209041/matlab_read/DARDAR/one_file_test/log26194.txt' , 'r');

%if file == -1
%continue;

%else
%file1 = fopen(s, 'r');
format = '%lf %lf %lf %d';
format1 = '%d %d %d';
sizeA = [4 inf];
sizeB = [3 inf];
raw_data = fscanf(file, format, sizeA);
raw = fscanf(file2, format1, sizeB);
log_raw = fscanf(file3, format, sizeA);
%center = fscanf(file2, format, sizeA);
%ind = fscanf(file2, format, sizeA);

%csize = fscanf(file1, format1);
%x = 1:max(csize);
%y = zeros(max(csize));
%for i = 1:7837;
%	y(csize(i)) = y(csize(i)) + csize(i);
%end
%scatter plot
raw_data = raw_data';
log_raw = log_raw';
raw = raw';
%center = center';
%ind = ind'
pp = double(zeros(4,size(log_raw,1), 3));
p=1;
q=1;
r=1;
s=1;
for i=1:size(log_raw,1)
	if log_raw(i,4) == 0
		for l=1:3
		  pp(1,p, l) = log_raw(i,l);
		end
		p = p+1;
	end
	if log_raw(i,4) == 1
		for o=1:3
		  pp(2,q, o) = log_raw(i,o);
		end
		q = q+1;
	end
	if log_raw(i,4) == 2
		for n=1:3
		  pp(3,r, n) = log_raw(i,n);
		end
		r = r+1;
	end
	if log_raw(i,4) == 3
		for m=1:3
		  pp(4,s, m) = log_raw(i,m);
		end
		s = s+1;
	end
end
%dataset = vertcat(dataset, raw_data);


%N = max(ind);

figure(1)
%scatter((raw_data(:,3).^(1/2))./raw_data(:,1), raw_data(:,2), 'filled');

scatter3(pp(1,:,1), pp(1,:,2), pp(1,:,3),'filled');
hold on
scatter3(pp(2,:,1), pp(2,:,2), pp(2,:,3),'filled');
scatter3(pp(3,:,1), pp(3,:,2), pp(3,:,3),'filled');
scatter3(pp(4,:,1), pp(4,:,2), pp(4,:,3),'filled');
title('201126194 ( log(log+1)+1) )');
xlabel('cloud thickness');
ylabel('cloud top');
zlabel('cloud size');
h = figure(1)
saveas(h, '../../jpg/log2011261943c.jpg');

figure(2)
subplot(3,1,1)
hist(raw_data(:,1));
title('Normalized');
xlabel('thickness');
ylabel('clouds');
subplot(3,1,2)
hist(raw_data(:,2));
xlabel('top');
ylabel('clouds');
subplot(3,1,3)
hist(raw_data(:,3));
xlabel('size');
ylabel('clouds');
h = figure(2)
saveas(h, '../../jpg/normalized_26194_histogram.jpg');


figure(3)
subplot(3,1,1)
hist(raw(:,1));
title('Raw');
xlabel('thickness');
ylabel('clouds');
subplot(3,1,2)
hist(raw(:,2));
xlabel('top');
ylabel('clouds');
subplot(3,1,3)
hist(raw(:,3));
xlabel('size');
ylabel('clouds');
h = figure(3)
saveas(h, '../../jpg/raw_26194_histogram.jpg');

figure(4)
subplot(3,1,1)
hist(log10(log10(raw(:,1)+1)+1));
title('Raw( log(log(raw+1)+1) )');
xlabel('thickness');
ylabel('clouds');
subplot(3,1,2)
hist(log10(log10(raw(:,2)+1)+1));
xlabel('top');
ylabel('clouds');
subplot(3,1,3)
hist(log10(log10(raw(:,3)+1)+1));
xlabel('size');
ylabel('clouds');
h = figure(4)
saveas(h, '../../jpg/rawloglog1_26194_histogram.jpg');


figure(5)
subplot(3,1,1)
hist(log10(raw_data(:,1)+1));
title('Normalized( log(raw+1) )');
xlabel('thickness');
ylabel('clouds');
subplot(3,1,2)
hist(log10(raw_data(:,2)+1));
xlabel('top');
ylabel('clouds');
subplot(3,1,3)
hist(log10(raw_data(:,3)+1));
xlabel('size');
ylabel('clouds');
h = figure(5)
saveas(h, '../../jpg/normalizedlog1_26194_histogram.jpg');


figure(6)
scatter3(log10(log10(raw(:,1)+1)+1), log10(log10(raw(:,2)+1)+1), log10(log10(raw(:,3)+1)+1),'filled');
title('201126194 log( log(raw+1)+1 )');
xlabel('cloud thickness');
ylabel('cloud top');
zlabel('cloud size');
h = figure(6)
saveas(h, '../../jpg/2011261943loglogr1.jpg');

figure(7)
scatter(log10(log10(raw(:,1)+1)+1), log10(log10(raw(:,3)+1)+1), 'filled')
title('201126194 thick v.s. size log(log(x+1))');
xlabel('cloud thickness');
ylabel('cloud size');
h = figure(7)
saveas(h, '../../jpg/2011261943thicksizelog.jpg');

figure(8)
scatter(log10(log10(raw(:,2)+1)+1), log10(log10(raw(:,3)+1)+1), 'filled')
title('201126194 top v.s. size log(log(x+1))');
xlabel('cloud top');
ylabel('cloud size');
h = figure(8)
saveas(h, '../../jpg/2011261943sizetoplog.jpg');

figure(9)
scatter(log10(log10(raw(:,1)+1)+1), log10(log10(raw(:,2)+1)+1), 'filled')
title('201126194 thick v.s. top log(log(x+1))');
xlabel('cloud top');
ylabel('cloud thickness');
h = figure(9)
saveas(h, '../../jpg/2011261943thicktoplog.jpg');

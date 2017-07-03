clear all
close all
%read file
%for i = 26193:26404;
%s = 'data/data_2011*';

%file = fopen(strcat(s, num2str(i), '.txt'), 'r');
file = fopen('/home/C.b01209041/matlab_read/DARDAR/data/3center_all.txt', 'r');
file2 = fopen('/home/C.b01209041/matlab_read/DARDAR/data/3center_ind.txt', 'r');
%file = fopen('/home/C.b01209041/matlab_read/DARDAR/data/individual_granule/data_2011*26241.txt', 'r');

%if file == -1
%continue;

%else
%file1 = fopen(s, 'r');
format = '%lf %lf %lf';
%format1 = '%d';
sizeA = [3 inf];
raw_data = fscanf(file, format, sizeA);
ind = fscanf(file2, format, sizeA);

%csize = fscanf(file1, format1);
%x = 1:max(csize);
%y = zeros(max(csize));
%for i = 1:7837;
%	y(csize(i)) = y(csize(i)) + csize(i);
%end
%scatter plot
raw_data = raw_data';
ind = ind'


%dataset = vertcat(dataset, raw_data);

raw_data = raw_data(~any(isnan(raw_data) | isinf(raw_data), 2), :);

ind = ind(~any(isnan(ind) | isinf(ind), 2), :);
M = max(raw_data);
N = max(ind);

file5 = fopen('/home/C.b01209041/matlab_read/DARDAR/data/c3center_all.txt', 'wt');
file6 = fopen('/home/C.b01209041/matlab_read/DARDAR/data/c3center_ind.txt', 'wt');
fprintf(file5, '%lf ', raw_data);
ind = ind.*ones(size(ind,1), size(ind,2))
for i=1:size(ind, 1);
  for j=1:size(ind, 2);
    fprintf(file6, '%f ', ind(i,j));
  end
fprintf(file6,'\n');
end

fclose(file5);
fclose(file6);
fclose(file);
fclose(file2);
%end
%end

%figure(1)
%scatter((raw_data(:,3).^(1/2))./raw_data(:,1), raw_data(:,2), 'filled');
%scatter3(raw_data(:,1), raw_data(:,2), raw_data(:,3),'filled');
%hold on
%scatter3(ind(:,1), ind(:,2), ind(:,3), 'filled');
%title('cloud base v.s. thickness v.s. size(unit:differences between adjacent grids)');
%ylabel('cloud top');
%xlabel('cloud sqrt(size)/thick');
%title('Cluster centroid distribution');
%xlabel('cloud thickness');
%ylabel('cloud top');
%zlabel('cloud size');
%h = figure(1)
%saveas(h, '../jpg/total_sample3.jpg');

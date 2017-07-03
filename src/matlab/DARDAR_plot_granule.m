clf;

% Input/output file names templates
%                     1       10        20        30        40        50        606for t = 26245:26432;

%2006 : 00702~00926, 2007:  04918~06193 2008 :  08922~14250  2009: 14253~19209
%2010 : 19797~24860, 2011: 26193~26432, 2012: 32170~32852, 2013: 36844~38081  
%2014 : 42474~42594, 2015 48046~48561: 
%dlog = fopen('../../log/log_image.txt', 'a');

% TARGET 2011/48479~48
for k = 2008:2008;
switch k   
case 2006 
	t1 = 00702;  t2 = 00926;
case 2007 
	t1 = 04970; t2 = 06193;
case 2008 
	t1 = 09406; t2 = 09521;
case 2009 
	t1 = 14253; t2 = 19209;
case 2010 
	t1= 19797; t2 = 24860;
case 2011 
	t1 = 26193; t2 = 26420;
case 2012 
	t1 = 32170; t2 = 32852;
case 2013 
	t1 = 37757; t2 = 38081;
case 2014 
	t1 = 42475; t2 = 42594;
case 2015 
	t1 = 48046; t2 = 48561;
otherwise
end

for t = t1:t2;

process_granule= strcat(num2str(k), '*', num2str(t));
%input_path1 =['/dadm/DATA/CloudSat/DARDAR_mask/',YY];
input_path1 =['/dadm1/obs/CloudSat/DARDAR_mask/'];
input_path1 = strcat(input_path1, num2str(k), '/');
file1=dir(strcat(input_path1, 'DARDAR-MASK*',process_granule,'.hdf'));
%Out_dir   =['~/temp/'];

%ofigname=  ['Example_Morakot_20090807_17429.eps'];
if size(file1,1) == 0
	continue
end

% read data
%i2=CPR_L1B_rdr_ICARE(input_path1,file1,{'CS_TRACK_Height','Temperature'});
%i=CPR_L1B_rdr_ICARE(input_path1,file1,{'Specific_humidity','Pressure'});
i1=CPR_L1B_rdr_ICARE(input_path1,file1,{'CLOUDSAT_Latitude','CLOUDSAT_Longitude'});
i2=CPR_L1B_rdr_ICARE(input_path1,file1,{'CS_TRACK_Height', 'DARMASK_Simplified_Categorization'});
Z=i2.DARMASK_Simplified_Categorization;
h=i2.CS_TRACK_Height';  % DARDAR_mask flag
%T = i1.Temperature;
%h = i2.Specific_humidity;
%P = i2.Pressure;
lon = i1.CLOUDSAT_Longitude;
lat = i1.CLOUDSAT_Latitude;
%total_p=size(Z,2);   % total number of profile in this granuel
%Y=repmat(i1.CS_TRACK_Height',1,total_p);  % altitude above mean sea level, km

%output pattern to test%
%display(size(Z));
X=['now on  year: ', num2str(k), '  granule: ', num2str(t)];
display(X);

file1=fopen(strcat('../../data/raw_data/height/', num2str(k),'/',  process_granule, '.txt'), 'w');
file2=fopen(strcat('../../data/raw_data/flag/', num2str(k),'/',  process_granule, '.txt'), 'w');
file3=fopen(strcat('../../data/raw_data/lon/', num2str(k),'/',  process_granule, '.txt'), 'w');
file4=fopen(strcat('../../data/raw_data/lat/', num2str(k),'/',  process_granule, '.txt'), 'w');
file5=fopen(strcat('../../data/raw_data/size/', num2str(k),'/',  process_granule, '.txt'), 'w');
for i = 1:size(h,1);
	fprintf(file1, '%f\n', h(i));
end
for i = 1:size(Z,2)
	for j = 1:size(Z,1)
		fprintf(file2, '%d ', Z(j,i));
	end
	fprintf(file2, '\n');
end
%for i = 1:size(T,2)
%	for j = 1:size(T,1)
%		fprintf(file2, '%f ', T(i,j));
%	end
%	fprintf(file2, '\n');
%end
for i = 1:size(lat,2)
		fprintf(file4, '%f\n', lat(i));
end

for i = 1:size(lon,2)
		fprintf(file3, '%f\n', lon(i));
end

fprintf(file5, '%d %d\n', size(Z,1), size(Z,2));

S=[num2str(Z(1))]
%fclose(file3);
%fclose(file4);
%fclose(file5);
end
end
%plot feature flag
%figure(1)
%seg=(3500:5000);  % segment of granule to plot
%X=repmat(seg,436,1); % profile #
%pcolor(X,Y(:,seg),Z(:,seg))
%colorbar;
%caxis([-1 9])
%shading flat
%title('Category1 cloud1, 2011/04/04 Granule 26249')
%title('Example of DARDAR_mask flag, 2009/08/07 Typhoon Morakot')
%xlabel('profile #')
%ylabel('Height (km)')
%
%h = figure(1)
%
%set (gcf,'PaperOrientation','landscape','PaperType','A4'); 
%saveas(h, '26249_cat1_cloud1.jpg');
%print ('-depsc2', strcat(Out_dir,ofigname));
%}

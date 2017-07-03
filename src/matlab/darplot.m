clf;

% Input/output file names templates
%                     1       10        20        30        40        50        606for t = 26245:26432;

%2006 : 00702~00926, 2007:  04918~06193 2008 :  08922~14250  2009: 14253~19209
%2010 : 19797~24860, 2011: 26193~26432, 2012: 32170~32852, 2013: 36844~38081  
%2014 : 42474~42594, 2015 48046~48561: 

process_granule= '2008*11722';
%input_path1 =['/dadm/DATA/CloudSat/DARDAR_mask/',YY];
input_path1 =['/dadm1/obs/CloudSat/DARDAR_mask/'];
input_path1 = strcat(input_path1 ,'2008/');
file1=dir(strcat(input_path1, 'DARDAR-MASK*',process_granule,'.hdf'));
%Out_dir   =['~/temp/'];

%ofigname=  ['Example_Morakot_20090807_17429.eps'];
i1=CPR_L1B_rdr_ICARE(input_path1,file1,{'CS_TRACK_Height','DARMASK_Simplified_Categorization'});

Z=i1.DARMASK_Simplified_Categorization';  % DARDAR_mask flag
total_p=size(Z,2);   % total number of profile in this granuel
Y=repmat(i1.CS_TRACK_Height',1,total_p);  % altitude above mean sea level, km


%output pattern to test%


%
%plot feature flag
figure(1)
seg=(1000:10000);  % segment of granule to plot
X=repmat(seg,436,1); % profile #
pcolor(X,Y(:,seg),Z(:,seg))
colorbar;
caxis([-1 9])
shading flat
title('Category1 cloud1, 2011/04/04 Granule 26249')
title('Example of DARDAR_mask flag, 2009/08/07 Typhoon Morakot')
xlabel('profile #')
ylabel('Height (km)')
%
%h = figure(1)
%
%set (gcf,'PaperOrientation','landscape','PaperType','A4'); 
%saveas(h, '26249_cat1_cloud1.jpg');
%print ('-depsc2', strcat(Out_dir,ofigname));
%}

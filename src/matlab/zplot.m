clear all
close all

file = fopen('../../one_file_test/pdf.txt', 'r')
sizeA = [64575388 1];
raw = fscanf(file, '%lf', sizeA);

[counts, bins] = hist(raw);
barh(bins, counts)
ylim([0 25])
title('Probability of Cloud Observance with Height')
ylabel('height (km)')
xlabel('Observance')
print -dpng 'cpdf.png'

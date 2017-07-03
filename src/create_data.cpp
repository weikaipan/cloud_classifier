#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "datatype.h"
#include "common.h"
#include <cstring>
#include <fstream>
#include <libgen.h>
using namespace std;

DifferentLabel checkMonotonous(int i, int j, int height, int width, IMAGE& img)
{
    DifferentLabel DL;
    Point tmpP;  tmpP.z = i; tmpP.x = j;
    vector<Point> checkBoundaryExceed(8, tmpP);
    vector<int> smallList;
    
    /* set boundary number in array */
    checkBoundaryExceed[0].z -= 1;  checkBoundaryExceed[0].x -= 1;
    checkBoundaryExceed[1].z -= 1; 
    checkBoundaryExceed[2].z -= 1;  checkBoundaryExceed[2].x += 1;
    checkBoundaryExceed[3].x -= 1;
    checkBoundaryExceed[4].x += 1;
    checkBoundaryExceed[5].z += 1;  checkBoundaryExceed[5].x -= 1;
    checkBoundaryExceed[6].z += 1;
    checkBoundaryExceed[7].z += 1;  checkBoundaryExceed[7].x += 1;
    /* check boundary exceed */
    for(int k = 0; k < 8; k++){
	if(checkBoundaryExceed[k].x >= 0 && checkBoundaryExceed[k].x <= width-1){
	   if(checkBoundaryExceed[k].z >= 0 && checkBoundaryExceed[k].z <= height-1){
		int m = checkBoundaryExceed[k].z, l = checkBoundaryExceed[k].x;
		if(img[m][l].key != 0)
		    smallList.push_back(img[m][l].key);
	   }
	}   
    }
    /* find the smallest label */
    DL.smallestLabel = smallList[0];
    for(int k = 1; k < (int)smallList.size(); k++){
	if(smallList[k] < DL.smallestLabel)
	    DL.smallestLabel = smallList[k];
    }
    /* check different labels */
    for(int k = 1; k < (int)smallList.size(); k++)
	if(smallList[k] != smallList[k-1])
	    DL.same = false;

    if(!DL.same){
        for(int k = 0; k < (int)smallList.size(); k++){
	    if(smallList[k] != DL.smallestLabel){   
		DJSET[smallList[k]-1].parent = &DJSET[DL.smallestLabel-1];
	    } 
	}
    }

    return DL;
}

bool isCloud(int pixel)
{
    return (pixel >= 1 && pixel <= 5);
}

bool isLabeled(int i, int j, int height, int width, IMAGE& img)
{
    Point tmpP;  tmpP.z = i; tmpP.x = j;
    vector<Point> checkBoundaryExceed(8, tmpP);
    vector<int> smallList;
    
    /* set boundary number in array */
    checkBoundaryExceed[0].z -= 1;  checkBoundaryExceed[0].x -= 1;
    checkBoundaryExceed[1].z -= 1; 
    checkBoundaryExceed[2].z -= 1;  checkBoundaryExceed[2].x += 1;
    checkBoundaryExceed[3].x -= 1;
    checkBoundaryExceed[4].x += 1;
    checkBoundaryExceed[5].z += 1;  checkBoundaryExceed[5].x -= 1;
    checkBoundaryExceed[6].z += 1;
    checkBoundaryExceed[7].z += 1;  checkBoundaryExceed[7].x += 1;
    /* check boundary exceed */
    for(int k = 0; k < 8; k++){
	if(checkBoundaryExceed[k].x >= 0 && checkBoundaryExceed[k].x <= width-1){
	   if(checkBoundaryExceed[k].z >= 0 && checkBoundaryExceed[k].z <= height-1){
		int m = checkBoundaryExceed[k].z, l = checkBoundaryExceed[k].x;
		smallList.push_back(img[m][l].key);
	   }
	}   
    }
    for(int k = 0; k < (int)smallList.size(); k++){
	if(smallList[k] != 0)
		return true;
    }

    return false;
}

// global variables for two pass algorithm
int currentLabel = 0;

int main(int argc, char* argv[])
{
    /* decalre */
    ifstream config;
    vector<string> var;
    int drop, height, width;
    string tmps(basename(argv[4]));
    E tmpPixel;
    /* read config */
    config.open(argv[1]);
    while (config.good()){
        string s;
        config >> s;
        var.push_back(s);
    }
    config.close();
    for(int i = 0; i < (int)var.size()-2; i++){
	var[i] += tmps;
	printf("Read file = %s\n", var[i].c_str());
    }
    /*read file*/
    FILE *flag, *lo, *la, *z, *dimension;
    flag = fopen(var[0].c_str(), "r");
    lo = fopen(var[1].c_str(), "r");
    la = fopen(var[2].c_str(), "r");
    z = fopen(var[3].c_str(), "r");
    dimension = fopen(var[4].c_str(), "r");
    drop = stoi(var[5]);
    /* initialize node in union-find data structure */
    /* read dimension */
    vector<int> dim(2, 0);
    for(int i = 0; i < 2; i++){
	fscanf(dimension, "%d", &dim[i]);
    	printf("%d ", dim[i]);
    }
    printf("\n");
    fclose(dimension);
    width = dim[0];
    height = dim[1];
    printf("%d\n", width);
    /* read file */
    vector< vector<int> > img(height, vector<int>(width, 0));
    IMAGE label(height, vector<E>(width, tmpPixel));              //  store label
    vector<double> lon(width, 0), lat(width, 0), zz(height, 0);
    printf("File name: %s\n", var[0].c_str()); 
    /* read image pixels */
    for(int i = 0; i < height; i++){
	for(int j = 0; j < width; j++){
            int pixels;
	    fscanf(flag, "%d", &pixels);
	    if(isCloud(pixels))
		img[i][j] = 1;
	    else
		img[i][j] = 0;
	}
    }
    fclose(flag);
    for(int i = 0; i < width; i++){
        fscanf(lo, "%lf", &lon[i]);
        fscanf(la, "%lf", &lat[i]);
    }
    fclose(lo); fclose(la);
    for(int i = 0; i < height; i++)
	fscanf(z, "%lf", &zz[i]);
    fclose(z);

    /* Algorithm start: first pass */
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(img[i][j] == 1){
                // check whether any neighbor is labeled
                if(isLabeled(i, j, height, width, label)){
                    DifferentLabel checkSame = checkMonotonous(i, j, height, width, label);
                    if(checkSame.same){
                        label[i][j].key = checkSame.smallestLabel;
                        label[i][j].parent = &(DJSET[checkSame.smallestLabel-1]);
                    }
                    else{
                        label[i][j].key = checkSame.smallestLabel;
                        label[i][j].parent = &(DJSET[checkSame.smallestLabel-1]);
                    }
                }
                else{
                    /* when pixel is set, push its Label value to pattern List */
                    currentLabel++;
                    DJSET[currentLabel-1].key = currentLabel;
                    DJSET[currentLabel-1].parent = &(DJSET[currentLabel-1]);
                    label[i][j].key = currentLabel;
                    label[i][j].parent = &(DJSET[currentLabel-1]);
                    
                }
            }
        }
    }
    /* second pass */
    Point p;
    vector< vector<Point> > LIST(DJSET.size(), vector<Point>(0, p));
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(label[i][j].key != 0){
                E *tmp = label[i][j].parent;
                while(tmp -> parent != tmp){
                    tmp = tmp -> parent;
                }
                Point tmpPoint; 
                tmpPoint.x = j; tmpPoint.z = i;                 
		LIST[tmp->key-1].push_back(tmpPoint);
            }
        }
    }
    /***** cluster analysis ******/
    /*
     *  cloudPattern : array containing the coordinates of cloud. 
     */
    vector< vector<Point> > cloudPattern;
    for(int i = 0; i < (int)LIST.size(); i++){
        if((int)LIST[i].size() > drop)
            cloudPattern.push_back(LIST[i]);
    }
    vector< vector<Point> > :: iterator it;
    
    /*1. define cloud attribute */
    vector<cloud> cloudDataPoint; 
    vector< vector<double> > zpdf; 
    int q;
    for(it = cloudPattern.begin(), q = 0; it != cloudPattern.end(); ++it, q++){
        /* find the cloud's height and width */
        int max_width = (*it)[0].x, min_width = (*it)[0].x;
        int max_height = (*it)[0].z, min_height = (*it)[0].z;
	int pos = (*it)[0].x;
	double xcen = (*it)[0].x, zcen = (*it)[0].z;
	double zmax = zz[(*it)[0].z];
	double loncen = lon[pos], latcen = lat[pos];
        for(int i = 1; i < (int)it->size(); i++){
            max_width = max_width < (*it)[i].x  ? (*it)[i].x : max_width;
            min_width = min_width > (*it)[i].x  ? (*it)[i].x : min_width;
            max_height = max_height < (*it)[i].z  ? (*it)[i].z : max_height;
            min_height = min_height > (*it)[i].z  ? (*it)[i].z : min_height;
	    zmax = zmax > zz[(*it)[i].z] ? zmax : zz[(*it)[i].z];
	    xcen += (*it)[i].x;
	    zcen += (*it)[i].z;
	    loncen += lon[(*it)[i].x];
	    latcen += lat[(*it)[i].x];
        }
	/* inform cloud attriutes data space */
        double h = max_height - min_height + 1;
	double l = max_width - min_width + 1;
	double size = (double)it->size();
	if (zmax < 4 || latcen/size < -20 || latcen/size > 20)
	    continue;
	cloud tmpcloud;
	tmpcloud.location.x = xcen/size;
	tmpcloud.location.z = zcen/size;
	tmpcloud.location.lon = loncen/size;
	tmpcloud.location.lat = latcen/size;
	tmpcloud.attribute.push_back(l);
	tmpcloud.attribute.push_back(h);
	tmpcloud.attribute.push_back(size);
	tmpcloud.attribute.push_back(zmax);

	cloudDataPoint.push_back(tmpcloud);
	vector<double> tmpzpdf;
	for(int i = 0; i < (int)it->size(); i++) {
	   tmpzpdf.push_back(zz[(*it)[i].z]); 
	}
	zpdf.push_back(tmpzpdf);
    }
    printf("Size of Cloud data set = %d and %d\n", (int)cloudDataPoint.size(), (int)zpdf.size());
    /* raw */
    FILE * raw_data;
    FILE * file;
    raw_data = fopen(argv[2],  "a");
    file = fopen(argv[3],  "a");
    for(int i = 0; i < (int)cloudDataPoint.size(); i++){
        fprintf(raw_data, "%lf %lf ", cloudDataPoint[i].location.lon, 
						cloudDataPoint[i].location.lat);
	for (int j = 0; j < (int)cloudDataPoint[i].attribute.size(); j++)
	    fprintf(raw_data, "%lf ", cloudDataPoint[i].attribute[j]);
    fprintf(raw_data, "\n");
	
	for (int k = 0; k < (int)zpdf[i].size(); k++)
    	    fprintf(file, "%lf ", zpdf[i][k]);
	fprintf(file, "\n");
    }
    fclose(raw_data);
    fclose(file);
    printf("\n");
    return 0;
}    

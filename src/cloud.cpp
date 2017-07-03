#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "datatype.h"

DifferentLabel checkMonotonous(int &i, int &j, IMAGE& img)
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

bool isLabeled(int &i, int &j, IMAGE& img)
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

double distance(clusterPosition center, Position point)
{
    return sqrt( abs(center.l - (double)point.w) + abs(center.m - (double)point.h) + abs(center.n - (double)point.top) );
}

bool check_error(vector<clusterPosition> &cp, double tolerance)
{
    for(int i = 0; i < (int)cp.size(); i++){
        if(cp[i].m > tolerance || cp[i].n > tolerance || cp[i].l > tolerance)
            return true;
    }
    return false;
}


int main(int argc, char* argv[])
{
    /*read file*/
    FILE * file;
    file = fopen(argv[1], "r+");
    clock_t start = clock();
    /*initialize node in union-find data structure*/
    E tmpPixel;
    vector< vector<int> > img(height, vector<int>(width, 0));     //  store image pixels
    IMAGE label(height, vector<E>(width, tmpPixel));              //  store label
    
    /*read image pixels */
    int pixels;
    for(int i = height-1; i >= 0; i--){
	for(int j = 0; j < width; j++){
            fscanf(file, "%d", &pixels);
	    if(isCloud(pixels))
		img[i][j] = 1;
	    else
		img[i][j] = 0;
	}
    }
    fclose(file);

    /* first pass */
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(img[i][j] == 1){
                // check whether any neighbor is labeled
                if(isLabeled(i, j, label)){
                    DifferentLabel checkSame = checkMonotonous(i, j, label);
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
		    //    consider nullprt
                    DJSET[currentLabel-1].parent = &(DJSET[currentLabel-1]);
		    //E tmpE;  tmpE.key = currentLabel;  tmpE.parent = &tmpE;
		    //DJSET.push_back(tmpE);			

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
	if(LIST[i].size() > 0){
            //printf("size of cloud : %d\n", (int)LIST[i].size());
	}
    }
    for(int i = 0; i < (int)LIST.size(); i++){
        if(LIST[i].size() > 0)
            cloudPattern.push_back(LIST[i]);
    }
    vector< vector<Point> > :: iterator it;
    
    /*1. define cloud attribute */
    vector<Position> cloudDataPoint; 
    int q;
    for(it = cloudPattern.begin(), q = 0; it != cloudPattern.end(); ++it, q++){
        /* find the cloud's height and width */
        int max_width = (*it)[0].x, min_width = (*it)[0].x;
        int max_height = (*it)[0].z, min_height = (*it)[0].z;
	for(int i = 1; i < (int)it->size(); i++){
            max_width = max_width < (*it)[i].x  ? (*it)[i].x : max_width;
            min_width = min_width > (*it)[i].x  ? (*it)[i].x : min_width;
            max_height = max_height < (*it)[i].z  ? (*it)[i].z : max_height;
            min_height = min_height > (*it)[i].z  ? (*it)[i].z : min_height;
        }
	/* inform cloud attriutes data space */
        Position tmpPosition;
        tmpPosition.h = max_height - min_height;
        tmpPosition.top = max_height;
	tmpPosition.w = (int)it->size();
	//tmpPosition.p = *it;
	//tmpPosition.base = min_height;
        tmpPosition.pattern = q;
        cloudDataPoint.push_back(tmpPosition);
    }
    
    
    
    /*3. cluseter centroid && the size of set */
    // center
    int categories = 3;
    clusterPosition *clusterCenter, *updateClusterCenter;
    clusterCenter = new clusterPosition[categories];
    updateClusterCenter = new clusterPosition[categories];
    // size
    int *size;
    size = new int[categories];
    for(int i = 0; i < categories; i++)
        size[i] = 0;
    
    /*4. arbitary select cluster center and initialize update cluster center */
    srand(time(NULL));
    for(int i = 0; i < categories; i++){
        int p = rand() % (int)cloudDataPoint.size();
        clusterCenter[i].m = cloudDataPoint[p].h;
        clusterCenter[i].n = cloudDataPoint[p].top;
        clusterCenter[i].l = cloudDataPoint[p].w;
    }
    for(int i = 0; i < categories; i++){
        updateClusterCenter[i].m = 0;
        updateClusterCenter[i].n = 0;
        updateClusterCenter[i].l = 0;
    }

    /*5. iteration */
    long int iterations = 0;
    // initialize tolerance
    clusterPosition tmpCP;
    tmpCP.m = 1000; tmpCP.n = 1000;
    vector<clusterPosition> tolerance(categories,tmpCP);

    while(check_error(tolerance, 0.00001)){
    for(int i = 0; i < categories; i++)
	//printf("%d centroid : (%lf, %lf, %lf)\n", i, clusterCenter[i].m, clusterCenter[i].n, clusterCenter[i].l);
	iterations++;
        //printf("%ldth iterations.\n", iterations);
        /*a. assign every Xi to belong to Cj */
        for(int i = 0; i < (int)cloudDataPoint.size(); i++){
            double minDistance = distance(clusterCenter[0], cloudDataPoint[i]);
            int shortest_cluster = 0;
            for(int j = 1; j < categories; j++){
                double d = distance(clusterCenter[j], cloudDataPoint[i]);
                if(d < minDistance){
                    shortest_cluster = j;
                    minDistance = d;
                }
            }
            cloudDataPoint[i].cluster = shortest_cluster;
        }
        /*b. calculate the mean distance of each objecs */
        for(int i = 0; i < (int)cloudDataPoint.size(); i++){
            updateClusterCenter[cloudDataPoint[i].cluster].m += (double)cloudDataPoint[i].h;
            updateClusterCenter[cloudDataPoint[i].cluster].n += (double)cloudDataPoint[i].top;
            updateClusterCenter[cloudDataPoint[i].cluster].l += (double)cloudDataPoint[i].w;
            size[cloudDataPoint[i].cluster]++;
        }
        for(int i = 0; i < categories; i++){
            updateClusterCenter[i].m /= (double)size[i];
            updateClusterCenter[i].n /= (double)size[i];
            updateClusterCenter[i].l /= (double)size[i];
        }
        /*c. calculate the variation of each centroid  */
        for(int i = 0; i < categories; i++){
            // calculate tolerance
            tolerance[i].m = abs(updateClusterCenter[i].m - clusterCenter[i].m);
            tolerance[i].n = abs(updateClusterCenter[i].n - clusterCenter[i].n);
            tolerance[i].l = abs(updateClusterCenter[i].l - clusterCenter[i].l);
            // update center
            clusterCenter[i].m = updateClusterCenter[i].m;
            clusterCenter[i].n = updateClusterCenter[i].n;
            clusterCenter[i].l = updateClusterCenter[i].l;
	    size[i] = 0;
        }
    }
    for(int i = 0; i < categories; i++)
	printf("%d centroid : (%lf, %lf, %lf)\n", i, clusterCenter[i].m, clusterCenter[i].n, clusterCenter[i].l);
    clock_t end = clock();
    /*
     *    clusteredPoint : holds classified categories
     *    clusteredPoint[i] : holds all cloud belong to i-category
     *    clusteredPoint[i][j] : holds all spatial point of a piece of cloud
     */
    vector< vector< vector<Point> > > clusteredPoint(categories);
    for(int i = 0; i < (int)cloudDataPoint.size(); i++){
        clusteredPoint[cloudDataPoint[i].cluster].push_back(cloudPattern[cloudDataPoint[i].pattern]);
    }
    /*  output a scatter plot
     *  raw_data : cloud attributes point on n-space  ( here : 2d-space, (width, height) )
     *  cluseter_data[k] :  each file contains all parcels of cloud belong to category "k"
     */
    //FILE * raw_data = fopen("/home/C.b01209041/matlab_read/DARDAR/data/inftest.txt", "w"); 
    FILE * cen1 = fopen("/home/C.b01209041/matlab_read/DARDAR/data/infcen.txt", "a");
    //FILE * cen2 = fopen("/home/C.b01209041/matlab_read/DARDAR/data/center2_ind.txt", "a");
    /*
     *   raw_data  : records clouds attributes of each cluster of cloud.
     *   cld : records position of each clouds belonging to certain cluster.
     *   cen : records cetorid of each cluster of cloud.
     */

    /* raw */
    //for(int i = 0; i < (int)cloudDataPoint.size(); i++){
    //    fprintf(raw_data, "%lf %lf %lf\n", cloudDataPoint[i].h, cloudDataPoint[i].top, cloudDataPoint[i].w);
    //fclose(raw_data);
//}
    /* cld 
    cld = fopen(fname3.c_str(), "w");
    for(int i = 0; i < (int)cloudDataPoint.size(); i++){
	
    fclose(cld);
    */
    /* cen */
	for(int i = 0; i < 2; i++)
	fprintf(cen1, "%lf %lf %lf\n",clusterCenter[i].m, clusterCenter[i].n, clusterCenter[i].l);

	//fprintf(cen2, "%lf %lf %lf\n",clusterCenter[1].m, clusterCenter[1].n, clusterCenter[1].l);
    printf("finish!\n");
	fclose(cen1);
    //fclose(cen2);

    /*
    string str3 = fname3.substr(5, 5);
    FILE **cluster_data;
    cluster_data = new FILE*[categories];
    for(int i = 0; i < categories; i++){
        for(int j = 0; j < (int)clusteredPoint[i].size(); j++){
            string dir = "cluster/" + str3 + "/category" + to_string((long long int)i+1) + "_cloud"  + to_string((long long int)j+1) + ".txt";
    	    cluster_data[i] = fopen(dir.c_str(), "w");
	    for(int k = 0; k < (int)clusteredPoint[i][j].size(); k++){
                fprintf(cluster_data[i], "%d %d\n", clusteredPoint[i][j][k].x, clusteredPoint[i][j][k].z); 
	    }
	    fclose(cluster_data[i]);
        }
    }
    printf("Time Elapse : %lf seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
    */
	return 0;
}


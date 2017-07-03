#include "datatype.h"
#include <fstream>
#include <cstdlib>
using namespace std;
double distance(clusterPosition center, Position point)
{
    return sqrt( abs(center.l - (double)point.w) + abs(center.m - (double)point.h) + abs(center.n - (double)point.top) );
}

bool check_error(vector<clusterPosition> &cp, double tolerance)
{
    for(int i = 0; i < (int)cp.size(); i++){
        if(cp[i].m > tolerance && cp[i].n > tolerance && cp[i].l > tolerance)
            return true;
    }
    return false;
}

int main(int argc, char **argv)
{
    //FILE * file;
    //file = fopen(argv[1], "r");	
    ifstream infile(argv[1]);
    int categories = 4;
    vector<Position> cloudDataPoint;
    while (infile.good()){
	Position tmp;
	infile >> tmp.h;
	infile >> tmp.top;
	infile >> tmp.w;
	cloudDataPoint.push_back(tmp); 
    }
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
    tmpCP.m = 1000; tmpCP.n = 1000; tmpCP.l = 1000;
    vector<clusterPosition> tolerance(categories,tmpCP);

    while(check_error(tolerance, 0.00001)){
    for(int k = 0; k < categories; k++)
	printf("%d centroid : (%lf, %lf, %lf)\n", k, clusterCenter[k].m, clusterCenter[k].n, clusterCenter[k].l);
	iterations++;
        printf("%ldth iterations.\n", iterations);
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
	    printf("temp cluster size = %d\n", size[i]);
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
    /*
     *    clusteredPoint : holds classified categories
     *    clusteredPoint[i] : holds all cloud belong to i-category
     *    clusteredPoint[i][j] : holds all spatial point of a piece of cloud
     */
    //vector< vector< vector<Point> > > clusteredPoint(categories);
    //for(int i = 0; i < (int)cloudDataPoint.size(); i++){
    //    clusteredPoint[cloudDataPoint[i].cluster].push_back(cloudPattern[cloudDataPoint[i].pattern]);
    //}
    /*  output a scatter plot
     *  raw_data : cloud attributes point on n-space  ( here : 2d-space, (width, height) )
     *  cluseter_data[k] :  each file contains all parcels of cloud belong to category "k"
     */
    FILE * raw_data;
    char path[] = "/home/C.b01209041/matlab_read/DARDAR/one_file_test/";
    raw_data = fopen(strcat(path, argv[2]),  "w");    
for(int i = 0; i < (int)cloudDataPoint.size(); i++)
        fprintf(raw_data, "%lf %lf %lf %d\n", cloudDataPoint[i].h, cloudDataPoint[i].top, cloudDataPoint[i].w, cloudDataPoint[i].cluster);
    fclose(raw_data);



    /*
    for(int i = 0; i < categories; i++){
	fprintf(center_data, "%lf %lf %lf\n",clusterCenter[i].m, clusterCenter[i].n, clusterCenter[i].l);
	fprintf(raw, "%lf %lf %lf\n",clusterCenter[i].m, clusterCenter[i].n, clusterCenter[i].l);
    }
    fprintf(raw, "\n"); 
     *   raw_data  : records clouds attributes of each cluster of cloud.
     *   cld : records position of each clouds belonging to certain cluster.
     *   cen : records cetorid of each cluster of cloud.
     */

    /* raw 
    raw_data = fopen(argv[1], "w");
    for(int i = 0; i < (int)cloudDataPoint.size(); i++)
        fprintf(raw_data, "%d %d %d %d\n", cloudDataPoint[i].h, cloudDataPoint[i].base, cloudDataPoint[i].w, cloudDataPoint[i].cluster);
    fclose(raw_data);
    */
	return 0;
}

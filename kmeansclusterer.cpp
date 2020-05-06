/* 
 * File:   KMeansClusterer.cpp
 * Author: Sindiso Mkhatshwa
 *
 * Created on 28 April 2020, 20:37
 */
#include "kmeansclusterer.h"
using namespace MKHSIN035;
using namespace std;

//------------------------------------------------------------------------------
//               Class KMeansClusterer member functions definitions
//------------------------------------------------------------------------------
/*
 * Default constructor
 */
MKHSIN035::KMeansClusterer::KMeansClusterer():Kvalue(10){}
/*
 * Constructor definition for KMeansClusterer
 */
MKHSIN035::KMeansClusterer::KMeansClusterer(int K):Kvalue(K){}

/*
 * Destructor definition for KMeansClusterer
 */
MKHSIN035::KMeansClusterer::~KMeansClusterer(){}

            
/*
 * Initializes clusters
 * @params vector<int>& initial_indices
 * @params vector<Image>& centroids 
 * @params vector<string>& initial_points_filenames
 */
void MKHSIN035::KMeansClusterer::initializeClusters(vector<int>& initIndices, vector<Image>& centroids, vector<string>& initialPointsFilenames){
cout<<"Initializing clusters..."<<endl;
    for(int i = 0; i < Kvalue; i++){
        while(true){
            srand(time(NULL));
            int index = rand()%images.size();
            if(find(initIndices.begin(), initIndices.end(), index) == initIndices.end()){
                //Avoid duplications even further
                string delimeter = "_";
                string name = images[index].getfilename().substr(0, images[index].getfilename().find(delimeter));
                if(Kvalue < 11){
                    if(find(initialPointsFilenames.begin(), initialPointsFilenames.end(), name) == initialPointsFilenames.end()){
                        centroids.push_back(images[index]);
                        initIndices.push_back(index);
                        initialPointsFilenames.push_back(name);
                        
                        break;
                }
                }
                else{
                    centroids.push_back(images[index]);
                    initIndices.push_back(index);
                    initialPointsFilenames.push_back(name);
                    
                    break;
                }
                
            }
        }
    }
}

/*
 * Performs K-means algorithm
 */
void MKHSIN035::KMeansClusterer::kmeansclustering(){
    //Initialization
    vector<int> initIndices;
    vector<Image> centroids;
    vector<string> initialPointsFilenames;
                
    initializeClusters(initIndices, centroids, initialPointsFilenames);
    
    cout<<"Performing K-means clustering..."<<endl;
    int count = 0;
    bool done = false;

    while(!done){
        //Assign each image to its nearest cluster
        for(int i = 0; i < centroids.size(); i++){
                        
             for (int j = 0 ; j < images.size(); j++) {
                Image image = images[j];
                double dist = centroids[i].distance(image);
                if (dist < image.min_dist) {
                    image.min_dist = dist;
                    image.cluster_id = i;
                }
                images[j] = image;
            }
            
        }
       
        vector<vector<double> > sum(Kvalue);
        vector<int> numPoints;
        for(int i = 0; i < Kvalue; i++){
            numPoints.push_back(0);
            sum[i] = vector<double>(images[0].featurelen);
            for(int j = 0; j < sum[i].size(); j++){
                sum[i][j] = 0;
            }
        }
        // Iterate over points to append data to centroids
        for (int i = 0; i < images.size(); i++) {
            int clusterId = images[i].cluster_id;
            numPoints[clusterId] += 1;
            for(int j = 0; j < images[i].featurelen; j++){
                sum[clusterId][j] += images[i].feature[j];
            }
            images[i].min_dist = DBL_MAX;  // reset distance
        }
        // Compute the new centroids
        for (int i = 0; i < centroids.size(); i++) {
            for(int j = 0; j < sum[i].size(); j++){
                //Check for convergence
                
                if(centroids[i].feature[j] != (sum[i][j] / numPoints[i])){
                    centroids[i].feature[j] = sum[i][j] / numPoints[i];
                    done = false;
                }
                else
                    done = true;
            }
        }
                                   
        count++;
 
    }
}
    

/*
 * getK function definition
 */
int MKHSIN035::KMeansClusterer::getK () const{return Kvalue;}


/*
 *operator<< writes the current clustering of the images 
 *to the supplied ostream
 * @params std::ostream& os 
 * @params const KMeansClusterer& kt
 */
ostream& MKHSIN035::operator<<(std::ostream& os, const MKHSIN035::KMeansClusterer& kt){
    os<<"Clusters:\n\n\n"<<endl;
    KMeansClusterer obj = kt;
    for(int i = 0; i < obj.getK(); i++){
        os<<"Cluster "<<i<<": ";
        for(int j = 0; j < obj.images.size(); j++){
            if(obj.images[j].getClusterId() == i)
                os<<obj.images[j].getfilename()<<" ";
        }
            
        os<<"\n";

    }
    return os;
}
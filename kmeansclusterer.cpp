#include "kmeansclusterer.h"
using namespace MKHSIN035;
using namespace std;

//------------------------------------------------------------------------------
//               Class KMeansClusterer member functions definitions
//------------------------------------------------------------------------------
/*
 * Constructor definition for KMeansClusterer
 */

MKHSIN035::KMeansClusterer::KMeansClusterer(int K, bool colour, int bin):Kvalue(K), color(colour), bin(bin){}

/*
 * Destructor definition for KMeansClusterer
 */
MKHSIN035::KMeansClusterer::~KMeansClusterer(){}




//void KMeansClusterer::readDataSet(string folder){
//    string extension = ".ppm";
//    string filename;
////    ifstream dataset;
//    //images = new unsigned char* [100];
//    int counter = 0;
//    for (int i = 0; i < 10; i++){
//        for(int j = 1; j <=10; j++ ){
//            ifstream dataset;
//            string name = filenames[i]+to_string(j)+extension;
//            Image obj(name);
//            filename = folder+name;
//            dataset.open(filename, ios::binary|ios::ate); 
//            streampos begin,end;
//            
//            if(dataset.is_open()){
//                end = dataset.tellg();
//                string dim;
//                string line;
//
//                //Take pointer back to the beginning of the file
//                dataset.seekg(0, ios::beg);
//
//                while(getline(dataset, line)){
//                    if(line == "255"){
//                        begin = dataset.tellg();
//                    }
//                }
//                int size = (end-begin);
//                obj.setImageDataSetlen(size);
//                char buf[size];
//                unsigned char val [size];
//                dataset.read(buf, size);
//                memcpy(&val, buf, sizeof(val));
//                obj.imageDataSet = val;
//                
//                if(!color)
//                    obj.createGreyScale();
//                
//                //Add image to collection of images
//                images.push_back(obj);
//                
//                dataset.close();
//
//            }
//            else{
//                cout<<"Could not open file "<<filename<<endl;
//            }
//            counter++;
//        }
//    }
//        
//}



            

int MKHSIN035::KMeansClusterer::closestCentroid(Image image){
    double sum = 0;
    double minDist;
    int closestClusterId;
    int featureSize = 0;
   
    for(int i = 0; i < image.getfeaturelen(); i++){
        sum += pow(clusters[0].getMean(i) - image.feature[i], 2);
    }
    minDist = sqrt(sum);
    closestClusterId = clusters[0].getId();
    
    for (int i = 1; i < Kvalue; i++){
        double d;
        sum = 0;
        for(int j = 0; j < image.getfeaturelen(); j++){
            sum += pow(clusters[i].getMean(j) - image.feature[j], 2);
        }
        d = sqrt(sum);
        if(d < minDist){
            minDist = d;
            closestClusterId = clusters[i].getId();
        }
    }
    return closestClusterId;
}

/*
 * Function definition for kmeansclustering()
 */
void MKHSIN035::KMeansClusterer::kmeansclustering(){
    //Initialization
    vector<int> initIndices;
    vector<Image> centroids;
    vector<string> initialPointsFilenames;
                
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
                        //Create new cluster
                        Cluster cluster(i, images[index]);
                        clusters.push_back(cluster);
                        break;
                }
                }
                else{
                    centroids.push_back(images[index]);
                    initIndices.push_back(index);
                    initialPointsFilenames.push_back(name);
                    //images[index].setClusterId(i);
                    cout<<index<<"\nImage: "<<images[index].getfilename()<<endl;
                    //Create new cluster
                    Cluster cluster(i, images[index]);
                    clusters.push_back(cluster);
                    break;
                }
                
            }
        }
    }
    cout<<"Performing K-means clustering..."<<endl;
    int count = 0;
    while(true){
        bool status = true;
        //Assign each image to its nearest cluster
        for(int i = 0; i < centroids.size(); i++){
            //int currentCluster = images[i].getClusterId();
            //int closestCluster = this->closestCentroid(images[i]);
            
             for (int j = 0 ; j < images.size(); j++) {
                Image image = images[j];
                double dist = centroids[i].distance(image);
                if (dist < image.min_dist) {
                    image.min_dist = dist;
                    image.cluster_id = i;
                }
                images[j] = image;
                //cout<<image.filename<<" Dist: "<<image.min_dist<<endl;
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
            for(int j = 0; j < sum[i].size(); j++)
                centroids[i].feature[j] = sum[i][j] / numPoints[i];
            
        }
                                   
        count++;

        if(count > 100)
            break;
        
    }
        
        
        
//            //Remove image from wrong cluster 
//            if(currentCluster != closestCluster){
//                for(int c = 0; c < Kvalue; c++){
//                    if(clusters[c].getId() == currentCluster){
//                        clusters[c].removeImage(images[i].getfilename());
//                    }
//                }
//            
//            
//                //Assign image to nearest cluster
//                for(int c = 0; c < Kvalue; c++){
//                    if(clusters[c].getId() == closestCluster){
//                        clusters[c].addImage(images[i]);
//                    }
//                }
//                images[i].setClusterId(closestCluster);
//                status = false;
//            }
//            cout<<"done assigning images to its nearest cluster. Iteration: "<<count<<endl;
        
//        
//        //Find the new center of each cluster
//        for(int i = 0; i < Kvalue; i++){
//            int clustersize = clusters[i].getSize();
//            for(int c = 0; c < images[0].getfeaturelen(); c++){
//                double sum = 0;
//                if(clustersize > 0){
//                    for(int d = 0; d < clustersize; d++){
//                        sum += clusters[i].getImage(d).feature[c];
//                    }
//                    double newMean = sum/clustersize;
//                    clusters[i].setMean(c, newMean);
//                }
//            }
//        }
//        if(status){
//            cout<<"Done clustering"<<endl;
//            break;
//        }
//        count++;
    }
    


/*
 * getClusteres function definition
 */
std::vector<Cluster>& MKHSIN035::KMeansClusterer::getClusteres(){
    return clusters;
}

/*
 * getK function definition
 */
int MKHSIN035::KMeansClusterer::getK () const{return Kvalue;}


/*
 * operator<< definition
 */
ostream& MKHSIN035::operator<<(std::ostream& os, const MKHSIN035::KMeansClusterer& kt){
    os<<"Clusters:\n\n\n"<<endl;
    KMeansClusterer obj = kt;
    for(int i = 0; i < obj.getK(); i++){
        os<<"Cluster"<<i<<": ";
        for(int j = 0; j < obj.images.size(); j++){
            if(obj.images[j].getClusterId() == i)
                os<<obj.images[j].getfilename()<<" ";
        }
            
        os<<"\n";

    }
    return os;
}
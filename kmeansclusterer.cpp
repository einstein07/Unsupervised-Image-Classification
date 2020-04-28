#include "kmeansclusterer.h"
using namespace MKHSIN035;
using namespace std;

//------------------------------------------------------------------------------
//               Class KMeansClusterer member functions definitions
//------------------------------------------------------------------------------
/*
 * Constructor definition for KMeansClusterer
 */

MKHSIN035::KMeansClusterer::KMeansClusterer(int K, bool colour):Kvalue(K), color(colour){}

/*
 * Destructor definition for KMeansClusterer
 */
MKHSIN035::KMeansClusterer::~KMeansClusterer(){}




void KMeansClusterer::readDataSet(string folder){
    string extension = ".ppm";
    string filename;
    ifstream dataset;
    //images = new unsigned char* [100];
    int counter = 0;
    for (int i = 0; i < 10; i++){
        for(int j = 1; j <=10; j++ ){
            
            string name = filenames[i]+to_string(j)+extension;
            Image obj(name);
            filename = folder+name;
            dataset.open(filename, ios::binary|ios::ate); 
            streampos begin,end;
            
            if(dataset.is_open()){
                end = dataset.tellg();
                string dim;
                string line;

                //Take pointer back to the beginning of the file
                dataset.seekg(0, ios::beg);

                while(getline(dataset, line)){
                    if(line == "255"){
                        begin = dataset.tellg();
                    }
                }
                int size = (end-begin);
                obj.setImageDataSetlen(size);
                char buf[size];
                unsigned char val [size];
                dataset.read(buf, size);
                memcpy(&val, buf, sizeof(val));
                obj.imageDataSet = val;
                
                if(!color)
                    obj.createGreyScale();
                
                //Add image to collection of images
                images.push_back(obj);
                
                

            }
            else{
                cout<<"Could not open file "<<filename<<endl;
            }
            dataset.close();
            counter++;
        }
    }
        
}


int MKHSIN035::KMeansClusterer::closestCentroid(Image image){
    double sum = 0;
    double minDist;
    int closestClusterId;
    int featureSize = 0;
    if(image.color)
        featureSize = image.getRGBfeaturelen();
    else
        featureSize = image.getfeaturelen();
    
    for(int i = 0; i < image.getfeaturelen(); i++){
        sum += pow(clusters[0].getMean(i)- image.feature[i], 2);
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
    vector<int> initialPoints;
    
    for(int i = 0; i < Kvalue; i++){
        while(true){
            srand(time(NULL));
            int index = rand()%images.size();
            if(find(initialPoints.begin(), initialPoints.end(), index) == initialPoints.end()){
                initialPoints.push_back(index);
                images[index].setClusterId(i);
                cout<<index<<"\nImage: "<<images[index].getfilename()<<endl;
                //Create new cluster
                Cluster cluster(i, images[index]);
                clusters.push_back(cluster);
                break;
            }
        }
    }
    cout<<"Clusters initialized successfully"<<endl;
    
    while(true){
        bool status = true;
        
        //Assign each image to its nearest cluster
        for(int i = 0; i < images.size(); i++){
            int currentCluster = images[i].getClusterId();
            int closestCluster = this->closestCentroid(images[i]);
            
            //Remove image from wrong cluster 
            if(currentCluster != closestCluster){
                for(int c = 0; c < Kvalue; c++){
                    if(clusters[c].getId() == currentCluster){
                        clusters[c].removeImage(images[i].getfilename());
                    }
                }
            
            
                //Assign image to nearest cluster
                for(int c = 0; c < Kvalue; c++){
                    if(clusters[c].getId() == closestCluster){
                        clusters[c].addImage(images[i]);
                    }
                }
                images[i].setClusterId(closestCluster);
                status = false;
            }
        }
        
        //Find the new center of each cluster
        for(int i = 0; i < Kvalue; i++){
            int clustersize = clusters[i].getSize();
            for(int c = 0; c < images[0].getfeaturelen(); c++){
                double sum = 0;
                if(clustersize > 0){
                    for(int d = 0; d < clustersize; d++){
                        sum += clusters[i].getImage(d).feature[c];
                    }
                    double newMean = sum/clustersize;
                    clusters[i].setMean(c, newMean);
                }
            }
        }
        if(status){
            cout<<"Done clustering"<<endl;
            break;
        }
    }
    
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
    
    KMeansClusterer obj = kt;
    vector<Cluster> clusters = obj.getClusteres();
    for(int i = 0; i < obj.getK(); i++){
        os<<"Cluster:"<<i<<" ";
        int clusterSize = clusters[i].getSize();
        for(int j = 0; j < clusterSize; j++){
            os<<clusters[i].getImage(j).getfilename()<<" ";
        }
            
        os<<"\n";

    }
    return os;
}
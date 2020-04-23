

/* 
 * File:   clusterer.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 26 March 2020, 22:05
 */

#include <valarray>

#include "clusterer.h"
using namespace MKHSIN035;
using namespace std;

//------------------------------------------------------------------------------
//                      Class Image member functions definitions
//------------------------------------------------------------------------------

/*
 * Default Constructor definition for Image class
 */
MKHSIN035::Image::Image(std::string name):filename(name), cluster_id(0){}

/*
 * Destructor definition for KMeansClusterer
 */
MKHSIN035::Image::~Image(){}

/*
 * setintensitylen definition
 */
void MKHSIN035::Image::setgreyscalelen(int len){greyscalelen = len;}

/*
 * setfeaturelen definition
 */
void MKHSIN035::Image::setfeaturelen(int len){featurelen = len;}

/*
 * setClusterId(int) method definition 
 */
void MKHSIN035::Image::setClusterId(int cluster_id){this->cluster_id = cluster_id;}

/*
 * getfilename definition
 */
string MKHSIN035::Image::getfilename(){return filename;}

/*
 * getintensitylen() definition
 */
int MKHSIN035::Image::getgreyscalelen(){return greyscalelen;}

/*
 * getintensitylen() definition
 */
int MKHSIN035::Image::getfeaturelen(){return featurelen;}

/*
 * getClusterId() definition
 */
int MKHSIN035::Image::getClusterId(){return this->cluster_id;}

//------------------------------------------------------------------------------
//               Class Cluster member functions definitions
//------------------------------------------------------------------------------

/*
 * Constructor definition
 */
MKHSIN035::Cluster::Cluster(int cluster_id, Image image):id(cluster_id){
    for(int i = 0; i < image.getfeaturelen(); i++){
        this->mean.push_back(image.feature[i]);
    }
    this->addImage(image);
}
/*
 * addImage definition
 */
void MKHSIN035::Cluster::addImage(Image image){
    image.setClusterId(this->id);
    clusterImages.push_back(image);
}
/*
 * removeImage definition
 */
bool MKHSIN035::Cluster::removeImage(std::string filename){
    for(int i = 0; i < clusterImages.size(); i++){
        if(clusterImages[i].getfilename() == filename){
            //vector<Image>::const_iterator it = find(images.begin(), images.end(), obj);
            clusterImages.erase(clusterImages.begin()+i);
            return true;
        }
    }
    return false;
}

/*
 * setMean function definition
 */
void MKHSIN035::Cluster::setMean(int position, double value){
    this->mean[position] = value;
}

/*
 * getId function definition
 */
int MKHSIN035::Cluster::getId(){return this->id;}

/*
 * getImage function definition
 */
Image MKHSIN035::Cluster::getImage(int position){return clusterImages[position];}

/*
 * getSize function definition
 */
int MKHSIN035::Cluster::getSize(){return clusterImages.size();}

/*
 * getMean function definition
 */
double MKHSIN035::Cluster::getMean(int position){return mean[position];}


//------------------------------------------------------------------------------
//               Class KMeansClusterer member functions definitions
//------------------------------------------------------------------------------
/*
 * Constructor definition for KMeansClusterer
 */
MKHSIN035::KMeansClusterer::KMeansClusterer(int K):Kvalue(K){}

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
                obj.setgreyscalelen(((end-begin)/3));
                obj.greyscale = new unsigned char[(obj.getgreyscalelen())];
                char buf[end-begin];
                unsigned char val [end-begin];
                dataset.read(buf, end-begin);
                memcpy(&val, buf, sizeof(val));
                
                int count = 0;
                for (int c = 0; c < obj.getgreyscalelen(); c++){
                    obj.greyscale[c] = 0.21*val[count] + 0.72*val[count+1] + 0.07*val[count+2];
                    count += 3;
                }
                
                //obj.intensity = val;
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
    
//    for(int i = 0; i < images.size(); i++){
//                                        
//        cout<<"\nDone reading image "<<images[i].getfilename()<<"\nSize: "<<images[i].getgreyscalelen()<<endl;            
//
//        for (int j = 0; j < images[i].getgreyscalelen(); j++){
//            cout<<+images[i].greyscale[j]<<" ";            
//
//        }
//
//    }
    
}

void MKHSIN035::KMeansClusterer::imageFeature(int bin){
    int featurelen = 256/bin;
    
    
    
   
    for(int i = 0; i < images.size(); i++){
        images[i].feature = new int[featurelen];
        images[i].setfeaturelen(featurelen);
        int Lbound = 0;
        int Ubound = bin;
    
        for (int a = 0; a < images[i].getfeaturelen(); a++){
            images[i].feature[a] = 0;
        }

        
        

        for (int k = 0; k < images[i].getfeaturelen(); k++){
            for (int j = 0; j <= images[i].getgreyscalelen(); j++){
                if (Lbound <= images[i].greyscale[j]  && images[i].greyscale[j] < Ubound){
                    images[i].feature[k]++;
                }

            }
               
            Lbound += bin;
            Ubound += bin;

        }
                    
        //cout<<"Done creating feature for image: "<<i<<endl;

        
    }
    
//   
}

int MKHSIN035::KMeansClusterer::closestCentroid(Image image){
    double sum = 0;
    double minDist;
    int closestClusterId;
    
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
int MKHSIN035::KMeansClusterer::getK(){return Kvalue;}


/*
 * operator<< definition
 */
ostream& MKHSIN035::operator<<(std::ostream& os, MKHSIN035::KMeansClusterer& kt){
    
    vector<Cluster> clusters = kt.getClusteres();
    for(int i = 0; i < kt.getK(); i++){
        os<<"Cluster:"<<i<<" ";
        int clusterSize = clusters[i].getSize();
        for(int j = 0; j < clusterSize; j++){
            os<<clusters[i].getImage(j).getfilename()<<" ";
        }
            
        os<<"\n";

    }
    return os;
}


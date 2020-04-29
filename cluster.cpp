

/* 
 * File:   clusterer.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 26 March 2020, 22:05
 */

#include <valarray>

#include "cluster.h"
using namespace MKHSIN035;
using namespace std;


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
int MKHSIN035::Cluster::getId()const{return this->id;}

/*
 * getImage function definition
 */
Image MKHSIN035::Cluster::getImage(int position)const{return clusterImages[position];}

/*
 * getSize function definition
 */
int MKHSIN035::Cluster::getSize()const{return clusterImages.size();}

/*
 * getMean function definition
 */
double MKHSIN035::Cluster::getMean(int position)const{return mean[position];}





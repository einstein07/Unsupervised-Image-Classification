

/* 
 * File:   clusterer.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 26 March 2020, 22:05
 */

#ifndef CLUSTERER_H
#define CLUSTERER_H
#include "image.h"


namespace MKHSIN035{
    
    class Cluster{
    private:
        int id;
        std::vector <double> mean;
        std::vector <Image> clusterImages;
    public: 
        
        /*
         * Cluster constructor
         */
        Cluster(int cluster_id, Image image);
        
        /*
         * Removes image from cluster
         */
        void addImage(Image image);
        
        /*
         * Removes image specified by filename 
         */
        bool removeImage(std::string filename);
        
        /*
         * sets mean
         */
        void setMean(int position, double value);
        
        /*
         * Returns id for this cluster
         */
        int getId()const;
        
        /*
         * Returns the image at index 'position'
         */
        Image getImage(int position)const;
        
        /*
         * Returns size of clusterImages vector
         */
        int getSize()const;
        
        /*
         * Returns the mean by position
         */
        double getMean(int position)const;
        
        
    };
    
    
    

}

#endif /* CLUSTERER_H */


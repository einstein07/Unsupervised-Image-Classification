

/* 
 * File:   clusterer.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 26 March 2020, 22:05
 */

#ifndef CLUSTERER_H
#define CLUSTERER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <cstring>
#include <ctime>


namespace MKHSIN035{
    class Image{
    
    private:
    
        std::string filename;
        int greyscalelen;
        int featurelen;
        int cluster_id;
        friend class KMeansClusterer;
    
    public:
        //Stores intensity values for each pixel
        unsigned char* greyscale;
        int* feature;
        Image(std::string name);
        ~Image();
        /*
         * Sets the length of the feature array 
         */
        void setfeaturelen(int len);
        /*
         * Sets the length of the intensity array 
         */
        void setgreyscalelen(int len);
        /*
         * Sets cluster id for this image
         */
        void setClusterId(int cluster_id);
        /*
         * Returns filename of image
         */
        std::string getfilename();
        
        /*
         * Returns the length of the intensity array
         */
        int getgreyscalelen();
        
        /*
         * Returns the length of the feature array
         */
        int getfeaturelen();
        
        /*
         * Returns cluster id for this image
         */
        int getClusterId();
        
    };
    
    
    
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
        int getId();
        
        /*
         * Returns the image at index 'position'
         */
        Image getImage(int position);
        
        /*
         * Returns size of clusterImages vector
         */
        int getSize();
        
        /*
         * Returns the mean by position
         */
        double getMean(int position);
        
        
    };
    
    
    
    class KMeansClusterer{
    private:
        int Kvalue;
        std::vector<Cluster> clusters;
    public:
        std::string filenames [10] = {"zero_", "one_", "two_", "three_", "four_", "five_", "six_", "seven_", "eight_", "nine_"}; 
        std::vector<Image> images;
        
        /*
         * Default constructor
         */
        KMeansClusterer(int K);
        
        /*
         * Destructor
         */
        ~KMeansClusterer();
        
        /*
         * This method reads the color images. 
         * Each color image is then converted into greyscale image i.e. a single
         * value per pixel.
         */
        void readDataSet(std::string folder);
        
        /*
         * This method uses a histogram to create an image feature for each image
         */
        void imageFeature(int bin);
        
        int closestCentroid(Image image);

        
        /*
         * This method generates k clusters using the K-means algorithm.
         * 
         */
        void kmeans();
        
        std::vector<Cluster>& getClusteres();
        int getK();
    };
    std::ostream& operator<<(std::ostream& os, KMeansClusterer& kt);


}

#endif /* CLUSTERER_H */


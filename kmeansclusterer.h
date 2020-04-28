/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KMeansClusterer.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 28 April 2020, 20:37
 */

#ifndef KMEANSCLUSTERER_H
#define KMEANSCLUSTERER_H

#include "image.h"
#include "cluster.h"


namespace MKHSIN035{
    class KMeansClusterer{
        private:
            int Kvalue;
            bool color;
            std::vector<Cluster> clusters;
        public:
            std::string filenames [10] = {"zero_", "one_", "two_", "three_", "four_",
            "five_", "six_", "seven_", "eight_", "nine_"}; 
            std::vector<Image> images;

            /*
             * Default constructor
             */
            KMeansClusterer(int K, bool colour);

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
            
            void createGreyScale();

            /*
             * This method uses a histogram to create an image feature for each image
             */
            void imageFeature(int bin);

            /*
             * RGB image feature creation
             */
            void RGBfeature(int bin);

            /*
             * This method returns the cluster id of the nearest cluster to the image
             * passed as an argument
             */
            int closestCentroid(Image image);


            /*
             * This method generates k clusters using the K-means/Floyd algorithm.
             * 
             */
            void kmeansclustering();

            /*
             * Returns a vector of clusters
             */
            std::vector<Cluster>& getClusteres();

            /*
             * Returns K value
             */
            int getK()const;
        };
        std::ostream& operator<<(std::ostream& os, const KMeansClusterer& kt);


}

#endif /* KMEANSCLUSTERER_H */

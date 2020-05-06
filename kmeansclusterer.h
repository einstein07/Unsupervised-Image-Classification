
/* 
 * File:   KMeansClusterer.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 28 April 2020, 20:37
 */

#ifndef KMEANSCLUSTERER_H
#define KMEANSCLUSTERER_H

#include "image.h"


namespace MKHSIN035{
    class KMeansClusterer{
        private:
            int Kvalue;
        public:
            
            std::vector<Image> images;

            /*
             * Default constructor
             */
            KMeansClusterer();
            /*
             * Default constructor
             */
            KMeansClusterer(int K);

            /*
             * Destructor
             */
            ~KMeansClusterer();

            /*
             * Initializes clusters
             */
            void initializeClusters(std::vector<int>& initIndices, std::vector<Image>& centroids, std::vector<std::string>& initialPointsFilenames);

            /*
             * This method generates k clusters using the K-means/Floyd algorithm.
             */
            void kmeansclustering();

            /*
             * Returns K value
             */
            int getK()const;
        };
        
        std::ostream& operator<<(std::ostream& os, const KMeansClusterer& kt);


}

#endif /* KMEANSCLUSTERER_H */

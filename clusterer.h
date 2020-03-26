

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
namespace MKHSIN035{
    class KMeansClusterer{
        KMeansClusterer();
        void readDataSet();
        std::ostream& operator<<(std::ostream& os, const KMeansClusterer& kt);
};

}

#endif /* CLUSTERER_H */


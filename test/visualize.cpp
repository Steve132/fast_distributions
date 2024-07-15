#include "visualize.hpp"
//#include "CImg.h"
#include <stdexcept>
#include <fstream>
//using namespace cimg_library;

namespace visualize{
    void scatter(const char* name,const std::vector<v3>& points){
        size_t N=points.size();
        std::ofstream file("scatter.py");

        file << "dpoints=[" << std::endl;

        auto print1=[&file](const v3& p){
            file << "[" << p[0] << "," << p[1] << "," << p[2] << "]";
        };
        print1(points[0]);
        file << std::endl;
        for(size_t i=1;i<N;i++){
            file << ",";
            print1(points[i]);
            file << std::endl;
        }
        file << "]" << std::endl;
        file << "points_name=\"" << name << "\"" << std::endl;
        file << R"PYTHON(
import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

dpoints=np.array(dpoints)

def plot_points(points):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(points[:, 0], points[:, 1], points[:, 2], c='b', marker='o')

    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    ax.set_title(points_name)

    plt.show()

plot_points(dpoints)

        )PYTHON";
        file.close();
        system("python3 scatter.py");
        
    }
    void scatter(const char* name,const std::vector<v2>& points){
        std::vector<v3> v3points(points.size());
        for(size_t i=0;i<points.size();i++){
            v3points[i][0]=points[i][0];
            v3points[i][1]=points[i][1];
            v3points[i][2]=0.0f;
        }
        scatter(name,v3points);
    }
    void histogram(const std::vector<float>& values,size_t resolution){
        
    }
}
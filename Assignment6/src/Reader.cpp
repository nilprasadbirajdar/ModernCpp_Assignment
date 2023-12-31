#include "../headers/Reader.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

Reader::Reader(std::string filePath)
{
    mFilePath = filePath;
}

Reader::~Reader()
{
}


void Reader::getTriangles(std::vector<Triangle> &triangles)
{
    std::ifstream dataFile;
    dataFile.open(mFilePath);

    
    std::string msg="Error Msg";
    auto displayFileNotFound = [msg]() mutable
    {
        msg = "File not found";
        return msg;
    };
    
    if (!dataFile.is_open())
    {
        std::cout << displayFileNotFound() << std::endl;
        return;
    }
    

    std::string line;

    while (std::getline(dataFile, line))
    {
        if (line.find("vertex") != std::string::npos)
        {
            std::istringstream issobj(line);
            std::string token;
            double x, y, z;

            issobj >> token >> x >> y >> z;

            Point3D point1(x, y, z);

            std::getline(dataFile, line);
            std::istringstream issobj1(line);
            issobj1 >> token >> x >> y >> z;
            Point3D point2(x, y, z);

            std::getline(dataFile, line);
            std::istringstream issobj2(line);
            issobj2 >> token >> x >> y >> z;
            Point3D point3(x, y, z);

            Triangle triangle(point1, point2, point3);
            triangles.push_back(triangle);
        }
    }
    dataFile.close();
}

void Reader::getPoints(std::vector<Point3D> &points)
{
    std::ifstream dataFile;
    dataFile.open(mFilePath);

    if (!dataFile.is_open())
    {
        std::cout << "File not exist" << std::endl;
    }

    std::string line;

    while (std::getline(dataFile, line))
    {
        std::istringstream iss(line);
        std::string token;
        double x, y, z;
        iss >> x >> y >> z;
        points.push_back(Point3D(x, y, z));
    }
    dataFile.close();
}

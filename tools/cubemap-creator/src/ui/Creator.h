//
//  CubemapCreator.h
//
//  Created by Nissim Hadar on 18 Jan 2018.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//
#ifndef hifi_Creator_h
#define hifi_Creator_h

#include <math.h>

#include <QImage>

class Creator {
public:
    Creator();
    ~Creator();

    void create6ColorCube();
    void createSphericalGridCube();

private:
    const int IMAGE_RESOLUTION { 2048 };
    const int IMAGE_WIDTH { IMAGE_RESOLUTION };
    const int NUM_FACES { 6 };
    const int IMAGE_HEIGHT { IMAGE_RESOLUTION * NUM_FACES };
    const int NUM_BYTES_PER_PIXEL { 3 };
    const int PIXEL_BUFFER_SIZE { IMAGE_WIDTH * IMAGE_HEIGHT * NUM_BYTES_PER_PIXEL };

    const double PI = 3.141592653589793;
    const double RAD_TO_DEG = 180.0 / PI;

    unsigned char* buffer;

    QImage* cubeMapImage;
};

#endif // hifi_Creator_h
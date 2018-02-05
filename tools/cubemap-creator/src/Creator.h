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

#include <glm/glm.hpp>

#include <QImage>
#include <QList>

class Star {
public:
    glm::vec3 position;
    double relativeBrightness;
};

class Creator {
public:
    Creator();
    ~Creator();

    void create6ColorCube();
    void createSphericalGridCube();
    void createStarMap();
    void drawStars(QList<Star*> starList);

private:
    const int IMAGE_RESOLUTION { 2048 };
    const int IMAGE_WIDTH { IMAGE_RESOLUTION };
    const int NUM_FACES { 6 };
    const int IMAGE_HEIGHT { IMAGE_RESOLUTION * NUM_FACES };
    const int NUM_BYTES_PER_PIXEL { 3 };
    const int PIXEL_BUFFER_SIZE { IMAGE_WIDTH * IMAGE_HEIGHT * NUM_BYTES_PER_PIXEL };

    const double PI { 3.141592653589793 };
    const double RAD_TO_DEG { 180.0 / PI };
    const double DEG_TO_RAD { PI / 180.0 };
    const double POGSON_RATIO = pow(100, 0.2);

    // Only display eye-visible stars
    const double NAKED_EYE_MAGNITUDE { 4.0 };

    // Sirius is the brightest star
    const double SIRIUS_MAGNITUDE { -1.44 };
    unsigned char* buffer;

    // Half angle of star
    const double STAR_HALF_ANGLE_RAD { 0.10 * DEG_TO_RAD };

    QImage* cubeMapImage;
    QRect rect;
};

#endif // hifi_Creator_h
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
#include <QProgressBar>

#include <map>

class Star {
public:
    glm::vec3 position;
    double    relativeBrightness;
    glm::vec3 color;
    double    halfAngle_rads;
};

class Creator {
public:
    Creator();
    ~Creator();

    void createYellowCube();
    void create6ColorCube();
    void createSphericalGridCube();
    void createStarMap(QProgressBar* progressBar);
    void drawStars(QList<Star*> starList, QProgressBar* progressBar);

private:
    const int NUM_FACES{ 6 };
    const int IMAGE_RESOLUTION { 2048 };
    const int IMAGE_WIDTH { IMAGE_RESOLUTION };
    const int IMAGE_HEIGHT { IMAGE_RESOLUTION * NUM_FACES };
    const int NUM_BYTES_PER_PIXEL { 3 };
    const int PIXEL_BUFFER_SIZE { IMAGE_WIDTH * IMAGE_HEIGHT * NUM_BYTES_PER_PIXEL };

    const double PI { 3.141592653589793 };
    const double RAD_TO_DEG { 180.0 / PI };
    const double DEG_TO_RAD { PI / 180.0 };
    const double POGSON_RATIO = pow(100, 0.2);

    // Only display eye-visible stars
    const double NAKED_EYE_MAGNITUDE { 6.0 };

    // Sirius is the brightest star
    const double SIRIUS_MAGNITUDE { -1.44 };

    // Buffer used to write star images into.  This is the final data that will be saved to file
    unsigned char* buffer;

    // Half angle of star (min and max)
    const double STAR_HALF_ANGLE_MAX_DEG { 0.32 };
    const double STAR_HALF_ANGLE_MIN_DEG { 0.16 };

    QImage* cubeMapImage;
    QRect rect;

    using ColorMap = std::map<QString, int>;
    ColorMap mapR;
    ColorMap mapG;
    ColorMap mapB;
};

#endif // hifi_Creator_h
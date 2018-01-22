//
//  Creator.cpp
//
//  Created by Nissim Hadar on 20 Jan 2018.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include "Creator.h"

Creator::Creator() {
    buffer = new unsigned char[IMAGE_WIDTH * IMAGE_HEIGHT * 6 * 3];

    cubeMapImage = new QImage(buffer, IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_RGB888);
}

Creator::~Creator() {
    delete[] buffer;
}

void Creator::create6ColorCube() {
    // cubemap is 6 consecutive squares, ordered as follows (when looking down -Z axis)
    //      +X (right)        red
    //      -X (left)         green
    //      +Y (up)           blue
    //      -Y (down)         yellow
    //      +Z (aft)          cyan
    //      -Z (forward)      magenta
    //
    // 3 bytes per pixel (RGB)
    //

    int offset { 0 };
    for (int face = 0; face < 6; ++face) {
        for (int row = 0; row < IMAGE_RESOLUTION; ++row) {
            for (int pixel = 0; pixel < IMAGE_RESOLUTION; ++pixel) {
                buffer[offset++] = (face == 0 || face == 3 || face == 5) ? 255 : 0; // red
                buffer[offset++] = (face == 1 || face == 3 || face == 4) ? 255 : 0; // green
                buffer[offset++] = (face == 2 || face == 4 || face == 5) ? 255 : 0; // blue
            }
        }
    }

    cubeMapImage->save(("D:\\GitHub\\m.jpg"));
}

void Creator::createSphericalGridCube() {
    int offset { 0 };
    const double HALF_WIDTH { IMAGE_RESOLUTION / 2.0 };
    for (int face = 0; face < 6; ++face) {
        for (int row = 0; row < IMAGE_RESOLUTION; ++row) {
            for (int pix = 0; pix < IMAGE_RESOLUTION; ++pix) {
                // Assuming the cube size is 2x2x2, compute the spherical coordinates of the pixel
                double x, y, z;
                switch (face) {
                case 0:
                    x = 1.0;
                    y = (HALF_WIDTH - row) / HALF_WIDTH;
                    z = (pix - HALF_WIDTH) / HALF_WIDTH;
                    break;
                case 1:
                    x = -1.0;
                    y = (HALF_WIDTH - row) / HALF_WIDTH;
                    z = (HALF_WIDTH - pix) / HALF_WIDTH;
                    break;
                case 2:
                    x = (pix - HALF_WIDTH) / HALF_WIDTH;
                    y = 1.0;
                    z = (HALF_WIDTH - row) / HALF_WIDTH;
                    break;
                case 3:
                    x = (pix - HALF_WIDTH) / HALF_WIDTH;
                    y = -1.0;
                    z = (row - HALF_WIDTH) / HALF_WIDTH;
                    break;
                case 4:
                    x = (HALF_WIDTH - pix) / HALF_WIDTH;
                    y = (HALF_WIDTH - row) / HALF_WIDTH;
                    z = 1.0;
                    break;
                case 5:
                    x = (pix - HALF_WIDTH) / HALF_WIDTH;
                    y = (HALF_WIDTH - row) / HALF_WIDTH;
                    z = -1.0;
                    break;
                }

                double phi   = atan2(-x, -z);
                double r     = sqrt(x * x + z * z);
                double theta = atan2(y, r);

                if (z > 0.0) {
                    buffer[offset++] = 255;
                    buffer[offset++] = 0;
                    buffer[offset++] = 255;
                } else {
                    buffer[offset++] = 0;
                    buffer[offset++] = 255;
                    buffer[offset++] = 255;
                }
            }
        }
    }

    cubeMapImage->save(("D:\\GitHub\\g.jpg"));
}

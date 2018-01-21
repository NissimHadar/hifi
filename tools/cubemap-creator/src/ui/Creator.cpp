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

#include <QImage>

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
    const int IMAGE_WIDTH  { IMAGE_RESOLUTION };
    const int IMAGE_HEIGHT { IMAGE_RESOLUTION * 6 };
    unsigned char* buffer = new unsigned char[IMAGE_WIDTH * IMAGE_HEIGHT * 6 * 3];

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

    QImage cubeMapImage(buffer, IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_RGB888);
    cubeMapImage.save(("D:\\GitHub\\m.jpg"));

    delete[] buffer;
}

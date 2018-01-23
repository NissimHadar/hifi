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

#include <QPainter>

Creator::Creator() {
    buffer = new unsigned char[PIXEL_BUFFER_SIZE];

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

    // Add axes
    QRect rect = cubeMapImage->rect();
    QPainter p;
    p.begin(cubeMapImage);

    p.setPen(QPen(Qt::black));
    p.setFont(QFont("Times", 36, QFont::Bold));

    p.drawText(QRect(0, 0 + 0 * IMAGE_WIDTH, IMAGE_WIDTH, IMAGE_WIDTH), Qt::AlignCenter, "+X");
    p.drawText(QRect(0, 0 + 1 * IMAGE_WIDTH, IMAGE_WIDTH, IMAGE_WIDTH), Qt::AlignCenter, "-X");
    p.drawText(QRect(0, 0 + 2 * IMAGE_WIDTH, IMAGE_WIDTH, IMAGE_WIDTH), Qt::AlignCenter, "+Y");
    p.drawText(QRect(0, 0 + 3 * IMAGE_WIDTH, IMAGE_WIDTH, IMAGE_WIDTH), Qt::AlignCenter, "-Y");
    p.drawText(QRect(0, 0 + 4 * IMAGE_WIDTH, IMAGE_WIDTH, IMAGE_WIDTH), Qt::AlignCenter, "+Z");
    p.drawText(QRect(0, 0 + 5 * IMAGE_WIDTH, IMAGE_WIDTH, IMAGE_WIDTH), Qt::AlignCenter, "-Z");

    p.end();

    cubeMapImage->save(("D:\\GitHub\\m.jpg"));
}

void Creator::createSphericalGridCube() {
    // Image quality is improved by using 3x3 subsampling
    // This will use a single byte for each sub-pixel
    const int OVER_SAMPLING { 9 };
    const int RAW_BUFFER_SIZE { IMAGE_WIDTH * OVER_SAMPLING * IMAGE_HEIGHT * OVER_SAMPLING };
    unsigned char* rawBuffer = new unsigned char[RAW_BUFFER_SIZE];

    int offset { 0 };
    const double HALF_WIDTH { IMAGE_RESOLUTION * OVER_SAMPLING / 2.0 };
    for (int face = 0; face < 6; ++face) {
        for (int row = 0; row < IMAGE_RESOLUTION * OVER_SAMPLING; ++row) {
            for (int pix = 0; pix < IMAGE_RESOLUTION * OVER_SAMPLING; ++pix) {
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

                double phi_degs = phi * RAD_TO_DEG;
                double theta_degs = theta * RAD_TO_DEG;

                if (abs(fmod(phi_degs, 30)) < 0.2 || abs(fmod(theta_degs, 30)) < 0.2) {
                    // Draw 30 degree latitude and longitude lines
                    rawBuffer[offset++] = 1;
                } else if (abs(fmod(phi_degs, 10)) < 0.1 || abs(fmod(theta_degs, 10)) < 0.1) {
                    // Draw 10 degree latitude and longitude lines
                    rawBuffer[offset++] = 1;
                } else {
                    rawBuffer[offset++] = 0;
                }
            }
        }
    }

    // Now compute average for each pixel
    // Note: outer 3 loops are over the output space
    //       the two inner loops are over the sub-pixels
    int bufferOffset { 0 };
    for (int face = 0; face < 6; ++face) {
        for (int row = 0; row < IMAGE_RESOLUTION; ++row) {
            for (int pix = 0; pix < IMAGE_RESOLUTION; ++pix) {
                int sum { 0 };
                int subRow { (face * IMAGE_RESOLUTION + row) * OVER_SAMPLING };
                for (int i = 0; i < OVER_SAMPLING; ++i) {
                    int subPix { pix * OVER_SAMPLING };
                    for (int j = 0; j < OVER_SAMPLING; ++j) {
                        sum += rawBuffer[subRow * IMAGE_RESOLUTION * OVER_SAMPLING + subPix++];
                    }
                    ++subRow;
                }

                unsigned char pixelIntensity = (255 * sum) / (OVER_SAMPLING * OVER_SAMPLING);
                buffer[bufferOffset++] = pixelIntensity;
                buffer[bufferOffset++] = pixelIntensity;
                buffer[bufferOffset++] = pixelIntensity;
            }
        }
    }

    // Add axes
    double d = tan(30.0 * DEG_TO_RAD); // offset from centre for 30 degrees

    QRect rect = cubeMapImage->rect();
    QPainter p;
    p.begin(cubeMapImage);

    p.setPen(QPen(Qt::red));
    p.setFont(QFont("Times", 36, QFont::Bold));

    p.drawText(QPoint(IMAGE_WIDTH / 2,                       11 * IMAGE_WIDTH / 2),   "N");
    p.drawText(QPoint(IMAGE_WIDTH / 2 + d * IMAGE_WIDTH / 2, 11 * IMAGE_WIDTH / 2),  "30");
    p.drawText(QPoint(IMAGE_WIDTH / 2 - d * IMAGE_WIDTH / 2,  1 * IMAGE_WIDTH / 2),  "60");
    p.drawText(QPoint(IMAGE_WIDTH / 2,                        1 * IMAGE_WIDTH / 2),   "E");
    p.drawText(QPoint(IMAGE_WIDTH / 2 + d * IMAGE_WIDTH / 2,  1 * IMAGE_WIDTH / 2), "120");
    p.drawText(QPoint(IMAGE_WIDTH / 2 - d * IMAGE_WIDTH / 2,  9 * IMAGE_WIDTH / 2), "150");
    p.drawText(QPoint(IMAGE_WIDTH / 2,                        9 * IMAGE_WIDTH / 2),   "S");
    p.drawText(QPoint(IMAGE_WIDTH / 2 + d * IMAGE_WIDTH / 2,  9 * IMAGE_WIDTH / 2), "210");
    p.drawText(QPoint(IMAGE_WIDTH / 2 - d * IMAGE_WIDTH / 2,  3 * IMAGE_WIDTH / 2), "240");
    p.drawText(QPoint(IMAGE_WIDTH / 2,                        3 * IMAGE_WIDTH / 2),   "W");
    p.drawText(QPoint(IMAGE_WIDTH / 2 + d * IMAGE_WIDTH / 2,  3 * IMAGE_WIDTH / 2), "300");
    p.drawText(QPoint(IMAGE_WIDTH / 2 - d * IMAGE_WIDTH / 2, 11 * IMAGE_WIDTH / 2), "330");

    p.end();

    cubeMapImage->save(("D:\\GitHub\\g.jpg"));
}

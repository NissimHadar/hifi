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

#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QTextStream>

Creator::Creator() {
    buffer = new unsigned char[PIXEL_BUFFER_SIZE];

    cubeMapImage = new QImage(buffer, IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_RGB888);
    rect = cubeMapImage->rect();

    // Initialize colour maps - see http://www.vendian.org/mncharity/dir3/starcolor/
    mapR["O"] = 155;
    mapG["O"] = 176;
    mapB["O"] = 255;

    mapR["B"] = 170;
    mapG["B"] = 191;
    mapB["B"] = 255;

    mapR["A"] = 202;
    mapG["A"] = 215;
    mapB["A"] = 255;

    mapR["F"] = 248;
    mapG["F"] = 247;
    mapB["F"] = 255;

    mapR["G"] = 255;
    mapG["G"] = 244;
    mapB["G"] = 234;

    mapR["K"] = 255;
    mapG["K"] = 210;
    mapB["K"] = 161;

    mapR["M"] = 255;
    mapG["M"] = 204;
    mapB["M"] = 111;
}

Creator::~Creator() {
    delete[] buffer;
}

void Creator::createWhiteCube() {
    int offset{ 0 };
    for (int face = 0; face < NUM_FACES; ++face) {
        for (int row = 0; row < IMAGE_RESOLUTION; ++row) {
            for (int pixel = 0; pixel < IMAGE_RESOLUTION; ++pixel) {
                buffer[offset++] = 255;  // red
                buffer[offset++] = 255;  // green
                buffer[offset++] = 255;  // blue
            }
        }
    }

    cubeMapImage->save(("D:\\GitHub\\WhiteCube.jpg"));
}

void Creator::createYellowCube() {
    int offset{ 0 };
    for (int face = 0; face < NUM_FACES; ++face) {
        for (int row = 0; row < IMAGE_RESOLUTION; ++row) {
            for (int pixel = 0; pixel < IMAGE_RESOLUTION; ++pixel) {
                buffer[offset++] = 255;  // red
                buffer[offset++] = 255;  // green
                buffer[offset++] =   0;  // blue
            }
        }
    }

    cubeMapImage->save(("D:\\GitHub\\YellowCube.jpg"));
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
    for (int face = 0; face < NUM_FACES; ++face) {
        for (int row = 0; row < IMAGE_RESOLUTION; ++row) {
            for (int pixel = 0; pixel < IMAGE_RESOLUTION; ++pixel) {
                buffer[offset++] = (face == 0 || face == 3 || face == 5) ? 255 : 0; // red
                buffer[offset++] = (face == 1 || face == 3 || face == 4) ? 255 : 0; // green
                buffer[offset++] = (face == 2 || face == 4 || face == 5) ? 255 : 0; // blue
            }
        }
    }

    // Add axes
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

    cubeMapImage->save(("D:\\GitHub\\colours.jpg"));
}

void Creator::createSphericalGridCube() {
    // Image quality is improved by using 3x3 subsampling
    // This will use a single byte for each sub-pixel
    const int OVER_SAMPLING { 3 };
    const int RAW_BUFFER_SIZE { IMAGE_WIDTH * OVER_SAMPLING * IMAGE_HEIGHT * OVER_SAMPLING };
    unsigned char* rawBuffer = new unsigned char[RAW_BUFFER_SIZE];

    int offset { 0 };
    const double HALF_WIDTH { IMAGE_RESOLUTION * OVER_SAMPLING / 2.0 };
    for (int face = 0; face < NUM_FACES; ++face) {
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

                double phi   = atan2(x, z);
                double r     = sqrt(x * x + z * z);
                double theta = atan2(y, r);

                double phi_degs = phi * RAD_TO_DEG;
                double theta_degs = theta * RAD_TO_DEG;

                const double MAJOR_LINE_WIDTH { 0.2 };
                const double MINOR_LINE_WIDTH { 0.1 };
                if (abs(fmod(phi_degs, 30)) < MAJOR_LINE_WIDTH || abs(fmod(theta_degs, 30)) < MAJOR_LINE_WIDTH) {
                    // Draw 30 degree latitude and longitude lines
                    rawBuffer[offset] = 1;
                } else if (abs(fmod(phi_degs, 10)) < MINOR_LINE_WIDTH || abs(fmod(theta_degs, 10)) < MINOR_LINE_WIDTH) {
                    // Draw 10 degree latitude and longitude lines
                    rawBuffer[offset] = 1;
                } else {
                    rawBuffer[offset] = 0;
                }
                ++offset;
            }
        }
    }

    // Now compute average for each pixel
    // Note: outer 3 loops are over the output space
    //       the two inner loops are over the sub-pixels
    int bufferOffset { 0 };
    for (int face = 0; face < NUM_FACES; ++face) {
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

    cubeMapImage->save(("D:\\GitHub\\grid.jpg"));
}

void Creator::drawStars(QList<Star*> stars, QProgressBar* progressBar) {
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setValue(0);
    progressBar->setVisible(true);

    // Image quality is improved by using 3x3 subsampling
    // This will use a single byte for each colour of each sub-pixel
    const int OVER_SAMPLING { 3 };
    const int RAW_BUFFER_SIZE { IMAGE_WIDTH * OVER_SAMPLING * IMAGE_HEIGHT * OVER_SAMPLING };
    unsigned char* rawBufferR = new unsigned char[RAW_BUFFER_SIZE];
    unsigned char* rawBufferG = new unsigned char[RAW_BUFFER_SIZE];
    unsigned char* rawBufferB = new unsigned char[RAW_BUFFER_SIZE];

    // Set rawBuffer to 0, the following code only increments the current value
    for (int i = 0; i < RAW_BUFFER_SIZE; ++i) {
        rawBufferR[i] = 0;
        rawBufferG[i] = 0;
        rawBufferB[i] = 0;
    }

    int offset { 0 };

    // progress bar advances for each line
    const int FULL_PROGRESS_BAR = NUM_FACES * IMAGE_RESOLUTION * OVER_SAMPLING;
    const double HALF_WIDTH { IMAGE_RESOLUTION * OVER_SAMPLING / 2.0 };
    for (int face = 0; face < NUM_FACES; ++face) {
        for (int row = 0; row < IMAGE_RESOLUTION * OVER_SAMPLING; ++row) {
            progressBar->setValue((float)100.0 * (face * IMAGE_RESOLUTION * OVER_SAMPLING + row) / FULL_PROGRESS_BAR);
            QApplication::processEvents();

            for (int pix = 0; pix < IMAGE_RESOLUTION * OVER_SAMPLING; ++pix) {
                // Assuming the cube size is 2x2x2, compute the spherical coordinates of the pixel
                glm::vec3 pixelPos;
                switch (face) {
                case 0:
                    pixelPos.x = 1.0;
                    pixelPos.y = (HALF_WIDTH - row) / HALF_WIDTH;
                    pixelPos.z = (pix - HALF_WIDTH) / HALF_WIDTH;
                    break;
                case 1:
                    pixelPos.x = -1.0;
                    pixelPos.y = (HALF_WIDTH - row) / HALF_WIDTH;
                    pixelPos.z = (HALF_WIDTH - pix) / HALF_WIDTH;
                    break;
                case 2:
                    pixelPos.x = (pix - HALF_WIDTH) / HALF_WIDTH;
                    pixelPos.y = 1.0;
                    pixelPos.z = (HALF_WIDTH - row) / HALF_WIDTH;
                    break;
                case 3:
                    pixelPos.x = (pix - HALF_WIDTH) / HALF_WIDTH;
                    pixelPos.y = -1.0;
                    pixelPos.z = (row - HALF_WIDTH) / HALF_WIDTH;
                    break;
                case 4:
                    pixelPos.x = (HALF_WIDTH - pix) / HALF_WIDTH;
                    pixelPos.y = (HALF_WIDTH - row) / HALF_WIDTH;
                    pixelPos.z = 1.0;
                    break;
                case 5:
                    pixelPos.x = (pix - HALF_WIDTH) / HALF_WIDTH;
                    pixelPos.y = (HALF_WIDTH - row) / HALF_WIDTH;
                    pixelPos.z = -1.0;
                    break;
                }

                // Now that we have the position of the pixel, compare to each star
                double pixelPosLength = glm::length(pixelPos);

                for (int i = 0; i < stars.size(); ++i) {
                    Star* star = stars[i];

                    double angle_rad = acos(glm::dot(pixelPos, star->position) / pixelPosLength);
                    if (angle_rad <= star->halfAngle_rads) {
                        // The modulation factor is a small power of the angle cosine.  This is a number that is usually close to 1
                        float modulationFactor = pow((star->halfAngle_rads - angle_rad) / star->halfAngle_rads, 0.15);
                        rawBufferR[offset] = star->color.r  * modulationFactor;
                        rawBufferG[offset] = star->color.g  * modulationFactor;
                        rawBufferB[offset] = star->color.b  * modulationFactor;
                    }
                }
                ++offset;
            }
        }
    }

    // Now compute average for each pixel
    // Note: outer 3 loops are over the output space
    //       the two inner loops are over the sub-pixels
    int bufferOffset { 0 };
    for (int face = 0; face < NUM_FACES; ++face) {
        for (int row = 0; row < IMAGE_RESOLUTION; ++row) {
            for (int pix = 0; pix < IMAGE_RESOLUTION; ++pix) {
                glm::vec3 sum { 0 };
                int subRow { (face * IMAGE_RESOLUTION + row) * OVER_SAMPLING };
                for (int i = 0; i < OVER_SAMPLING; ++i) {
                    int subPix { pix * OVER_SAMPLING };
                    for (int j = 0; j < OVER_SAMPLING; ++j) {
                        sum.r += rawBufferR[subRow * IMAGE_RESOLUTION * OVER_SAMPLING + subPix];
                        sum.g += rawBufferG[subRow * IMAGE_RESOLUTION * OVER_SAMPLING + subPix];
                        sum.b += rawBufferB[subRow * IMAGE_RESOLUTION * OVER_SAMPLING + subPix];
                        ++subPix;
                    }
                    ++subRow;
                }

                buffer[bufferOffset++] = sum.r / (OVER_SAMPLING * OVER_SAMPLING);
                buffer[bufferOffset++] = sum.g / (OVER_SAMPLING * OVER_SAMPLING);
                buffer[bufferOffset++] = sum.b / (OVER_SAMPLING * OVER_SAMPLING);
            }
        }
    }

    cubeMapImage->save(("D:\\GitHub\\StarMap.jpg"));

    progressBar->setVisible(false);
}

void Creator::createStarMap(QProgressBar* progressBar) {
    // Read in star data
    QFile starDataFile("hygdata_v3.csv");
    if (!starDataFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", starDataFile.errorString());
        exit(-1);
    }

    QTextStream starDataStream(&starDataFile);

    // The angular size of a displayed star is proportional to the square root of it's brightness
    // This effect provides some control over a star's brightness, as the dynamic range is insufficient
    // This is computed as A * sqrt(brightness difference) + B
    const double MAX_DELTA_MAGNITUDE = NAKED_EYE_MAGNITUDE - SIRIUS_MAGNITUDE;
    const double SQRT_MIN_RELATIVE_BRIGHTNESS = sqrt(pow(POGSON_RATIO, -MAX_DELTA_MAGNITUDE));
    const double A = (STAR_HALF_ANGLE_MAX_DEG - STAR_HALF_ANGLE_MIN_DEG) / (1.0 - SQRT_MIN_RELATIVE_BRIGHTNESS);
    const double B = STAR_HALF_ANGLE_MAX_DEG - A;

    // See "README for hygdata.md" for description
    // First line is headers, second is the sun
    starDataStream.readLine();
    starDataStream.readLine();

    QList<Star*> stars;

    while (!starDataStream.atEnd()) {
        QString line = starDataStream.readLine();
        QStringList fields = line.split(",");

        double magnitude = fields[13].toDouble();
        if (magnitude <= NAKED_EYE_MAGNITUDE) {
            Star* star = new Star;

            // Note that right ascension is in hours
            double rightAscension_rad = fields[7].toDouble() * DEG_TO_RAD * 15.0;
            double declination_rad    = fields[8].toDouble() * DEG_TO_RAD;

            // Right ascension 0 is towards -z, increasing towards -x
            // Declination of 90 degrees is towards +y
            // Locate face.  The range is set to 1, then xyz are computed
            star->position.x = -sin(rightAscension_rad) * cos(declination_rad);
            star->position.z = -cos(rightAscension_rad) * cos(declination_rad);
            star->position.y =  sin(declination_rad);

            // The sqrt of the relative brightness is stored.
            // This is to reduce the dynamic range
            double deltaMagnitude = magnitude - SIRIUS_MAGNITUDE;
            star->relativeBrightness = pow(POGSON_RATIO, -deltaMagnitude / 2.0);
            
            // A and B are explained above
            star->halfAngle_rads = DEG_TO_RAD * (A * star->relativeBrightness + B);

            // The star's colour is determined by the spectrum.
            // Due to the very limited colour gamut, only the first character is used
            // As an optimization, the colour is modulated by the brightness at this early stage
            QString spectrum = fields[15][0];

            star->color.r = mapR[spectrum] * star->relativeBrightness;
            star->color.g = mapB[spectrum] * star->relativeBrightness;
            star->color.b = mapG[spectrum] * star->relativeBrightness;

            stars.push_back(star);
        }
    }

    starDataFile.close();

    drawStars(stars, progressBar);

    qDeleteAll(stars);
    stars.clear();
}
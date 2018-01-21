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

class Creator {
public:
    void create6ColorCube();

private:
    const int IMAGE_RESOLUTION { 2048 };
};

#endif // hifi_Creator_h
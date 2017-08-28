//
//  Created by Bradley Austin Davis on 2015/12/10
//  Copyright 2015 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include "NsightHelpers.h"


#if defined(_WIN32) && defined(NSIGHT_FOUND)

#include "nvToolsExt.h"

static const char* NSIGHT_FLAG("NSIGHT_LAUNCHED");
static const bool nsightLaunched = qEnvironmentVariableIsSet(NSIGHT_FLAG);

bool nsightActive() {
    return nsightLaunched;
}

#else

bool nsightActive() {
    return false;
}

#endif // _WIN32

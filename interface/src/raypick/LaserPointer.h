//
//  LaserPointer.h
//  interface/src/raypick
//
//  Created by Sam Gondelman 7/11/2017
//  Copyright 2017 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//
#ifndef hifi_LaserPointer_h
#define hifi_LaserPointer_h

#include <QString>
#include <glm/glm.hpp>

#include <DependencyManager.h>
#include <shared/ReadWriteLockable.h>

#include "ui/overlays/Overlay.h"

class RayPickResult;

struct LockEndObject {
    QUuid id { QUuid() };
    bool isOverlay { false };
    glm::mat4 offsetMat { glm::mat4() };
};

class RenderState {

public:
    RenderState() {}
    RenderState(const OverlayID& startID, const OverlayID& pathID, const OverlayID& endID);

    const OverlayID& getStartID() const { return _startID; }
    const OverlayID& getPathID() const { return _pathID; }
    const OverlayID& getEndID() const { return _endID; }
    const bool& doesStartIgnoreRays() const { return _startIgnoreRays; }
    const bool& doesPathIgnoreRays() const { return _pathIgnoreRays; }
    const bool& doesEndIgnoreRays() const { return _endIgnoreRays; }

    void setEndDim(const glm::vec3& endDim) { _endDim = endDim; }
    const glm::vec3& getEndDim() const { return _endDim; }

    void setLineWidth(const float& lineWidth) { _lineWidth = lineWidth; }
    const float& getLineWidth() const { return _lineWidth; }

    void deleteOverlays();

private:
    OverlayID _startID;
    OverlayID _pathID;
    OverlayID _endID;
    bool _startIgnoreRays;
    bool _pathIgnoreRays;
    bool _endIgnoreRays;

    glm::vec3 _endDim;
    float _lineWidth;
};


class LaserPointer : public ReadWriteLockable {

public:
    using Pointer = std::shared_ptr<LaserPointer>;

    typedef std::unordered_map<std::string, RenderState> RenderStateMap;
    typedef std::unordered_map<std::string, std::pair<float, RenderState>> DefaultRenderStateMap;

    LaserPointer(const QVariant& rayProps, const RenderStateMap& renderStates, const DefaultRenderStateMap& defaultRenderStates,
        const bool faceAvatar, const bool centerEndY, const bool lockEnd, const bool distanceScaleEnd, const bool scaleWithAvatar, const bool enabled);
    ~LaserPointer();

    QUuid getRayUID() { return _rayPickUID; }
    void enable();
    void disable();
    const RayPickResult getPrevRayPickResult();

    void setRenderState(const std::string& state);
    // You cannot use editRenderState to change the overlay type of any part of the laser pointer.  You can only edit the properties of the existing overlays.
    void editRenderState(const std::string& state, const QVariant& startProps, const QVariant& pathProps, const QVariant& endProps);

    void setPrecisionPicking(const bool precisionPicking);
    void setLaserLength(const float laserLength);
    void setLockEndUUID(QUuid objectID, const bool isOverlay, const glm::mat4& offsetMat = glm::mat4());

    void setIgnoreItems(const QVector<QUuid>& ignoreItems) const;
    void setIncludeItems(const QVector<QUuid>& includeItems) const;

    void update();

private:
    bool _renderingEnabled;
    float _laserLength { 0.0f };
    std::string _currentRenderState { "" };
    RenderStateMap _renderStates;
    DefaultRenderStateMap _defaultRenderStates;
    bool _faceAvatar;
    bool _centerEndY;
    bool _lockEnd;
    bool _distanceScaleEnd;
    bool _scaleWithAvatar;
    LockEndObject _lockEndObject;

    const QUuid _rayPickUID;

    void updateRenderStateOverlay(const OverlayID& id, const QVariant& props);
    void updateRenderState(const RenderState& renderState, const IntersectionType type, const float distance, const QUuid& objectID, const PickRay& pickRay, const bool defaultState);
    void disableRenderState(const RenderState& renderState);

};

#endif // hifi_LaserPointer_h

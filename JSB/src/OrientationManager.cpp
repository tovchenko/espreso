#include "OrientationManager.h"
#include "cocos2d_specifics.hpp"

using namespace es;


auto OrientationManager::getInstance()->OrientationManager* {
    static OrientationManager* _sInstance = nullptr;
    if (!_sInstance) _sInstance = new OrientationManager;
        return _sInstance;
}

auto OrientationManager::postOrientation(Orientation& orientation)->void {
    _orientation = orientation;
}
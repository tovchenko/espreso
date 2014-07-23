
#ifndef OrientationManager_H
#define OrientationManager_H

#include "cocos2d.h"
using namespace cocos2d;

namespace es {
    
    class OrientationManager {
    public:
        enum class Orientation {
            UNKNOWN,
            PORTRAIT,
            LANDSCAPE
        };
        
        static auto getInstance()->OrientationManager*;
        
        auto postOrientation(Orientation& orientation)->void;
        auto getOrientation() const->Orientation { return _orientation; }
        
    protected:
        OrientationManager() {}
        
        Orientation _orientation;
    };
}

#endif // OrientationManager_H


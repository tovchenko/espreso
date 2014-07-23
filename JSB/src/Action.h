
#ifndef EspresoAction_H
#define EspresoAction_H

#include "cocos2d.h"
using namespace cocos2d;

namespace es {
    
    class EspresoAction : public Action {
    public:
        EspresoAction() {}
        static auto create()->EspresoAction*;
        
        virtual auto clone() const->Action*;
        virtual auto reverse() const->Action*;
        virtual auto step(float dt)->void;
    };
}

#endif // EspresoAction_H


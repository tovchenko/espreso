
#ifndef EspresoAction_H
#define EspresoAction_H

#include "cocos2d.h"

namespace es {
    
    class Action : public cocos2d::Action {
    public:
        static auto create()->Action*;
        
        virtual auto clone() const->cocos2d::Action*;
        virtual auto reverse() const->cocos2d::Action*;
        virtual auto step(float dt)->void;
    };
}

#endif // EspresoAction_H



#ifndef espreso_H
#define espreso_H

#include "cocos2d.h"

namespace es {
    
    class EspresoAction : public cocos2d::Action {
    public:
        EspresoAction() {}
        static EspresoAction* create();
    
        virtual std::string description() const { return cocos2d::Action::description(); }
        virtual cocos2d::Action* clone() const;
        virtual cocos2d::Action* reverse() const;
        virtual bool isDone() const { return cocos2d::Action::isDone(); }
        virtual void startWithTarget(cocos2d::Node *target) { cocos2d::Action::startWithTarget(target); }
        virtual void stop() { cocos2d::Action::stop(); }
        virtual void step(float dt);
        virtual void update(float time) { cocos2d::Action::update(time); }
        cocos2d::Node* getTarget() const { return cocos2d::Action::getTarget(); }
        void setTarget(cocos2d::Node *target) { cocos2d::Action::setTarget(target); }
        cocos2d::Node* getOriginalTarget() const { return cocos2d::Action::getOriginalTarget(); }
        void setOriginalTarget(cocos2d::Node *originalTarget) { cocos2d::Action::setOriginalTarget(originalTarget); }
        int getTag() const { return cocos2d::Action::getTag(); }
        void setTag(int tag) { cocos2d::Action::setTag(tag); }
    };
    
    
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

#endif // espreso_H


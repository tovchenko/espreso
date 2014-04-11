
#ifndef espreso_H
#define espreso_H

#include "cocos2d.h"

namespace es {
    
    class EspresoAction : public cocos2d::Action {
    public:
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
        
    protected:
        EspresoAction() {}
    };
    
    
    class EspresoComponent : public cocos2d::Component {
    public:
        static EspresoComponent* create();
    
        virtual bool init() { return cocos2d::Component::init(); }
        virtual void onEnter() { return cocos2d::Component::onEnter(); }
        virtual void onExit() { return cocos2d::Component::onExit(); }
        virtual void update(float delta) { return cocos2d::Component::update(delta); }
        virtual bool serialize(void* r) { return cocos2d::Component::serialize(r); }
        virtual bool isEnabled() const { return cocos2d::Component::isEnabled(); }
        virtual void setEnabled(bool b) { cocos2d::Component::setEnabled(b); }
        const std::string& getName() const { return cocos2d::Component::getName(); }
        void setName(const std::string& name) { cocos2d::Component::setName(name); }
        void setOwner(cocos2d::Node *pOwner) { cocos2d::Component::setOwner(pOwner); }
        cocos2d::Node* getOwner() const { return cocos2d::Component::getOwner(); }
        
    protected:
        EspresoComponent() {}
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


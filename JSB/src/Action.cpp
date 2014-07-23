#include "Action.h"
#include "cocos2d_specifics.hpp"

using namespace es;


auto EspresoAction::create()->EspresoAction* {
	auto ret = new EspresoAction();
    if (ret) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

auto EspresoAction::step(float dt)->void {
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    js_proxy_t* p = jsb_get_native_proxy(this);
    if (!p) {
        CCLOG("JSB: Wrong native object = %p", this);
        return;
    }
    
    jsval retval;
    jsval dataVal = DOUBLE_TO_JSVAL(dt);
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "step", 1, &dataVal, &retval);
}

auto EspresoAction::clone() const->Action* {
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    js_proxy_t* p = jsb_get_native_proxy(const_cast<EspresoAction*>(this));
    if (!p) {
        CCLOG("JSB: Wrong native object = %p", this);
        return nullptr;
    }
    
    jsval retval;
    jsval dataVal = INT_TO_JSVAL(1);
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "clone", 1, &dataVal, &retval);
    return static_cast<cocos2d::Action*>(JSVAL_TO_PRIVATE(retval));
}

auto EspresoAction::reverse() const->Action* {
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    js_proxy_t* p = jsb_get_native_proxy(const_cast<EspresoAction*>(this));
    if (!p) {
        CCLOG("JSB: Wrong native object = %p", this);
        return nullptr;
    }
    
    jsval retval;
    jsval dataVal = INT_TO_JSVAL(1);
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "reverse", 1, &dataVal, &retval);
    return static_cast<cocos2d::Action*>(JSVAL_TO_PRIVATE(retval));
}
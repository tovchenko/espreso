#include "Action.h"
#include "cocos2d_specifics.hpp"

using namespace es;


auto Action::create()->Action* {
	auto ret = new Action();
    if (ret) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

auto Action::step(float dt)->void {
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

auto Action::clone() const->cocos2d::Action* {
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    js_proxy_t* p = jsb_get_native_proxy(const_cast<Action*>(this));
    if (!p) {
        CCLOG("JSB: Wrong native object = %p", this);
        return nullptr;
    }
    
    jsval retval;
    jsval dataVal = INT_TO_JSVAL(1);
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "clone", 1, &dataVal, &retval);
    auto retProxy = jsb_get_js_proxy(JSVAL_TO_OBJECT(retval));
    return static_cast<cocos2d::Action*>(retProxy->ptr);
}

auto Action::reverse() const->cocos2d::Action* {
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    js_proxy_t* p = jsb_get_native_proxy(const_cast<Action*>(this));
    if (!p) {
        CCLOG("JSB: Wrong native object = %p", this);
        return nullptr;
    }
    
    jsval retval;
    jsval dataVal = INT_TO_JSVAL(1);
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "reverse", 1, &dataVal, &retval);
    auto retProxy = jsb_get_js_proxy(JSVAL_TO_OBJECT(retval));
    return static_cast<cocos2d::Action*>(retProxy->ptr);
}
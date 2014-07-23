#include "MenuItemScalable.h"
#include "cocos2d_specifics.hpp"

using namespace es;


auto MenuItemScalable::create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite)->MenuItemSprite* {
    return create(normalSprite, selectedSprite, disabledSprite, (const ccMenuCallback&)nullptr);
}

auto MenuItemScalable::create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const cocos2d::ccMenuCallback& callback)->MenuItemSprite* {
    auto ret = new MenuItemScalable();
    ret->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
    ret->autorelease();
    return ret;
}

auto MenuItemScalable::selected()->void {
    if (_isCalled)
        return;
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    js_proxy_t* p = jsb_get_native_proxy(const_cast<MenuItemScalable*>(this));
    if (!p) {
        CCLOG("JSB: Wrong native object = %p", this);
        return;
    }
    
    jsval retval;
    jsval dataVal = INT_TO_JSVAL(1);
    _isCalled = true;
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "selected", 1, &dataVal, &retval);
    _isCalled = false;
}

auto MenuItemScalable::unselected()->void {
    if (_isCalled)
        return;
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    js_proxy_t* p = jsb_get_native_proxy(const_cast<MenuItemScalable*>(this));
    if (!p) {
        CCLOG("JSB: Wrong native object = %p", this);
        return;
    }
    
    jsval retval;
    jsval dataVal = INT_TO_JSVAL(1);
    _isCalled = true;
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "unselected", 1, &dataVal, &retval);
    _isCalled = false;
}
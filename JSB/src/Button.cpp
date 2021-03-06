#include "Button.h"
#include "cocos2d_specifics.hpp"

using namespace es;

IMPLEMENT_CLASS_GUI_INFO(es::Button)

auto Button::create()->Button* {
    auto widget = new Button();
    if (widget && widget->init()) {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

auto Button::getNormalTextureScaleInSize() const->Size {
    return Size(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
}

auto Button::onPressStateChangedToNormal()->void {
    ui::Button::onPressStateChangedToNormal();
    const auto coef = getPressedCoef();
    
    if (-1 != coef && !_pressedTextureLoaded && !_scale9Enabled) {
        _buttonNormalRenderer->setScale(_normalTextureScaleXInSize * coef, _normalTextureScaleYInSize * coef);
        _buttonNormalRenderer->runAction(getPressAction(_normalTextureScaleXInSize, _normalTextureScaleYInSize));
    }
}

auto Button::onPressStateChangedToPressed()->void {
    ui::Button::onPressStateChangedToPressed();
    const auto coef = getPressedCoef();
    
    if (-1 != coef && !_pressedTextureLoaded && !_scale9Enabled) {
        _buttonNormalRenderer->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
        _buttonNormalRenderer->runAction(getPressAction(_normalTextureScaleXInSize * coef, _normalTextureScaleYInSize * coef));
    }
}

auto Button::getPressedCoef() const->double {
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    js_proxy_t* p = jsb_get_native_proxy(const_cast<Button*>(this));
    if (!p) {
        return -1;
    }
    
    jsval retval;
    jsval dataVal = INT_TO_JSVAL(1);
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "getPressedCoef", 1, &dataVal, &retval);
    
    return JSVAL_TO_DOUBLE(retval);
}

auto Button::getPressAction(double sx, double sy) const->Action* {
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    js_proxy_t* p = jsb_get_native_proxy(const_cast<Button*>(this));
    if (!p) {
        CCLOG("JSB: Wrong native object = %p", this);
        return nullptr;
    }
    
    jsval retval;
    jsval dataVal[] = {
        DOUBLE_TO_JSVAL(sx),
        DOUBLE_TO_JSVAL(sy)
    };
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "getPressAction", 2, dataVal, &retval);
    auto retProxy = jsb_get_js_proxy(JSVAL_TO_OBJECT(retval));
    return static_cast<Action*>(retProxy->ptr);
}
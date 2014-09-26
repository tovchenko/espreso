#ifndef __controls_h__
#define __controls_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_es_Button_class;
extern JSObject *jsb_es_Button_prototype;

bool js_controls_Button_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_controls_Button_finalize(JSContext *cx, JSObject *obj);
void js_register_controls_Button(JSContext *cx, JSObject *global);
void register_all_controls(JSContext* cx, JSObject* obj);
bool js_controls_Button_getNormalTextureScaleInSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_controls_Button_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_controls_Button_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
#endif


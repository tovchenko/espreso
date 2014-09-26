#ifndef __controls_h__
#define __controls_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_es_EspresoButton_class;
extern JSObject *jsb_es_EspresoButton_prototype;

bool js_controls_EspresoButton_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_controls_EspresoButton_finalize(JSContext *cx, JSObject *obj);
void js_register_controls_EspresoButton(JSContext *cx, JSObject *global);
void register_all_controls(JSContext* cx, JSObject* obj);
bool js_controls_EspresoButton_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_controls_EspresoButton_createInstance(JSContext *cx, uint32_t argc, jsval *vp);
#endif


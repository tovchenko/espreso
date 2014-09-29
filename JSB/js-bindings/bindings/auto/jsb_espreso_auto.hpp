#ifndef __espreso_h__
#define __espreso_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_es_MenuItemScalable_class;
extern JSObject *jsb_es_MenuItemScalable_prototype;

bool js_espreso_MenuItemScalable_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_espreso_MenuItemScalable_finalize(JSContext *cx, JSObject *obj);
void js_register_espreso_MenuItemScalable(JSContext *cx, JSObject *global);
void register_all_espreso(JSContext* cx, JSObject* obj);
bool js_espreso_MenuItemScalable_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_MenuItemScalable_MenuItemScalable(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_es_Action_class;
extern JSObject *jsb_es_Action_prototype;

bool js_espreso_Action_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_espreso_Action_finalize(JSContext *cx, JSObject *obj);
void js_register_espreso_Action(JSContext *cx, JSObject *global);
void register_all_espreso(JSContext* cx, JSObject* obj);
bool js_espreso_Action_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_Action_reverse(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_Action_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_es_OrientationManager_class;
extern JSObject *jsb_es_OrientationManager_prototype;

bool js_espreso_OrientationManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_espreso_OrientationManager_finalize(JSContext *cx, JSObject *obj);
void js_register_espreso_OrientationManager(JSContext *cx, JSObject *global);
void register_all_espreso(JSContext* cx, JSObject* obj);
bool js_espreso_OrientationManager_getOrientation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_OrientationManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
#endif


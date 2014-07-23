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

extern JSClass  *jsb_es_EspresoAction_class;
extern JSObject *jsb_es_EspresoAction_prototype;

bool js_espreso_EspresoAction_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_espreso_EspresoAction_finalize(JSContext *cx, JSObject *obj);
void js_register_espreso_EspresoAction(JSContext *cx, JSObject *global);
void register_all_espreso(JSContext* cx, JSObject* obj);
bool js_espreso_EspresoAction_startWithTarget(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_reverse(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_setOriginalTarget(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_getOriginalTarget(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_update(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_getTarget(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_setTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_getTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_setTarget(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_isDone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_EspresoAction_EspresoAction(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_es_OrientationManager_class;
extern JSObject *jsb_es_OrientationManager_prototype;

bool js_espreso_OrientationManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_espreso_OrientationManager_finalize(JSContext *cx, JSObject *obj);
void js_register_espreso_OrientationManager(JSContext *cx, JSObject *global);
void register_all_espreso(JSContext* cx, JSObject* obj);
bool js_espreso_OrientationManager_getOrientation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_espreso_OrientationManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
#endif


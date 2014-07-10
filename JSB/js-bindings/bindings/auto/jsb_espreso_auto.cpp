#include "jsb_espreso_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "espreso.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JSObject* global = ScriptingCore::getInstance()->getGlobalObject();
	isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && JSVAL_TO_BOOLEAN(initializing);
	if (isNewValid)
	{
		TypeTest<T> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");

		JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
		return true;
	}

    JS_ReportError(cx, "Don't use `new cc.XXX`, please use `cc.XXX.create` instead! ");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
	vp.set(BOOLEAN_TO_JSVAL(true));
	return true;	
}
JSClass  *jsb_es_EspresoAction_class;
JSObject *jsb_es_EspresoAction_prototype;

bool js_espreso_EspresoAction_startWithTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_startWithTarget : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Node* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_espreso_EspresoAction_startWithTarget : Error processing arguments");
		cobj->startWithTarget(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_startWithTarget : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_espreso_EspresoAction_reverse(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_reverse : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Action* ret = cobj->reverse();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Action>(cx, (cocos2d::Action*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_reverse : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoAction_setOriginalTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_setOriginalTarget : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Node* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_espreso_EspresoAction_setOriginalTarget : Error processing arguments");
		cobj->setOriginalTarget(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_setOriginalTarget : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_espreso_EspresoAction_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_clone : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Action* ret = cobj->clone();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Action>(cx, (cocos2d::Action*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoAction_getOriginalTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_getOriginalTarget : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Node* ret = cobj->getOriginalTarget();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_getOriginalTarget : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoAction_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_stop : Invalid Native Object");
	if (argc == 0) {
		cobj->stop();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_stop : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoAction_update(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_update : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_espreso_EspresoAction_update : Error processing arguments");
		cobj->update(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_update : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_espreso_EspresoAction_getTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_getTarget : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Node* ret = cobj->getTarget();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_getTarget : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoAction_setTag(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_setTag : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_espreso_EspresoAction_setTag : Error processing arguments");
		cobj->setTag(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_setTag : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_espreso_EspresoAction_getTag(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_getTag : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getTag();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_getTag : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoAction_setTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_setTarget : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Node* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_espreso_EspresoAction_setTarget : Error processing arguments");
		cobj->setTarget(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_setTarget : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_espreso_EspresoAction_isDone(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoAction* cobj = (es::EspresoAction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoAction_isDone : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isDone();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoAction_isDone : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoAction_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		es::EspresoAction* ret = es::EspresoAction::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<es::EspresoAction>(cx, (es::EspresoAction*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_espreso_EspresoAction_create : wrong number of arguments");
	return false;
}

bool js_espreso_EspresoAction_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    es::EspresoAction* cobj = new es::EspresoAction();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<es::EspresoAction> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "es::EspresoAction");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_es_EspresoAction_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (EspresoAction)", obj);
}

static bool js_es_EspresoAction_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    es::EspresoAction *nobj = new es::EspresoAction();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "es::EspresoAction");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return true;
}
void js_register_espreso_EspresoAction(JSContext *cx, JSObject *global) {
	jsb_es_EspresoAction_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_es_EspresoAction_class->name = "Action";
	jsb_es_EspresoAction_class->addProperty = JS_PropertyStub;
	jsb_es_EspresoAction_class->delProperty = JS_DeletePropertyStub;
	jsb_es_EspresoAction_class->getProperty = JS_PropertyStub;
	jsb_es_EspresoAction_class->setProperty = JS_StrictPropertyStub;
	jsb_es_EspresoAction_class->enumerate = JS_EnumerateStub;
	jsb_es_EspresoAction_class->resolve = JS_ResolveStub;
	jsb_es_EspresoAction_class->convert = JS_ConvertStub;
	jsb_es_EspresoAction_class->finalize = js_es_EspresoAction_finalize;
	jsb_es_EspresoAction_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("startWithTarget", js_espreso_EspresoAction_startWithTarget, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("reverse", js_espreso_EspresoAction_reverse, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setOriginalTarget", js_espreso_EspresoAction_setOriginalTarget, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("clone", js_espreso_EspresoAction_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getOriginalTarget", js_espreso_EspresoAction_getOriginalTarget, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("stop", js_espreso_EspresoAction_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("update", js_espreso_EspresoAction_update, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTarget", js_espreso_EspresoAction_getTarget, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTag", js_espreso_EspresoAction_setTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTag", js_espreso_EspresoAction_getTag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTarget", js_espreso_EspresoAction_setTarget, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isDone", js_espreso_EspresoAction_isDone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_es_EspresoAction_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_espreso_EspresoAction_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_es_EspresoAction_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_es_EspresoAction_class,
		js_espreso_EspresoAction_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "Action", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<es::EspresoAction> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_es_EspresoAction_class;
		p->proto = jsb_es_EspresoAction_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_es_EspresoComponent_class;
JSObject *jsb_es_EspresoComponent_prototype;

bool js_espreso_EspresoComponent_setEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoComponent* cobj = (es::EspresoComponent *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoComponent_setEnabled : Invalid Native Object");
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_espreso_EspresoComponent_setEnabled : Error processing arguments");
		cobj->setEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoComponent_setEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_espreso_EspresoComponent_setName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoComponent* cobj = (es::EspresoComponent *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoComponent_setName : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_espreso_EspresoComponent_setName : Error processing arguments");
		cobj->setName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoComponent_setName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_espreso_EspresoComponent_isEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoComponent* cobj = (es::EspresoComponent *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoComponent_isEnabled : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isEnabled();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoComponent_isEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoComponent_serialize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoComponent* cobj = (es::EspresoComponent *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoComponent_serialize : Invalid Native Object");
	if (argc == 1) {
		void* arg0;
		#pragma warning NO CONVERSION TO NATIVE FOR void*;
		JSB_PRECONDITION2(ok, cx, false, "js_espreso_EspresoComponent_serialize : Error processing arguments");
		bool ret = cobj->serialize(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoComponent_serialize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_espreso_EspresoComponent_update(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoComponent* cobj = (es::EspresoComponent *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoComponent_update : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_espreso_EspresoComponent_update : Error processing arguments");
		cobj->update(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoComponent_update : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_espreso_EspresoComponent_getOwner(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoComponent* cobj = (es::EspresoComponent *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoComponent_getOwner : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Node* ret = cobj->getOwner();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoComponent_getOwner : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoComponent_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoComponent* cobj = (es::EspresoComponent *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoComponent_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoComponent_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoComponent_setOwner(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoComponent* cobj = (es::EspresoComponent *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoComponent_setOwner : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Node* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_espreso_EspresoComponent_setOwner : Error processing arguments");
		cobj->setOwner(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoComponent_setOwner : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_espreso_EspresoComponent_getName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::EspresoComponent* cobj = (es::EspresoComponent *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_EspresoComponent_getName : Invalid Native Object");
	if (argc == 0) {
		const std::string& ret = cobj->getName();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_EspresoComponent_getName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_EspresoComponent_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		es::EspresoComponent* ret = es::EspresoComponent::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<es::EspresoComponent>(cx, (es::EspresoComponent*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_espreso_EspresoComponent_create : wrong number of arguments");
	return false;
}

bool js_espreso_EspresoComponent_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    es::EspresoComponent* cobj = new es::EspresoComponent();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<es::EspresoComponent> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "es::EspresoComponent");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_es_EspresoComponent_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (EspresoComponent)", obj);
}

static bool js_es_EspresoComponent_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    es::EspresoComponent *nobj = new es::EspresoComponent();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "es::EspresoComponent");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return true;
}
void js_register_espreso_EspresoComponent(JSContext *cx, JSObject *global) {
	jsb_es_EspresoComponent_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_es_EspresoComponent_class->name = "Component";
	jsb_es_EspresoComponent_class->addProperty = JS_PropertyStub;
	jsb_es_EspresoComponent_class->delProperty = JS_DeletePropertyStub;
	jsb_es_EspresoComponent_class->getProperty = JS_PropertyStub;
	jsb_es_EspresoComponent_class->setProperty = JS_StrictPropertyStub;
	jsb_es_EspresoComponent_class->enumerate = JS_EnumerateStub;
	jsb_es_EspresoComponent_class->resolve = JS_ResolveStub;
	jsb_es_EspresoComponent_class->convert = JS_ConvertStub;
	jsb_es_EspresoComponent_class->finalize = js_es_EspresoComponent_finalize;
	jsb_es_EspresoComponent_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setEnabled", js_espreso_EspresoComponent_setEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setName", js_espreso_EspresoComponent_setName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isEnabled", js_espreso_EspresoComponent_isEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("serialize", js_espreso_EspresoComponent_serialize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("update", js_espreso_EspresoComponent_update, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getOwner", js_espreso_EspresoComponent_getOwner, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_espreso_EspresoComponent_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setOwner", js_espreso_EspresoComponent_setOwner, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getName", js_espreso_EspresoComponent_getName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_es_EspresoComponent_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_espreso_EspresoComponent_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_es_EspresoComponent_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_es_EspresoComponent_class,
		js_espreso_EspresoComponent_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "Component", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<es::EspresoComponent> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_es_EspresoComponent_class;
		p->proto = jsb_es_EspresoComponent_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_es_OrientationManager_class;
JSObject *jsb_es_OrientationManager_prototype;

bool js_espreso_OrientationManager_getOrientation(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::OrientationManager* cobj = (es::OrientationManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_espreso_OrientationManager_getOrientation : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getOrientation();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_espreso_OrientationManager_getOrientation : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_espreso_OrientationManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		es::OrientationManager* ret = es::OrientationManager::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<es::OrientationManager>(cx, (es::OrientationManager*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_espreso_OrientationManager_getInstance : wrong number of arguments");
	return false;
}



void js_es_OrientationManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (OrientationManager)", obj);
}

void js_register_espreso_OrientationManager(JSContext *cx, JSObject *global) {
	jsb_es_OrientationManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_es_OrientationManager_class->name = "OrientationManager";
	jsb_es_OrientationManager_class->addProperty = JS_PropertyStub;
	jsb_es_OrientationManager_class->delProperty = JS_DeletePropertyStub;
	jsb_es_OrientationManager_class->getProperty = JS_PropertyStub;
	jsb_es_OrientationManager_class->setProperty = JS_StrictPropertyStub;
	jsb_es_OrientationManager_class->enumerate = JS_EnumerateStub;
	jsb_es_OrientationManager_class->resolve = JS_ResolveStub;
	jsb_es_OrientationManager_class->convert = JS_ConvertStub;
	jsb_es_OrientationManager_class->finalize = js_es_OrientationManager_finalize;
	jsb_es_OrientationManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getOrientation", js_espreso_OrientationManager_getOrientation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("getInstance", js_espreso_OrientationManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_es_OrientationManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_es_OrientationManager_class,
		dummy_constructor<es::OrientationManager>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "OrientationManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<es::OrientationManager> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_es_OrientationManager_class;
		p->proto = jsb_es_OrientationManager_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

void register_all_espreso(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	JS::RootedValue nsval(cx);
	JS::RootedObject ns(cx);
	JS_GetProperty(cx, obj, "cc", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "cc", nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_espreso_OrientationManager(cx, obj);
	js_register_espreso_EspresoAction(cx, obj);
	js_register_espreso_EspresoComponent(cx, obj);
}


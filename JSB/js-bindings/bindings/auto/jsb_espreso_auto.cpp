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
JSClass  *jsb_es_MenuItemScalable_class;
JSObject *jsb_es_MenuItemScalable_prototype;

bool js_espreso_MenuItemScalable_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	
	do {
		if (argc == 4) {
			cocos2d::Node* arg0;
			do {
				if (!argv[0].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::Node* arg1;
			do {
				if (!argv[1].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::Node* arg2;
			do {
				if (!argv[2].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg2 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			std::function<void (cocos2d::Ref *)> arg3;
			do {
				std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[3]));
				auto lambda = [=](cocos2d::Ref* larg0) -> void {
					jsval largv[1];
					do {
						if (larg0) {
							js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)larg0);
							largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
						} else {
							largv[0] = JSVAL_NULL;
						}
					} while (0);
					jsval rval;
					bool ok = func->invoke(1, &largv[0], rval);
					if (!ok && JS_IsExceptionPending(cx)) {
						JS_ReportPendingException(cx);
					}
				};
				arg3 = lambda;
			} while(0)
			;
			if (!ok) { ok = true; break; }
			cocos2d::MenuItemSprite* ret = es::MenuItemScalable::create(arg0, arg1, arg2, arg3);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::MenuItemSprite>(cx, (cocos2d::MenuItemSprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 2) {
			cocos2d::Node* arg0;
			do {
				if (!argv[0].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::Node* arg1;
			do {
				if (!argv[1].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::MenuItemSprite* ret = es::MenuItemScalable::create(arg0, arg1);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::MenuItemSprite>(cx, (cocos2d::MenuItemSprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	do {
		if (argc == 3) {
			cocos2d::Node* arg0;
			do {
				if (!argv[0].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::Node* arg1;
			do {
				if (!argv[1].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::Node* arg2;
			do {
				if (!argv[2].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg2 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::MenuItemSprite* ret = es::MenuItemScalable::create(arg0, arg1, arg2);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::MenuItemSprite>(cx, (cocos2d::MenuItemSprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	JS_ReportError(cx, "js_espreso_MenuItemScalable_create : wrong number of arguments");
	return false;
}
bool js_espreso_MenuItemScalable_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    es::MenuItemScalable* cobj = new es::MenuItemScalable();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<es::MenuItemScalable> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "es::MenuItemScalable");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_cocos2d_MenuItemSprite_prototype;

void js_es_MenuItemScalable_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MenuItemScalable)", obj);
}

static bool js_es_MenuItemScalable_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    es::MenuItemScalable *nobj = new es::MenuItemScalable();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "es::MenuItemScalable");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return true;
}
void js_register_espreso_MenuItemScalable(JSContext *cx, JSObject *global) {
	jsb_es_MenuItemScalable_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_es_MenuItemScalable_class->name = "MenuItemSprite";
	jsb_es_MenuItemScalable_class->addProperty = JS_PropertyStub;
	jsb_es_MenuItemScalable_class->delProperty = JS_DeletePropertyStub;
	jsb_es_MenuItemScalable_class->getProperty = JS_PropertyStub;
	jsb_es_MenuItemScalable_class->setProperty = JS_StrictPropertyStub;
	jsb_es_MenuItemScalable_class->enumerate = JS_EnumerateStub;
	jsb_es_MenuItemScalable_class->resolve = JS_ResolveStub;
	jsb_es_MenuItemScalable_class->convert = JS_ConvertStub;
	jsb_es_MenuItemScalable_class->finalize = js_es_MenuItemScalable_finalize;
	jsb_es_MenuItemScalable_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FN("ctor", js_es_MenuItemScalable_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_espreso_MenuItemScalable_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_es_MenuItemScalable_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_MenuItemSprite_prototype,
		jsb_es_MenuItemScalable_class,
		js_espreso_MenuItemScalable_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "MenuItemSprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<es::MenuItemScalable> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_es_MenuItemScalable_class;
		p->proto = jsb_es_MenuItemScalable_prototype;
		p->parentProto = jsb_cocos2d_MenuItemSprite_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_es_EspresoAction_class;
JSObject *jsb_es_EspresoAction_prototype;

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


extern JSObject *jsb_cocos2d_Action_prototype;

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
		JS_FN("clone", js_espreso_EspresoAction_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("reverse", js_espreso_EspresoAction_reverse, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_es_EspresoAction_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_espreso_EspresoAction_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_es_EspresoAction_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_Action_prototype,
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
		p->parentProto = jsb_cocos2d_Action_prototype;
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

	js_register_espreso_MenuItemScalable(cx, obj);
	js_register_espreso_OrientationManager(cx, obj);
	js_register_espreso_EspresoAction(cx, obj);
}


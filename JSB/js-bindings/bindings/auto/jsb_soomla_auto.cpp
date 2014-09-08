#include "jsb_soomla_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "Cocos2dxStore.h"

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
JSClass  *jsb_soomla_CCDomain_class;
JSObject *jsb_soomla_CCDomain_prototype;

bool js_soomla_CCDomain_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCDomain* cobj = (soomla::CCDomain *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCDomain_initWithDictionary : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCDomain_initWithDictionary : Error processing arguments");
		bool ret = cobj->initWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCDomain_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCDomain_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCDomain* cobj = (soomla::CCDomain *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCDomain_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCDomain_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}


void js_soomla_CCDomain_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCDomain)", obj);
}

void js_register_soomla_CCDomain(JSContext *cx, JSObject *global) {
	jsb_soomla_CCDomain_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCDomain_class->name = "Domain";
	jsb_soomla_CCDomain_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCDomain_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCDomain_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCDomain_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCDomain_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCDomain_class->resolve = JS_ResolveStub;
	jsb_soomla_CCDomain_class->convert = JS_ConvertStub;
	jsb_soomla_CCDomain_class->finalize = js_soomla_CCDomain_finalize;
	jsb_soomla_CCDomain_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("initWithDictionary", js_soomla_CCDomain_initWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCDomain_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_soomla_CCDomain_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_CCDomain_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "Domain", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCDomain> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCDomain_class;
		p->proto = jsb_soomla_CCDomain_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCSoomlaEntity_class;
JSObject *jsb_soomla_CCSoomlaEntity_prototype;

bool js_soomla_CCSoomlaEntity_setDescription(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaEntity* cobj = (soomla::CCSoomlaEntity *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaEntity_setDescription : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSoomlaEntity_setDescription : Error processing arguments");
		cobj->setDescription(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaEntity_setDescription : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCSoomlaEntity_setName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaEntity* cobj = (soomla::CCSoomlaEntity *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaEntity_setName : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSoomlaEntity_setName : Error processing arguments");
		cobj->setName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaEntity_setName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCSoomlaEntity_getName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaEntity* cobj = (soomla::CCSoomlaEntity *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaEntity_getName : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getName();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaEntity_getName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSoomlaEntity_getDescription(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaEntity* cobj = (soomla::CCSoomlaEntity *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaEntity_getDescription : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getDescription();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaEntity_getDescription : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSoomlaEntity_getId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaEntity* cobj = (soomla::CCSoomlaEntity *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaEntity_getId : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getId();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaEntity_getId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSoomlaEntity_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaEntity* cobj = (soomla::CCSoomlaEntity *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaEntity_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaEntity_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSoomlaEntity_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaEntity* cobj = (soomla::CCSoomlaEntity *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaEntity_init : Invalid Native Object");
	if (argc == 3) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSoomlaEntity_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaEntity_init : wrong number of arguments: %d, was expecting %d", argc, 3);
	return false;
}
bool js_soomla_CCSoomlaEntity_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaEntity* cobj = (soomla::CCSoomlaEntity *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaEntity_initWithDictionary : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSoomlaEntity_initWithDictionary : Error processing arguments");
		bool ret = cobj->initWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaEntity_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCSoomlaEntity_setId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaEntity* cobj = (soomla::CCSoomlaEntity *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaEntity_setId : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSoomlaEntity_setId : Error processing arguments");
		cobj->setId(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaEntity_setId : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCSoomlaEntity_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCSoomlaEntity* cobj = new soomla::CCSoomlaEntity();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCSoomlaEntity> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCSoomlaEntity");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_soomla_CCDomain_prototype;

void js_soomla_CCSoomlaEntity_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCSoomlaEntity)", obj);
}

static bool js_soomla_CCSoomlaEntity_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    soomla::CCSoomlaEntity *nobj = new soomla::CCSoomlaEntity();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCSoomlaEntity");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return true;
}
void js_register_soomla_CCSoomlaEntity(JSContext *cx, JSObject *global) {
	jsb_soomla_CCSoomlaEntity_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCSoomlaEntity_class->name = "SoomlaEntity";
	jsb_soomla_CCSoomlaEntity_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCSoomlaEntity_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCSoomlaEntity_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCSoomlaEntity_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCSoomlaEntity_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCSoomlaEntity_class->resolve = JS_ResolveStub;
	jsb_soomla_CCSoomlaEntity_class->convert = JS_ConvertStub;
	jsb_soomla_CCSoomlaEntity_class->finalize = js_soomla_CCSoomlaEntity_finalize;
	jsb_soomla_CCSoomlaEntity_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setDescription", js_soomla_CCSoomlaEntity_setDescription, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setName", js_soomla_CCSoomlaEntity_setName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getName", js_soomla_CCSoomlaEntity_getName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getDescription", js_soomla_CCSoomlaEntity_getDescription, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getId", js_soomla_CCSoomlaEntity_getId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCSoomlaEntity_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCSoomlaEntity_init, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithDictionary", js_soomla_CCSoomlaEntity_initWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setId", js_soomla_CCSoomlaEntity_setId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_soomla_CCSoomlaEntity_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_soomla_CCSoomlaEntity_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCDomain_prototype,
		jsb_soomla_CCSoomlaEntity_class,
		js_soomla_CCSoomlaEntity_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "SoomlaEntity", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCSoomlaEntity> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCSoomlaEntity_class;
		p->proto = jsb_soomla_CCSoomlaEntity_prototype;
		p->parentProto = jsb_soomla_CCDomain_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCVirtualItem_class;
JSObject *jsb_soomla_CCVirtualItem_prototype;

bool js_soomla_CCVirtualItem_save(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualItem* cobj = (soomla::CCVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualItem_save : Invalid Native Object");
	if (argc == 0) {
		cobj->save();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualItem_save : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCVirtualItem_getItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualItem* cobj = (soomla::CCVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualItem_getItemId : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getItemId();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualItem_getItemId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCVirtualItem_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualItem* cobj = (soomla::CCVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualItem_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualItem_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCVirtualItem_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 3) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualItem_create : Error processing arguments");
		soomla::CCVirtualItem* ret = soomla::CCVirtualItem::create(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualItem>(cx, (soomla::CCVirtualItem*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualItem_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCVirtualItem_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualItem_createWithDictionary : Error processing arguments");
		soomla::CCVirtualItem* ret = soomla::CCVirtualItem::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualItem>(cx, (soomla::CCVirtualItem*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualItem_createWithDictionary : wrong number of arguments");
	return false;
}


extern JSObject *jsb_soomla_CCSoomlaEntity_prototype;

void js_soomla_CCVirtualItem_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCVirtualItem)", obj);
}

void js_register_soomla_CCVirtualItem(JSContext *cx, JSObject *global) {
	jsb_soomla_CCVirtualItem_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCVirtualItem_class->name = "VirtualItem";
	jsb_soomla_CCVirtualItem_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCVirtualItem_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCVirtualItem_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCVirtualItem_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCVirtualItem_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCVirtualItem_class->resolve = JS_ResolveStub;
	jsb_soomla_CCVirtualItem_class->convert = JS_ConvertStub;
	jsb_soomla_CCVirtualItem_class->finalize = js_soomla_CCVirtualItem_finalize;
	jsb_soomla_CCVirtualItem_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("save", js_soomla_CCVirtualItem_save, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getItemId", js_soomla_CCVirtualItem_getItemId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCVirtualItem_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCVirtualItem_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCVirtualItem_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCVirtualItem_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCSoomlaEntity_prototype,
		jsb_soomla_CCVirtualItem_class,
		dummy_constructor<soomla::CCVirtualItem>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "VirtualItem", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCVirtualItem> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCVirtualItem_class;
		p->proto = jsb_soomla_CCVirtualItem_prototype;
		p->parentProto = jsb_soomla_CCSoomlaEntity_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCPurchaseType_class;
JSObject *jsb_soomla_CCPurchaseType_prototype;

bool js_soomla_CCPurchaseType_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchaseType* cobj = (soomla::CCPurchaseType *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchaseType_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchaseType_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCPurchaseType_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		soomla::CCPurchaseType* ret = soomla::CCPurchaseType::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchaseType>(cx, (soomla::CCPurchaseType*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCPurchaseType_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCPurchaseType_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCPurchaseType* cobj = new soomla::CCPurchaseType();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCPurchaseType> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCPurchaseType");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_soomla_CCPurchaseType_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCPurchaseType)", obj);
}

static bool js_soomla_CCPurchaseType_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    soomla::CCPurchaseType *nobj = new soomla::CCPurchaseType();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCPurchaseType");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return true;
}
void js_register_soomla_CCPurchaseType(JSContext *cx, JSObject *global) {
	jsb_soomla_CCPurchaseType_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCPurchaseType_class->name = "PurchaseType";
	jsb_soomla_CCPurchaseType_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCPurchaseType_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCPurchaseType_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCPurchaseType_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCPurchaseType_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCPurchaseType_class->resolve = JS_ResolveStub;
	jsb_soomla_CCPurchaseType_class->convert = JS_ConvertStub;
	jsb_soomla_CCPurchaseType_class->finalize = js_soomla_CCPurchaseType_finalize;
	jsb_soomla_CCPurchaseType_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("init", js_soomla_CCPurchaseType_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_soomla_CCPurchaseType_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCPurchaseType_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCPurchaseType_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_CCPurchaseType_class,
		js_soomla_CCPurchaseType_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PurchaseType", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCPurchaseType> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCPurchaseType_class;
		p->proto = jsb_soomla_CCPurchaseType_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCPurchasableVirtualItem_class;
JSObject *jsb_soomla_CCPurchasableVirtualItem_prototype;

bool js_soomla_CCPurchasableVirtualItem_getPurchaseType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchasableVirtualItem* cobj = (soomla::CCPurchasableVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchasableVirtualItem_getPurchaseType : Invalid Native Object");
	if (argc == 0) {
		soomla::CCPurchaseType* ret = cobj->getPurchaseType();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchaseType>(cx, (soomla::CCPurchaseType*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchasableVirtualItem_getPurchaseType : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCPurchasableVirtualItem_setPurchaseType(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchasableVirtualItem* cobj = (soomla::CCPurchasableVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchasableVirtualItem_setPurchaseType : Invalid Native Object");
	if (argc == 1) {
		soomla::CCPurchaseType* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchasableVirtualItem_setPurchaseType : Error processing arguments");
		cobj->setPurchaseType(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchasableVirtualItem_setPurchaseType : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCPurchasableVirtualItem_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchasableVirtualItem* cobj = (soomla::CCPurchasableVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchasableVirtualItem_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchasableVirtualItem_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCPurchasableVirtualItem_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchasableVirtualItem* cobj = (soomla::CCPurchasableVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchasableVirtualItem_init : Invalid Native Object");
	if (argc == 4) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		soomla::CCPurchaseType* arg3;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchasableVirtualItem_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1, arg2, arg3);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchasableVirtualItem_init : wrong number of arguments: %d, was expecting %d", argc, 4);
	return false;
}
bool js_soomla_CCPurchasableVirtualItem_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchasableVirtualItem* cobj = (soomla::CCPurchasableVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchasableVirtualItem_initWithDictionary : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchasableVirtualItem_initWithDictionary : Error processing arguments");
		bool ret = cobj->initWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchasableVirtualItem_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCPurchasableVirtualItem_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 4) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		soomla::CCPurchaseType* arg3;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchasableVirtualItem_create : Error processing arguments");
		soomla::CCPurchasableVirtualItem* ret = soomla::CCPurchasableVirtualItem::create(arg0, arg1, arg2, arg3);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchasableVirtualItem>(cx, (soomla::CCPurchasableVirtualItem*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCPurchasableVirtualItem_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCPurchasableVirtualItem_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchasableVirtualItem_createWithDictionary : Error processing arguments");
		soomla::CCPurchasableVirtualItem* ret = soomla::CCPurchasableVirtualItem::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchasableVirtualItem>(cx, (soomla::CCPurchasableVirtualItem*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCPurchasableVirtualItem_createWithDictionary : wrong number of arguments");
	return false;
}

bool js_soomla_CCPurchasableVirtualItem_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCPurchasableVirtualItem* cobj = new soomla::CCPurchasableVirtualItem();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCPurchasableVirtualItem> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCPurchasableVirtualItem");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_soomla_CCVirtualItem_prototype;

void js_soomla_CCPurchasableVirtualItem_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCPurchasableVirtualItem)", obj);
}

void js_register_soomla_CCPurchasableVirtualItem(JSContext *cx, JSObject *global) {
	jsb_soomla_CCPurchasableVirtualItem_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCPurchasableVirtualItem_class->name = "PurchasableVirtualItem";
	jsb_soomla_CCPurchasableVirtualItem_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCPurchasableVirtualItem_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCPurchasableVirtualItem_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCPurchasableVirtualItem_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCPurchasableVirtualItem_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCPurchasableVirtualItem_class->resolve = JS_ResolveStub;
	jsb_soomla_CCPurchasableVirtualItem_class->convert = JS_ConvertStub;
	jsb_soomla_CCPurchasableVirtualItem_class->finalize = js_soomla_CCPurchasableVirtualItem_finalize;
	jsb_soomla_CCPurchasableVirtualItem_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getPurchaseType", js_soomla_CCPurchasableVirtualItem_getPurchaseType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPurchaseType", js_soomla_CCPurchasableVirtualItem_setPurchaseType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCPurchasableVirtualItem_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCPurchasableVirtualItem_init, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithDictionary", js_soomla_CCPurchasableVirtualItem_initWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCPurchasableVirtualItem_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCPurchasableVirtualItem_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCPurchasableVirtualItem_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCVirtualItem_prototype,
		jsb_soomla_CCPurchasableVirtualItem_class,
		js_soomla_CCPurchasableVirtualItem_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PurchasableVirtualItem", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCPurchasableVirtualItem> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCPurchasableVirtualItem_class;
		p->proto = jsb_soomla_CCPurchasableVirtualItem_prototype;
		p->parentProto = jsb_soomla_CCVirtualItem_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCVirtualGood_class;
JSObject *jsb_soomla_CCVirtualGood_prototype;

bool js_soomla_CCVirtualGood_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 4) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		soomla::CCPurchaseType* arg3;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualGood_create : Error processing arguments");
		soomla::CCVirtualGood* ret = soomla::CCVirtualGood::create(arg0, arg1, arg2, arg3);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualGood>(cx, (soomla::CCVirtualGood*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualGood_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCVirtualGood_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualGood_createWithDictionary : Error processing arguments");
		soomla::CCVirtualGood* ret = soomla::CCVirtualGood::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualGood>(cx, (soomla::CCVirtualGood*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualGood_createWithDictionary : wrong number of arguments");
	return false;
}


extern JSObject *jsb_soomla_CCPurchasableVirtualItem_prototype;

void js_soomla_CCVirtualGood_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCVirtualGood)", obj);
}

void js_register_soomla_CCVirtualGood(JSContext *cx, JSObject *global) {
	jsb_soomla_CCVirtualGood_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCVirtualGood_class->name = "VirtualGood";
	jsb_soomla_CCVirtualGood_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCVirtualGood_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCVirtualGood_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCVirtualGood_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCVirtualGood_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCVirtualGood_class->resolve = JS_ResolveStub;
	jsb_soomla_CCVirtualGood_class->convert = JS_ConvertStub;
	jsb_soomla_CCVirtualGood_class->finalize = js_soomla_CCVirtualGood_finalize;
	jsb_soomla_CCVirtualGood_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCVirtualGood_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCVirtualGood_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCVirtualGood_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCPurchasableVirtualItem_prototype,
		jsb_soomla_CCVirtualGood_class,
		dummy_constructor<soomla::CCVirtualGood>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "VirtualGood", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCVirtualGood> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCVirtualGood_class;
		p->proto = jsb_soomla_CCVirtualGood_prototype;
		p->parentProto = jsb_soomla_CCPurchasableVirtualItem_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCLifetimeVG_class;
JSObject *jsb_soomla_CCLifetimeVG_prototype;

bool js_soomla_CCLifetimeVG_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 4) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		soomla::CCPurchaseType* arg3;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCLifetimeVG_create : Error processing arguments");
		soomla::CCLifetimeVG* ret = soomla::CCLifetimeVG::create(arg0, arg1, arg2, arg3);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCLifetimeVG>(cx, (soomla::CCLifetimeVG*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCLifetimeVG_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCLifetimeVG_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCLifetimeVG_createWithDictionary : Error processing arguments");
		soomla::CCLifetimeVG* ret = soomla::CCLifetimeVG::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCLifetimeVG>(cx, (soomla::CCLifetimeVG*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCLifetimeVG_createWithDictionary : wrong number of arguments");
	return false;
}


extern JSObject *jsb_soomla_CCVirtualGood_prototype;

void js_soomla_CCLifetimeVG_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCLifetimeVG)", obj);
}

void js_register_soomla_CCLifetimeVG(JSContext *cx, JSObject *global) {
	jsb_soomla_CCLifetimeVG_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCLifetimeVG_class->name = "LifetimeVG";
	jsb_soomla_CCLifetimeVG_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCLifetimeVG_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCLifetimeVG_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCLifetimeVG_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCLifetimeVG_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCLifetimeVG_class->resolve = JS_ResolveStub;
	jsb_soomla_CCLifetimeVG_class->convert = JS_ConvertStub;
	jsb_soomla_CCLifetimeVG_class->finalize = js_soomla_CCLifetimeVG_finalize;
	jsb_soomla_CCLifetimeVG_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCLifetimeVG_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCLifetimeVG_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCLifetimeVG_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCVirtualGood_prototype,
		jsb_soomla_CCLifetimeVG_class,
		dummy_constructor<soomla::CCLifetimeVG>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "LifetimeVG", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCLifetimeVG> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCLifetimeVG_class;
		p->proto = jsb_soomla_CCLifetimeVG_prototype;
		p->parentProto = jsb_soomla_CCVirtualGood_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCEquippableVG_class;
JSObject *jsb_soomla_CCEquippableVG_prototype;

bool js_soomla_CCEquippableVG_setEquippingModel(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCEquippableVG* cobj = (soomla::CCEquippableVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCEquippableVG_setEquippingModel : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Integer* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCEquippableVG_setEquippingModel : Error processing arguments");
		cobj->setEquippingModel(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCEquippableVG_setEquippingModel : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCEquippableVG_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCEquippableVG* cobj = (soomla::CCEquippableVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCEquippableVG_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCEquippableVG_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCEquippableVG_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCEquippableVG* cobj = (soomla::CCEquippableVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCEquippableVG_init : Invalid Native Object");
	if (argc == 5) {
		cocos2d::__Integer* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		cocos2d::__String* arg3;
		soomla::CCPurchaseType* arg4;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[4].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[4]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg4 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg4, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCEquippableVG_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCEquippableVG_init : wrong number of arguments: %d, was expecting %d", argc, 5);
	return false;
}
bool js_soomla_CCEquippableVG_getEquippingModel(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCEquippableVG* cobj = (soomla::CCEquippableVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCEquippableVG_getEquippingModel : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Integer* ret = cobj->getEquippingModel();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Integer>(cx, (cocos2d::__Integer*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCEquippableVG_getEquippingModel : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCEquippableVG_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 5) {
		cocos2d::__Integer* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		cocos2d::__String* arg3;
		soomla::CCPurchaseType* arg4;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[4].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[4]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg4 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg4, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCEquippableVG_create : Error processing arguments");
		soomla::CCEquippableVG* ret = soomla::CCEquippableVG::create(arg0, arg1, arg2, arg3, arg4);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCEquippableVG>(cx, (soomla::CCEquippableVG*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCEquippableVG_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCEquippableVG_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCEquippableVG_createWithDictionary : Error processing arguments");
		soomla::CCEquippableVG* ret = soomla::CCEquippableVG::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCEquippableVG>(cx, (soomla::CCEquippableVG*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCEquippableVG_createWithDictionary : wrong number of arguments");
	return false;
}

bool js_soomla_CCEquippableVG_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCEquippableVG* cobj = new soomla::CCEquippableVG();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCEquippableVG> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCEquippableVG");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_soomla_CCLifetimeVG_prototype;

void js_soomla_CCEquippableVG_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCEquippableVG)", obj);
}

void js_register_soomla_CCEquippableVG(JSContext *cx, JSObject *global) {
	jsb_soomla_CCEquippableVG_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCEquippableVG_class->name = "EquippableVG";
	jsb_soomla_CCEquippableVG_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCEquippableVG_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCEquippableVG_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCEquippableVG_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCEquippableVG_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCEquippableVG_class->resolve = JS_ResolveStub;
	jsb_soomla_CCEquippableVG_class->convert = JS_ConvertStub;
	jsb_soomla_CCEquippableVG_class->finalize = js_soomla_CCEquippableVG_finalize;
	jsb_soomla_CCEquippableVG_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setEquippingModel", js_soomla_CCEquippableVG_setEquippingModel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCEquippableVG_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCEquippableVG_init, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getEquippingModel", js_soomla_CCEquippableVG_getEquippingModel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCEquippableVG_create, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCEquippableVG_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCEquippableVG_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCLifetimeVG_prototype,
		jsb_soomla_CCEquippableVG_class,
		js_soomla_CCEquippableVG_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "EquippableVG", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCEquippableVG> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCEquippableVG_class;
		p->proto = jsb_soomla_CCEquippableVG_prototype;
		p->parentProto = jsb_soomla_CCLifetimeVG_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCMarketItem_class;
JSObject *jsb_soomla_CCMarketItem_prototype;

bool js_soomla_CCMarketItem_getMarketTitle(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_getMarketTitle : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getMarketTitle();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_getMarketTitle : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCMarketItem_setMarketDescription(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_setMarketDescription : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCMarketItem_setMarketDescription : Error processing arguments");
		cobj->setMarketDescription(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_setMarketDescription : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCMarketItem_setMarketTitle(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_setMarketTitle : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCMarketItem_setMarketTitle : Error processing arguments");
		cobj->setMarketTitle(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_setMarketTitle : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCMarketItem_getMarketDescription(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_getMarketDescription : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getMarketDescription();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_getMarketDescription : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCMarketItem_setPrice(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_setPrice : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Double* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Double*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCMarketItem_setPrice : Error processing arguments");
		cobj->setPrice(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_setPrice : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCMarketItem_setMarketPrice(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_setMarketPrice : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCMarketItem_setMarketPrice : Error processing arguments");
		cobj->setMarketPrice(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_setMarketPrice : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCMarketItem_getMarketPrice(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_getMarketPrice : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getMarketPrice();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_getMarketPrice : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCMarketItem_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCMarketItem_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_init : Invalid Native Object");
	if (argc == 3) {
		cocos2d::__String* arg0;
		cocos2d::__Integer* arg1;
		cocos2d::__Double* arg2;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__Double*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCMarketItem_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_init : wrong number of arguments: %d, was expecting %d", argc, 3);
	return false;
}
bool js_soomla_CCMarketItem_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_initWithDictionary : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCMarketItem_initWithDictionary : Error processing arguments");
		bool ret = cobj->initWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCMarketItem_getProductId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_getProductId : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getProductId();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_getProductId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCMarketItem_getConsumable(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_getConsumable : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Integer* ret = cobj->getConsumable();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Integer>(cx, (cocos2d::__Integer*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_getConsumable : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCMarketItem_setProductId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_setProductId : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCMarketItem_setProductId : Error processing arguments");
		cobj->setProductId(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_setProductId : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCMarketItem_getPrice(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_getPrice : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Double* ret = cobj->getPrice();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Double>(cx, (cocos2d::__Double*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_getPrice : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCMarketItem_setConsumable(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCMarketItem* cobj = (soomla::CCMarketItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCMarketItem_setConsumable : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Integer* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCMarketItem_setConsumable : Error processing arguments");
		cobj->setConsumable(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCMarketItem_setConsumable : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCMarketItem_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 3) {
		cocos2d::__String* arg0;
		cocos2d::__Integer* arg1;
		cocos2d::__Double* arg2;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__Double*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCMarketItem_create : Error processing arguments");
		soomla::CCMarketItem* ret = soomla::CCMarketItem::create(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCMarketItem>(cx, (soomla::CCMarketItem*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCMarketItem_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCMarketItem_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCMarketItem_createWithDictionary : Error processing arguments");
		soomla::CCMarketItem* ret = soomla::CCMarketItem::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCMarketItem>(cx, (soomla::CCMarketItem*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCMarketItem_createWithDictionary : wrong number of arguments");
	return false;
}

bool js_soomla_CCMarketItem_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCMarketItem* cobj = new soomla::CCMarketItem();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCMarketItem> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCMarketItem");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_soomla_CCDomain_prototype;

void js_soomla_CCMarketItem_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCMarketItem)", obj);
}

void js_register_soomla_CCMarketItem(JSContext *cx, JSObject *global) {
	jsb_soomla_CCMarketItem_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCMarketItem_class->name = "MarketItem";
	jsb_soomla_CCMarketItem_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCMarketItem_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCMarketItem_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCMarketItem_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCMarketItem_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCMarketItem_class->resolve = JS_ResolveStub;
	jsb_soomla_CCMarketItem_class->convert = JS_ConvertStub;
	jsb_soomla_CCMarketItem_class->finalize = js_soomla_CCMarketItem_finalize;
	jsb_soomla_CCMarketItem_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getMarketTitle", js_soomla_CCMarketItem_getMarketTitle, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMarketDescription", js_soomla_CCMarketItem_setMarketDescription, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMarketTitle", js_soomla_CCMarketItem_setMarketTitle, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getMarketDescription", js_soomla_CCMarketItem_getMarketDescription, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPrice", js_soomla_CCMarketItem_setPrice, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMarketPrice", js_soomla_CCMarketItem_setMarketPrice, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getMarketPrice", js_soomla_CCMarketItem_getMarketPrice, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCMarketItem_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCMarketItem_init, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithDictionary", js_soomla_CCMarketItem_initWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getProductId", js_soomla_CCMarketItem_getProductId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getConsumable", js_soomla_CCMarketItem_getConsumable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setProductId", js_soomla_CCMarketItem_setProductId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPrice", js_soomla_CCMarketItem_getPrice, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setConsumable", js_soomla_CCMarketItem_setConsumable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCMarketItem_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCMarketItem_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCMarketItem_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCDomain_prototype,
		jsb_soomla_CCMarketItem_class,
		js_soomla_CCMarketItem_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "MarketItem", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCMarketItem> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCMarketItem_class;
		p->proto = jsb_soomla_CCMarketItem_prototype;
		p->parentProto = jsb_soomla_CCDomain_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCNonConsumableItem_class;
JSObject *jsb_soomla_CCNonConsumableItem_prototype;

bool js_soomla_CCNonConsumableItem_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 4) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		soomla::CCPurchaseType* arg3;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCNonConsumableItem_create : Error processing arguments");
		soomla::CCNonConsumableItem* ret = soomla::CCNonConsumableItem::create(arg0, arg1, arg2, arg3);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCNonConsumableItem>(cx, (soomla::CCNonConsumableItem*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCNonConsumableItem_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCNonConsumableItem_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCNonConsumableItem_createWithDictionary : Error processing arguments");
		soomla::CCNonConsumableItem* ret = soomla::CCNonConsumableItem::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCNonConsumableItem>(cx, (soomla::CCNonConsumableItem*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCNonConsumableItem_createWithDictionary : wrong number of arguments");
	return false;
}

bool js_soomla_CCNonConsumableItem_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCNonConsumableItem* cobj = new soomla::CCNonConsumableItem();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCNonConsumableItem> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCNonConsumableItem");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_soomla_CCPurchasableVirtualItem_prototype;

void js_soomla_CCNonConsumableItem_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCNonConsumableItem)", obj);
}

void js_register_soomla_CCNonConsumableItem(JSContext *cx, JSObject *global) {
	jsb_soomla_CCNonConsumableItem_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCNonConsumableItem_class->name = "NonConsumableItem";
	jsb_soomla_CCNonConsumableItem_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCNonConsumableItem_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCNonConsumableItem_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCNonConsumableItem_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCNonConsumableItem_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCNonConsumableItem_class->resolve = JS_ResolveStub;
	jsb_soomla_CCNonConsumableItem_class->convert = JS_ConvertStub;
	jsb_soomla_CCNonConsumableItem_class->finalize = js_soomla_CCNonConsumableItem_finalize;
	jsb_soomla_CCNonConsumableItem_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCNonConsumableItem_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCNonConsumableItem_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCNonConsumableItem_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCPurchasableVirtualItem_prototype,
		jsb_soomla_CCNonConsumableItem_class,
		js_soomla_CCNonConsumableItem_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "NonConsumableItem", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCNonConsumableItem> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCNonConsumableItem_class;
		p->proto = jsb_soomla_CCNonConsumableItem_prototype;
		p->parentProto = jsb_soomla_CCPurchasableVirtualItem_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCPurchaseWithMarket_class;
JSObject *jsb_soomla_CCPurchaseWithMarket_prototype;

bool js_soomla_CCPurchaseWithMarket_setMarketItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchaseWithMarket* cobj = (soomla::CCPurchaseWithMarket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchaseWithMarket_setMarketItem : Invalid Native Object");
	if (argc == 1) {
		soomla::CCMarketItem* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (soomla::CCMarketItem*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchaseWithMarket_setMarketItem : Error processing arguments");
		cobj->setMarketItem(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchaseWithMarket_setMarketItem : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCPurchaseWithMarket_getMarketItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchaseWithMarket* cobj = (soomla::CCPurchaseWithMarket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchaseWithMarket_getMarketItem : Invalid Native Object");
	if (argc == 0) {
		soomla::CCMarketItem* ret = cobj->getMarketItem();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCMarketItem>(cx, (soomla::CCMarketItem*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchaseWithMarket_getMarketItem : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCPurchaseWithMarket_initWithMarketItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchaseWithMarket* cobj = (soomla::CCPurchaseWithMarket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchaseWithMarket_initWithMarketItem : Invalid Native Object");
	if (argc == 1) {
		soomla::CCMarketItem* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (soomla::CCMarketItem*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchaseWithMarket_initWithMarketItem : Error processing arguments");
		bool ret = cobj->initWithMarketItem(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchaseWithMarket_initWithMarketItem : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCPurchaseWithMarket_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 2) {
		cocos2d::__String* arg0;
		cocos2d::__Double* arg1;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__Double*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchaseWithMarket_create : Error processing arguments");
		soomla::CCPurchaseWithMarket* ret = soomla::CCPurchaseWithMarket::create(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchaseWithMarket>(cx, (soomla::CCPurchaseWithMarket*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCPurchaseWithMarket_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCPurchaseWithMarket_createWithMarketItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		soomla::CCMarketItem* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (soomla::CCMarketItem*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchaseWithMarket_createWithMarketItem : Error processing arguments");
		soomla::CCPurchaseWithMarket* ret = soomla::CCPurchaseWithMarket::createWithMarketItem(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchaseWithMarket>(cx, (soomla::CCPurchaseWithMarket*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCPurchaseWithMarket_createWithMarketItem : wrong number of arguments");
	return false;
}

bool js_soomla_CCPurchaseWithMarket_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;

	JSObject *obj = NULL;
	soomla::CCPurchaseWithMarket* cobj = NULL;
	do {
		if (argc == 1) {
			cocos2d::ValueMap arg0;
			ok &= jsval_to_ccvaluemap(cx, argv[0], &arg0);
			if (!ok) { ok = true; break; }
			cobj = new soomla::CCPurchaseWithMarket(arg0);
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCPurchaseWithMarket> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCPurchaseWithMarket");
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj = new soomla::CCPurchaseWithMarket();
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCPurchaseWithMarket> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCPurchaseWithMarket");
		}
	} while(0);

	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCPurchaseWithMarket_constructor : wrong number of arguments");
	return false;
}


extern JSObject *jsb_soomla_CCPurchaseType_prototype;

void js_soomla_CCPurchaseWithMarket_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCPurchaseWithMarket)", obj);
}

void js_register_soomla_CCPurchaseWithMarket(JSContext *cx, JSObject *global) {
	jsb_soomla_CCPurchaseWithMarket_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCPurchaseWithMarket_class->name = "PurchaseWithMarket";
	jsb_soomla_CCPurchaseWithMarket_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCPurchaseWithMarket_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCPurchaseWithMarket_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCPurchaseWithMarket_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCPurchaseWithMarket_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCPurchaseWithMarket_class->resolve = JS_ResolveStub;
	jsb_soomla_CCPurchaseWithMarket_class->convert = JS_ConvertStub;
	jsb_soomla_CCPurchaseWithMarket_class->finalize = js_soomla_CCPurchaseWithMarket_finalize;
	jsb_soomla_CCPurchaseWithMarket_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setMarketItem", js_soomla_CCPurchaseWithMarket_setMarketItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getMarketItem", js_soomla_CCPurchaseWithMarket_getMarketItem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithMarketItem", js_soomla_CCPurchaseWithMarket_initWithMarketItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCPurchaseWithMarket_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithMarketItem", js_soomla_CCPurchaseWithMarket_createWithMarketItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCPurchaseWithMarket_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCPurchaseType_prototype,
		jsb_soomla_CCPurchaseWithMarket_class,
		js_soomla_CCPurchaseWithMarket_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PurchaseWithMarket", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCPurchaseWithMarket> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCPurchaseWithMarket_class;
		p->proto = jsb_soomla_CCPurchaseWithMarket_prototype;
		p->parentProto = jsb_soomla_CCPurchaseType_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCPurchaseWithVirtualItem_class;
JSObject *jsb_soomla_CCPurchaseWithVirtualItem_prototype;

bool js_soomla_CCPurchaseWithVirtualItem_getItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchaseWithVirtualItem* cobj = (soomla::CCPurchaseWithVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchaseWithVirtualItem_getItemId : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getItemId();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchaseWithVirtualItem_getItemId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCPurchaseWithVirtualItem_getAmount(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchaseWithVirtualItem* cobj = (soomla::CCPurchaseWithVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchaseWithVirtualItem_getAmount : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Integer* ret = cobj->getAmount();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Integer>(cx, (cocos2d::__Integer*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchaseWithVirtualItem_getAmount : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCPurchaseWithVirtualItem_setItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchaseWithVirtualItem* cobj = (soomla::CCPurchaseWithVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchaseWithVirtualItem_setItemId : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchaseWithVirtualItem_setItemId : Error processing arguments");
		cobj->setItemId(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchaseWithVirtualItem_setItemId : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCPurchaseWithVirtualItem_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchaseWithVirtualItem* cobj = (soomla::CCPurchaseWithVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchaseWithVirtualItem_init : Invalid Native Object");
	if (argc == 2) {
		cocos2d::__String* arg0;
		cocos2d::__Integer* arg1;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchaseWithVirtualItem_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchaseWithVirtualItem_init : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCPurchaseWithVirtualItem_setAmount(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCPurchaseWithVirtualItem* cobj = (soomla::CCPurchaseWithVirtualItem *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCPurchaseWithVirtualItem_setAmount : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Integer* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchaseWithVirtualItem_setAmount : Error processing arguments");
		cobj->setAmount(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCPurchaseWithVirtualItem_setAmount : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCPurchaseWithVirtualItem_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 2) {
		cocos2d::__String* arg0;
		cocos2d::__Integer* arg1;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCPurchaseWithVirtualItem_create : Error processing arguments");
		soomla::CCPurchaseWithVirtualItem* ret = soomla::CCPurchaseWithVirtualItem::create(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchaseWithVirtualItem>(cx, (soomla::CCPurchaseWithVirtualItem*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCPurchaseWithVirtualItem_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCPurchaseWithVirtualItem_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;

	JSObject *obj = NULL;
	soomla::CCPurchaseWithVirtualItem* cobj = NULL;
	do {
		if (argc == 1) {
			cocos2d::ValueMap arg0;
			ok &= jsval_to_ccvaluemap(cx, argv[0], &arg0);
			if (!ok) { ok = true; break; }
			cobj = new soomla::CCPurchaseWithVirtualItem(arg0);
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCPurchaseWithVirtualItem> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCPurchaseWithVirtualItem");
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj = new soomla::CCPurchaseWithVirtualItem();
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCPurchaseWithVirtualItem> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCPurchaseWithVirtualItem");
		}
	} while(0);

	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCPurchaseWithVirtualItem_constructor : wrong number of arguments");
	return false;
}


extern JSObject *jsb_soomla_CCPurchaseType_prototype;

void js_soomla_CCPurchaseWithVirtualItem_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCPurchaseWithVirtualItem)", obj);
}

void js_register_soomla_CCPurchaseWithVirtualItem(JSContext *cx, JSObject *global) {
	jsb_soomla_CCPurchaseWithVirtualItem_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCPurchaseWithVirtualItem_class->name = "PurchaseWithVirtualItem";
	jsb_soomla_CCPurchaseWithVirtualItem_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCPurchaseWithVirtualItem_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCPurchaseWithVirtualItem_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCPurchaseWithVirtualItem_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCPurchaseWithVirtualItem_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCPurchaseWithVirtualItem_class->resolve = JS_ResolveStub;
	jsb_soomla_CCPurchaseWithVirtualItem_class->convert = JS_ConvertStub;
	jsb_soomla_CCPurchaseWithVirtualItem_class->finalize = js_soomla_CCPurchaseWithVirtualItem_finalize;
	jsb_soomla_CCPurchaseWithVirtualItem_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getItemId", js_soomla_CCPurchaseWithVirtualItem_getItemId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getAmount", js_soomla_CCPurchaseWithVirtualItem_getAmount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setItemId", js_soomla_CCPurchaseWithVirtualItem_setItemId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCPurchaseWithVirtualItem_init, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAmount", js_soomla_CCPurchaseWithVirtualItem_setAmount, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCPurchaseWithVirtualItem_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCPurchaseWithVirtualItem_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCPurchaseType_prototype,
		jsb_soomla_CCPurchaseWithVirtualItem_class,
		js_soomla_CCPurchaseWithVirtualItem_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PurchaseWithVirtualItem", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCPurchaseWithVirtualItem> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCPurchaseWithVirtualItem_class;
		p->proto = jsb_soomla_CCPurchaseWithVirtualItem_prototype;
		p->parentProto = jsb_soomla_CCPurchaseType_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCSingleUsePackVG_class;
JSObject *jsb_soomla_CCSingleUsePackVG_prototype;

bool js_soomla_CCSingleUsePackVG_getGoodItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSingleUsePackVG* cobj = (soomla::CCSingleUsePackVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSingleUsePackVG_getGoodItemId : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getGoodItemId();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSingleUsePackVG_getGoodItemId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSingleUsePackVG_getGoodAmount(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSingleUsePackVG* cobj = (soomla::CCSingleUsePackVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSingleUsePackVG_getGoodAmount : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Integer* ret = cobj->getGoodAmount();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Integer>(cx, (cocos2d::__Integer*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSingleUsePackVG_getGoodAmount : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSingleUsePackVG_setGoodItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSingleUsePackVG* cobj = (soomla::CCSingleUsePackVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSingleUsePackVG_setGoodItemId : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSingleUsePackVG_setGoodItemId : Error processing arguments");
		cobj->setGoodItemId(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSingleUsePackVG_setGoodItemId : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCSingleUsePackVG_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSingleUsePackVG* cobj = (soomla::CCSingleUsePackVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSingleUsePackVG_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSingleUsePackVG_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSingleUsePackVG_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSingleUsePackVG* cobj = (soomla::CCSingleUsePackVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSingleUsePackVG_init : Invalid Native Object");
	if (argc == 6) {
		cocos2d::__String* arg0;
		cocos2d::__Integer* arg1;
		cocos2d::__String* arg2;
		cocos2d::__String* arg3;
		cocos2d::__String* arg4;
		soomla::CCPurchaseType* arg5;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[4].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[4]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg4 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg4, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[5].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[5]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg5 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg5, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSingleUsePackVG_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSingleUsePackVG_init : wrong number of arguments: %d, was expecting %d", argc, 6);
	return false;
}
bool js_soomla_CCSingleUsePackVG_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSingleUsePackVG* cobj = (soomla::CCSingleUsePackVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSingleUsePackVG_initWithDictionary : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSingleUsePackVG_initWithDictionary : Error processing arguments");
		bool ret = cobj->initWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSingleUsePackVG_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCSingleUsePackVG_setGoodAmount(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSingleUsePackVG* cobj = (soomla::CCSingleUsePackVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSingleUsePackVG_setGoodAmount : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Integer* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSingleUsePackVG_setGoodAmount : Error processing arguments");
		cobj->setGoodAmount(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSingleUsePackVG_setGoodAmount : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCSingleUsePackVG_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 6) {
		cocos2d::__String* arg0;
		cocos2d::__Integer* arg1;
		cocos2d::__String* arg2;
		cocos2d::__String* arg3;
		cocos2d::__String* arg4;
		soomla::CCPurchaseType* arg5;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[4].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[4]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg4 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg4, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[5].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[5]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg5 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg5, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSingleUsePackVG_create : Error processing arguments");
		soomla::CCSingleUsePackVG* ret = soomla::CCSingleUsePackVG::create(arg0, arg1, arg2, arg3, arg4, arg5);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCSingleUsePackVG>(cx, (soomla::CCSingleUsePackVG*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCSingleUsePackVG_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCSingleUsePackVG_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSingleUsePackVG_createWithDictionary : Error processing arguments");
		soomla::CCSingleUsePackVG* ret = soomla::CCSingleUsePackVG::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCSingleUsePackVG>(cx, (soomla::CCSingleUsePackVG*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCSingleUsePackVG_createWithDictionary : wrong number of arguments");
	return false;
}

bool js_soomla_CCSingleUsePackVG_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCSingleUsePackVG* cobj = new soomla::CCSingleUsePackVG();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCSingleUsePackVG> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCSingleUsePackVG");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_soomla_CCVirtualGood_prototype;

void js_soomla_CCSingleUsePackVG_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCSingleUsePackVG)", obj);
}

void js_register_soomla_CCSingleUsePackVG(JSContext *cx, JSObject *global) {
	jsb_soomla_CCSingleUsePackVG_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCSingleUsePackVG_class->name = "SingleUsePackVG";
	jsb_soomla_CCSingleUsePackVG_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCSingleUsePackVG_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCSingleUsePackVG_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCSingleUsePackVG_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCSingleUsePackVG_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCSingleUsePackVG_class->resolve = JS_ResolveStub;
	jsb_soomla_CCSingleUsePackVG_class->convert = JS_ConvertStub;
	jsb_soomla_CCSingleUsePackVG_class->finalize = js_soomla_CCSingleUsePackVG_finalize;
	jsb_soomla_CCSingleUsePackVG_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getGoodItemId", js_soomla_CCSingleUsePackVG_getGoodItemId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getGoodAmount", js_soomla_CCSingleUsePackVG_getGoodAmount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setGoodItemId", js_soomla_CCSingleUsePackVG_setGoodItemId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCSingleUsePackVG_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCSingleUsePackVG_init, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithDictionary", js_soomla_CCSingleUsePackVG_initWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setGoodAmount", js_soomla_CCSingleUsePackVG_setGoodAmount, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCSingleUsePackVG_create, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCSingleUsePackVG_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCSingleUsePackVG_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCVirtualGood_prototype,
		jsb_soomla_CCSingleUsePackVG_class,
		js_soomla_CCSingleUsePackVG_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "SingleUsePackVG", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCSingleUsePackVG> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCSingleUsePackVG_class;
		p->proto = jsb_soomla_CCSingleUsePackVG_prototype;
		p->parentProto = jsb_soomla_CCVirtualGood_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCSingleUseVG_class;
JSObject *jsb_soomla_CCSingleUseVG_prototype;

bool js_soomla_CCSingleUseVG_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 4) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		soomla::CCPurchaseType* arg3;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSingleUseVG_create : Error processing arguments");
		soomla::CCSingleUseVG* ret = soomla::CCSingleUseVG::create(arg0, arg1, arg2, arg3);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCSingleUseVG>(cx, (soomla::CCSingleUseVG*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCSingleUseVG_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCSingleUseVG_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSingleUseVG_createWithDictionary : Error processing arguments");
		soomla::CCSingleUseVG* ret = soomla::CCSingleUseVG::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCSingleUseVG>(cx, (soomla::CCSingleUseVG*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCSingleUseVG_createWithDictionary : wrong number of arguments");
	return false;
}

bool js_soomla_CCSingleUseVG_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;

	JSObject *obj = NULL;
	soomla::CCSingleUseVG* cobj = NULL;
	do {
		if (argc == 2) {
			cocos2d::ValueMap arg0;
			ok &= jsval_to_ccvaluemap(cx, argv[0], &arg0);
			if (!ok) { ok = true; break; }
			soomla::CCPurchaseType* arg1;
			do {
				if (!argv[1].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg1 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cobj = new soomla::CCSingleUseVG(arg0, arg1);
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCSingleUseVG> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCSingleUseVG");
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj = new soomla::CCSingleUseVG();
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCSingleUseVG> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCSingleUseVG");
		}
	} while(0);

	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCSingleUseVG_constructor : wrong number of arguments");
	return false;
}


extern JSObject *jsb_soomla_CCVirtualGood_prototype;

void js_soomla_CCSingleUseVG_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCSingleUseVG)", obj);
}

void js_register_soomla_CCSingleUseVG(JSContext *cx, JSObject *global) {
	jsb_soomla_CCSingleUseVG_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCSingleUseVG_class->name = "SingleUseVG";
	jsb_soomla_CCSingleUseVG_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCSingleUseVG_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCSingleUseVG_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCSingleUseVG_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCSingleUseVG_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCSingleUseVG_class->resolve = JS_ResolveStub;
	jsb_soomla_CCSingleUseVG_class->convert = JS_ConvertStub;
	jsb_soomla_CCSingleUseVG_class->finalize = js_soomla_CCSingleUseVG_finalize;
	jsb_soomla_CCSingleUseVG_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCSingleUseVG_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCSingleUseVG_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCSingleUseVG_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCVirtualGood_prototype,
		jsb_soomla_CCSingleUseVG_class,
		js_soomla_CCSingleUseVG_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "SingleUseVG", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCSingleUseVG> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCSingleUseVG_class;
		p->proto = jsb_soomla_CCSingleUseVG_prototype;
		p->parentProto = jsb_soomla_CCVirtualGood_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCError_class;
JSObject *jsb_soomla_CCError_prototype;

bool js_soomla_CCError_getInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCError* cobj = (soomla::CCError *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCError_getInfo : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getInfo();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCError_getInfo : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCError_createWithObject(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::Ref* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCError_createWithObject : Error processing arguments");
		soomla::CCError* ret = soomla::CCError::createWithObject(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCError>(cx, (soomla::CCError*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCError_createWithObject : wrong number of arguments");
	return false;
}



void js_soomla_CCError_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCError)", obj);
}

void js_register_soomla_CCError(JSContext *cx, JSObject *global) {
	jsb_soomla_CCError_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCError_class->name = "Error";
	jsb_soomla_CCError_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCError_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCError_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCError_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCError_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCError_class->resolve = JS_ResolveStub;
	jsb_soomla_CCError_class->convert = JS_ConvertStub;
	jsb_soomla_CCError_class->finalize = js_soomla_CCError_finalize;
	jsb_soomla_CCError_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getInfo", js_soomla_CCError_getInfo, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("createWithObject", js_soomla_CCError_createWithObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCError_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_CCError_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "Error", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCError> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCError_class;
		p->proto = jsb_soomla_CCError_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCSoomlaStore_class;
JSObject *jsb_soomla_CCSoomlaStore_prototype;

bool js_soomla_CCSoomlaStore_buyMarketItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaStore* cobj = (soomla::CCSoomlaStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaStore_buyMarketItem : Invalid Native Object");
	if (argc == 3) {
		const char* arg0;
		const char* arg1;
		soomla::CCError** arg2;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSoomlaStore_buyMarketItem : Error processing arguments");
		cobj->buyMarketItem(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaStore_buyMarketItem : wrong number of arguments: %d, was expecting %d", argc, 3);
	return false;
}
bool js_soomla_CCSoomlaStore_stopIabServiceInBg(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaStore* cobj = (soomla::CCSoomlaStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaStore_stopIabServiceInBg : Invalid Native Object");
	if (argc == 0) {
		cobj->stopIabServiceInBg();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaStore_stopIabServiceInBg : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSoomlaStore_refreshMarketItemsDetails(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaStore* cobj = (soomla::CCSoomlaStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaStore_refreshMarketItemsDetails : Invalid Native Object");
	if (argc == 1) {
		soomla::CCError** arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCSoomlaStore_refreshMarketItemsDetails : Error processing arguments");
		cobj->refreshMarketItemsDetails(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaStore_refreshMarketItemsDetails : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCSoomlaStore_restoreTransactions(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaStore* cobj = (soomla::CCSoomlaStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaStore_restoreTransactions : Invalid Native Object");
	if (argc == 0) {
		cobj->restoreTransactions();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaStore_restoreTransactions : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSoomlaStore_refreshInventory(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaStore* cobj = (soomla::CCSoomlaStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaStore_refreshInventory : Invalid Native Object");
	if (argc == 0) {
		cobj->refreshInventory();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaStore_refreshInventory : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSoomlaStore_startIabServiceInBg(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaStore* cobj = (soomla::CCSoomlaStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaStore_startIabServiceInBg : Invalid Native Object");
	if (argc == 0) {
		cobj->startIabServiceInBg();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaStore_startIabServiceInBg : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSoomlaStore_transactionsAlreadyRestored(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCSoomlaStore* cobj = (soomla::CCSoomlaStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCSoomlaStore_transactionsAlreadyRestored : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->transactionsAlreadyRestored();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCSoomlaStore_transactionsAlreadyRestored : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCSoomlaStore_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		soomla::CCSoomlaStore* ret = soomla::CCSoomlaStore::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCSoomlaStore>(cx, (soomla::CCSoomlaStore*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCSoomlaStore_getInstance : wrong number of arguments");
	return false;
}

bool js_soomla_CCSoomlaStore_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCSoomlaStore* cobj = new soomla::CCSoomlaStore();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCSoomlaStore> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCSoomlaStore");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_soomla_CCSoomlaStore_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCSoomlaStore)", obj);
}

void js_register_soomla_CCSoomlaStore(JSContext *cx, JSObject *global) {
	jsb_soomla_CCSoomlaStore_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCSoomlaStore_class->name = "SoomlaStore";
	jsb_soomla_CCSoomlaStore_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCSoomlaStore_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCSoomlaStore_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCSoomlaStore_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCSoomlaStore_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCSoomlaStore_class->resolve = JS_ResolveStub;
	jsb_soomla_CCSoomlaStore_class->convert = JS_ConvertStub;
	jsb_soomla_CCSoomlaStore_class->finalize = js_soomla_CCSoomlaStore_finalize;
	jsb_soomla_CCSoomlaStore_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("buyMarketItem", js_soomla_CCSoomlaStore_buyMarketItem, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("stopIabServiceInBg", js_soomla_CCSoomlaStore_stopIabServiceInBg, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("refreshMarketItemsDetails", js_soomla_CCSoomlaStore_refreshMarketItemsDetails, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("restoreTransactions", js_soomla_CCSoomlaStore_restoreTransactions, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("refreshInventory", js_soomla_CCSoomlaStore_refreshInventory, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("startIabServiceInBg", js_soomla_CCSoomlaStore_startIabServiceInBg, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("transactionsAlreadyRestored", js_soomla_CCSoomlaStore_transactionsAlreadyRestored, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("getInstance", js_soomla_CCSoomlaStore_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCSoomlaStore_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_CCSoomlaStore_class,
		js_soomla_CCSoomlaStore_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "SoomlaStore", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCSoomlaStore> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCSoomlaStore_class;
		p->proto = jsb_soomla_CCSoomlaStore_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCUpgradeVG_class;
JSObject *jsb_soomla_CCUpgradeVG_prototype;

bool js_soomla_CCUpgradeVG_getGoodItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCUpgradeVG* cobj = (soomla::CCUpgradeVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCUpgradeVG_getGoodItemId : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getGoodItemId();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCUpgradeVG_getGoodItemId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCUpgradeVG_setNextItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCUpgradeVG* cobj = (soomla::CCUpgradeVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCUpgradeVG_setNextItemId : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCUpgradeVG_setNextItemId : Error processing arguments");
		cobj->setNextItemId(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCUpgradeVG_setNextItemId : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCUpgradeVG_getNextItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCUpgradeVG* cobj = (soomla::CCUpgradeVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCUpgradeVG_getNextItemId : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getNextItemId();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCUpgradeVG_getNextItemId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCUpgradeVG_getPrevItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCUpgradeVG* cobj = (soomla::CCUpgradeVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCUpgradeVG_getPrevItemId : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getPrevItemId();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCUpgradeVG_getPrevItemId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCUpgradeVG_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCUpgradeVG* cobj = (soomla::CCUpgradeVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCUpgradeVG_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCUpgradeVG_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCUpgradeVG_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCUpgradeVG* cobj = (soomla::CCUpgradeVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCUpgradeVG_init : Invalid Native Object");
	if (argc == 7) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		cocos2d::__String* arg3;
		cocos2d::__String* arg4;
		cocos2d::__String* arg5;
		soomla::CCPurchaseType* arg6;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[4].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[4]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg4 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg4, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[5].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[5]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg5 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg5, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[6].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[6]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg6 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg6, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCUpgradeVG_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCUpgradeVG_init : wrong number of arguments: %d, was expecting %d", argc, 7);
	return false;
}
bool js_soomla_CCUpgradeVG_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCUpgradeVG* cobj = (soomla::CCUpgradeVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCUpgradeVG_initWithDictionary : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCUpgradeVG_initWithDictionary : Error processing arguments");
		bool ret = cobj->initWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCUpgradeVG_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCUpgradeVG_setGoodItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCUpgradeVG* cobj = (soomla::CCUpgradeVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCUpgradeVG_setGoodItemId : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCUpgradeVG_setGoodItemId : Error processing arguments");
		cobj->setGoodItemId(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCUpgradeVG_setGoodItemId : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCUpgradeVG_setPrevItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCUpgradeVG* cobj = (soomla::CCUpgradeVG *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCUpgradeVG_setPrevItemId : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCUpgradeVG_setPrevItemId : Error processing arguments");
		cobj->setPrevItemId(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCUpgradeVG_setPrevItemId : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCUpgradeVG_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 7) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		cocos2d::__String* arg3;
		cocos2d::__String* arg4;
		cocos2d::__String* arg5;
		soomla::CCPurchaseType* arg6;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[4].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[4]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg4 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg4, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[5].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[5]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg5 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg5, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[6].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[6]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg6 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg6, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCUpgradeVG_create : Error processing arguments");
		soomla::CCUpgradeVG* ret = soomla::CCUpgradeVG::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCUpgradeVG>(cx, (soomla::CCUpgradeVG*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCUpgradeVG_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCUpgradeVG_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCUpgradeVG_createWithDictionary : Error processing arguments");
		soomla::CCUpgradeVG* ret = soomla::CCUpgradeVG::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCUpgradeVG>(cx, (soomla::CCUpgradeVG*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCUpgradeVG_createWithDictionary : wrong number of arguments");
	return false;
}

bool js_soomla_CCUpgradeVG_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCUpgradeVG* cobj = new soomla::CCUpgradeVG();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCUpgradeVG> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCUpgradeVG");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_soomla_CCVirtualGood_prototype;

void js_soomla_CCUpgradeVG_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCUpgradeVG)", obj);
}

void js_register_soomla_CCUpgradeVG(JSContext *cx, JSObject *global) {
	jsb_soomla_CCUpgradeVG_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCUpgradeVG_class->name = "UpgradeVG";
	jsb_soomla_CCUpgradeVG_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCUpgradeVG_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCUpgradeVG_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCUpgradeVG_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCUpgradeVG_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCUpgradeVG_class->resolve = JS_ResolveStub;
	jsb_soomla_CCUpgradeVG_class->convert = JS_ConvertStub;
	jsb_soomla_CCUpgradeVG_class->finalize = js_soomla_CCUpgradeVG_finalize;
	jsb_soomla_CCUpgradeVG_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getGoodItemId", js_soomla_CCUpgradeVG_getGoodItemId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setNextItemId", js_soomla_CCUpgradeVG_setNextItemId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getNextItemId", js_soomla_CCUpgradeVG_getNextItemId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPrevItemId", js_soomla_CCUpgradeVG_getPrevItemId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCUpgradeVG_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCUpgradeVG_init, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithDictionary", js_soomla_CCUpgradeVG_initWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setGoodItemId", js_soomla_CCUpgradeVG_setGoodItemId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPrevItemId", js_soomla_CCUpgradeVG_setPrevItemId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCUpgradeVG_create, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCUpgradeVG_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCUpgradeVG_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCVirtualGood_prototype,
		jsb_soomla_CCUpgradeVG_class,
		js_soomla_CCUpgradeVG_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "UpgradeVG", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCUpgradeVG> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCUpgradeVG_class;
		p->proto = jsb_soomla_CCUpgradeVG_prototype;
		p->parentProto = jsb_soomla_CCVirtualGood_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCVirtualCategory_class;
JSObject *jsb_soomla_CCVirtualCategory_prototype;

bool js_soomla_CCVirtualCategory_setName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCategory* cobj = (soomla::CCVirtualCategory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCategory_setName : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCategory_setName : Error processing arguments");
		cobj->setName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCategory_setName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCVirtualCategory_setGoodItemIds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCategory* cobj = (soomla::CCVirtualCategory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCategory_setGoodItemIds : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Array* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Array*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCategory_setGoodItemIds : Error processing arguments");
		cobj->setGoodItemIds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCategory_setGoodItemIds : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCVirtualCategory_getName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCategory* cobj = (soomla::CCVirtualCategory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCategory_getName : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getName();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCategory_getName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCVirtualCategory_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCategory* cobj = (soomla::CCVirtualCategory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCategory_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCategory_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCVirtualCategory_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCategory* cobj = (soomla::CCVirtualCategory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCategory_init : Invalid Native Object");
	if (argc == 2) {
		cocos2d::__String* arg0;
		cocos2d::__Array* arg1;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__Array*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCategory_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCategory_init : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCVirtualCategory_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCategory* cobj = (soomla::CCVirtualCategory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCategory_initWithDictionary : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCategory_initWithDictionary : Error processing arguments");
		bool ret = cobj->initWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCategory_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCVirtualCategory_getGoodItemIds(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCategory* cobj = (soomla::CCVirtualCategory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCategory_getGoodItemIds : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Array* ret = cobj->getGoodItemIds();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCategory_getGoodItemIds : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCVirtualCategory_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 2) {
		cocos2d::__String* arg0;
		cocos2d::__Array* arg1;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__Array*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCategory_create : Error processing arguments");
		soomla::CCVirtualCategory* ret = soomla::CCVirtualCategory::create(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualCategory>(cx, (soomla::CCVirtualCategory*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualCategory_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCVirtualCategory_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCategory_createWithDictionary : Error processing arguments");
		soomla::CCVirtualCategory* ret = soomla::CCVirtualCategory::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualCategory>(cx, (soomla::CCVirtualCategory*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualCategory_createWithDictionary : wrong number of arguments");
	return false;
}

bool js_soomla_CCVirtualCategory_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;

	JSObject *obj = NULL;
	soomla::CCVirtualCategory* cobj = NULL;
	do {
		if (argc == 1) {
			cocos2d::ValueMap arg0;
			ok &= jsval_to_ccvaluemap(cx, argv[0], &arg0);
			if (!ok) { ok = true; break; }
			cobj = new soomla::CCVirtualCategory(arg0);
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCVirtualCategory> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCVirtualCategory");
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj = new soomla::CCVirtualCategory();
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCVirtualCategory> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCVirtualCategory");
		}
	} while(0);

	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualCategory_constructor : wrong number of arguments");
	return false;
}


extern JSObject *jsb_soomla_CCDomain_prototype;

void js_soomla_CCVirtualCategory_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCVirtualCategory)", obj);
}

static bool js_soomla_CCVirtualCategory_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    soomla::CCVirtualCategory *nobj = new soomla::CCVirtualCategory();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCVirtualCategory");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return true;
}
void js_register_soomla_CCVirtualCategory(JSContext *cx, JSObject *global) {
	jsb_soomla_CCVirtualCategory_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCVirtualCategory_class->name = "VirtualCategory";
	jsb_soomla_CCVirtualCategory_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCVirtualCategory_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCVirtualCategory_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCVirtualCategory_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCVirtualCategory_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCVirtualCategory_class->resolve = JS_ResolveStub;
	jsb_soomla_CCVirtualCategory_class->convert = JS_ConvertStub;
	jsb_soomla_CCVirtualCategory_class->finalize = js_soomla_CCVirtualCategory_finalize;
	jsb_soomla_CCVirtualCategory_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setName", js_soomla_CCVirtualCategory_setName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setGoodItemIds", js_soomla_CCVirtualCategory_setGoodItemIds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getName", js_soomla_CCVirtualCategory_getName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCVirtualCategory_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCVirtualCategory_init, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithDictionary", js_soomla_CCVirtualCategory_initWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getGoodItemIds", js_soomla_CCVirtualCategory_getGoodItemIds, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_soomla_CCVirtualCategory_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCVirtualCategory_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCVirtualCategory_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCVirtualCategory_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCDomain_prototype,
		jsb_soomla_CCVirtualCategory_class,
		js_soomla_CCVirtualCategory_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "VirtualCategory", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCVirtualCategory> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCVirtualCategory_class;
		p->proto = jsb_soomla_CCVirtualCategory_prototype;
		p->parentProto = jsb_soomla_CCDomain_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCStoreInfo_class;
JSObject *jsb_soomla_CCStoreInfo_prototype;

bool js_soomla_CCStoreInfo_getVirtualCurrencyPacks(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getVirtualCurrencyPacks : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Array* ret = cobj->getVirtualCurrencyPacks();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getVirtualCurrencyPacks : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCStoreInfo_getUpgradesForVirtualGood(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getUpgradesForVirtualGood : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInfo_getUpgradesForVirtualGood : Error processing arguments");
		cocos2d::__Array* ret = cobj->getUpgradesForVirtualGood(arg0);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getUpgradesForVirtualGood : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCStoreInfo_getNonConsumableItems(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getNonConsumableItems : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Array* ret = cobj->getNonConsumableItems();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getNonConsumableItems : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCStoreInfo_getVirtualCategories(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getVirtualCategories : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Array* ret = cobj->getVirtualCategories();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getVirtualCategories : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCStoreInfo_getPurchasableItemWithProductId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getPurchasableItemWithProductId : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInfo_getPurchasableItemWithProductId : Error processing arguments");
		soomla::CCPurchasableVirtualItem* ret = cobj->getPurchasableItemWithProductId(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchasableVirtualItem>(cx, (soomla::CCPurchasableVirtualItem*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getPurchasableItemWithProductId : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInfo_getItemByItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getItemByItemId : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInfo_getItemByItemId : Error processing arguments");
		soomla::CCVirtualItem* ret = cobj->getItemByItemId(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualItem>(cx, (soomla::CCVirtualItem*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getItemByItemId : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInfo_getLastUpgradeForVirtualGood(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getLastUpgradeForVirtualGood : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInfo_getLastUpgradeForVirtualGood : Error processing arguments");
		soomla::CCUpgradeVG* ret = cobj->getLastUpgradeForVirtualGood(arg0);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCUpgradeVG>(cx, (soomla::CCUpgradeVG*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getLastUpgradeForVirtualGood : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCStoreInfo_getVirtualGoods(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getVirtualGoods : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Array* ret = cobj->getVirtualGoods();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getVirtualGoods : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCStoreInfo_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_init : Invalid Native Object");
	if (argc == 1) {
		soomla::CCStoreAssets* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (soomla::CCStoreAssets*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInfo_init : Error processing arguments");
		bool ret = cobj->init(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_init : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCStoreInfo_getCategoryForVirtualGood(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getCategoryForVirtualGood : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInfo_getCategoryForVirtualGood : Error processing arguments");
		soomla::CCVirtualCategory* ret = cobj->getCategoryForVirtualGood(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualCategory>(cx, (soomla::CCVirtualCategory*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getCategoryForVirtualGood : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInfo_getFirstUpgradeForVirtualGood(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getFirstUpgradeForVirtualGood : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInfo_getFirstUpgradeForVirtualGood : Error processing arguments");
		soomla::CCUpgradeVG* ret = cobj->getFirstUpgradeForVirtualGood(arg0);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCUpgradeVG>(cx, (soomla::CCUpgradeVG*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getFirstUpgradeForVirtualGood : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCStoreInfo_getVirtualCurrencies(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_getVirtualCurrencies : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Array* ret = cobj->getVirtualCurrencies();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_getVirtualCurrencies : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCStoreInfo_saveItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInfo* cobj = (soomla::CCStoreInfo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInfo_saveItem : Invalid Native Object");
	if (argc == 1) {
		soomla::CCVirtualItem* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (soomla::CCVirtualItem*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInfo_saveItem : Error processing arguments");
		cobj->saveItem(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInfo_saveItem : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCStoreInfo_sharedStoreInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		soomla::CCStoreInfo* ret = soomla::CCStoreInfo::sharedStoreInfo();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCStoreInfo>(cx, (soomla::CCStoreInfo*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCStoreInfo_sharedStoreInfo : wrong number of arguments");
	return false;
}

bool js_soomla_CCStoreInfo_createShared(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		soomla::CCStoreAssets* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (soomla::CCStoreAssets*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInfo_createShared : Error processing arguments");
		soomla::CCStoreInfo::createShared(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCStoreInfo_createShared : wrong number of arguments");
	return false;
}



void js_soomla_CCStoreInfo_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCStoreInfo)", obj);
}

void js_register_soomla_CCStoreInfo(JSContext *cx, JSObject *global) {
	jsb_soomla_CCStoreInfo_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCStoreInfo_class->name = "StoreInfo";
	jsb_soomla_CCStoreInfo_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCStoreInfo_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCStoreInfo_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCStoreInfo_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCStoreInfo_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCStoreInfo_class->resolve = JS_ResolveStub;
	jsb_soomla_CCStoreInfo_class->convert = JS_ConvertStub;
	jsb_soomla_CCStoreInfo_class->finalize = js_soomla_CCStoreInfo_finalize;
	jsb_soomla_CCStoreInfo_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getVirtualCurrencyPacks", js_soomla_CCStoreInfo_getVirtualCurrencyPacks, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getUpgradesForVirtualGood", js_soomla_CCStoreInfo_getUpgradesForVirtualGood, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getNonConsumableItems", js_soomla_CCStoreInfo_getNonConsumableItems, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getVirtualCategories", js_soomla_CCStoreInfo_getVirtualCategories, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPurchasableItemWithProductId", js_soomla_CCStoreInfo_getPurchasableItemWithProductId, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getItemByItemId", js_soomla_CCStoreInfo_getItemByItemId, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getLastUpgradeForVirtualGood", js_soomla_CCStoreInfo_getLastUpgradeForVirtualGood, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getVirtualGoods", js_soomla_CCStoreInfo_getVirtualGoods, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCStoreInfo_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCategoryForVirtualGood", js_soomla_CCStoreInfo_getCategoryForVirtualGood, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getFirstUpgradeForVirtualGood", js_soomla_CCStoreInfo_getFirstUpgradeForVirtualGood, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getVirtualCurrencies", js_soomla_CCStoreInfo_getVirtualCurrencies, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("saveItem", js_soomla_CCStoreInfo_saveItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("sharedStoreInfo", js_soomla_CCStoreInfo_sharedStoreInfo, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createShared", js_soomla_CCStoreInfo_createShared, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCStoreInfo_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_CCStoreInfo_class,
		dummy_constructor<soomla::CCStoreInfo>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "StoreInfo", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCStoreInfo> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCStoreInfo_class;
		p->proto = jsb_soomla_CCStoreInfo_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCStoreInventory_class;
JSObject *jsb_soomla_CCStoreInventory_prototype;

bool js_soomla_CCStoreInventory_upgradeGood(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_upgradeGood : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_upgradeGood : Error processing arguments");
		cobj->upgradeGood(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_upgradeGood : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_takeItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_takeItem : Invalid Native Object");
	if (argc == 3) {
		const char* arg0;
		int arg1;
		soomla::CCError** arg2;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_takeItem : Error processing arguments");
		cobj->takeItem(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_takeItem : wrong number of arguments: %d, was expecting %d", argc, 3);
	return false;
}
bool js_soomla_CCStoreInventory_nonConsumableItemExists(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_nonConsumableItemExists : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_nonConsumableItemExists : Error processing arguments");
		bool ret = cobj->nonConsumableItemExists(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_nonConsumableItemExists : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_isVirtualGoodEquipped(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_isVirtualGoodEquipped : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_isVirtualGoodEquipped : Error processing arguments");
		bool ret = cobj->isVirtualGoodEquipped(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_isVirtualGoodEquipped : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_unEquipVirtualGood(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_unEquipVirtualGood : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_unEquipVirtualGood : Error processing arguments");
		cobj->unEquipVirtualGood(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_unEquipVirtualGood : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_addNonConsumableItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_addNonConsumableItem : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_addNonConsumableItem : Error processing arguments");
		cobj->addNonConsumableItem(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_addNonConsumableItem : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_equipVirtualGood(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_equipVirtualGood : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_equipVirtualGood : Error processing arguments");
		cobj->equipVirtualGood(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_equipVirtualGood : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_buyItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;

	JSObject *obj = NULL;
	soomla::CCStoreInventory* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_buyItem : Invalid Native Object");
	do {
		if (argc == 3) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			const char* arg1;
			std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
			if (!ok) { ok = true; break; }
			soomla::CCError** arg2;
			do {
				if (!argv[2].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg2 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cobj->buyItem(arg0, arg1, arg2);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return true;
		}
	} while(0);

	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			soomla::CCError** arg1;
			do {
				if (!argv[1].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cobj->buyItem(arg0, arg1);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return true;
		}
	} while(0);

	JS_ReportError(cx, "js_soomla_CCStoreInventory_buyItem : wrong number of arguments");
	return false;
}
bool js_soomla_CCStoreInventory_giveItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_giveItem : Invalid Native Object");
	if (argc == 3) {
		const char* arg0;
		int arg1;
		soomla::CCError** arg2;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_giveItem : Error processing arguments");
		cobj->giveItem(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_giveItem : wrong number of arguments: %d, was expecting %d", argc, 3);
	return false;
}
bool js_soomla_CCStoreInventory_getGoodCurrentUpgrade(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_getGoodCurrentUpgrade : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_getGoodCurrentUpgrade : Error processing arguments");
		std::string ret = cobj->getGoodCurrentUpgrade(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_getGoodCurrentUpgrade : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCStoreInventory_removeNonConsumableItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_removeNonConsumableItem : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_removeNonConsumableItem : Error processing arguments");
		cobj->removeNonConsumableItem(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_removeNonConsumableItem : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_getItemBalance(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_getItemBalance : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_getItemBalance : Error processing arguments");
		int ret = cobj->getItemBalance(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_getItemBalance : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_getGoodUpgradeLevel(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_getGoodUpgradeLevel : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_getGoodUpgradeLevel : Error processing arguments");
		int ret = cobj->getGoodUpgradeLevel(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_getGoodUpgradeLevel : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_removeGoodUpgrades(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreInventory* cobj = (soomla::CCStoreInventory *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreInventory_removeGoodUpgrades : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		soomla::CCError** arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (soomla::CCError**)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreInventory_removeGoodUpgrades : Error processing arguments");
		cobj->removeGoodUpgrades(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreInventory_removeGoodUpgrades : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreInventory_sharedStoreInventory(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		soomla::CCStoreInventory* ret = soomla::CCStoreInventory::sharedStoreInventory();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCStoreInventory>(cx, (soomla::CCStoreInventory*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCStoreInventory_sharedStoreInventory : wrong number of arguments");
	return false;
}

bool js_soomla_CCStoreInventory_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCStoreInventory* cobj = new soomla::CCStoreInventory();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCStoreInventory> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCStoreInventory");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_soomla_CCStoreInventory_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCStoreInventory)", obj);
}

void js_register_soomla_CCStoreInventory(JSContext *cx, JSObject *global) {
	jsb_soomla_CCStoreInventory_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCStoreInventory_class->name = "StoreInventory";
	jsb_soomla_CCStoreInventory_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCStoreInventory_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCStoreInventory_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCStoreInventory_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCStoreInventory_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCStoreInventory_class->resolve = JS_ResolveStub;
	jsb_soomla_CCStoreInventory_class->convert = JS_ConvertStub;
	jsb_soomla_CCStoreInventory_class->finalize = js_soomla_CCStoreInventory_finalize;
	jsb_soomla_CCStoreInventory_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("upgradeGood", js_soomla_CCStoreInventory_upgradeGood, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("takeItem", js_soomla_CCStoreInventory_takeItem, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("nonConsumableItemExists", js_soomla_CCStoreInventory_nonConsumableItemExists, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isVirtualGoodEquipped", js_soomla_CCStoreInventory_isVirtualGoodEquipped, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("unEquipVirtualGood", js_soomla_CCStoreInventory_unEquipVirtualGood, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addNonConsumableItem", js_soomla_CCStoreInventory_addNonConsumableItem, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("equipVirtualGood", js_soomla_CCStoreInventory_equipVirtualGood, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("buyItem", js_soomla_CCStoreInventory_buyItem, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("giveItem", js_soomla_CCStoreInventory_giveItem, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getGoodCurrentUpgrade", js_soomla_CCStoreInventory_getGoodCurrentUpgrade, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCStoreInventory_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeNonConsumableItem", js_soomla_CCStoreInventory_removeNonConsumableItem, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getItemBalance", js_soomla_CCStoreInventory_getItemBalance, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getGoodUpgradeLevel", js_soomla_CCStoreInventory_getGoodUpgradeLevel, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeGoodUpgrades", js_soomla_CCStoreInventory_removeGoodUpgrades, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("sharedStoreInventory", js_soomla_CCStoreInventory_sharedStoreInventory, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCStoreInventory_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_CCStoreInventory_class,
		js_soomla_CCStoreInventory_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "StoreInventory", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCStoreInventory> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCStoreInventory_class;
		p->proto = jsb_soomla_CCStoreInventory_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCVirtualCurrency_class;
JSObject *jsb_soomla_CCVirtualCurrency_prototype;

bool js_soomla_CCVirtualCurrency_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 3) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCurrency_create : Error processing arguments");
		soomla::CCVirtualCurrency* ret = soomla::CCVirtualCurrency::create(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualCurrency>(cx, (soomla::CCVirtualCurrency*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualCurrency_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCVirtualCurrency_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCurrency_createWithDictionary : Error processing arguments");
		soomla::CCVirtualCurrency* ret = soomla::CCVirtualCurrency::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualCurrency>(cx, (soomla::CCVirtualCurrency*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualCurrency_createWithDictionary : wrong number of arguments");
	return false;
}

bool js_soomla_CCVirtualCurrency_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;

	JSObject *obj = NULL;
	soomla::CCVirtualCurrency* cobj = NULL;
	do {
		if (argc == 1) {
			cocos2d::ValueMap arg0;
			ok &= jsval_to_ccvaluemap(cx, argv[0], &arg0);
			if (!ok) { ok = true; break; }
			cobj = new soomla::CCVirtualCurrency(arg0);
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCVirtualCurrency> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCVirtualCurrency");
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj = new soomla::CCVirtualCurrency();
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCVirtualCurrency> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCVirtualCurrency");
		}
	} while(0);

	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualCurrency_constructor : wrong number of arguments");
	return false;
}


extern JSObject *jsb_soomla_CCVirtualItem_prototype;

void js_soomla_CCVirtualCurrency_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCVirtualCurrency)", obj);
}

void js_register_soomla_CCVirtualCurrency(JSContext *cx, JSObject *global) {
	jsb_soomla_CCVirtualCurrency_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCVirtualCurrency_class->name = "VirtualCurrency";
	jsb_soomla_CCVirtualCurrency_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCVirtualCurrency_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCVirtualCurrency_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCVirtualCurrency_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCVirtualCurrency_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCVirtualCurrency_class->resolve = JS_ResolveStub;
	jsb_soomla_CCVirtualCurrency_class->convert = JS_ConvertStub;
	jsb_soomla_CCVirtualCurrency_class->finalize = js_soomla_CCVirtualCurrency_finalize;
	jsb_soomla_CCVirtualCurrency_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCVirtualCurrency_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCVirtualCurrency_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCVirtualCurrency_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCVirtualItem_prototype,
		jsb_soomla_CCVirtualCurrency_class,
		js_soomla_CCVirtualCurrency_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "VirtualCurrency", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCVirtualCurrency> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCVirtualCurrency_class;
		p->proto = jsb_soomla_CCVirtualCurrency_prototype;
		p->parentProto = jsb_soomla_CCVirtualItem_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCVirtualCurrencyPack_class;
JSObject *jsb_soomla_CCVirtualCurrencyPack_prototype;

bool js_soomla_CCVirtualCurrencyPack_setCurrencyAmount(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCurrencyPack* cobj = (soomla::CCVirtualCurrencyPack *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCurrencyPack_setCurrencyAmount : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Integer* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCurrencyPack_setCurrencyAmount : Error processing arguments");
		cobj->setCurrencyAmount(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCurrencyPack_setCurrencyAmount : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCVirtualCurrencyPack_getCurrencyItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCurrencyPack* cobj = (soomla::CCVirtualCurrencyPack *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCurrencyPack_getCurrencyItemId : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getCurrencyItemId();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCurrencyPack_getCurrencyItemId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCVirtualCurrencyPack_setCurrencyItemId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCurrencyPack* cobj = (soomla::CCVirtualCurrencyPack *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCurrencyPack_setCurrencyItemId : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCurrencyPack_setCurrencyItemId : Error processing arguments");
		cobj->setCurrencyItemId(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCurrencyPack_setCurrencyItemId : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCVirtualCurrencyPack_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCurrencyPack* cobj = (soomla::CCVirtualCurrencyPack *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCurrencyPack_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCurrencyPack_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCVirtualCurrencyPack_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCurrencyPack* cobj = (soomla::CCVirtualCurrencyPack *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCurrencyPack_init : Invalid Native Object");
	if (argc == 6) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		cocos2d::__Integer* arg3;
		cocos2d::__String* arg4;
		soomla::CCPurchaseType* arg5;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[4].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[4]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg4 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg4, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[5].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[5]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg5 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg5, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCurrencyPack_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCurrencyPack_init : wrong number of arguments: %d, was expecting %d", argc, 6);
	return false;
}
bool js_soomla_CCVirtualCurrencyPack_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCurrencyPack* cobj = (soomla::CCVirtualCurrencyPack *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCurrencyPack_initWithDictionary : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCurrencyPack_initWithDictionary : Error processing arguments");
		bool ret = cobj->initWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCurrencyPack_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCVirtualCurrencyPack_getCurrencyAmount(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCVirtualCurrencyPack* cobj = (soomla::CCVirtualCurrencyPack *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCVirtualCurrencyPack_getCurrencyAmount : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Integer* ret = cobj->getCurrencyAmount();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Integer>(cx, (cocos2d::__Integer*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCVirtualCurrencyPack_getCurrencyAmount : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCVirtualCurrencyPack_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 6) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__String* arg2;
		cocos2d::__Integer* arg3;
		cocos2d::__String* arg4;
		soomla::CCPurchaseType* arg5;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[3].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg3 = (cocos2d::__Integer*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[4].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[4]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg4 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg4, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[5].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[5]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg5 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg5, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCurrencyPack_create : Error processing arguments");
		soomla::CCVirtualCurrencyPack* ret = soomla::CCVirtualCurrencyPack::create(arg0, arg1, arg2, arg3, arg4, arg5);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualCurrencyPack>(cx, (soomla::CCVirtualCurrencyPack*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualCurrencyPack_create : wrong number of arguments");
	return false;
}

bool js_soomla_CCVirtualCurrencyPack_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCVirtualCurrencyPack_createWithDictionary : Error processing arguments");
		soomla::CCVirtualCurrencyPack* ret = soomla::CCVirtualCurrencyPack::createWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualCurrencyPack>(cx, (soomla::CCVirtualCurrencyPack*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualCurrencyPack_createWithDictionary : wrong number of arguments");
	return false;
}

bool js_soomla_CCVirtualCurrencyPack_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;

	JSObject *obj = NULL;
	soomla::CCVirtualCurrencyPack* cobj = NULL;
	do {
		if (argc == 2) {
			cocos2d::ValueMap arg0;
			ok &= jsval_to_ccvaluemap(cx, argv[0], &arg0);
			if (!ok) { ok = true; break; }
			soomla::CCPurchaseType* arg1;
			do {
				if (!argv[1].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg1 = (soomla::CCPurchaseType*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cobj = new soomla::CCVirtualCurrencyPack(arg0, arg1);
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCVirtualCurrencyPack> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCVirtualCurrencyPack");
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj = new soomla::CCVirtualCurrencyPack();
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<soomla::CCVirtualCurrencyPack> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCVirtualCurrencyPack");
		}
	} while(0);

	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCVirtualCurrencyPack_constructor : wrong number of arguments");
	return false;
}


extern JSObject *jsb_soomla_CCPurchasableVirtualItem_prototype;

void js_soomla_CCVirtualCurrencyPack_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCVirtualCurrencyPack)", obj);
}

void js_register_soomla_CCVirtualCurrencyPack(JSContext *cx, JSObject *global) {
	jsb_soomla_CCVirtualCurrencyPack_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCVirtualCurrencyPack_class->name = "VirtualCurrencyPack";
	jsb_soomla_CCVirtualCurrencyPack_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCVirtualCurrencyPack_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCVirtualCurrencyPack_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCVirtualCurrencyPack_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCVirtualCurrencyPack_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCVirtualCurrencyPack_class->resolve = JS_ResolveStub;
	jsb_soomla_CCVirtualCurrencyPack_class->convert = JS_ConvertStub;
	jsb_soomla_CCVirtualCurrencyPack_class->finalize = js_soomla_CCVirtualCurrencyPack_finalize;
	jsb_soomla_CCVirtualCurrencyPack_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setCurrencyAmount", js_soomla_CCVirtualCurrencyPack_setCurrencyAmount, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurrencyItemId", js_soomla_CCVirtualCurrencyPack_getCurrencyItemId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCurrencyItemId", js_soomla_CCVirtualCurrencyPack_setCurrencyItemId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCVirtualCurrencyPack_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCVirtualCurrencyPack_init, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithDictionary", js_soomla_CCVirtualCurrencyPack_initWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurrencyAmount", js_soomla_CCVirtualCurrencyPack_getCurrencyAmount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_soomla_CCVirtualCurrencyPack_create, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithDictionary", js_soomla_CCVirtualCurrencyPack_createWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCVirtualCurrencyPack_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCPurchasableVirtualItem_prototype,
		jsb_soomla_CCVirtualCurrencyPack_class,
		js_soomla_CCVirtualCurrencyPack_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "VirtualCurrencyPack", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCVirtualCurrencyPack> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCVirtualCurrencyPack_class;
		p->proto = jsb_soomla_CCVirtualCurrencyPack_prototype;
		p->parentProto = jsb_soomla_CCPurchasableVirtualItem_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCStoreService_class;
JSObject *jsb_soomla_CCStoreService_prototype;

bool js_soomla_CCStoreService_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCStoreService* cobj = (soomla::CCStoreService *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCStoreService_init : Invalid Native Object");
	if (argc == 2) {
		soomla::CCStoreAssets* arg0;
		cocos2d::__Dictionary* arg1;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (soomla::CCStoreAssets*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreService_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCStoreService_init : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_soomla_CCStoreService_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		soomla::CCStoreService* ret = soomla::CCStoreService::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCStoreService>(cx, (soomla::CCStoreService*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCStoreService_getInstance : wrong number of arguments");
	return false;
}

bool js_soomla_CCStoreService_initShared(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 2) {
		soomla::CCStoreAssets* arg0;
		cocos2d::ValueMap arg1;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (soomla::CCStoreAssets*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		ok &= jsval_to_ccvaluemap(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCStoreService_initShared : Error processing arguments");
		soomla::CCStoreService::initShared(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCStoreService_initShared : wrong number of arguments");
	return false;
}

bool js_soomla_CCStoreService_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCStoreService* cobj = new soomla::CCStoreService();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCStoreService> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCStoreService");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_soomla_CCStoreService_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCStoreService)", obj);
}

void js_register_soomla_CCStoreService(JSContext *cx, JSObject *global) {
	jsb_soomla_CCStoreService_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCStoreService_class->name = "StoreService";
	jsb_soomla_CCStoreService_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCStoreService_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCStoreService_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCStoreService_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCStoreService_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCStoreService_class->resolve = JS_ResolveStub;
	jsb_soomla_CCStoreService_class->convert = JS_ConvertStub;
	jsb_soomla_CCStoreService_class->finalize = js_soomla_CCStoreService_finalize;
	jsb_soomla_CCStoreService_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("init", js_soomla_CCStoreService_init, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("getInstance", js_soomla_CCStoreService_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initShared", js_soomla_CCStoreService_initShared, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCStoreService_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_CCStoreService_class,
		js_soomla_CCStoreService_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "StoreService", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCStoreService> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCStoreService_class;
		p->proto = jsb_soomla_CCStoreService_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCReward_class;
JSObject *jsb_soomla_CCReward_prototype;

bool js_soomla_CCReward_setName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCReward* cobj = (soomla::CCReward *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCReward_setName : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCReward_setName : Error processing arguments");
		cobj->setName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCReward_setName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCReward_getRepeatable(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCReward* cobj = (soomla::CCReward *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCReward_getRepeatable : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Bool* ret = cobj->getRepeatable();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Bool>(cx, (cocos2d::__Bool*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCReward_getRepeatable : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCReward_getName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCReward* cobj = (soomla::CCReward *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCReward_getName : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getName();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCReward_getName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCReward_getType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCReward* cobj = (soomla::CCReward *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCReward_getType : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getType();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCReward_getType : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCReward_toDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCReward* cobj = (soomla::CCReward *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCReward_toDictionary : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__Dictionary* ret = cobj->toDictionary();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCReward_toDictionary : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCReward_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCReward* cobj = (soomla::CCReward *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCReward_init : Invalid Native Object");
	if (argc == 3) {
		cocos2d::__String* arg0;
		cocos2d::__String* arg1;
		cocos2d::__Bool* arg2;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[2].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::__Bool*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCReward_init : Error processing arguments");
		bool ret = cobj->init(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCReward_init : wrong number of arguments: %d, was expecting %d", argc, 3);
	return false;
}
bool js_soomla_CCReward_setRepeatable(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCReward* cobj = (soomla::CCReward *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCReward_setRepeatable : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Bool* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Bool*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCReward_setRepeatable : Error processing arguments");
		cobj->setRepeatable(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCReward_setRepeatable : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCReward_setRewardId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCReward* cobj = (soomla::CCReward *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCReward_setRewardId : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__String* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__String*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCReward_setRewardId : Error processing arguments");
		cobj->setRewardId(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCReward_setRewardId : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCReward_getRewardId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCReward* cobj = (soomla::CCReward *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCReward_getRewardId : Invalid Native Object");
	if (argc == 0) {
		cocos2d::__String* ret = cobj->getRewardId();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCReward_getRewardId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCReward_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCReward* cobj = (soomla::CCReward *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCReward_initWithDictionary : Invalid Native Object");
	if (argc == 1) {
		cocos2d::__Dictionary* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::__Dictionary*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCReward_initWithDictionary : Error processing arguments");
		bool ret = cobj->initWithDictionary(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCReward_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

extern JSObject *jsb_soomla_CCDomain_prototype;

void js_soomla_CCReward_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCReward)", obj);
}

void js_register_soomla_CCReward(JSContext *cx, JSObject *global) {
	jsb_soomla_CCReward_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCReward_class->name = "Reward";
	jsb_soomla_CCReward_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCReward_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCReward_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCReward_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCReward_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCReward_class->resolve = JS_ResolveStub;
	jsb_soomla_CCReward_class->convert = JS_ConvertStub;
	jsb_soomla_CCReward_class->finalize = js_soomla_CCReward_finalize;
	jsb_soomla_CCReward_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setName", js_soomla_CCReward_setName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getRepeatable", js_soomla_CCReward_getRepeatable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getName", js_soomla_CCReward_getName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getType", js_soomla_CCReward_getType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("toDictionary", js_soomla_CCReward_toDictionary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_soomla_CCReward_init, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setRepeatable", js_soomla_CCReward_setRepeatable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setRewardId", js_soomla_CCReward_setRewardId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getRewardId", js_soomla_CCReward_getRewardId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithDictionary", js_soomla_CCReward_initWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_soomla_CCReward_prototype = JS_InitClass(
		cx, global,
		jsb_soomla_CCDomain_prototype,
		jsb_soomla_CCReward_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "Reward", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCReward> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCReward_class;
		p->proto = jsb_soomla_CCReward_prototype;
		p->parentProto = jsb_soomla_CCDomain_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCCoreService_class;
JSObject *jsb_soomla_CCCoreService_prototype;

bool js_soomla_CCCoreService_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCCoreService* cobj = (soomla::CCCoreService *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCCoreService_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCCoreService_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCCoreService_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		soomla::CCCoreService* ret = soomla::CCCoreService::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCCoreService>(cx, (soomla::CCCoreService*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCCoreService_getInstance : wrong number of arguments");
	return false;
}

bool js_soomla_CCCoreService_initShared(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		soomla::CCCoreService::initShared();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCCoreService_initShared : wrong number of arguments");
	return false;
}

bool js_soomla_CCCoreService_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::CCCoreService* cobj = new soomla::CCCoreService();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::CCCoreService> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCCoreService");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_soomla_CCCoreService_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCCoreService)", obj);
}

static bool js_soomla_CCCoreService_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    soomla::CCCoreService *nobj = new soomla::CCCoreService();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::CCCoreService");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return true;
}
void js_register_soomla_CCCoreService(JSContext *cx, JSObject *global) {
	jsb_soomla_CCCoreService_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCCoreService_class->name = "CoreService";
	jsb_soomla_CCCoreService_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCCoreService_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCCoreService_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCCoreService_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCCoreService_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCCoreService_class->resolve = JS_ResolveStub;
	jsb_soomla_CCCoreService_class->convert = JS_ConvertStub;
	jsb_soomla_CCCoreService_class->finalize = js_soomla_CCCoreService_finalize;
	jsb_soomla_CCCoreService_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("init", js_soomla_CCCoreService_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_soomla_CCCoreService_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("getInstance", js_soomla_CCCoreService_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initShared", js_soomla_CCCoreService_initShared, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCCoreService_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_CCCoreService_class,
		js_soomla_CCCoreService_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "CoreService", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCCoreService> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCCoreService_class;
		p->proto = jsb_soomla_CCCoreService_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_CCServiceManager_class;
JSObject *jsb_soomla_CCServiceManager_prototype;

bool js_soomla_CCServiceManager_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCServiceManager* cobj = (soomla::CCServiceManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCServiceManager_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCServiceManager_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_soomla_CCServiceManager_setCommonParams(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::CCServiceManager* cobj = (soomla::CCServiceManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_CCServiceManager_setCommonParams : Invalid Native Object");
	if (argc == 1) {
		cocos2d::ValueMap arg0;
		ok &= jsval_to_ccvaluemap(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_CCServiceManager_setCommonParams : Error processing arguments");
		cobj->setCommonParams(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_CCServiceManager_setCommonParams : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_CCServiceManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		soomla::CCServiceManager* ret = soomla::CCServiceManager::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCServiceManager>(cx, (soomla::CCServiceManager*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_CCServiceManager_getInstance : wrong number of arguments");
	return false;
}



void js_soomla_CCServiceManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCServiceManager)", obj);
}

void js_register_soomla_CCServiceManager(JSContext *cx, JSObject *global) {
	jsb_soomla_CCServiceManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_CCServiceManager_class->name = "ServiceManager";
	jsb_soomla_CCServiceManager_class->addProperty = JS_PropertyStub;
	jsb_soomla_CCServiceManager_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_CCServiceManager_class->getProperty = JS_PropertyStub;
	jsb_soomla_CCServiceManager_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_CCServiceManager_class->enumerate = JS_EnumerateStub;
	jsb_soomla_CCServiceManager_class->resolve = JS_ResolveStub;
	jsb_soomla_CCServiceManager_class->convert = JS_ConvertStub;
	jsb_soomla_CCServiceManager_class->finalize = js_soomla_CCServiceManager_finalize;
	jsb_soomla_CCServiceManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("init", js_soomla_CCServiceManager_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCommonParams", js_soomla_CCServiceManager_setCommonParams, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("getInstance", js_soomla_CCServiceManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_CCServiceManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_CCServiceManager_class,
		dummy_constructor<soomla::CCServiceManager>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ServiceManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::CCServiceManager> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_CCServiceManager_class;
		p->proto = jsb_soomla_CCServiceManager_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_JSBEventHandler_class;
JSObject *jsb_soomla_JSBEventHandler_prototype;

bool js_soomla_JSBEventHandler_setGoodBalanceChangedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setGoodBalanceChangedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCVirtualGood *, int, int)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCVirtualGood* larg0, int larg1, int larg2) -> void {
				jsval largv[3];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualGood>(cx, (soomla::CCVirtualGood*)larg0);
						largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
					} else {
						largv[0] = JSVAL_NULL;
					}
				} while (0);
				largv[1] = int32_to_jsval(cx, larg1);
				largv[2] = int32_to_jsval(cx, larg2);
				jsval rval;
				bool ok = func->invoke(3, &largv[0], rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setGoodBalanceChangedHandler : Error processing arguments");
		cobj->setGoodBalanceChangedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setGoodBalanceChangedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setGoodUnEquippedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setGoodUnEquippedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCEquippableVG *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCEquippableVG* larg0) -> void {
				jsval largv[1];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCEquippableVG>(cx, (soomla::CCEquippableVG*)larg0);
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
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setGoodUnEquippedHandler : Error processing arguments");
		cobj->setGoodUnEquippedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setGoodUnEquippedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setItemPurchaseStartedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setItemPurchaseStartedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCPurchasableVirtualItem *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCPurchasableVirtualItem* larg0) -> void {
				jsval largv[1];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchasableVirtualItem>(cx, (soomla::CCPurchasableVirtualItem*)larg0);
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
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setItemPurchaseStartedHandler : Error processing arguments");
		cobj->setItemPurchaseStartedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setItemPurchaseStartedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setRestoreTransactionsStartedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setRestoreTransactionsStartedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void ()> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setRestoreTransactionsStartedHandler : Error processing arguments");
		cobj->setRestoreTransactionsStartedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setRestoreTransactionsStartedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setCurrencyBalanceChangedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setCurrencyBalanceChangedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCVirtualCurrency *, int, int)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCVirtualCurrency* larg0, int larg1, int larg2) -> void {
				jsval largv[3];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualCurrency>(cx, (soomla::CCVirtualCurrency*)larg0);
						largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
					} else {
						largv[0] = JSVAL_NULL;
					}
				} while (0);
				largv[1] = int32_to_jsval(cx, larg1);
				largv[2] = int32_to_jsval(cx, larg2);
				jsval rval;
				bool ok = func->invoke(3, &largv[0], rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setCurrencyBalanceChangedHandler : Error processing arguments");
		cobj->setCurrencyBalanceChangedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setCurrencyBalanceChangedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setMarketItemsRefreshedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setMarketItemsRefreshedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (cocos2d::__Array *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](cocos2d::__Array* larg0) -> void {
				jsval largv[1];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)larg0);
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
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setMarketItemsRefreshedHandler : Error processing arguments");
		cobj->setMarketItemsRefreshedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setMarketItemsRefreshedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setStoreControllerInitializedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setStoreControllerInitializedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void ()> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setStoreControllerInitializedHandler : Error processing arguments");
		cobj->setStoreControllerInitializedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setStoreControllerInitializedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setGoodUpgradeHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setGoodUpgradeHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCVirtualGood *, soomla::CCUpgradeVG *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCVirtualGood* larg0, soomla::CCUpgradeVG* larg1) -> void {
				jsval largv[2];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCVirtualGood>(cx, (soomla::CCVirtualGood*)larg0);
						largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
					} else {
						largv[0] = JSVAL_NULL;
					}
				} while (0);
				do {
					if (larg1) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCUpgradeVG>(cx, (soomla::CCUpgradeVG*)larg1);
						largv[1] = OBJECT_TO_JSVAL(jsProxy->obj);
					} else {
						largv[1] = JSVAL_NULL;
					}
				} while (0);
				jsval rval;
				bool ok = func->invoke(2, &largv[0], rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setGoodUpgradeHandler : Error processing arguments");
		cobj->setGoodUpgradeHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setGoodUpgradeHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setAndroidMarketRefundHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setAndroidMarketRefundHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCPurchasableVirtualItem *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCPurchasableVirtualItem* larg0) -> void {
				jsval largv[1];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchasableVirtualItem>(cx, (soomla::CCPurchasableVirtualItem*)larg0);
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
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setAndroidMarketRefundHandler : Error processing arguments");
		cobj->setAndroidMarketRefundHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setAndroidMarketRefundHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setItemPurchasedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setItemPurchasedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCPurchasableVirtualItem *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCPurchasableVirtualItem* larg0) -> void {
				jsval largv[1];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchasableVirtualItem>(cx, (soomla::CCPurchasableVirtualItem*)larg0);
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
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setItemPurchasedHandler : Error processing arguments");
		cobj->setItemPurchasedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setItemPurchasedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setRestoreTransactionsFinishedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setRestoreTransactionsFinishedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (bool)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](bool larg0) -> void {
				jsval largv[1];
				largv[0] = BOOLEAN_TO_JSVAL(larg0);
				jsval rval;
				bool ok = func->invoke(1, &largv[0], rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setRestoreTransactionsFinishedHandler : Error processing arguments");
		cobj->setRestoreTransactionsFinishedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setRestoreTransactionsFinishedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setMarketPurchaseVerificationHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setMarketPurchaseVerificationHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCPurchasableVirtualItem *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCPurchasableVirtualItem* larg0) -> void {
				jsval largv[1];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchasableVirtualItem>(cx, (soomla::CCPurchasableVirtualItem*)larg0);
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
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setMarketPurchaseVerificationHandler : Error processing arguments");
		cobj->setMarketPurchaseVerificationHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setMarketPurchaseVerificationHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setBillingSupportedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setBillingSupportedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void ()> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setBillingSupportedHandler : Error processing arguments");
		cobj->setBillingSupportedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setBillingSupportedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setBillingNotSupportedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setBillingNotSupportedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void ()> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setBillingNotSupportedHandler : Error processing arguments");
		cobj->setBillingNotSupportedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setBillingNotSupportedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setGoodEquippedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setGoodEquippedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCEquippableVG *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCEquippableVG* larg0) -> void {
				jsval largv[1];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCEquippableVG>(cx, (soomla::CCEquippableVG*)larg0);
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
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setGoodEquippedHandler : Error processing arguments");
		cobj->setGoodEquippedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setGoodEquippedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setAndroidIabServiceStartedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setAndroidIabServiceStartedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void ()> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setAndroidIabServiceStartedHandler : Error processing arguments");
		cobj->setAndroidIabServiceStartedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setAndroidIabServiceStartedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setMarketPurchaseStartedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setMarketPurchaseStartedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCPurchasableVirtualItem *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCPurchasableVirtualItem* larg0) -> void {
				jsval largv[1];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchasableVirtualItem>(cx, (soomla::CCPurchasableVirtualItem*)larg0);
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
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setMarketPurchaseStartedHandler : Error processing arguments");
		cobj->setMarketPurchaseStartedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setMarketPurchaseStartedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setUnexpectedErrorInStoreHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setUnexpectedErrorInStoreHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void ()> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setUnexpectedErrorInStoreHandler : Error processing arguments");
		cobj->setUnexpectedErrorInStoreHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setUnexpectedErrorInStoreHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setMarketPurchaseHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setMarketPurchaseHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCPurchasableVirtualItem *, cocos2d::__String *, cocos2d::__String *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCPurchasableVirtualItem* larg0, cocos2d::__String* larg1, cocos2d::__String* larg2) -> void {
				jsval largv[3];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchasableVirtualItem>(cx, (soomla::CCPurchasableVirtualItem*)larg0);
						largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
					} else {
						largv[0] = JSVAL_NULL;
					}
				} while (0);
				do {
					if (larg1) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)larg1);
						largv[1] = OBJECT_TO_JSVAL(jsProxy->obj);
					} else {
						largv[1] = JSVAL_NULL;
					}
				} while (0);
				do {
					if (larg2) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__String>(cx, (cocos2d::__String*)larg2);
						largv[2] = OBJECT_TO_JSVAL(jsProxy->obj);
					} else {
						largv[2] = JSVAL_NULL;
					}
				} while (0);
				jsval rval;
				bool ok = func->invoke(3, &largv[0], rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setMarketPurchaseHandler : Error processing arguments");
		cobj->setMarketPurchaseHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setMarketPurchaseHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setMarketPurchaseCancelledHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setMarketPurchaseCancelledHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void (soomla::CCPurchasableVirtualItem *)> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=](soomla::CCPurchasableVirtualItem* larg0) -> void {
				jsval largv[1];
				do {
					if (larg0) {
						js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::CCPurchasableVirtualItem>(cx, (soomla::CCPurchasableVirtualItem*)larg0);
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
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setMarketPurchaseCancelledHandler : Error processing arguments");
		cobj->setMarketPurchaseCancelledHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setMarketPurchaseCancelledHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setMarketItemsRefreshStartedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setMarketItemsRefreshStartedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void ()> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setMarketItemsRefreshStartedHandler : Error processing arguments");
		cobj->setMarketItemsRefreshStartedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setMarketItemsRefreshStartedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_setAndroidIabServiceStoppedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBEventHandler* cobj = (soomla::JSBEventHandler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBEventHandler_setAndroidIabServiceStoppedHandler : Invalid Native Object");
	if (argc == 1) {
		std::function<void ()> arg0;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg0 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBEventHandler_setAndroidIabServiceStoppedHandler : Error processing arguments");
		cobj->setAndroidIabServiceStoppedHandler(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBEventHandler_setAndroidIabServiceStoppedHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBEventHandler_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		soomla::JSBEventHandler* ret = soomla::JSBEventHandler::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<soomla::JSBEventHandler>(cx, (soomla::JSBEventHandler*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_soomla_JSBEventHandler_getInstance : wrong number of arguments");
	return false;
}



void js_soomla_JSBEventHandler_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (JSBEventHandler)", obj);
}

void js_register_soomla_JSBEventHandler(JSContext *cx, JSObject *global) {
	jsb_soomla_JSBEventHandler_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_JSBEventHandler_class->name = "EventHandler";
	jsb_soomla_JSBEventHandler_class->addProperty = JS_PropertyStub;
	jsb_soomla_JSBEventHandler_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_JSBEventHandler_class->getProperty = JS_PropertyStub;
	jsb_soomla_JSBEventHandler_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_JSBEventHandler_class->enumerate = JS_EnumerateStub;
	jsb_soomla_JSBEventHandler_class->resolve = JS_ResolveStub;
	jsb_soomla_JSBEventHandler_class->convert = JS_ConvertStub;
	jsb_soomla_JSBEventHandler_class->finalize = js_soomla_JSBEventHandler_finalize;
	jsb_soomla_JSBEventHandler_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setGoodBalanceChangedHandler", js_soomla_JSBEventHandler_setGoodBalanceChangedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setGoodUnEquippedHandler", js_soomla_JSBEventHandler_setGoodUnEquippedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setItemPurchaseStartedHandler", js_soomla_JSBEventHandler_setItemPurchaseStartedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setRestoreTransactionsStartedHandler", js_soomla_JSBEventHandler_setRestoreTransactionsStartedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCurrencyBalanceChangedHandler", js_soomla_JSBEventHandler_setCurrencyBalanceChangedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMarketItemsRefreshedHandler", js_soomla_JSBEventHandler_setMarketItemsRefreshedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setStoreControllerInitializedHandler", js_soomla_JSBEventHandler_setStoreControllerInitializedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setGoodUpgradeHandler", js_soomla_JSBEventHandler_setGoodUpgradeHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAndroidMarketRefundHandler", js_soomla_JSBEventHandler_setAndroidMarketRefundHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setItemPurchasedHandler", js_soomla_JSBEventHandler_setItemPurchasedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setRestoreTransactionsFinishedHandler", js_soomla_JSBEventHandler_setRestoreTransactionsFinishedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMarketPurchaseVerificationHandler", js_soomla_JSBEventHandler_setMarketPurchaseVerificationHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBillingSupportedHandler", js_soomla_JSBEventHandler_setBillingSupportedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBillingNotSupportedHandler", js_soomla_JSBEventHandler_setBillingNotSupportedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setGoodEquippedHandler", js_soomla_JSBEventHandler_setGoodEquippedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAndroidIabServiceStartedHandler", js_soomla_JSBEventHandler_setAndroidIabServiceStartedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMarketPurchaseStartedHandler", js_soomla_JSBEventHandler_setMarketPurchaseStartedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setUnexpectedErrorInStoreHandler", js_soomla_JSBEventHandler_setUnexpectedErrorInStoreHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMarketPurchaseHandler", js_soomla_JSBEventHandler_setMarketPurchaseHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMarketPurchaseCancelledHandler", js_soomla_JSBEventHandler_setMarketPurchaseCancelledHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMarketItemsRefreshStartedHandler", js_soomla_JSBEventHandler_setMarketItemsRefreshStartedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAndroidIabServiceStoppedHandler", js_soomla_JSBEventHandler_setAndroidIabServiceStoppedHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("getInstance", js_soomla_JSBEventHandler_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_soomla_JSBEventHandler_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_JSBEventHandler_class,
		dummy_constructor<soomla::JSBEventHandler>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "EventHandler", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::JSBEventHandler> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_JSBEventHandler_class;
		p->proto = jsb_soomla_JSBEventHandler_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_soomla_JSBStoreAssets_class;
JSObject *jsb_soomla_JSBStoreAssets_prototype;

bool js_soomla_JSBStoreAssets_addGood(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBStoreAssets* cobj = (soomla::JSBStoreAssets *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBStoreAssets_addGood : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Ref* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBStoreAssets_addGood : Error processing arguments");
		cobj->addGood(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBStoreAssets_addGood : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBStoreAssets_addNonConsumableItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBStoreAssets* cobj = (soomla::JSBStoreAssets *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBStoreAssets_addNonConsumableItem : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Ref* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBStoreAssets_addNonConsumableItem : Error processing arguments");
		cobj->addNonConsumableItem(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBStoreAssets_addNonConsumableItem : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBStoreAssets_addCurrency(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBStoreAssets* cobj = (soomla::JSBStoreAssets *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBStoreAssets_addCurrency : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Ref* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBStoreAssets_addCurrency : Error processing arguments");
		cobj->addCurrency(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBStoreAssets_addCurrency : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBStoreAssets_addCurrencyPack(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBStoreAssets* cobj = (soomla::JSBStoreAssets *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBStoreAssets_addCurrencyPack : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Ref* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBStoreAssets_addCurrencyPack : Error processing arguments");
		cobj->addCurrencyPack(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBStoreAssets_addCurrencyPack : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBStoreAssets_addCategory(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBStoreAssets* cobj = (soomla::JSBStoreAssets *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBStoreAssets_addCategory : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Ref* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBStoreAssets_addCategory : Error processing arguments");
		cobj->addCategory(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBStoreAssets_addCategory : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBStoreAssets_setVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	soomla::JSBStoreAssets* cobj = (soomla::JSBStoreAssets *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_soomla_JSBStoreAssets_setVersion : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_soomla_JSBStoreAssets_setVersion : Error processing arguments");
		cobj->setVersion(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_soomla_JSBStoreAssets_setVersion : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_soomla_JSBStoreAssets_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    soomla::JSBStoreAssets* cobj = new soomla::JSBStoreAssets();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<soomla::JSBStoreAssets> t;
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
    JS_AddNamedObjectRoot(cx, &p->obj, "soomla::JSBStoreAssets");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_soomla_JSBStoreAssets_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (JSBStoreAssets)", obj);
}

void js_register_soomla_JSBStoreAssets(JSContext *cx, JSObject *global) {
	jsb_soomla_JSBStoreAssets_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_soomla_JSBStoreAssets_class->name = "StoreAssets";
	jsb_soomla_JSBStoreAssets_class->addProperty = JS_PropertyStub;
	jsb_soomla_JSBStoreAssets_class->delProperty = JS_DeletePropertyStub;
	jsb_soomla_JSBStoreAssets_class->getProperty = JS_PropertyStub;
	jsb_soomla_JSBStoreAssets_class->setProperty = JS_StrictPropertyStub;
	jsb_soomla_JSBStoreAssets_class->enumerate = JS_EnumerateStub;
	jsb_soomla_JSBStoreAssets_class->resolve = JS_ResolveStub;
	jsb_soomla_JSBStoreAssets_class->convert = JS_ConvertStub;
	jsb_soomla_JSBStoreAssets_class->finalize = js_soomla_JSBStoreAssets_finalize;
	jsb_soomla_JSBStoreAssets_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("addGood", js_soomla_JSBStoreAssets_addGood, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addNonConsumableItem", js_soomla_JSBStoreAssets_addNonConsumableItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addCurrency", js_soomla_JSBStoreAssets_addCurrency, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addCurrencyPack", js_soomla_JSBStoreAssets_addCurrencyPack, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addCategory", js_soomla_JSBStoreAssets_addCategory, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setVersion", js_soomla_JSBStoreAssets_setVersion, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_soomla_JSBStoreAssets_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_soomla_JSBStoreAssets_class,
		js_soomla_JSBStoreAssets_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "StoreAssets", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<soomla::JSBStoreAssets> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_soomla_JSBStoreAssets_class;
		p->proto = jsb_soomla_JSBStoreAssets_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

void register_all_soomla(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	JS::RootedValue nsval(cx);
	JS::RootedObject ns(cx);
	JS_GetProperty(cx, obj, "soomla", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "soomla", nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_soomla_CCStoreInfo(cx, obj);
	js_register_soomla_CCDomain(cx, obj);
	js_register_soomla_CCMarketItem(cx, obj);
	js_register_soomla_CCServiceManager(cx, obj);
	js_register_soomla_CCSoomlaEntity(cx, obj);
	js_register_soomla_CCVirtualItem(cx, obj);
	js_register_soomla_CCPurchasableVirtualItem(cx, obj);
	js_register_soomla_CCVirtualCurrencyPack(cx, obj);
	js_register_soomla_CCError(cx, obj);
	js_register_soomla_CCVirtualCategory(cx, obj);
	js_register_soomla_CCNonConsumableItem(cx, obj);
	js_register_soomla_CCCoreService(cx, obj);
	js_register_soomla_CCPurchaseType(cx, obj);
	js_register_soomla_CCReward(cx, obj);
	js_register_soomla_CCVirtualGood(cx, obj);
	js_register_soomla_CCLifetimeVG(cx, obj);
	js_register_soomla_CCEquippableVG(cx, obj);
	js_register_soomla_CCUpgradeVG(cx, obj);
	js_register_soomla_CCSingleUsePackVG(cx, obj);
	js_register_soomla_CCPurchaseWithMarket(cx, obj);
	js_register_soomla_CCSoomlaStore(cx, obj);
	js_register_soomla_CCVirtualCurrency(cx, obj);
	js_register_soomla_CCStoreService(cx, obj);
	js_register_soomla_CCPurchaseWithVirtualItem(cx, obj);
	js_register_soomla_JSBStoreAssets(cx, obj);
	js_register_soomla_CCStoreInventory(cx, obj);
	js_register_soomla_CCSingleUseVG(cx, obj);
	js_register_soomla_JSBEventHandler(cx, obj);
}


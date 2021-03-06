#include "jsb_controls_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "Button.h"

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
JSClass  *jsb_es_Button_class;
JSObject *jsb_es_Button_prototype;

bool js_controls_Button_getNormalTextureScaleInSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	es::Button* cobj = (es::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_controls_Button_getNormalTextureScaleInSize : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Size ret = cobj->getNormalTextureScaleInSize();
		jsval jsret = JSVAL_NULL;
		jsret = ccsize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_controls_Button_getNormalTextureScaleInSize : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_controls_Button_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		es::Button* ret = es::Button::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<es::Button>(cx, (es::Button*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_controls_Button_create : wrong number of arguments");
	return false;
}

bool js_controls_Button_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::Ref* ret = es::Button::createInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_controls_Button_createInstance : wrong number of arguments");
	return false;
}


extern JSObject *jsb_cocos2d_ui_Button_prototype;

void js_es_Button_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Button)", obj);
}

static bool js_es_Button_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    es::Button *nobj = new es::Button();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "es::Button");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return true;
}
void js_register_controls_Button(JSContext *cx, JSObject *global) {
	jsb_es_Button_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_es_Button_class->name = "Button";
	jsb_es_Button_class->addProperty = JS_PropertyStub;
	jsb_es_Button_class->delProperty = JS_DeletePropertyStub;
	jsb_es_Button_class->getProperty = JS_PropertyStub;
	jsb_es_Button_class->setProperty = JS_StrictPropertyStub;
	jsb_es_Button_class->enumerate = JS_EnumerateStub;
	jsb_es_Button_class->resolve = JS_ResolveStub;
	jsb_es_Button_class->convert = JS_ConvertStub;
	jsb_es_Button_class->finalize = js_es_Button_finalize;
	jsb_es_Button_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getNormalTextureScaleInSize", js_controls_Button_getNormalTextureScaleInSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_es_Button_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_controls_Button_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createInstance", js_controls_Button_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_es_Button_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_ui_Button_prototype,
		jsb_es_Button_class,
		dummy_constructor<es::Button>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "Button", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<es::Button> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_es_Button_class;
		p->proto = jsb_es_Button_prototype;
		p->parentProto = jsb_cocos2d_ui_Button_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

void register_all_controls(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	JS::RootedValue nsval(cx);
	JS::RootedObject ns(cx);
	JS_GetProperty(cx, obj, "ccui", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "ccui", nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_controls_Button(cx, obj);
}


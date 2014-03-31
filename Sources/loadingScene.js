/**
 * Created by mc309 on 1/29/14.
 */

var es = es || {};

es.LoadingLayer = cc.LayerColor.extend({
    _finishFn:null,
    _hasParent:false,

    ctor:function() {
        this._super();
        cc.associateWithNative(this, cc.LayerColor);
        var sz = cc.director.getVisibleSize();
        this.init(cc.color(), sz.width, sz.height);

        this._finishFn = null;
        this._hasParent = false;
        this._implementContent();
    },

    step:function(percent) {
        this._setContentValue(percent);

        if (0 === percent) {
            this.retain();

            if (this.getParent()) {
                this.setZOrder(Math.floor(Number.MAX_VALUE));
                this._hasParent = true;
            } else {
                cc.director.runScene(this._getScene());
            }
        } else if (100 <= percent) {
            cc.director.getScheduler().scheduleCallbackForTarget(this, this._finish, 0, 0, 0.5, false);
        }
    },

    setFinishHandler:function(handler) {
        this._finishFn = handler;
    },

    _finish:function() {
        if (this._hasParent) {
            this.removeFromParent();
        }
        if (this._finishFn)
            this._finishFn();

        this.release();
    },

    _implementContent:function() {
        var sz = cc.director.getVisibleSize();
        this._label = cc.LabelTTF.create('0%', 'Arial', 48);
        this._label.setPosition(cc.p(0.5*sz.width, 0.5*sz.height));
        this.addChild(this._label);
    },

    _setContentValue:function(val) {
        this._label.setString(val.toFixed(1) + '%');
    },

    _getScene:function() {
        var scene = cc.Scene.create();
        scene.addChild(this);
        return scene;
    }
});

es.LoadingLayer.create = function() {
    return new es.LoadingLayer();
};



es.LoadingScene = cc.Class.extend({
    initWith:function(fileName, loadingLayer, endFn) {
        var builder = es.ObjectBuilder.create(fileName, loadingLayer.step.bind(loadingLayer));
        loadingLayer.setFinishHandler(function() {
            if (!endFn)
                throw {
                    name:'es.LoadingScene Error',
                    message:'You must provide callback function.',
                    toString:function() {return this.name + ": " + this.message}
                };

            endFn(builder);
        });
    }
});

es.LoadingScene.preload = function(fileName, loadingLayerOrEndFn, endFn) {
    if (!this._instance)
        this._instance = new es.LoadingScene();

    var argLen = arguments.length;
    if(argLen === 2) {
        this._instance.initWith(fileName, es.LoadingLayer.create(), loadingLayerOrEndFn);
    } else {
        this._instance.initWith(fileName, loadingLayerOrEndFn, endFn);
    }
    return this._instance;
};
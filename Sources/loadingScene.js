/**
 * Created by tovchenko on 1/29/14.
 */

var es = es || {};

es.LoadingLayer = cc.LayerColor.extend({
    _label: null,
    _builder: null,

    ctor: function(builderPromise, nextScene, loaderBuilderPromise) {
        this._super();
        nextScene && nextScene.retain();

        var sz = cc.director.getVisibleSize();
        this.init(cc.color(), sz.width, sz.height);

        var that = this;
        var showLoading = function(builder) {
            that._builder = builder;
            that._implementContent();

            builderPromise.then(function() {
                if (nextScene) {
                    cc.director.popToRootScene();
                    cc.director.pushScene(nextScene);
                    nextScene.release();
                }
            }, function() {
                nextScene.release();
                throw new Error('Scene loading error!');
            }, function(percent) {
                that._setContentValue(percent);
            });
        };

        loaderBuilderPromise
            ? loaderBuilderPromise.then(showLoading)
            : showLoading();
    },

    _implementContent: function() {
        var sz = cc.director.getVisibleSize();
        this._label = new cc.LabelTTF('0%', 'Arial', 48);
        this._label.setPosition(cc.p(0.5*sz.width, 0.5*sz.height));
        this.addChild(this._label);
    },

    _setContentValue: function(val) {
        this._label.setString(val.toFixed(1) + '%');
    }
});


es.LoadingScene = cc.Scene.extend({
    ctor: function(builderPromise, nextScene, loaderBuilderPromise) {
        this._super();
        this.init();
        var layer = new es.LoadingLayer(builderPromise, nextScene, loaderBuilderPromise);
        this.addChild(layer);
    }
});
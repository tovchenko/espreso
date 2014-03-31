/**
 * Created by mc309 on 2/6/14.
 */

var es = es || {};

es.POPUP = {
    MIN_SCALE:0.7,
    MAX_SCALE:1.15,
    ANIM_TIME1:0.15,
    ANIM_TIME2:0.2
};

es.Popup = cc.Layer.extend({
    _widget:null,
    _isTouched:null,
    _fadeLayer:null,
    _enableCloseByClick:true,

    ctor:function(jsonFile) {
        this._super();
        cc.associateWithNative(this, cc.Layer);
        this.init();

        this._isTouched = false;
        this.setEnableCloseByClick(true);

        this._fadeLayer = cc.LayerColor.create(cc.color(0, 0, 0, 0.7));
        this.addChild(this._fadeLayer, -1);

        this._widget = ccs.uiReader.widgetFromJsonFile(es.manager.makeResourcePath(jsonFile));
        this._widget.setAnchorPoint(0.5, 0.5);
        this.addChild(this._widget);

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches:true,

            onTouchBegan:function(touch, event) {
                var target = event.getCurrentTarget();
                var pt = target.convertTouchToNodeSpace(touch);
                target._isTouched = !cc.rectContainsPoint(target._widget.getBoundingBox(), pt);
                return true;
            },

            onTouchEnded:function(touch, event) {
                var target = event.getCurrentTarget();
                if (target._isTouched) {
                    var pt = target.convertTouchToNodeSpace(touch);
                    if (target._enableCloseByClick && !cc.rectContainsPoint(target._widget.getBoundingBox(), pt))
                        target.dismiss();
                }
                target._isTouched = false;
            },

            onTouchCancelled:function(touch, event) {
                var target = event.getCurrentTarget();
                target._isTouched = false;
            }
        }, this);
    },

    getRootWidget:function() {
        return this._widget;
    },

    show:function(parent) {
        parent = parent || cc.director.getRunningScene();
        parent.addChild(this);
        this._layout();
        this._performTransition(true);
    },

    dismiss:function() {
        this._performTransition(false);
        this._fadeLayer.stopAllActions();
        var that = this;
        this._fadeLayer.runAction(cc.Sequence.create(
            cc.FadeTo.create(es.POPUP.ANIM_TIME1 + es.POPUP.ANIM_TIME2, 0),
            cc.CallFunc.create(function() {
                that.removeFromParent();
        })));
    },

    onEnterTransitionDidFinish:function() {
        this._super();
        if (0 === this._fadeLayer.getOpacity())
            this._fadeLayer.runAction(cc.FadeTo.create(es.POPUP.ANIM_TIME1 + es.POPUP.ANIM_TIME2, 155));
    },

    setEnableCloseByClick:function(val) {
        this._enableCloseByClick = val;
    },

    _performTransition:function(forShowing) {
        if (!this._widget)
            return;

        if (forShowing) {
            this._widget.setScale(es.POPUP.MIN_SCALE);
            this._widget.runAction(cc.Sequence.create(cc.ScaleTo.create(es.POPUP.ANIM_TIME1, es.POPUP.MAX_SCALE),
                                                      cc.ScaleTo.create(es.POPUP.ANIM_TIME2, 1)));
        } else {
            this._widget.runAction(cc.Sequence.create(cc.ScaleTo.create(es.POPUP.ANIM_TIME2, es.POPUP.MAX_SCALE),
                                                      cc.ScaleTo.create(es.POPUP.ANIM_TIME1, 0)));
        }
    },

    _layout:function() {
        var visibleSz = cc.director.getVisibleSize();
        var origin = cc.director.getVisibleOrigin();
        this._widget.setPosition(0.5*visibleSz.width + origin.x, 0.5*visibleSz.height + origin.y);
    }
});


es.Popup.create = function(jsonFile) {
    return new es.Popup(jsonFile);
};
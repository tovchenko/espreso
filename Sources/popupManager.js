/**
 * Created by tovchenko on 10/24/14.
 */

var es = es || {};

es.PopupManager = cc.Class.extend({
    _activePopups: null,

    ctor: function() {
        this._activePopups = [];
    },

    // options: {
    //   modal: bool
    //   transition: (NO, DIMOUT, SCALE, DIMOUT_SCALE)
    //   closeTap: bool
    //   position: x, y
    // }
    present: function(popup, options) {
        if (!popup)
            throw new Error('Trying to show an undefined popup!');

        options = options || {};
        return this._makeLayerForPopup(popup, options);
    },

    dismiss: function(popup) {
        var p;
        popup = popup || ((p = _.last(this._activePopups)) && p.popup);
        if (!popup)
            return null;

        var object = _.find(this._activePopups, function(item) { return item.popup === popup; });
        if (!object)
            return null;

        var deferred = Q.defer();
        var that = this;
        this._performTransition(popup, object.options, false, function(opt, show) {
            that._handleTouches(popup, opt, show);
            popup.getParent().removeFromParent();
            _.remove(that._activePopups, function(obj) {
                return obj.popup === popup;
            });
            deferred.resolve();
        });

        return deferred.promise;
    },

    dismissAllPopups: function() {
        for (var i = 0; i < this._activePopups.length; ++i)
            this.dismiss(this._activePopups[i].popup);
    },

    _makeLayerForPopup: function(popup, options) {
        var currentScene = cc.director.getRunningScene();
        if (!currentScene)
            throw new Error('Can\'t show popup, no one run scene!');

        var layer = new cc.LayerColor(cc.color(0, 0, 0, 0));
        var lastObject = _.last(this._activePopups);
        var lastLayer = lastObject && lastObject.popup && lastObject.popup.getParent();
        currentScene.addChild(layer, lastLayer ? lastLayer.getLocalZOrder() + 1 : 0);

        this._activatePopup(layer, popup, options);

        var deferred = Q.defer();
        var that = this;
        this._handleTouches(popup, options, true);
        this._performTransition(popup, options, true, function() {
            that._activePopups.push({
                popup: popup,
                options: options
            });
            deferred.resolve();
        });

        return deferred.promise;
    },

    _activatePopup: function(layer, popup, options) {
        var sz = cc.pAdd(cc.pFromSize(cc.director.getVisibleSize()), cc.director.getVisibleOrigin());

        if (options.position) {
            var pos = options.position;
            popup.setPosition(pos);
            layer.setAnchorPoint(cc.p(pos.x / sz.x, pos.y / sz.y));
        } else {
            popup.setPosition(cc.pMult(sz, 0.5));
        }
        layer.addChild(popup);
    },

    _handleTouches: function(popup, options, doConnect) {
        var that = this;
        var layer = popup.getParent();
        if (!layer)
            throw new Error('Trying to handle touches for disconnected popup!');

        if (doConnect) {
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ONE_BY_ONE,
                swallowTouches: typeof options.modal !== 'undefined' ? options.modal : true,

                onTouchBegan: function(touch, event) {
                    var target = event.getCurrentTarget();
                    var pt = target.convertTouchToNodeSpace(touch);
                    target.__touched = !cc.rectContainsPoint(popup.getBoundingBox(), pt);
                    return true;
                },
                onTouchEnded: function(touch, event) {
                    var target = event.getCurrentTarget();
                    if (target.__touched) {
                        var pt = target.convertTouchToNodeSpace(touch);
                        if (options.closeTap && !cc.rectContainsPoint(popup.getBoundingBox(), pt))
                            that.dismiss(popup);
                    }
                    target.__touched = false;
                },
                onTouchCancelled: function(touch, event) {
                    var target = event.getCurrentTarget();
                    target.__touched = false;
                }
            }, layer);
        } else {
            cc.eventManager.removeListener(layer);
        }
    },

    _performTransition: function(popup, options, show, callback) {
        options = options || {};
        var transition = options.transition || es.PopupManager.Transition.DIMOUT_SCALE;
        switch (transition) {
            case es.PopupManager.Transition.NO: {
                callback && callback(options, show);
                break;
            }

            case es.PopupManager.Transition.DIMOUT:
            case es.PopupManager.Transition.SCALE:
            case es.PopupManager.Transition.DIMOUT_SCALE: {
                var backFn = cc.callFunc(_.partial(callback, options, show));
                var layer = popup.getParent();
                var seq0, seq1;
                if (show) {
                    if (transition === es.PopupManager.Transition.SCALE || transition === es.PopupManager.Transition.DIMOUT_SCALE) {
                        seq0 = cc.sequence(
                            cc.scaleTo(es.PopupManager._Dimout.ANIM_TIME_IN, es.PopupManager._Dimout.MAX_SCALE).easing(cc.easeOut(5)),
                            cc.scaleTo(es.PopupManager._Dimout.ANIM_TIME_OUT, 1).easing(cc.easeIn(5)));
                    }
                    if (transition === es.PopupManager.Transition.DIMOUT || transition === es.PopupManager.Transition.DIMOUT_SCALE) {
                        seq1 = cc.fadeTo(es.PopupManager._Dimout.ANIM_TIME_IN + es.PopupManager._Dimout.ANIM_TIME_OUT, 150);
                    }
                } else {
                    if (transition === es.PopupManager.Transition.SCALE || transition === es.PopupManager.Transition.DIMOUT_SCALE) {
                        seq0 = cc.sequence(
                            cc.scaleTo(es.PopupManager._Dimout.ANIM_TIME_OUT, es.PopupManager._Dimout.MAX_SCALE).easing(cc.easeOut(5)),
                            cc.scaleTo(es.PopupManager._Dimout.ANIM_TIME_IN, 0).easing(cc.easeIn(5)));
                    }
                    if (transition === es.PopupManager.Transition.DIMOUT || transition === es.PopupManager.Transition.DIMOUT_SCALE) {
                        seq1 = cc.fadeTo(es.PopupManager._Dimout.ANIM_TIME_IN + es.PopupManager._Dimout.ANIM_TIME_OUT, 0);
                    }
                }

                layer.runAction(cc.sequence(seq0 ? (seq1 ? cc.spawn(seq0, seq1) : seq0) : seq1, backFn));
                break;
            }

            case es.PopupManager.Transition.TOOLTIP: {
                backFn = cc.callFunc(_.partial(callback, options, show));
                layer = popup.getParent();
                if (show) {
                    layer.setScale(es.PopupManager._ToolScale.MIN_SCALE);
                    layer.runAction(cc.sequence(cc.scaleTo(es.PopupManager._ToolScale.TIME, 1).easing(cc.easeElasticOut()), backFn));
                } else {
                    callback && callback(options, show);
                }
                break;
            }

            default:
                break;
        }
    }
});

es.PopupManager._Dimout = {
    MIN_SCALE: 0.7,
    MAX_SCALE: 1.15,
    ANIM_TIME_IN: 0.1,
    ANIM_TIME_OUT: 0.15
};

es.PopupManager._ToolScale = {
    MIN_SCALE: 0.2,
    TIME: 0.2
};

es.PopupManager.Transition = {
    NO: 1,
    DIMOUT: 2,
    SCALE: 3,
    DIMOUT_SCALE: 4,
    TOOLTIP: 5
};

es.PopupManager.getInstance = function() {
    !es.PopupManager._instance && (es.PopupManager._instance = new es.PopupManager());
    return es.PopupManager._instance;
};

es.popupManager = es.PopupManager.getInstance();
/**
 * Created by tovchenko on 10/24/14.
 */

var es = es || {};

es.PopupManager = cc.Class.extend({
    _activePopups: null,
    _isAnimating: false,

    ctor: function() {
        this._activePopups = [];
        this._isAnimating = false;
    },

    // options: {
    //   modal: bool
    //   transition: (NO, DIMOUT)
    //   closeTap: bool
    //   hideOthers: bool
    //   position: x, y
    // }
    present: function(popup, options) {
        if (!popup)
            throw new Error('Trying to show an undefined popup!');

        this._makeLayerForPopup(popup, options);
    },

    dismiss: function(popup) {
        if (this._isAnimating)
            return;

        this._isAnimating = true;
        var p;
        popup = popup || ((p = _.last(this._activePopups)) && p.popup);
        if (!popup)
            throw new Error('Trying to dismiss an undefined popup!');

        var that = this;
        this._performTransition(popup, false, function(opt, show) {
            that._handleTouches(popup, opt, show);
            popup.getParent().removeFromParent();
            _.remove(that._activePopups, function(obj) {
                return obj.popup === popup;
            });

            that._isAnimating = false;
        });
    },

    _makeLayerForPopup: function(popup, options) {
        if (this._isAnimating)
            return;

        var currentScene = cc.director.getRunningScene();
        if (!currentScene)
            throw new Error('Can\'t show popup, no one run scene!');

        this._isAnimating = true;
        var layer = new cc.LayerColor(cc.color(0, 0, 0, 0));
        var lastObject = _.last(this._activePopups);
        var lastLayer = lastObject && lastObject.popup && lastObject.popup.getParent();
        currentScene.addChild(layer, lastLayer ? lastLayer.getLocalZOrder() + 1 : 0);
        this._activePopups.push({
            popup: popup,
            options: options
        });

        this._activatePopup(layer);

        var that = this;
        this._handleTouches(popup, options, true);
        this._performTransition(popup, true, function() {
            that._isAnimating = false;
        });
    },

    _activatePopup: function(layer) {
        var object = _.last(this._activePopups);
        if (!object)
            throw new Error('No one active popup found!');

        var options = object.options;
        var popup = object.popup;
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
                    var pt = target.convertToNodeSpace(touch);
                    target.__touched = !cc.rectContainsPoint(popup.getBoundingBox(), pt);
                    return true;
                },
                onTouchEnded: function(touch, event) {
                    var target = event.getCurrentTarget();
                    if (target.__touched) {
                        var pt = target.convertToNodeSpace(touch);
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

    _performTransition: function(popup, show, callback) {
        var object = _.find(this._activePopups, function(item) { return item.popup === popup; });
        if (!object)
            throw new Error('Trying to run transition for disconnected popup!');

        var options = object.options || {};
        var transition = options.transition || es.PopupManager.Transition.NO;
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

                layer.runAction(cc.sequence(seq0 ? (seq1 ? cc.spawn(seq0, seq1) : seq0) : seq1 , backFn));
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

es.PopupManager.Transition = {
    NO: 0,
    DIMOUT: 1,
    SCALE: 2,
    DIMOUT_SCALE: 3
};

es.PopupManager.getInstance = function() {
    !es.PopupManager._instance && (es.PopupManager._instance = new es.PopupManager());
    return es.PopupManager._instance;
};

es.popupManager = es.PopupManager.getInstance();
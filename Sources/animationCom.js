/**
 * Created by mc309 on 1/20/14.
 */

var es = es || {};

es.AnimationCom = cc.Component.extend({
    _prefix: null,
    _info: null,
    _actions: null,

    ctor: function(prefix, info) {
        this._super();
        cc.associateWithNative(this, cc.Component);
        this.init();
        this.setName(es.AnimationCom.identifier);

        this._prefix = prefix;
        this._info = info;
        this._actions = {};
    },

    playAnimation: function(name, isReverse, endCallback) {
        var animName = this._prefix + name;
        var anim = cc.animationCache.getAnimation(animName);
        if (!anim)
            throw {
                name: 'es.AnimationCom Error',
                message: 'Animation ' + name + ' isn\'t exist.',
                toString: function() {return this.name + ": " + this.message}
            };

        var looped = this._info[name];
        var action = isReverse ? cc.animate(anim).reverse() : cc.animate(anim);
        action = endCallback
                    ? cc.sequence(action, cc.callFunc(endCallback))
                    : (looped ? cc.repeatForever(action) : action);

        this._actions[animName] = action;
        this.getOwner().runAction(action);
    },

    stopAnimation: function(name) {
        var animName = this._prefix + name;
        this.getOwner().stopAction(this._actions[animName]);
    }
});

es.AnimationCom.create = function(prefix, info) {
    return new es.AnimationCom(prefix, info);
}

es.AnimationCom.identifier = 'Animation';

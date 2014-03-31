/**
 * Created by mc309 on 1/20/14.
 */

var es = es || {};

es.AnimationCom = cc.Component.extend({
    _prefix:null,
    _info:null,

    ctor:function(prefix, info) {
        this._super();
        cc.associateWithNative(this, cc.Component);
        this.init();
        this.setName(es.AnimationCom.identifier);

        this._prefix = prefix;
        this._info = info;
    },

    playAnimation:function(name, isReverse, endCallback) {
        var animName = this._prefix + name;
        var anim = cc.animationCache.getAnimation(animName);
        if (!anim)
            throw {
                name:'es.AnimationCom Error',
                message:'Animation ' + name + 'isn\'t exist.',
                toString:function() {return this.name + ": " + this.message}
            };

        var looped = this._info[name];
        var action = isReverse ? cc.Animate.create(anim).reverse() : cc.Animate.create(anim);
        action = endCallback
                    ? cc.Sequence.create(action, cc.CallFunc.create(endCallback))
                    : (looped ? cc.RepeatForever.create(action) : action);

        this.getOwner().runAction(action);
    }
});

es.AnimationCom.create = function(prefix, info) {
    return new es.AnimationCom(prefix, info);
}

es.AnimationCom.identifier = 'Animation';

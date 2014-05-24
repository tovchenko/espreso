/**
 * Created by mc309 on 1/20/14.
 */

var es = es || {};

es.PlayAnimation = cc.Action.extend({
    _animationName : null,
    _playReverse : null,
    _endCallback : null,

    ctor : function(animationName, callback) {
        this._super();
        cc.associateWithNative(this, cc.Action);

        this._animationName = animationName;
        this._playReverse = false;
        this._endCallback = callback;
    },

    setEndHandler : function(cb) {
        this._endCallback = cb;
    },

    step : function(dt) {
        var com = this.getTarget().getComponent(es.AnimationCom.identifier);
        com.playAnimation(this._animationName, this._playReverse, this._endCallback);
    },

    clone : function() {
        return es.PlayAnimation.create(this._animationName);
    },

    reverse : function() {
        var res = this.clone();
        res._playReverse = !this._playReverse;
        return res;
    }
});

es.PlayAnimation.create = function(animationName, callback) {
    return new es.PlayAnimation(animationName, callback);
};



es.StopAnimation = cc.Action.extend({
    _animationName : null,

    ctor : function(animationName) {
        this._super();
        cc.associateWithNative(this, cc.Action);
        this._animationName = animationName;
    },

    step : function(dt) {
        var com = this.getTarget().getComponent(es.AnimationCom.identifier);
        com.stopAnimation(this._animationName);
    },

    clone : function() {
        return es.StopAnimation.create(this._animationName);
    },

    reverse : function() {
        return this.clone();
    }
});

es.StopAnimation.create = function(animationName) {
    return new es.StopAnimation(animationName);
};



es.PlaySfx = cc.Action.extend({
    _soundName : null,

    ctor : function(soundName) {
        this._super();
        cc.associateWithNative(this, cc.Action);
        this._soundName = soundName;
    },

    step : function(dt) {
        var com = this.getTarget().getComponent(es.AudioCom.identifier);
        com.playEffect(this._soundName);
    },

    clone : function() {
        return es.PlaySfx.create(this._soundName);
    },

    reverse:function() {
        return this.clone();
    }
});

es.PlaySfx.create = function(soundName) {
    return new es.PlaySfx(soundName);
};



es.PlayMusic = cc.Action.extend({
    _soundName : null,

    ctor : function(soundName) {
        this._super();
        cc.associateWithNative(this, cc.Action);
        this._soundName = soundName;
    },

    step : function(dt) {
        var com = this.getTarget().getComponent(es.AudioCom.identifier);
        com.playMusic(this._soundName);
    },

    clone : function() {
        return es.PlayMusic.create(this._soundName);
    },

    reverse : function() {
        return this.clone();
    }
});

es.PlayMusic.create = function(soundName) {
    return new es.PlayMusic(soundName);
};



es.PlayArmature = cc.Action.extend({
    _animationName : null,
    _endCallback : null,

    ctor : function(animationName, callback) {
        this._super();
        cc.associateWithNative(this, cc.Action);

        this._animationName = animationName;
        this._endCallback = callback;
    },

    setEndHandler : function(cb) {
        this._endCallback = cb;
    },

    step : function(dt) {
        var com = this.getTarget().getComponent(es.ArmatureCom.identifier);
        com.playAnimation(this._animationName, this._endCallback);
    },

    clone : function() {
        return es.PlayArmature.create(this._animationName);
    },

    reverse : function() {
        var res = this.clone();
        return res;
    }
});

es.PlayArmature.create = function(animationName, callback) {
    return new es.PlayArmature(animationName, callback);
};
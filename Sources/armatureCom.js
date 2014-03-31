/**
 * Created by mc309 on 2/14/14.
 */

var es = es || {};

es.ArmatureCom = cc.Component.extend({
    _armature:null,
    _info:null,

    ctor:function(armature, info) {
        this._super();
        cc.associateWithNative(this, cc.Component);
        this.init();
        this.setName(es.ArmatureCom.identifier);

        this._armature = armature;
        this._info = info;
    },

    playAnimation:function(name, callback) {
        this._checkType();

        this._armature.getAnimation().play(name, -1, this._info[name] && this._info[name]['loop'] ? 1 : 0);
        this._armature.getAnimation().setMovementEventCallFunc(function(arma, type) {
            if (callback && ccs.MovementEventType.complete === type)
                callback();
        }, this);
    },

    stopAnimation:function() {
        this._checkType();
        this._armature.getAnimation().stop();
    },

    _checkType:function() {
        if (!this._armature instanceof ccs.Armature)
            throw {
                name:'es.ArmatureCom Error',
                message:'Object has no the Armature Component',
                toString:function() {return this.name + ": " + this.message}
            };
    }
});


es.ArmatureCom.create = function(armature, info) {
    return new es.ArmatureCom(armature, info);
};


es.ArmatureCom.identifier = 'Armature';
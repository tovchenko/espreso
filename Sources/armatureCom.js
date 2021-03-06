/**
 * Created by mc309 on 2/14/14.
 */

var es = es || {};

es.ArmatureCom = cc.Component.extend({
    _armature: null,
    _info: null,

    ctor: function(armature, info) {
        this._super();
        this.init();
        this.setName(es.ArmatureCom.identifier);

        this._armature = armature;
        this._info = info;
    },

    playAnimation: function(name, callback) {
        this._checkType();

        var that = this;
        this._armature.getAnimation().play(name, -1, this._info[name] && this._info[name]['loop'] ? 1 : 0);
        this._armature.getAnimation().setMovementEventCallFunc(function(arma, type) {
            if (callback && ccs.MovementEventType.complete === type)
                callback(that.getOwner());
        }, this);
    },

    stopAnimation: function() {
        this._checkType();
        this._armature.getAnimation().stop();
    },

    _checkType: function() {
        if (!this._armature instanceof ccs.Armature)
            throw new Error('Object has no the Armature Component');
    }
});


es.ArmatureCom.create = function(armature, info) {
    return new es.ArmatureCom(armature, info);
};


es.ArmatureCom.identifier = 'Armature';
/**
 * Created by mc309 on 1/27/14.
 */

var es = es || {};

es.AudioCom = cc.Component.extend({
    _sounds: null,
    _music: null,

    ctor: function() {
        this._super();
        cc.associateWithNative(this, cc.Component);
        this.init();
        this.setName(es.AudioCom.identifier);

        this._sounds = {};
        this._music = {};
    },

    addEffect: function(name, fileName, looped, volume) {
        this._sounds[name] = [fileName, looped, volume];
    },

    addMusic: function(name, fileName, looped, volume) {
        this._music[name] = [fileName, looped, volume];
    },

    playEffect: function(name) {
        var val = this._sounds[name];
        if (!val)
            throw {
                name: 'es.AudioCom Error',
                message: 'The sound effect: ' + name + ' isn\'t found in the component.',
                toString: function() {return this.name + ": " + this.message}
            };

//        cc.AudioEngine.getInstance().setEffectsVolume(val[2] || 1);
        cc.audioEngine.playEffect(val[0], val[1]);
    },

    playMusic: function(name) {
        var val = this._music[name];
        if (!val)
            throw {
                name: 'es.AudioCom Error',
                message: 'The background music: ' + name + ' isn\'t found in the component.',
                toString: function() {return this.name + ": " + this.message}
            };

//        cc.AudioEngine.getInstance().setMusicVolume(val[2] || 1);
        cc.audioEngine.playMusic(val[0], val[1]);
    }
});


es.AudioCom.create = function() {
    return new es.AudioCom();
};

es.AudioCom.identifier = 'Audio';
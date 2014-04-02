/**
 * Created by doctorset on 2/2/14.
 */

var es = es || {};

es.platform = {
    _androidTextureExts:['pvr.ccz', 'pkm'],
    _iosTextureExt:'pvr.ccz',
    _webTextureExt:'png',
    _androidSoundExt:'ogg',
    _iosSoundExt:'caf',
    _webSoundExt:['mp3', 'ogg'],

    textureFileName:function(nameWithoutExtension) {
        if (cc.sys.isNative) {
            if (cc.sys.os === cc.sys.OS_ANDROID) {
                for (var i = 0; i < this._androidTextureExts.length; ++i) {
                    var basename = nameWithoutExtension + '.' + exts[i];
                    if (cc.FileUtils.getInstance().isFileExist(cc.FileUtils.getInstance().fullPathForFilename(basename))) {
                        return basename;
                    }
                }
            } else if (cc.sys.os === cc.sys.OS_IOS) {
                return nameWithoutExtension + '.' + this._iosTextureExt;
            }
        } else {
            return nameWithoutExtension + '.' + this._webTextureExt;
        }
    },

    soundFileName:function(nameWithoutExtension) {
        if (cc.sys.isNative) {
            if (cc.sys.os === cc.sys.OS_ANDROID) {
                return nameWithoutExtension + '.' + this._androidSoundExt;
            } else if (cc.sys.os === cc.sys.OS_IOS) {
                return nameWithoutExtension + '.' + this._iosSoundExt;
            }
        } else {
            return nameWithoutExtension + '.' + this._webSoundExt[1];
        }
    }
};

// === Compatibility workarounds ===

(function() {
    var superAddAnimationFn = cc.animationCache.addAnimationsWithDictionary;
    cc.animationCache.addAnimationsWithDictionary = function(dict) {
        if (cc.sys.isNative) {
            superAddAnimationFn.call(cc.animationCache, dict, '');
        } else {
            cc.animationCache._addAnimationsWithDictionary(dict, '');
        }
    };
}());

(function() {
    var superAddSpriteFramesFn = cc.spriteFrameCache.addSpriteFrames;
    cc.spriteFrameCache.addSpriteFrames = function(filePath) {
        superAddSpriteFramesFn.call(cc.spriteFrameCache, es.manager.makeResourcePath(filePath, true));
    };
}());

(function() {
    var superRemoveSpriteFramesFn = cc.spriteFrameCache.removeSpriteFramesFromFile;
    cc.spriteFrameCache.removeSpriteFramesFromFile = function(filePath) {
        superRemoveSpriteFramesFn.call(cc.spriteFrameCache, es.manager.makeResourcePath(filePath, true));
    };
}());

(function() {
    var superSetTexParametersFn = cc.Texture2D.prototype.setTexParameters;
    cc.Texture2D.prototype.setTexParameters = function(params) {
        if (cc.sys.isNative) {
            superSetTexParametersFn.call(this, params.minFilter, params.magFilter, params.wrapS, params.wrapT);
        } else {
            superSetTexParametersFn.call(this, params);
        }
    };
}());


(function() {
    if (!ccs.dataReaderHelper)
        return;

    var superRemoveConfigFileFn = ccs.dataReaderHelper.removeConfigFile;
    ccs.dataReaderHelper.removeConfigFile = function(configFile) {
        superRemoveConfigFileFn.call(this, es.manager.makeResourcePath(configFile));
    };
}());

(function() {
    var superPlayFn = ccs.ArmatureAnimation.prototype.play;
    ccs.ArmatureAnimation.prototype.play = function(name, durationTo, loop) {
        if (cc.sys.isNative) {
            superPlayFn.call(this, name, durationTo, loop);
        } else {
            superPlayFn.call(this, name, durationTo, -1, loop, -1);
            this.setProcessScale(this._processScale);
        }
    };
}());

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

    textureFileName : function(nameWithoutExtension) {
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

    soundFileName : function(nameWithoutExtension) {
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
    cc.Sprite.prototype.getSpriteFrame = cc.Sprite.prototype.getSpriteFrame || cc.Sprite.prototype.displayFrame;

    if (cc.sys.isNative) {
        cc.Component.extend = cc.Class.extend;
        cc.Action.extend = cc.Class.extend;
    }

    var superAddAnimationFn = cc.animationCache.addAnimationsWithDictionary;
    cc.animationCache.addAnimationsWithDictionary = function(dict) {
        if (cc.sys.isNative) {
            superAddAnimationFn.call(cc.animationCache, dict, '');
        } else {
            cc.animationCache._addAnimationsWithDictionary(dict, '');
        }
    };

    var superAddSpriteFramesFn = cc.spriteFrameCache.addSpriteFrames;
    cc.spriteFrameCache.addSpriteFrames = function(filePath) {
        superAddSpriteFramesFn.call(cc.spriteFrameCache, es.manager.makeResourcePath(filePath, true));
    };

    var superRemoveSpriteFramesFn = cc.spriteFrameCache.removeSpriteFramesFromFile;
    cc.spriteFrameCache.removeSpriteFramesFromFile = function(filePath) {
        superRemoveSpriteFramesFn.call(cc.spriteFrameCache, es.manager.makeResourcePath(filePath, true));
    };

    var superSetTexParametersFn = cc.Texture2D.prototype.setTexParameters;
    cc.Texture2D.prototype.setTexParameters = function(params) {
        if (cc.sys.isNative) {
            superSetTexParametersFn.call(this, params.minFilter, params.magFilter, params.wrapS, params.wrapT);
        } else {
            superSetTexParametersFn.call(this, params);
        }
    };

    if (ccs.dataReaderHelper) {
        var superRemoveConfigFileFn = ccs.dataReaderHelper.removeConfigFile;
        ccs.dataReaderHelper.removeConfigFile = function (configFile) {
            superRemoveConfigFileFn.call(this, es.manager.makeResourcePath(configFile));
        };
    }

    var superPlayFn = ccs.ArmatureAnimation.prototype.play;
    ccs.ArmatureAnimation.prototype.play = function(name, durationTo, loop) {
        if (cc.sys.isNative) {
            superPlayFn.call(this, name, durationTo, loop);
        } else {
            superPlayFn.call(this, name, durationTo, -1, loop, -1);
            this.setProcessScale(this._processScale);
        }
    };

    var superFn = ccs.uiReader.widgetFromJsonFile;
    ccs.uiReader.widgetFromJsonFile = function (fileName) {
        if (cc.sys.isNative) {
            return superFn.call(ccs.uiReader, fileName);
        } else {
            var jsonDict = cc.loader.getRes(fileName);
            if(!jsonDict) throw "Please load the resource first : " + fileName;

            var tempFilePath = cc.path.dirname(fileName);
            this._filePath = tempFilePath === fileName ? "" : tempFilePath + "/";

            var fileVersion = jsonDict["version"];
            var pReader, widget;
            var versionInteger = this.getVersionInteger(fileVersion);
            if (fileVersion) {
                if (versionInteger < 250) {
                    pReader = new ccs.WidgetPropertiesReader0250();
                    widget = pReader.createWidget(jsonDict, this._filePath, fileName);
                } else {
                    pReader = new ccs.WidgetPropertiesReader0300();
                    widget = pReader.createWidget(jsonDict, this._filePath, fileName);
                }
            } else {
                pReader = new ccs.WidgetPropertiesReader0250();
                widget = pReader.createWidget(jsonDict, this._filePath, fileName);
            }

            if (!fileVersion || versionInteger < 250) {
                this._olderVersion = true;
            }
            jsonDict = null;
            return widget;
        }
    };
}());

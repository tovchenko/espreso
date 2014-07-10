/**
 * Created by Tovchenko on 1/16/14.
 */


var es = es || {};

es.ResourceType = {
    TEXTURE : 0,
    SPRITE_FRAMES : 1,
    ANIMATION : 2,
    SOUND : 3,
    MUSIC : 4,
    ARMATURE : 5,
    END : 6
};

es.ObjectBuilder = cc.Class.extend({
    _animations : null,
    _animationsCachedPaths : null,
    _sounds : null,
    _soundsCachedPaths : null,
    _music : null,
    _musicCachedPaths : null,
    _spriteFrames : null,
    _spriteFramesCachedPaths : null,
    _textures : null,
    _texturesCachedPaths : null,
    _armatures : null,
    _data : null,
    _dataCachedPaths : null,
    _fonts:null,
    _fontsCachedPaths:null,
    _jsonData : null,
    _updateFn : null,

    _resIter : null,
    _typeIter : null,
    _totalResCount : null,
    _loadedResCount : null,

    _updateProgress : function() {
        ++this._loadedResCount;
        if (this._updateFn)
            this._updateFn(100 * this._loadedResCount / this._totalResCount);
    },

    ctor : function(jsonFileOrFiles, updateFn) {
        this._animations = {};
        this._sounds = {};
        this._music = {};
        this._spriteFrames = [];
        this._textures = [];
        this._armatures = [];
        this._data = {};
        this._fonts = [];
        this._jsonData = null;
        this._updateFn = null;
        this._resIter = 0;
        this._typeIter = es.ResourceType.TEXTURE;
        this._totalResCount = 0;
        this._loadedResCount = 0;

        var jsonFiles = null;
        if (typeof jsonFileOrFiles === 'string') jsonFiles = [jsonFileOrFiles];
        else jsonFiles = [].concat(jsonFileOrFiles);
        jsonFiles = this._getFullUrl(jsonFiles);

        this._jsonData = {};
        var that = this;
        var cnt = 0;
        for (var i = 0; i < jsonFiles.length; ++i) {
            cc.loader.loadJson(jsonFiles[i], function(err, json) {
                if (err) throw err;

                for (var key in json) {
                    if (json.hasOwnProperty(key)) {
                        that._jsonData[key] = json[key];
                    }
                }

                if (++cnt >= jsonFiles.length) {
                    if (Object.keys(that._jsonData).length === 0)
                        return;

                    that._updateFn = updateFn;
                    that._collectInfo(function() {
                        if (that._updateFn) {
                            that._updateFn(0);
                            cc.director.getScheduler().scheduleCallbackForTarget(that, that._loadOneRes, 0, cc.REPEAT_FOREVER, 0, false);
                        } else {
                            var loadNext = true;
                            while (loadNext) {
                                loadNext = that._loadOneRes();
                            }
                        }
                    });
                }
            });
        }
    },

    make : function(objectName) {
        var object = this._jsonData[objectName];
        if (!object)
            throw {
                name:'es.ObjectBuilder Error',
                message:'Object \'' + objectName + '\' doesn\'t exist in the JSON scene file.',
                toString:function() {return this.name + ": " + this.message}
            };

        var res = null;
        // render
        var render = object['render'];
        if (!render) res = cc.Node.create();
        else {
            var armature = render['armature'];
            if (armature) {
                var fileName = armature['file'];
                if (!fileName)
                    throw {
                        name:'es.ObjectBuilder Error',
                        message:'Armature must have \'file\' member.',
                        toString:function() {return this.name + ": " + this.message}
                    };
                var name = fileName.substr(0, fileName.lastIndexOf('.'));
                res = cc.Node.create();
                res.setAnchorPoint(0.5, 0.5);
                var obj = ccs.Armature.create(name);
                obj.setAnchorPoint(0.5, 0.5);
                res.addChild(obj);
                res.addComponent(es.ArmatureCom.create(obj, armature));
            } else {
                var atlas = render['atlas'];
                if (atlas) {
                    if (render['sprite']) res = cc.Sprite.create('#' + render['sprite']);
                    else {
                        var atlasName = es.manager.makeResourcePath(es.platform.textureFileName(atlas), true);
                        res = cc.Sprite.create(atlasName, cc.rect(0,0,0,0)); // this case use only for animations
                    }
                } else {
                    var spriteName = es.manager.makeResourcePath(render['sprite'], true);
                    spriteName = es.platform.textureFileName(spriteName);
                    res = cc.Sprite.create(spriteName);
                }
            }
        }
        // stub
        res.addComponent(new (cc.Component.extend({})));
        // animation
        var animator = object['animator'];
        if (animator) {
            var dict = this._animations[animator];
            var infos = {};

            var anims = dict['animations'];
            for (var key in anims) {
                if (anims.hasOwnProperty(key)) {
                    infos[key] = anims[key] && anims[key]['forever'];
                }
            }
            res.addComponent(es.AnimationCom.create(animator, infos));
        }
        // sound
        var sounds = object['sound'];
        if (sounds) {
            var com = res.getComponent(es.AudioCom.identifier);
            if (!com) {
                com = es.AudioCom.create();
                res.addComponent(com);
            }

            for (var snd in sounds) {
                if (sounds.hasOwnProperty(snd)) {
                    var sndName = es.manager.makeResourcePath(es.platform.soundFileName(sounds[snd]['src']));
                    com.addEffect(snd, sndName, sounds[snd]['loop'], sounds[snd]['volume']);
                }
            }
        }
        // music
        var music = object['music'];
        if (music) {
            var com = res.getComponent(es.AudioCom.identifier);
            if (!com) {
                com = es.AudioCom.create();
                res.addComponent(com);
            }

            for (var snd in music) {
                if (music.hasOwnProperty(snd)) {
                    var musName = es.manager.makeResourcePath(es.platform.soundFileName(music[snd]['src']));
                    com.addMusic(snd, musName, music[snd]['loop'], music[snd]['volume']);
                }
            }
        }
        // sound
        var data = object['data'];
        if (data) {
            var com = res.getComponent(es.DataCom.identifier);
            if (!com) {
                res.addComponent(es.DataCom.create(data));
            }
        }
        return res;
    },

    makeBatchNode : function(objectName) {
        var object = this._jsonData[objectName];
        if (!object)
            throw {
                name:'es.ObjectBuilder Error',
                message:'Object \'' + objectName + '\' doesn\'t exist in the JSON scene file.',
                toString:function() {return this.name + ": " + this.message}
            };

        var render = object['render'];
        if (!render)
            throw {
                name:'es.ObjectBuilder Error',
                message:'Attempt to create SpriteBatchNode from the object with no render part.',
                toString:function() {return this.name + ": " + this.message}
            };

        if (render['armature']) {
            return ccs.BatchNode.create();
        }

        var textureName = render['atlas'] || render['sprite'];
        textureName = es.manager.makeResourcePath(textureName, true);
        textureName = es.platform.textureFileName(textureName);
        return cc.SpriteBatchNode.create(textureName);
    },

    _getFullUrl : function(urlList, useResolution) {
        var res = [];
        urlList.forEach(function(url) {
            res.push(es.manager.makeResourcePath(url, useResolution));
        });
        return res;
    },

    _collectInfo : function(cb) {
        var that = this;
        this._animationsCachedPaths = [];

        for (var objectName in this._jsonData) {
            if (!this._jsonData.hasOwnProperty(objectName))
                continue;
            // render
            var render = this._jsonData[objectName]['render'];
            if (render) {
                var armature = render['armature'];
                if (armature) {
                    if (-1 === this._armatures.indexOf(armature['file'])) {
                        this._armatures.push(armature['file']);
                        ++this._totalResCount;
                    }
                }
                var atlasName = render['atlas'];
                if (atlasName) {
                    texName = es.platform.textureFileName(atlasName);
                    if (-1 === this._textures.indexOf(texName)) {
                        this._textures.push(texName);
                        this._spriteFrames.push(atlasName + '.plist');
                        this._totalResCount += 2;
                    }
                } else {
                    var spriteName = render['sprite'];
                    if (spriteName) {
                        var texName = es.platform.textureFileName(spriteName);
                        if (-1 === this._textures.indexOf(texName)) {
                            this._textures.push(texName);
                            ++this._totalResCount;
                        }
                    } else if (!armature) {
                        throw {
                            name:'es.ObjectBuilder Error',
                            message:'Object doesn\'t have sprite property.',
                            toString:function() {return this.name + ": " + this.message}
                        };
                    }
                }
            }
            //sounds can not be preloaded on mobile browsers
            if (cc.sys.isNative || !cc.sys.isMobile) {
                // sound
                var sounds = this._jsonData[objectName]['sound'];
                if (sounds) {
                    for (var key in sounds) {
                        if (sounds.hasOwnProperty(key)) {
                            var soundId = sounds[key]['src'];
                            if (!this._sounds[soundId]) {
                                this._sounds[soundId] = sounds[key];
                                ++this._totalResCount;
                            }
                        }
                    }
                }
                // music
                var music = this._jsonData[objectName]['music'];
                if (music) {
                    for (var key in music) {
                        if (music.hasOwnProperty(key)) {
                            var musicId = music[key]['src'];
                            if (!this._music[musicId]) {
                                this._music[musicId] = music[key];
                                ++this._totalResCount;
                            }
                        }
                    }
                }
            }
            // data
            var data = this._jsonData[objectName]['data'];
            if (data) {
                this._data[objectName] = data;
            }
            // fonts
            var font = this._jsonData[objectName]['font'];
            if (font && -1 === this._fonts.indexOf(font)) {
                this._fonts.push(font);
            }
            // animations
            var animator = this._jsonData[objectName]['animator'];
            if (animator && -1 === this._animationsCachedPaths.indexOf(animator)) {
                this._animationsCachedPaths.push(animator);
            }
        }

        cc.loader.load(this._animationsCachedPaths, function() {
            for (var i = 0; i < that._animationsCachedPaths.length; ++i) {
                var animator = that._animationsCachedPaths[i];

                var dict = cc.loader.getRes(animator);
                if (!dict)
                    throw {
                        name:'es.ObjectBuilder Error',
                        message:'Animation json file doesn\'t exist or is empty.',
                        toString:function() {return this.name + ": " + this.message}
                    };

                var sheets = dict['properties'] && dict['properties']['spritesheets'];
                if (sheets) {
                    for (var j = 0; j < sheets.length; ++j) {
                        var texNameWithoutExt = sheets[j].substr(0, sheets[j].lastIndexOf('.'));
                        var texName = es.platform.textureFileName(texNameWithoutExt);
                        sheets[j] = texNameWithoutExt + '.plist';
                        if (-1 === that._textures.indexOf(texName)) {
                            that._textures.push(texName);
                            that._spriteFrames.push(sheets[j]);
                            that._totalResCount += 2;
                        }
                    }
                }
                that._animations[animator] = dict;
                ++that._totalResCount;
            }

            // load other resources
            that._texturesCachedPaths = that._getFullUrl(that._textures, true);
            that._spriteFramesCachedPaths = that._getFullUrl(that._spriteFrames, true);

            that._soundsCachedPaths = [];
            for (var key in that._sounds)
                if (that._sounds.hasOwnProperty(key))
                    that._soundsCachedPaths.push(es.platform.soundFileName(that._sounds[key]['src']));
            that._soundsCachedPaths = that._getFullUrl(that._soundsCachedPaths);

            that._musicCachedPaths = [];
            for (var key in that._music)
                if (that._music.hasOwnProperty(key))
                    that._musicCachedPaths.push(es.platform.soundFileName(that._music[key]['src']));
            that._musicCachedPaths = that._getFullUrl(that._musicCachedPaths);

            that._dataCachedPaths = [];
            for (var key in that._data)
                if (that._data.hasOwnProperty(key))
                    that._dataCachedPaths.push(that._data[key]);

            that._fontsCachedPaths = [];
            for (var key in that._fonts)
                if (that._fonts.hasOwnProperty(key))
                    that._fontsCachedPaths.push(es.manager.makeResourcePath(that._fonts[key]));

            var list = [].concat(
                that._texturesCachedPaths,
                that._spriteFramesCachedPaths,
                that._armatures,
                that._soundsCachedPaths,
                that._musicCachedPaths,
                that._dataCachedPaths,
                that._fontsCachedPaths);

            cc.loader.load(list, cb);
        });
    },

    _loadOneRes : function() {
        var isLast = false;
        var isEmpty = false;

        switch (this._typeIter) {
            case es.ResourceType.TEXTURE:
                if (!this._texturesCachedPaths.length) {
                    isLast = isEmpty = true;
                    break;
                }
                var obj = this._texturesCachedPaths[this._resIter];
                cc.log('Loading texture: ' + obj);
                cc.textureCache.addImage(obj);
                isLast = ++this._resIter === this._texturesCachedPaths.length;
                break;

            case es.ResourceType.SPRITE_FRAMES:
                if (!this._spriteFramesCachedPaths.length) {
                    isLast = isEmpty = true;
                    break;
                }
                var obj = this._spriteFramesCachedPaths[this._resIter];
                cc.log('Loading sprite frames: ' + obj);
                cc.spriteFrameCache.addSpriteFrames(obj);
                isLast = ++this._resIter === this._spriteFramesCachedPaths.length;
                break;

            case es.ResourceType.ANIMATION:
                var keys = Object.keys(this._animations);
                if (!keys.length) {
                    isLast = isEmpty = true;
                    break;
                }
                var keyFileName = keys[this._resIter];
                cc.log('Loading animations: ' + keyFileName);
                var dict = this._animations[keyFileName];

                var anims = dict['animations'];
                if (anims) {
                    for (var key in anims) {
                        if (anims.hasOwnProperty(key)) {
                            anims[key]['forever'] = anims[key]['loop'];
                            anims[key]['loop'] = false;
                        }
                    }
                }
                cc.animationCache.addAnimationsWithDictionary(dict);
                if (anims) {
                    for (var key in anims) {
                        if (anims.hasOwnProperty(key)) {
                            var animation = cc.animationCache.getAnimation(key);
                            cc.animationCache.addAnimation(animation, keyFileName + key);
                            cc.animationCache.removeAnimation(key);
                        }
                    }
                }
                isLast = ++this._resIter === keys.length;
                break;

            case es.ResourceType.SOUND:
                if (!this._soundsCachedPaths.length) {
                    isLast = isEmpty = true;
                    break;
                }

                var obj = this._soundsCachedPaths[this._resIter];
                cc.log('Loading sound: ' + obj);
                cc.sys.isNative && cc.audioEngine.preloadEffect(obj);
                isLast = ++this._resIter === this._soundsCachedPaths.length;
                break;

            case es.ResourceType.MUSIC:
                if (!this._musicCachedPaths.length) {
                    isLast = isEmpty = true;
                    break;
                }

                var obj = this._musicCachedPaths[this._resIter];
                cc.log('Loading music: ' + obj);
                // cc.sys.isNative && cc.audioEngine.preloadMusic(obj);
                isLast = ++this._resIter === this._musicCachedPaths.length;
                break;

            case  es.ResourceType.ARMATURE:
                if (!this._armatures.length) {
                    isLast = isEmpty = true;
                    break;
                }

                var obj = this._armatures[this._resIter];
                cc.log('Loading armature: ' + obj);
                ccs.armatureDataManager.addArmatureFileInfo(obj);
                isLast = ++this._resIter === this._armatures.length;
                break;
        }

        if (!isEmpty)
            this._updateProgress();

        if (isLast) {
            this._resIter = 0;
            if (++this._typeIter === es.ResourceType.END) {
                if (this._updateFn) {
                    cc.director.getScheduler().unscheduleCallbackForTarget(this, arguments.callee);
                    if (0 === this._loadedResCount)
                        this._updateFn(100);
                }
                return false;
            }
        }
        return true;
    },

    purge : function() {
        this._texturesCachedPaths.forEach(function(tex) {
            cc.log('Unloading texture: ' + tex);
            cc.loader.release(tex);
            cc.textureCache.removeTextureForKey(tex);
        });
        this._spriteFramesCachedPaths.forEach(function(obj) {
            cc.log('Unloading sprite frames: ' + obj);
            cc.loader.release(obj);
            cc.spriteFrameCache.removeSpriteFramesFromFile(obj);
        });
        this._armatures.forEach(function(obj) {
            cc.log('Unloading armature: ' + obj);
            cc.loader.release(obj);
            ccs.armatureDataManager.removeArmatureFileInfo(obj);
        });
        for (var keyFileName in this._animations) {
            if (this._animations.hasOwnProperty(keyFileName)) {
                cc.log('Unloading animations: ' + keyFileName);
                cc.animationCache.removeAnimation(keyFileName);
            }
        }
        this._soundsCachedPaths.forEach(function(obj) {
            cc.log('Unloading sound: ' + obj);
            cc.loader.release(obj);
            cc.audioEngine.unloadEffect(obj);
        });
        this._dataCachedPaths.forEach(function(obj) {
            cc.log('Unloading JSON: ' + obj);
            cc.loader.release(obj);
        });
        this._fontsCachedPaths.forEach(function(obj) {
            cc.log('Unloading FONT: ' + obj);
            cc.loader.release(obj);
        });
        this._animationsCachedPaths.forEach(function(obj) {
            cc.log('Unloading Animation plist: ' + obj);
            cc.loader.release(obj);
        });
    }
});

es.ObjectBuilder.create = function(jsonFileOrFiles, finishFn) {
    return new es.ObjectBuilder(jsonFileOrFiles, finishFn);
};
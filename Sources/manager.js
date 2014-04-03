/**
 * Created by mc309 on 1/30/14.
 */

var es = es || {};


es.manager = {
    _resolutionDependedPath:null,
    _resPath:'',

    getScreenSize:function() {
        if (!this._screenSize) {
            this._screenSize = cc.view.getFrameSize ? cc.view.getFrameSize() : cc.view.getWinSizeInPixels();
        }
        return function(w, h) {
            return cc.size(w, h);
        }(this._screenSize.width, this._screenSize.height);
    },

    applyDefaults:function() {
        var maxRes = cc.size(640, 420);
        this.setDesignResolutionSize(cc.size(480, 320), maxRes);
        this.setSearchPathsByScales(maxRes, [[4, 'HDR'], [2, 'HD'], [1, 'SD']]);
    },

    setDesignResolutionSize:function(minScreenSize, maxTextureSizeOrPolicy) {
        if (typeof maxTextureSizeOrPolicy === 'number') {
            cc.view.setDesignResolutionSize(minScreenSize.width, minScreenSize.height, maxTextureSizeOrPolicy);
            return;
        }

        var fs =  this.getScreenSize();
        var minSz = this._longSideToLongSide(minScreenSize, fs);
        var maxSz = this._longSideToLongSide(maxTextureSizeOrPolicy, fs);

        while (fs.width > maxSz.width || fs.height > maxSz.height) {
            fs.width *= 0.5;
            fs.height *= 0.5;
        }

        if (fs.width >= minSz.width && fs.height >= minSz.height) {
            cc.view.setDesignResolutionSize(fs.width, fs.height, cc.ResolutionPolicy.NO_BORDER);
        } else if (fs.width / fs.height > minSz.width / minSz.height) { // if frame wider than minSz
            cc.view.setDesignResolutionSize(minSz.height * fs.width / fs.height, minSz.height, cc.ResolutionPolicy.NO_BORDER);
        } else {
            cc.view.setDesignResolutionSize(minSz.width, minSz.width * fs.height / fs.width, cc.ResolutionPolicy.NO_BORDER);
        }
    },

    setSearchPathsByScales:function(maxTextureSize, paths) {
        var fs =  this.getScreenSize();

        var maxSz = this._longSideToLongSide(maxTextureSize, fs);
        var scale = 1;
        var power = 0;
        while (fs.width > maxSz.width || fs.height > maxSz.height) {
            scale = Math.pow(2, ++power);
            fs.width *= 0.5;
            fs.height *= 0.5;
        }

        var sf = 1;
        for (var i = 0; i < paths.length; ++i) {
            var path = paths[i];
            if (scale >= path[0]) {
                this._resolutionDependedPath = path[1];
                sf = (sf < path[0]) ? path[0] : sf;
                break;
            }
        }
        cc.director.setContentScaleFactor(sf);
    },

    makeResourcePath:function(path, useResolutionPath, useResPath) {
        var pathParts = path.split('/');
        var len = pathParts.length;
        var base = cc.path.basename(path);

        if (len > 1) {
            var hasResolution = (pathParts[len - 2] === this._resolutionDependedPath);
            var hasResource = (hasResolution && len > 2 && pathParts[len - 3] === this._resPath) ||
                              (!hasResolution && pathParts[len - 2] === this._resPath);

            if (useResolutionPath) {
                if (hasResource && hasResolution) {
                    if (useResPath) return path;
                    return cc.path.join(this._resolutionDependedPath, base);
                }
                if (hasResource) {
                    if (useResPath)
                        return cc.path.join(cc.path.join(cc.path.dirname(path), this._resolutionDependedPath), base);
                    return cc.path.join(this._resolutionDependedPath, base);
                }
                if (hasResolution)
                    return path;
                throw {
                    name:'es.manager Error',
                    message:'Can\'t calculate a path.',
                    toString:function() {return this.name + ": " + this.message}
                };
            } else {
                if (hasResource && hasResolution) {
                    pathParts.splice(len - 1, 1);
                    return cc.path.join(pathParts.join('/'), base);
                }
                if (hasResource)
                    return path;
                throw {
                    name:'es.manager Error',
                    message:'Can\'t calculate a path.',
                    toString:function() {return this.name + ": " + this.message}
                };
            }
        } else {
            if (useResolutionPath) {
                if (useResPath)
                    return cc.path.join(cc.path.join(this._resPath, this._resolutionDependedPath), path);
                return cc.path.join(this._resolutionDependedPath, path);
            }
            else
                return cc.path.join(this._resPath, path);
        }
    },

    _longSideToLongSide:function(sizeToFit, srcSize) {
        if (srcSize.width > sizeToFit.height) {
            if (sizeToFit.width < sizeToFit.height)
                return cc.size(sizeToFit.height, sizeToFit.width);
        } else if (sizeToFit.width > sizeToFit.height) {
            return cc.size(sizeToFit.height, sizeToFit.width);
        }
        return sizeToFit;
    }
};

(function() {
    es.manager._resPath = cc.loader.resPath;
}());
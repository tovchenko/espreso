/**
 * Created by mc309 on 1/30/14.
 */

var es = es || {};


es.manager = {
    _resolutionDependedPath : null,

    defaultLODs : [
        { scale:2, path:'HDR', size:cc.size(1920, 1280) },
        { scale:1, path:'HD', size:cc.size(960, 640) },
        { scale:0.5, path:'SD', size:cc.size(0, 0) }],

    setup : function(LODs) {
        this.setDesignResolutionSize(cc.view.getFrameSize(), cc.ResolutionPolicy.SHOW_ALL);
        this.setSearchPathsByScales(LODs);
    },

    setDesignResolutionSize : function(minScreenSize, maxTextureSizeOrPolicy) {
        if (typeof maxTextureSizeOrPolicy === 'number') {
            cc.view.setDesignResolutionSize(minScreenSize.width, minScreenSize.height, maxTextureSizeOrPolicy);
            return;
        }

        var fs = cc.view.getFrameSize();
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

    setSearchPathsByScales : function(paths) {
        var fs = cc.view.getFrameSize();
        cc.log('Frame Size = ' + fs.width + 'x' + fs.height);

        var current = cc.size(0, 0);
        for (var i = 0; i < paths.length; ++i) {
            var sz = this._longSideToLongSide(paths[i].size, fs);
            if ((sz.width >= current.width && sz.width < fs.width)
               || (sz.height >= current.height && sz.height < fs.height))
            {
                current = sz;
                this._resolutionDependedPath = paths[i].path;
                cc.director.setContentScaleFactor(paths[i].scale);
            }
        }
    },

    makeResourcePath : function(path, useResolutionPath, useResPath) {
        var pathParts = path.split('/');
        var len = pathParts.length;
        var base = cc.path.basename(path);

        if (len > 1) {
            var hasResolution = (pathParts[len - 2] === this._resolutionDependedPath);
            var hasResource = (hasResolution && len > 2 && pathParts[len - 3] === cc.loader.resPath) ||
                              (!hasResolution && pathParts[len - 2] === cc.loader.resPath);

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
                    return cc.path.join(cc.path.join(cc.loader.resPath, this._resolutionDependedPath), path);
                return cc.path.join(this._resolutionDependedPath, path);
            }
            else
                return cc.path.join(cc.loader.resPath, path);
        }
    },

    _longSideToLongSide : function(sizeToFit, srcSize) {
        if (srcSize.width > sizeToFit.height) {
            if (sizeToFit.width < sizeToFit.height)
                return cc.size(sizeToFit.height, sizeToFit.width);
        } else if (sizeToFit.width > sizeToFit.height) {
            return cc.size(sizeToFit.height, sizeToFit.width);
        }
        return sizeToFit;
    }
};
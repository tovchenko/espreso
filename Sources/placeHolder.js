/**
 * Created by doctorset on 2/19/14.
 */

var es = es || {};

es.PlaceHolder = cc.Class.extend({
    _builders : null,
    _jsonData : null,

    ctor : function(jsonScene, builders) {
        this._builders = [];

        if (Object.prototype.toString.call(builders) === '[object Array]')
            this._builders.concat(builders);
        else
            this._builders.push(builders);

        this._jsonData = jsonScene;
    },

    makeTree : function(name) {
        var info = this._getInfoByName(name);
        var root = null;
        if (!name) { // it is 'widgetTree'
            var size = cc.director.getWinSize();
            root = this._buildNodeTree(info, size, size);
        } else {
            root = this._buildNodeTree(info, cc.size(0, 0));
        }
        return root;
    },

    makeObjectFromBuilder : function(name) {
        var node = null;
        for (var i = 0; i < this._builders.length && !node; ++i) {
            try {
                node = this._builders[i].make(name);
            } catch(obj) {
            }
        }
        if (!node)
            node = cc.Node.create();
        return node;
    },

    _buildNodeTree : function(info, parentSize, rootSize) {
        var options = info['options'] || info;
        var name = options['name'];
        var idx;
        name && (-1 !== (idx = name.indexOf('@'))) && (name = name.substring(0, idx));

        var node = this.makeObjectFromBuilder(name);
        this.setPropertyFromJsonDict(node, options, parentSize);
        if (rootSize) { // it is 'widgetTree'
            node.setContentSize(rootSize);
            node.setAnchorPoint(0.5, 0.5);
            node.setPosition(0.5 * rootSize.width, 0.5 * rootSize.height);
        }

        var children = info['children'] || [];
        for (var i = 0; i < children.length; ++i) {
            node.addChild(arguments.callee.call(this, children[i], node.getContentSize()));
        }
        return node;
    },

    _getInfoByName : function(name, info) {
        var widgets = this._jsonData['widgetTree'];
        if (!name) return widgets;

        info = info || widgets;
        var objectName = info['options']['name'];
        if (objectName && objectName === name)
            return info;

        var children = info['children'] || [];
        for (var i = 0; i < children.length; ++i) {
            var res = arguments.callee.call(this, name, children[i]);
            if (res) return res;
        }
        return null;
    },

    setPropertyFromJsonDict : function (node, dict, parentSize) {
        (typeof parentSize === 'undefined') && (parentSize = cc.size(0, 0));
        (typeof parentSize.width === 'undefined') && (parentSize.width = 0);
        (typeof parentSize.height === 'undefined') && (parentSize.height = 0);

        var usePercentPosition = Boolean((typeof  dict['positionType'] === 'undefined') ? 0 : dict['positionType']);
        if (usePercentPosition) {
            var xp = (typeof dict['positionPercentX'] === 'undefined') ? 0 : dict['positionPercentX'];
            var yp = (typeof dict['positionPercentY'] === 'undefined') ? 0 : dict['positionPercentY'];
            node.setPosition(parentSize.width * xp, parentSize.height * yp);
        } else {
            var x = (typeof dict['x'] === 'undefined') ? 0 : dict['x'];
            var y = (typeof dict['y'] === 'undefined') ? 0 : dict['y'];
            node.setPosition(x, y);
        }

        var ignoreSize = Boolean((typeof dict['ignoreSize'] === 'undefined') ? 1 : dict['ignoreSize']);
        if (!ignoreSize) {
            var usePercentSize = Boolean((typeof  dict['sizeType'] === 'undefined') ? 0 : dict['sizeType']);
            if (usePercentSize) {
                var wp = (typeof dict['sizePercentX'] === 'undefined') ? 0 : dict['sizePercentX'];
                var hp = (typeof dict['sizePercentY'] === 'undefined') ? 0 : dict['sizePercentY'];
                node.setContentSize(parentSize.width * wp, parentSize.height * hp);
            } else {
                var width = (typeof dict['width'] === 'undefined') ? 0 : dict['width'];
                var height = (typeof dict['height'] === 'undefined') ? 0 : dict['height'];
                node.setContentSize(width, height);
            }
        }

        var bVisible = Boolean((typeof dict['visible'] === 'undefined') ? 1 : dict['visible']);
        node.setVisible(bVisible);

        var nTag = (typeof dict['tag'] === 'undefined') ? -1 : dict['tag'];
        node.setTag(nTag);

        var name = (typeof dict['name'] === 'undefined') ? 'undefined' : dict['name'];
        node.setName(name);

        var nZorder = (typeof dict['ZOrder'] === 'undefined') ? 0 : dict['ZOrder'];
        node.setLocalZOrder(nZorder);

        var fScaleX = (typeof dict['scaleX'] === 'undefined') ? 1 : dict['scaleX'];
        var fScaleY = (typeof dict['scaleY'] === 'undefined') ? 1 : dict['scaleY'];
        node.setScaleX(fScaleX);
        node.setScaleY(fScaleY);

        var fAnchorX = (typeof dict['anchorPointX'] === 'undefined') ? 0.5 : dict['anchorPointX'];
        var fAnchorY = (typeof dict['anchorPointY'] === 'undefined') ? 0.5 : dict['anchorPointY'];
        node.setAnchorPoint(fAnchorX, fAnchorY);

        var fRotationZ = (typeof dict['rotation'] === 'undefined') ? 0 : dict['rotation'];
        node.setRotation(fRotationZ);
    }
});

es.PlaceHolder.create = function(jsonScene, builders) {
    return new es.PlaceHolder(jsonScene, builders);
};


es.HolderCache = function(tree) {
    this.tree = tree;
    this.cache = {};
};

es.HolderCache.prototype.find = function(name, root) {
    var res = this.cache[name];
    if (res) return res;

    !root && (root = this.tree);
    res = root.getChildByName(name);
    if (!res) {
        var children = root.getChildren();
        for (var i = 0, len = children.length; i < len; ++i) {
            res = arguments.callee.call(this, name, children[i]);
            if (res) {
                this.cache[name] = res;
                return res;
            }
        }
    }
    return res;
};
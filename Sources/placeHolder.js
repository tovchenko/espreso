/**
 * Created by doctorset on 2/19/14.
 */

var es = es || {};

es.PlaceHolder = cc.Class.extend({
    _builders:null,
    _jsonData:null,

    ctor:function(jsonScene, builders) {
        this._builders = [];

        if (Object.prototype.toString.call(builders) === '[object Array]')
            this._builders.concat(builders);
        else
            this._builders.push(builders);

        this._jsonData = jsonScene;
    },

    makeTree:function(name) {
        var size = this._jsonData['CanvasSize'];
        var info = this._getInfoByName(name);
        var root = this._buildNodeTree(info);
        if (!name) {
            root.setAnchorPoint(0.5, 0.5);
            root.setContentSize(size['_width'], size['_height']);
        }
        return root;
    },

    makeObjectFromBuilder:function(name) {
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

    _buildNodeTree:function(info) {
        var node = this.makeObjectFromBuilder(info['name']);
        this.setPropertyFromJsonDict(node, info);

        var children = info['gameobjects'] || [];
        for (var i = 0; i < children.length; ++i) {
            node.addChild(arguments.callee.call(this, children[i]));
        }
        return node;
    },

    _getInfoByName:function(name, info) {
        if (!name) return this._jsonData;

        info = info || this._jsonData;
        if (info['name'] && info['name'] === name)
            return info;

        var children = info['gameobjects'] || [];
        for (var i = 0; i < children.length; ++i) {
            var res = arguments.callee.call(this, name, children[i]);
            if (res) return res;
        }
        return null;
    },

    setPropertyFromJsonDict: function (node, dict) {
        var x = dict['x'] || 0;
        var y = dict['y'] || 0;
        node.setPosition(x, y);

        var bVisible = Boolean(dict['visible']);
        node.setVisible(bVisible);

        var nTag = dict['objecttag'] || -1;
        node.setTag(nTag);

        var nZorder = dict['zorder'] || 0;
        node.setLocalZOrder(nZorder);

        var fScaleX = dict['scalex'] || 1;
        var fScaleY = dict['scaley'] || 1;
        node.setScaleX(fScaleX);
        node.setScaleY(fScaleY);

        var fRotationZ = dict['rotation'] || 0;
        node.setRotation(fRotationZ);
    }
});

es.PlaceHolder.create = function(jsonScene, builders) {
    return new es.PlaceHolder(jsonScene, builders);
};

es.PlaceHolder.getNodeByTag = function(root, tag) {
    var res = root.getChildByTag(tag);
    if (!res) {
        var children = root.getChildren();
        for (var i = 0; i < children.length; ++i) {
            res = arguments.callee.call(null, children[i], tag);
            if (res) return res;
        }
    }
    return res;
};
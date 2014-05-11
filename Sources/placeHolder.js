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

    makeTree : function(name, frozen) {
        var info = this._getInfoByName(name);
        var root = this._buildNodeTree(info);
        if (!name) {
            var sz = cc.director.getVisibleSize();
            var origin = cc.director.getVisibleOrigin();
            root.setAnchorPoint(0.5, 0.5);
            root.setPosition(0.5 * sz.width + origin.x, 0.5 * sz.height + origin.y);
        } else if (!frozen) {
            var sz = cc.director.getVisibleSize();
            var pt = cc.p(0.5 * (sz.width - this._jsonData['designWidth']),
                          0.5 * (sz.height - this._jsonData['designHeight']));
            root.setPosition(cc.pAdd(cc.pAdd(root.getPosition(), pt), cc.director.getVisibleOrigin()));
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

    _buildNodeTree : function(info) {
        var options = info['options'] || info;
        var node = this.makeObjectFromBuilder(options['name']);
        this.setPropertyFromJsonDict(node, options);

        var children = info['children'] || [];
        for (var i = 0; i < children.length; ++i) {
            node.addChild(arguments.callee.call(this, children[i]));
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

    setPropertyFromJsonDict : function (node, dict) {
        var x = (typeof dict["x"] === 'undefined')?0:dict["x"];
        var y = (typeof dict["y"] === 'undefined')?0:dict["y"];
        node.setPosition(x, y);

        var ignoreSize = Boolean((typeof dict["ignoreSize"] === 'undefined')?1:dict["ignoreSize"]);
        if (!ignoreSize) {
            var width = (typeof dict["width"] === 'undefined') ? 0 : dict["width"];
            var height = (typeof dict["height"] === 'undefined') ? 0 : dict["height"];
            node.setContentSize(width, height);
        }

        var bVisible = Boolean((typeof dict["visible"] === 'undefined')?1:dict["visible"]);
        node.setVisible(bVisible);

        var nTag = (typeof dict["objecttag"] === 'undefined')?-1:dict["objecttag"];
        node.setTag(nTag);

        var nZorder = (typeof dict["zorder"] === 'undefined')?0:dict["zorder"];
        node.setLocalZOrder(nZorder);

        var fScaleX = (typeof dict["scalex"] === 'undefined')?1:dict["scalex"];
        var fScaleY = (typeof dict["scaley"] === 'undefined')?1:dict["scaley"];
        node.setScaleX(fScaleX);
        node.setScaleY(fScaleY);

        var fRotationZ = (typeof dict["rotation"] === 'undefined')?0:dict["rotation"];
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
/**
 * Created by mc309 on 2/12/14.
 */

var es = es || {};

es.utils = {
    readRectsFromCocoStudioGUI:function(jsonOfFileName) {
        if (typeof jsonOfFileName === 'string')
            jsonOfFileName = cc.loader.getRes(es.manager.makeResourcePath(jsonOfFileName));

        var widgetTree = jsonOfFileName['widgetTree'];
        var rectNodes = widgetTree && widgetTree['children'];
        if (!rectNodes)
            throw {
                name:'es.utils.readRectsFromCocoStudioGUI Error',
                message:'File should have been created in CocoStudio GUI editor.',
                toString:function() {return this.name + ": " + this.message}
            };
        var rects = [];
        for (var i = 0; i < rectNodes.length; ++i) {
            var node = rectNodes[i]['options'];
            if (!node)
                throw {
                    name:'es.utils.readRectsFromCocoStudioGUI Error',
                    message:'Incorrect node structure in CocoStudio GUI editor.',
                    toString:function() {return this.name + ": " + this.message}
                };
            rects.push({name:node['name'], rect:cc.rect(node['x'], node['y'], node['width'], node['height']), z:node['ZOrder']});
        }
        return rects;
    },

    getProps:function(object) {
        return object.getComponent(es.DataCom.identifier).getData();
    },

    getPropsFileName:function(object) {
        return object.getComponent(es.DataCom.identifier).getFileName();
    }
};

// --------------------------------------------------------------------------------------------------------------
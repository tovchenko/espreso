/**
 * Created by mc309 on 3/28/14.
 */

var es = es || {};

es.DataCom = cc.Component.extend({
    _jsonData: null,
    _fileName: null,

    ctor: function(filename) {
        this._super();
        cc.associateWithNative(this, cc.Component);
        this.init();
        this.setName(es.DataCom.identifier);

        this._fileName = filename;
        this._jsonData = cc.loader.getRes(this._fileName);
    },

    getData: function() {
        return this._jsonData;
    },

    getFileName: function() {
        return this._fileName;
    }
});

es.DataCom.create = function(filename) {
    return new es.DataCom(filename);
};

es.DataCom.identifier = 'Data';
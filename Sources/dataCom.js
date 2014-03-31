/**
 * Created by mc309 on 3/28/14.
 */

es.DataCom = cc.Component.extend({
    _jsonData:null,

    ctor:function(json) {
        this._super();
        cc.associateWithNative(this, cc.Component);
        this.init();
        this.setName(es.DataCom.identifier);

        this._jsonData = json;
    },

    getData:function() {
        return this._jsonData;
    }
});

es.DataCom.create = function(json) {
    return new es.DataCom(json);
};

es.DataCom.identifier = 'Data';
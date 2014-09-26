/**
 * Created by tovchenko on 9/25/14.
 */

var es = es || {};

var _superOnPressStateChangedToNormal = null;
var _superOnPressStateChangedToPressed = null;

(function() {
    // registers in HTML5 new button type - EspresoButton
    var factoryCreate = ccs.objectFactory;
    factoryCreate.registerType({_className: 'EspresoButtonReader', _fun: ccs.ButtonReader});
    factoryCreate.registerType({_className: 'EspresoButton', _fun: ccui.Button});

    _superOnPressStateChangedToNormal = ccui.Button.prototype._onPressStateChangedToNormal;
    _superOnPressStateChangedToPressed = ccui.Button.prototype._onPressStateChangedToPressed;
}());

ccui.Button.prototype._onPressStateChangedToNormal = function() {
    _superOnPressStateChangedToNormal.call(this);

    if (!this._pressedTextureLoaded && !this._scale9Enabled) {
        const coef = this.getPressedCoef();
        this._buttonNormalRenderer.setScale(this._normalTextureScaleXInSize * coef, this._normalTextureScaleYInSize * coef);
        this._buttonNormalRenderer.runAction(this.getPressAction(this._normalTextureScaleXInSize, this._normalTextureScaleYInSize));
    }
};

ccui.Button.prototype._onPressStateChangedToPressed = function() {
    _superOnPressStateChangedToPressed.call(this);

    if (!this._pressedTextureLoaded && !this._scale9Enabled) {
        const coef = this.getPressedCoef();
        this._buttonNormalRenderer.setScale(this._normalTextureScaleXInSize, this._normalTextureScaleYInSize);
        this._buttonNormalRenderer.runAction(this.getPressAction(this._normalTextureScaleXInSize * coef, this._normalTextureScaleYInSize * coef));
    }
};

ccui.Button.prototype.getPressedCoef = function() {
    return 1.2;
};

ccui.Button.prototype.getPressAction = function(sx, sy) {
    return cc.scaleTo(0.4, sx, sy).easing(cc.easeElasticOut());
};
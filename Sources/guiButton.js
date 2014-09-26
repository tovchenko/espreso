/**
 * Created by tovchenko on 9/25/14.
 */

var es = es || {};

(function() {
    const kForce = 0.05;

    // registers in HTML5 new button type - EspresoButton
    var factoryCreate = ccs.objectFactory;
    factoryCreate.registerType({_className: 'es::ButtonReader', _fun: ccs.ButtonReader});
    factoryCreate.registerType({_className: 'es::Button', _fun: ccui.Button});

    var _superOnPressStateChangedToNormal = ccui.Button.prototype._onPressStateChangedToNormal;
    ccui.Button.prototype._onPressStateChangedToNormal = function () {
        _superOnPressStateChangedToNormal.apply(this, arguments);

        if (!this._pressedTextureLoaded && !this._scale9Enabled) {
            const coef = this.getPressedCoef();
            this._buttonNormalRenderer.setScale(this._normalTextureScaleXInSize * coef, this._normalTextureScaleYInSize * coef);
            this._buttonNormalRenderer.runAction(this.getPressAction(this._normalTextureScaleXInSize, this._normalTextureScaleYInSize));
        }
    };

    var _superOnPressStateChangedToPressed = ccui.Button.prototype._onPressStateChangedToPressed;
    ccui.Button.prototype._onPressStateChangedToPressed = function () {
        _superOnPressStateChangedToPressed.apply(this, arguments);

        if (!this._pressedTextureLoaded && !this._scale9Enabled) {
            const coef = this.getPressedCoef();
            this._buttonNormalRenderer.setScale(this._normalTextureScaleXInSize, this._normalTextureScaleYInSize);
            this._buttonNormalRenderer.runAction(this.getPressAction(this._normalTextureScaleXInSize * coef, this._normalTextureScaleYInSize * coef));
        }
    };

    var _superOnEnter = ccui.Button.prototype.onEnter;
    ccui.Button.prototype.onEnter = function () {
        _superOnEnter.apply(this, arguments);

        if (this._isJellyAnimationEnabled)
            this._startJellyAnimation();
    };

    var _superOnExit = ccui.Button.prototype.onExit;
    ccui.Button.prototype.onExit = function () {
        this.unscheduleUpdate();
        _superOnExit.apply(this, arguments);
    };

    var _superUpdate = ccui.Button.prototype.update;
    ccui.Button.prototype.update = function (dt) {
        _superUpdate.apply(this, arguments);

        if (!this._isJellyAnimationEnabled)
            return;

        this._counter += 0.5 * dt;
        const newBouncingX = 0.5 * (Math.cos(this._counter * 10) + 1) * kForce * this.getNormalScaleInSize().width;
        const newBouncingY = 0.5 * (Math.sin(this._counter * 10) + 1) * kForce * this.getNormalScaleInSize().height;

        this.setScaleX(this.getScaleX() + newBouncingX - this._scaleBouncingX);
        this.setScaleY(this.getScaleY() + newBouncingY - this._scaleBouncingY);

        this._scaleBouncingX = newBouncingX;
        this._scaleBouncingY = newBouncingY;

        if (this._counter > 10 * Math.PI)
            this._counter = 0;
    };

    ccui.Button.prototype.getNormalScaleInSize = function () {
        return cc.sys.isNative
            ? this.getNormalTextureScaleInSize()
            : cc.size(this._normalTextureScaleXInSize, this._normalTextureScaleYInSize);
    };

    ccui.Button.prototype.getPressedCoef = function () {
        return 1.2;
    };

    ccui.Button.prototype.getPressAction = function (sx, sy) {
        return cc.scaleTo(0.4, sx, sy).easing(cc.easeElasticOut());
    };

    ccui.Button.prototype._startJellyAnimation = function() {
        this._counter = Math.random() % 31;
        this._scaleBouncingX = 0.5 * (Math.cos(this._counter * 10) + 1) * kForce;
        this._scaleBouncingY = 0.5 * (Math.sin(this._counter * 10) + 1) * kForce;

        this.scheduleUpdate();
    };

    ccui.Button.prototype.setJellyAnimationEnabled = function(enabled) {
        if (enabled && !this._isJellyAnimationEnabled) {
            this._isJellyAnimationEnabled = true;
            if (this.isRunning())
                this._startJellyAnimation();
        } else if (!enabled && this._isJellyAnimationEnabled) {
            this._isJellyAnimationEnabled = false;
            if (this.isRunning())
                this.unscheduleUpdate();
        }
    };

    ccui.Button.prototype.getJellyAnimationEnabled = function() {
        return this._isJellyAnimationEnabled;
    };
}());
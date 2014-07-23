/**
 * Created by tovchenko on 7/23/14.
 */

var es = es || {};

es.makeMenuItemScalable = function(menuItem, scale) {
    var originalScale = menuItem.getScale();
    var selectedScale = originalScale * (scale || 1.2);
    var superSelected = menuItem.selected;
    var superUnselected = menuItem.unselected;

    var scaleActionTag = Math.floor(Number.MAX_VALUE);

    menuItem.selected = function() {
        superSelected.call(this);

        this.stopActionByTag(scaleActionTag);
        var scaleAction = cc.EaseElasticOut.create(cc.ScaleTo.create(0.4, selectedScale));
        scaleAction.tag = scaleActionTag;

        this.runAction(scaleAction);
    };

    menuItem.unselected = function () {
        superUnselected.call(this);

        this.stopActionByTag(scaleActionTag);
        var scaleAction = cc.EaseElasticOut.create(cc.ScaleTo.create(0.4, originalScale));
        scaleAction.tag = scaleActionTag;

        this.runAction(scaleAction);
    };
};
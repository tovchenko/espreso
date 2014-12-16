/**
 * Created by tovchenko on 7/23/14.
 */

var es = es || {};
es.MenuItem = es.MenuItem || {};

es.makeMenuItemScalable = function(menuItem, scale) {
    var originalScale = menuItem.getScale();
    var selectedScale = originalScale * (scale || 1.2);
    var superSelected = menuItem.selected;
    var superUnselected = menuItem.unselected;

    var scaleActionTag = Math.floor(Number.MAX_VALUE);

    menuItem.selected = function() {
        superSelected.call(this);

        this.stopActionByTag(scaleActionTag);
        var scaleAction =  cc.scaleTo(0.4, selectedScale).easing(cc.easeElasticOut());
        scaleAction.tag = scaleActionTag;

        this.runAction(scaleAction);
    };

    menuItem.unselected = function() {
        superUnselected.call(this);

        this.stopActionByTag(scaleActionTag);
        var scaleAction = cc.scaleTo(0.4, originalScale).easing(cc.easeElasticOut());
        scaleAction.tag = scaleActionTag;

        this.runAction(scaleAction);
    };
};

es.MenuItem.createScalable = function(sprite, callback, scale) {
    var item = new cc.MenuItemSprite();
    item.setNormalImage(sprite);
    item.setAnchorPoint(0.5, 0.5);
    item.setEnabled(true);
    callback && item.setCallback(callback);
    es.makeMenuItemScalable(item, scale);
    return item;
};
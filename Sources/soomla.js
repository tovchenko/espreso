/**
 * Created by tovchenko on 2/12/14.
 */

var es = es || {};

if (cc.sys.isNative) {
    soomla.serviceManager = soomla.ServiceManager.getInstance();
    soomla.eventHandler = soomla.EventHandler.getInstance();
    soomla.initShared = soomla.StoreService.initShared;

    soomla.StoreAssets.create = function(params) {
        var res = new soomla.StoreAssets();

        var categories = params['categories'];
        if (categories && Object.prototype.toString.call(categories) === '[object Array]') {
            categories.forEach(function(obj) {
                res.addCategory(obj);
            });
        }

        var currencies = params['currencies'];
        if (currencies && Object.prototype.toString.call(currencies) === '[object Array]') {
            currencies.forEach(function(obj) {
                res.addCurrency(obj);
            });
        }

        var currencyPacks = params['currencyPacks'];
        if (currencyPacks && Object.prototype.toString.call(currencyPacks) === '[object Array]') {
            currencyPacks.forEach(function(obj) {
                res.addCurrencyPack(obj);
            });
        }

        var goods = params['goods'];
        if (goods && Object.prototype.toString.call(goods) === '[object Array]') {
            goods.forEach(function(obj) {
                res.addGood(obj);
            });
        }

        var nonConsumables = params['nonConsumables'];
        if (nonConsumables && Object.prototype.toString.call(nonConsumables) === '[object Array]') {
            goods.forEach(function(obj) {
                res.addNonConsumableItem(obj);
            });
        }

        res.setVersion(params['version'] || 1);

        return res;
    };

    soomla.VirtualCurrency.create = function(params) {
        return new soomla.VirtualCurrency(params);
    };

    soomla.VirtualCurrencyPack.create = function(params) {
        var purchaseType = params['purchaseType'];
        delete params['purchaseType'];
        return new soomla.VirtualCurrencyPack(params, purchaseType);
    };

    soomla.PurchaseWithMarket.create = function(params) {
        return new soomla.PurchaseWithMarket(params);
    };

    soomla.SingleUseVG.create = function(params) {
        var purchaseType = params['purchaseType'];
        delete params['purchaseType'];
        return new soomla.SingleUseVG(params, purchaseType);
    };

    soomla.PurchaseWithVirtualItem.create = function(params) {
        return new soomla.PurchaseWithVirtualItem(params);
    };

    soomla.VirtualCategory.create = function(params) {
        return new soomla.VirtualCategory(params);
    };
}
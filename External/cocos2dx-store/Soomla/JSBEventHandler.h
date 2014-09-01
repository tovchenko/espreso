// Created by Tovchenko Taras 2014

#ifndef __JSBEventHandler__
#define __JSBEventHandler__

#include <string>
#include "CCStoreEventHandler.h"


using namespace std;

namespace soomla {
    
    class JSBEventHandler : public CCStoreEventHandler {
    public:
        static JSBEventHandler *getInstance();
        
        auto setBillingNotSupportedHandler(function<void()> cb)->void;
        auto setBillingSupportedHandler(function<void()> cb)->void;
        auto setCurrencyBalanceChangedHandler(function<void(CCVirtualCurrency*, int, int)> cb)->void;
        auto setGoodBalanceChangedHandler(function<void(CCVirtualGood*, int, int)> cb)->void;
        auto setGoodEquippedHandler(function<void(CCEquippableVG*)> cb)->void;
        auto setGoodUnEquippedHandler(function<void(CCEquippableVG*)> cb)->void;
        auto setGoodUpgradeHandler(function<void(CCVirtualGood*, CCUpgradeVG*)> cb)->void;
        auto setItemPurchasedHandler(function<void(CCPurchasableVirtualItem*)> cb)->void;
        auto setItemPurchaseStartedHandler(function<void(CCPurchasableVirtualItem*)> cb)->void;
        auto setMarketPurchaseCancelledHandler(function<void(CCPurchasableVirtualItem*)> cb)->void;
        auto setMarketPurchaseHandler(function<void(CCPurchasableVirtualItem*, cocos2d::__String*, cocos2d::__String*)> cb)->void;
        auto setMarketPurchaseStartedHandler(function<void(CCPurchasableVirtualItem*)> cb)->void;
        auto setMarketPurchaseVerificationHandler(function<void(CCPurchasableVirtualItem*)> cb)->void;
        auto setRestoreTransactionsStartedHandler(function<void()> cb)->void;
        auto setRestoreTransactionsFinishedHandler(function<void(bool)> cb)->void;
        auto setUnexpectedErrorInStoreHandler(function<void()> cb)->void;
        auto setStoreControllerInitializedHandler(function<void()> cb)->void;
        auto setMarketItemsRefreshedHandler(function<void(cocos2d::__Array*)> cb)->void;
        auto setMarketItemsRefreshStartedHandler(function<void()> cb)->void;
        
        auto setAndroidMarketRefundHandler(function<void(CCPurchasableVirtualItem*)> cb)->void;
        auto setAndroidIabServiceStartedHandler(function<void()> cb)->void;
        auto setAndroidIabServiceStoppedHandler(function<void()> cb)->void;
        
    protected:
        JSBEventHandler();
        virtual ~JSBEventHandler();
        
        virtual void onBillingNotSupported();
        virtual void onBillingSupported();
        virtual void onCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded);
        virtual void onGoodBalanceChanged(CCVirtualGood *virtualGood, int balance, int amountAdded);
        virtual void onGoodEquipped(CCEquippableVG *equippableVG);
        virtual void onGoodUnEquipped(CCEquippableVG *equippableVG);
        virtual void onGoodUpgrade(CCVirtualGood *virtualGood, CCUpgradeVG *upgradeVG);
        virtual void onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem);
        virtual void onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem);
        virtual void onMarketPurchaseCancelled(CCPurchasableVirtualItem *purchasableVirtualItem);
        virtual void onMarketPurchase(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::__String *token, cocos2d::__String *payload);
        virtual void onMarketPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem);
        virtual void onMarketPurchaseVerification(CCPurchasableVirtualItem *purchasableVirtualItem);
        virtual void onRestoreTransactionsStarted();
        virtual void onRestoreTransactionsFinished(bool success);
        virtual void onUnexpectedErrorInStore();
        virtual void onStoreControllerInitialized();
        virtual void onMarketItemsRefreshed(cocos2d::__Array *pArray);
        virtual void onMarketItemsRefreshStarted();

        // ===== CC_PLATFORM_ANDROID =========================================================
        virtual void onMarketRefund(CCPurchasableVirtualItem *purchasableVirtualItem);
        virtual void onIabServiceStarted();
        virtual void onIabServiceStopped();
        
        function<void()>                                _onBillingNotSupported = nullptr;
        function<void()>                                _onBillingSupported = nullptr;
        function<void(CCVirtualCurrency*, int, int)>    _onCurrencyBalanceChanged = nullptr;
        function<void(CCVirtualGood*, int, int)>        _onGoodBalanceChanged = nullptr;
        function<void(CCEquippableVG*)>                 _onGoodEquipped = nullptr;
        function<void(CCEquippableVG*)>                 _onGoodUnEquipped = nullptr;
        function<void(CCVirtualGood*, CCUpgradeVG*)>    _onGoodUpgrade = nullptr;
        function<void(CCPurchasableVirtualItem*)>       _onItemPurchased = nullptr;
        function<void(CCPurchasableVirtualItem*)>       _onItemPurchaseStarted = nullptr;
        function<void(CCPurchasableVirtualItem*)>       _onMarketPurchaseCancelled = nullptr;
        function<void(CCPurchasableVirtualItem*, cocos2d::__String*, cocos2d::__String*)>   _onMarketPurchase = nullptr;
        function<void(CCPurchasableVirtualItem*)>       _onMarketPurchaseStarted = nullptr;
        function<void(CCPurchasableVirtualItem*)>       _onMarketPurchaseVerification = nullptr;
        function<void()>                                _onRestoreTransactionsStarted = nullptr;
        function<void(bool)>                            _onRestoreTransactionsFinished = nullptr;
        function<void()>                                _onUnexpectedErrorInStore = nullptr;
        function<void()>                                _onStoreControllerInitialized = nullptr;
        function<void(cocos2d::__Array*)>               _onMarketItemsRefreshed = nullptr;
        function<void()>                                _onMarketItemsRefreshStarted = nullptr;
        function<void(CCPurchasableVirtualItem*)>       _onMarketRefund = nullptr;
        function<void()>                                _onIabServiceStarted = nullptr;
        function<void()>                                _onIabServiceStopped = nullptr;
    };
}

#endif /* !JSBEventHandler */

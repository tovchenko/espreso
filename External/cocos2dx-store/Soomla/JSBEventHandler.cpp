
#include "JSBEventHandler.h"
#include "CCStoreEventDispatcher.h"
#include "CCStoreUtils.h"
#include "cocos2d.h"

#define TAG "Soomla: JSBEventHandler >>>"

using namespace cocos2d;
using namespace soomla;

static JSBEventHandler *s_SharedInstance = nullptr;

JSBEventHandler *JSBEventHandler::getInstance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new JSBEventHandler;
    }
    return s_SharedInstance;
}

JSBEventHandler::JSBEventHandler() {
    CCStoreEventDispatcher::getInstance()->addEventHandler(this);
}

JSBEventHandler::~JSBEventHandler() {
    CCStoreEventDispatcher::getInstance()->removeEventHandler(this);
}

auto JSBEventHandler::setBillingNotSupportedHandler(function<void()> cb)->void {
    _onBillingNotSupported = cb;
}

auto JSBEventHandler::setBillingSupportedHandler(function<void()> cb)->void {
    _onBillingSupported = cb;
}

auto JSBEventHandler::setCurrencyBalanceChangedHandler(function<void(CCVirtualCurrency*, int, int)> cb)->void {
    _onCurrencyBalanceChanged = cb;
}

auto JSBEventHandler::setGoodBalanceChangedHandler(function<void(CCVirtualGood*, int, int)> cb)->void {
    _onGoodBalanceChanged = cb;
}

auto JSBEventHandler::setGoodEquippedHandler(function<void(CCEquippableVG*)> cb)->void {
    _onGoodEquipped = cb;
}

auto JSBEventHandler::setGoodUnEquippedHandler(function<void(CCEquippableVG*)> cb)->void {
    _onGoodUnEquipped = cb;
}

auto JSBEventHandler::setGoodUpgradeHandler(function<void(CCVirtualGood*, CCUpgradeVG*)> cb)->void {
    _onGoodUpgrade = cb;
}

auto JSBEventHandler::setItemPurchasedHandler(function<void(CCPurchasableVirtualItem*)> cb)->void {
    _onItemPurchased = cb;
}

auto JSBEventHandler::setItemPurchaseStartedHandler(function<void(CCPurchasableVirtualItem*)> cb)->void {
    _onItemPurchaseStarted = cb;
}

auto JSBEventHandler::setMarketPurchaseCancelledHandler(function<void(CCPurchasableVirtualItem*)> cb)->void {
    _onMarketPurchaseCancelled = cb;
}

auto JSBEventHandler::setMarketPurchaseHandler(function<void(CCPurchasableVirtualItem*, cocos2d::__String*, cocos2d::__String*)> cb)->void {
    _onMarketPurchase = cb;
}

auto JSBEventHandler::setMarketPurchaseStartedHandler(function<void(CCPurchasableVirtualItem*)> cb)->void {
    _onMarketPurchaseStarted = cb;
}

auto JSBEventHandler::setMarketPurchaseVerificationHandler(function<void(CCPurchasableVirtualItem*)> cb)->void {
    _onMarketPurchaseVerification = cb;
}

auto JSBEventHandler::setRestoreTransactionsStartedHandler(function<void()> cb)->void {
    _onRestoreTransactionsStarted = cb;
}

auto JSBEventHandler::setRestoreTransactionsFinishedHandler(function<void(bool)> cb)->void {
    _onRestoreTransactionsFinished = cb;
}

auto JSBEventHandler::setUnexpectedErrorInStoreHandler(function<void()> cb)->void {
    _onUnexpectedErrorInStore = cb;
}

auto JSBEventHandler::setStoreControllerInitializedHandler(function<void()> cb)->void {
    _onStoreControllerInitialized = cb;
}

auto JSBEventHandler::setMarketItemsRefreshedHandler(function<void(cocos2d::__Array*)> cb)->void {
    _onMarketItemsRefreshed = cb;
}

auto JSBEventHandler::setMarketItemsRefreshStartedHandler(function<void()> cb)->void {
    _onMarketItemsRefreshStarted = cb;
}

auto JSBEventHandler::setAndroidMarketRefundHandler(function<void(CCPurchasableVirtualItem*)> cb)->void {
    _onMarketRefund = cb;
}

auto JSBEventHandler::setAndroidIabServiceStartedHandler(function<void()> cb)->void {
    _onIabServiceStarted = cb;
}

auto JSBEventHandler::setAndroidIabServiceStoppedHandler(function<void()> cb)->void {
    _onIabServiceStopped = cb;
}

void JSBEventHandler::onBillingNotSupported() {
    if (_onBillingNotSupported)
        _onBillingNotSupported();
    CCStoreUtils::logDebug(TAG, "BillingNotSupported");
}

void JSBEventHandler::onBillingSupported() {
    if (_onBillingSupported)
        _onBillingSupported();
    CCStoreUtils::logDebug(TAG, "BillingSupported");
}

void JSBEventHandler::onCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded) {
    if (_onCurrencyBalanceChanged)
        _onCurrencyBalanceChanged(virtualCurrency, balance, amountAdded);
    CCStoreUtils::logDebug(TAG, "CurrencyBalanceChanged");
}

void JSBEventHandler::onGoodBalanceChanged(CCVirtualGood *virtualGood, int balance, int amountAdded) {
    if (_onGoodBalanceChanged)
        _onGoodBalanceChanged(virtualGood, balance, amountAdded);
    CCStoreUtils::logDebug(TAG, "GoodBalanceChanged");
}

void JSBEventHandler::onGoodEquipped(CCEquippableVG *equippableVG) {
    if (_onGoodEquipped)
        _onGoodEquipped(equippableVG);
    CCStoreUtils::logDebug(TAG, "GoodEquipped");
}

void JSBEventHandler::onGoodUnEquipped(CCEquippableVG *equippableVG) {
    if (_onGoodUnEquipped)
        _onGoodUnEquipped(equippableVG);
    CCStoreUtils::logDebug(TAG, "GoodUnEquipped");
}

void JSBEventHandler::onGoodUpgrade(CCVirtualGood *virtualGood, CCUpgradeVG *upgradeVG) {
    if (_onGoodUpgrade)
        _onGoodUpgrade(virtualGood, upgradeVG);
    CCStoreUtils::logDebug(TAG, "GoodUpgrade");
}

void JSBEventHandler::onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem) {
    if (_onItemPurchased)
        _onItemPurchased(purchasableVirtualItem);
    CCStoreUtils::logDebug(TAG, "ItemPurchased");
}

void JSBEventHandler::onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) {
    if (_onItemPurchaseStarted)
        _onItemPurchaseStarted(purchasableVirtualItem);
    CCStoreUtils::logDebug(TAG, "ItemPurchaseStarted");
}

void JSBEventHandler::onMarketPurchaseCancelled(CCPurchasableVirtualItem *purchasableVirtualItem) {
    if (_onMarketPurchaseCancelled)
        _onMarketPurchaseCancelled(purchasableVirtualItem);
    CCStoreUtils::logDebug(TAG, "MarketPurchaseCancelled");
}

void JSBEventHandler::onMarketPurchase(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::__String *token, cocos2d::__String *payload) {
    if (_onMarketPurchase)
        _onMarketPurchase(purchasableVirtualItem, token, payload);
    CCStoreUtils::logDebug(TAG, "MarketPurchase");
}

void JSBEventHandler::onMarketPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) {
    if (_onMarketPurchaseStarted)
        _onMarketPurchaseStarted(purchasableVirtualItem);
    CCStoreUtils::logDebug(TAG, "MarketPurchaseStarted");
}

void JSBEventHandler::onMarketPurchaseVerification(CCPurchasableVirtualItem *purchasableVirtualItem) {
    if (_onMarketPurchaseVerification)
        _onMarketPurchaseVerification(purchasableVirtualItem);
    CCStoreUtils::logDebug(TAG, "MarketPurchaseVerification");
}

void JSBEventHandler::onRestoreTransactionsStarted() {
    if (_onRestoreTransactionsStarted)
        _onRestoreTransactionsStarted();
    CCStoreUtils::logDebug(TAG, "RestoreTransactionsStarted");
}

void JSBEventHandler::onRestoreTransactionsFinished(bool success) {
    if (_onRestoreTransactionsFinished)
        _onRestoreTransactionsFinished(success);
    CCStoreUtils::logDebug(TAG, "RestoreTransactionsFinished");
}

void JSBEventHandler::onUnexpectedErrorInStore() {
    if (_onUnexpectedErrorInStore)
        _onUnexpectedErrorInStore();
    CCStoreUtils::logDebug(TAG, "UnexpectedErrorInStore");
}

void JSBEventHandler::onStoreControllerInitialized() {
    if (_onStoreControllerInitialized)
        _onStoreControllerInitialized();
    CCStoreUtils::logDebug(TAG, "StoreContorllerInitialized");
}

void JSBEventHandler::onMarketItemsRefreshed(cocos2d::__Array *pArray) {
    if (_onMarketItemsRefreshed)
        _onMarketItemsRefreshed(pArray);
    CCStoreUtils::logDebug(TAG, "MarketItemsRefreshed");
}

void JSBEventHandler::onMarketItemsRefreshStarted() {
    if (_onMarketItemsRefreshStarted)
        _onMarketItemsRefreshStarted();
    CCStoreUtils::logDebug(TAG, "MarketItemsRefreshStarted");
}



void JSBEventHandler::onMarketRefund(CCPurchasableVirtualItem *purchasableVirtualItem) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (_onMarketRefund)
        _onMarketRefund(purchasableVirtualItem);
    CCStoreUtils::logDebug(TAG, "MarketRefund");
#endif
}

void JSBEventHandler::onIabServiceStarted() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (_onIabServiceStarted)
        _onIabServiceStarted();
    CCStoreUtils::logDebug(TAG, "IabServiceStarted");
#endif
}

void JSBEventHandler::onIabServiceStopped() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (_onIabServiceStopped)
        _onIabServiceStopped();
    CCStoreUtils::logDebug(TAG, "IabServiceStopped");
#endif
}

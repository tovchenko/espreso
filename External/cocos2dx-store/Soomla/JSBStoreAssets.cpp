
#include "JSBStoreAssets.h"

using namespace soomla;


JSBStoreAssets::~JSBStoreAssets() {
    CC_SAFE_RELEASE(_currencies);
    CC_SAFE_RELEASE(_goods);
    CC_SAFE_RELEASE(_currencyPacks);
    CC_SAFE_RELEASE(_categories);
    CC_SAFE_RELEASE(_nonConsumableItems);
}

auto JSBStoreAssets::addCategory(cocos2d::Ref* category)->void {
    if (!_categories) {
        _categories = soomla::Array::createWithObject(category);
        _categories->retain();
    } else _categories->addObject(category);
}

auto JSBStoreAssets::addCurrency(cocos2d::Ref* currency)->void {
    if (!_currencies) {
        _currencies = soomla::Array::createWithObject(currency);
        _currencies->retain();
    } else _currencies->addObject(currency);
}

auto JSBStoreAssets::addCurrencyPack(cocos2d::Ref* pack)->void {
    if (!_currencyPacks) {
        _currencyPacks = soomla::Array::createWithObject(pack);
        _currencyPacks->retain();
    } else _currencyPacks->addObject(pack);
}

auto JSBStoreAssets::addGood(cocos2d::Ref* good)->void {
    if (!_goods) {
        _goods = soomla::Array::createWithObject(good);
        _goods->retain();
    } else _goods->addObject(good);
}

auto JSBStoreAssets::addNonConsumableItem(cocos2d::Ref* item)->void {
    if (!_nonConsumableItems) {
        _nonConsumableItems = soomla::Array::createWithObject(item);
        _nonConsumableItems->retain();
    } else _nonConsumableItems->addObject(item);
}
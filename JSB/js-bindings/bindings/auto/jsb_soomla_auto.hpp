#ifndef __soomla_h__
#define __soomla_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_soomla_CCDomain_class;
extern JSObject *jsb_soomla_CCDomain_prototype;

bool js_soomla_CCDomain_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCDomain_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCDomain(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCDomain_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCDomain_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCSoomlaEntity_class;
extern JSObject *jsb_soomla_CCSoomlaEntity_prototype;

bool js_soomla_CCSoomlaEntity_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCSoomlaEntity_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCSoomlaEntity(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCSoomlaEntity_setDescription(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaEntity_setName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaEntity_getName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaEntity_getDescription(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaEntity_getId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaEntity_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaEntity_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaEntity_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaEntity_setId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaEntity_CCSoomlaEntity(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCVirtualItem_class;
extern JSObject *jsb_soomla_CCVirtualItem_prototype;

bool js_soomla_CCVirtualItem_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCVirtualItem_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCVirtualItem(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCVirtualItem_save(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualItem_getItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualItem_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualItem_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualItem_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCPurchaseType_class;
extern JSObject *jsb_soomla_CCPurchaseType_prototype;

bool js_soomla_CCPurchaseType_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCPurchaseType_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCPurchaseType(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCPurchaseType_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseType_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseType_CCPurchaseType(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCPurchasableVirtualItem_class;
extern JSObject *jsb_soomla_CCPurchasableVirtualItem_prototype;

bool js_soomla_CCPurchasableVirtualItem_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCPurchasableVirtualItem_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCPurchasableVirtualItem(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCPurchasableVirtualItem_getPurchaseType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchasableVirtualItem_setPurchaseType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchasableVirtualItem_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchasableVirtualItem_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchasableVirtualItem_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchasableVirtualItem_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchasableVirtualItem_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchasableVirtualItem_CCPurchasableVirtualItem(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCVirtualGood_class;
extern JSObject *jsb_soomla_CCVirtualGood_prototype;

bool js_soomla_CCVirtualGood_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCVirtualGood_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCVirtualGood(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCVirtualGood_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualGood_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCLifetimeVG_class;
extern JSObject *jsb_soomla_CCLifetimeVG_prototype;

bool js_soomla_CCLifetimeVG_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCLifetimeVG_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCLifetimeVG(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCLifetimeVG_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCLifetimeVG_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCEquippableVG_class;
extern JSObject *jsb_soomla_CCEquippableVG_prototype;

bool js_soomla_CCEquippableVG_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCEquippableVG_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCEquippableVG(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCEquippableVG_setEquippingModel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCEquippableVG_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCEquippableVG_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCEquippableVG_getEquippingModel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCEquippableVG_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCEquippableVG_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCEquippableVG_CCEquippableVG(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCMarketItem_class;
extern JSObject *jsb_soomla_CCMarketItem_prototype;

bool js_soomla_CCMarketItem_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCMarketItem_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCMarketItem(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCMarketItem_getMarketTitle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_setMarketDescription(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_setMarketTitle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_getMarketDescription(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_setPrice(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_setMarketPrice(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_getMarketPrice(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_getProductId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_getConsumable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_setProductId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_getPrice(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_setConsumable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCMarketItem_CCMarketItem(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCNonConsumableItem_class;
extern JSObject *jsb_soomla_CCNonConsumableItem_prototype;

bool js_soomla_CCNonConsumableItem_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCNonConsumableItem_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCNonConsumableItem(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCNonConsumableItem_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCNonConsumableItem_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCNonConsumableItem_CCNonConsumableItem(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCPurchaseWithMarket_class;
extern JSObject *jsb_soomla_CCPurchaseWithMarket_prototype;

bool js_soomla_CCPurchaseWithMarket_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCPurchaseWithMarket_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCPurchaseWithMarket(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCPurchaseWithMarket_setMarketItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithMarket_getMarketItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithMarket_initWithMarketItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithMarket_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithMarket_createWithMarketItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithMarket_CCPurchaseWithMarket(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCPurchaseWithVirtualItem_class;
extern JSObject *jsb_soomla_CCPurchaseWithVirtualItem_prototype;

bool js_soomla_CCPurchaseWithVirtualItem_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCPurchaseWithVirtualItem_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCPurchaseWithVirtualItem(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCPurchaseWithVirtualItem_getItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithVirtualItem_getAmount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithVirtualItem_setItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithVirtualItem_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithVirtualItem_setAmount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithVirtualItem_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCPurchaseWithVirtualItem_CCPurchaseWithVirtualItem(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCSingleUsePackVG_class;
extern JSObject *jsb_soomla_CCSingleUsePackVG_prototype;

bool js_soomla_CCSingleUsePackVG_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCSingleUsePackVG_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCSingleUsePackVG(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCSingleUsePackVG_getGoodItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUsePackVG_getGoodAmount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUsePackVG_setGoodItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUsePackVG_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUsePackVG_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUsePackVG_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUsePackVG_setGoodAmount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUsePackVG_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUsePackVG_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUsePackVG_CCSingleUsePackVG(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCSingleUseVG_class;
extern JSObject *jsb_soomla_CCSingleUseVG_prototype;

bool js_soomla_CCSingleUseVG_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCSingleUseVG_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCSingleUseVG(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCSingleUseVG_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUseVG_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSingleUseVG_CCSingleUseVG(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCError_class;
extern JSObject *jsb_soomla_CCError_prototype;

bool js_soomla_CCError_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCError_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCError(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCError_getInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCError_createWithObject(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCSoomlaStore_class;
extern JSObject *jsb_soomla_CCSoomlaStore_prototype;

bool js_soomla_CCSoomlaStore_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCSoomlaStore_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCSoomlaStore(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCSoomlaStore_buyMarketItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaStore_stopIabServiceInBg(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaStore_refreshMarketItemsDetails(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaStore_restoreTransactions(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaStore_refreshInventory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaStore_startIabServiceInBg(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaStore_transactionsAlreadyRestored(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaStore_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCSoomlaStore_CCSoomlaStore(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCUpgradeVG_class;
extern JSObject *jsb_soomla_CCUpgradeVG_prototype;

bool js_soomla_CCUpgradeVG_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCUpgradeVG_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCUpgradeVG(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCUpgradeVG_getGoodItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_setNextItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_getNextItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_getPrevItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_setGoodItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_setPrevItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCUpgradeVG_CCUpgradeVG(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCVirtualCategory_class;
extern JSObject *jsb_soomla_CCVirtualCategory_prototype;

bool js_soomla_CCVirtualCategory_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCVirtualCategory_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCVirtualCategory(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCVirtualCategory_setName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCategory_setGoodItemIds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCategory_getName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCategory_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCategory_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCategory_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCategory_getGoodItemIds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCategory_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCategory_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCategory_CCVirtualCategory(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCStoreInfo_class;
extern JSObject *jsb_soomla_CCStoreInfo_prototype;

bool js_soomla_CCStoreInfo_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCStoreInfo_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCStoreInfo(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCStoreInfo_getVirtualCurrencyPacks(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_getUpgradesForVirtualGood(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_getNonConsumableItems(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_getVirtualCategories(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_getPurchasableItemWithProductId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_getItemByItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_getLastUpgradeForVirtualGood(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_getVirtualGoods(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_getCategoryForVirtualGood(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_getFirstUpgradeForVirtualGood(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_getVirtualCurrencies(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_saveItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_sharedStoreInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInfo_createShared(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCStoreInventory_class;
extern JSObject *jsb_soomla_CCStoreInventory_prototype;

bool js_soomla_CCStoreInventory_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCStoreInventory_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCStoreInventory(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCStoreInventory_upgradeGood(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_takeItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_nonConsumableItemExists(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_isVirtualGoodEquipped(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_unEquipVirtualGood(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_addNonConsumableItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_equipVirtualGood(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_buyItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_giveItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_getGoodCurrentUpgrade(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_removeNonConsumableItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_getItemBalance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_getGoodUpgradeLevel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_removeGoodUpgrades(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_sharedStoreInventory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreInventory_CCStoreInventory(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCVirtualCurrency_class;
extern JSObject *jsb_soomla_CCVirtualCurrency_prototype;

bool js_soomla_CCVirtualCurrency_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCVirtualCurrency_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCVirtualCurrency(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCVirtualCurrency_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrency_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrency_CCVirtualCurrency(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCVirtualCurrencyPack_class;
extern JSObject *jsb_soomla_CCVirtualCurrencyPack_prototype;

bool js_soomla_CCVirtualCurrencyPack_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCVirtualCurrencyPack_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCVirtualCurrencyPack(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCVirtualCurrencyPack_setCurrencyAmount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrencyPack_getCurrencyItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrencyPack_setCurrencyItemId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrencyPack_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrencyPack_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrencyPack_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrencyPack_getCurrencyAmount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrencyPack_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrencyPack_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCVirtualCurrencyPack_CCVirtualCurrencyPack(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCStoreService_class;
extern JSObject *jsb_soomla_CCStoreService_prototype;

bool js_soomla_CCStoreService_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCStoreService_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCStoreService(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCStoreService_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreService_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreService_initShared(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCStoreService_CCStoreService(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCReward_class;
extern JSObject *jsb_soomla_CCReward_prototype;

bool js_soomla_CCReward_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCReward_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCReward(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCReward_setName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCReward_getRepeatable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCReward_getName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCReward_getType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCReward_toDictionary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCReward_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCReward_setRepeatable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCReward_setRewardId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCReward_getRewardId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCReward_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCCoreService_class;
extern JSObject *jsb_soomla_CCCoreService_prototype;

bool js_soomla_CCCoreService_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCCoreService_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCCoreService(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCCoreService_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCCoreService_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCCoreService_initShared(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCCoreService_CCCoreService(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_CCServiceManager_class;
extern JSObject *jsb_soomla_CCServiceManager_prototype;

bool js_soomla_CCServiceManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_CCServiceManager_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_CCServiceManager(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_CCServiceManager_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCServiceManager_setCommonParams(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_CCServiceManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_JSBEventHandler_class;
extern JSObject *jsb_soomla_JSBEventHandler_prototype;

bool js_soomla_JSBEventHandler_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_JSBEventHandler_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_JSBEventHandler(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_JSBEventHandler_setGoodBalanceChangedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setGoodUnEquippedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setItemPurchaseStartedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setRestoreTransactionsStartedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setCurrencyBalanceChangedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setMarketItemsRefreshedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setStoreControllerInitializedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setGoodUpgradeHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setAndroidMarketRefundHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setItemPurchasedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setRestoreTransactionsFinishedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setMarketPurchaseVerificationHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setBillingSupportedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setBillingNotSupportedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setGoodEquippedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setAndroidIabServiceStartedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setMarketPurchaseStartedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setUnexpectedErrorInStoreHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setMarketPurchaseHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setMarketPurchaseCancelledHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setMarketItemsRefreshStartedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_setAndroidIabServiceStoppedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBEventHandler_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_soomla_JSBStoreAssets_class;
extern JSObject *jsb_soomla_JSBStoreAssets_prototype;

bool js_soomla_JSBStoreAssets_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_soomla_JSBStoreAssets_finalize(JSContext *cx, JSObject *obj);
void js_register_soomla_JSBStoreAssets(JSContext *cx, JSObject *global);
void register_all_soomla(JSContext* cx, JSObject* obj);
bool js_soomla_JSBStoreAssets_addGood(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBStoreAssets_addNonConsumableItem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBStoreAssets_addCurrency(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBStoreAssets_addCurrencyPack(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBStoreAssets_addCategory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBStoreAssets_setVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_soomla_JSBStoreAssets_JSBStoreAssets(JSContext *cx, uint32_t argc, jsval *vp);
#endif


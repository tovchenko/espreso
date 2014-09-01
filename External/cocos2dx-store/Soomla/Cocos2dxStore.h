#ifndef _Cocos2dxSoomla_H
#define _Cocos2dxSoomla_H

#include "domain/virtualGoods/CCEquippableVG.h"
#include "CCStoreAssets.h"
#include "domain/virtualGoods/CCLifetimeVG.h"
#include "domain/CCMarketItem.h"
#include "domain/CCNonConsumableItem.h"
#include "domain/CCPurchasableVirtualItem.h"
#include "PurchaseTypes/CCPurchaseType.h"
#include "PurchaseTypes/CCPurchaseWithMarket.h"
#include "PurchaseTypes/CCPurchaseWithVirtualItem.h"
#include "domain/virtualGoods/CCSingleUsePackVG.h"
#include "domain/virtualGoods/CCSingleUseVG.h"
#include "CCSoomlaStore.h"
#include "data/CCStoreInfo.h"
#include "CCStoreInventory.h"
#include "CCStoreUtils.h"
#include "domain/virtualGoods/CCUpgradeVG.h"
#include "domain/CCVirtualCategory.h"
#include "domain/virtualCurrencies/CCVirtualCurrency.h"
#include "domain/virtualCurrencies/CCVirtualCurrencyPack.h"
#include "domain/virtualGoods/CCVirtualGood.h"
#include "domain/CCVirtualItem.h"

#include "CCStoreEventDispatcher.h"
#include "CCStoreEventHandler.h"
#include "CCStoreService.h"


// ===== Cocos2dXCore =====================================
#include "../../soomla-cocos2dx-core/Soomla/CCError.h"
#include "../../soomla-cocos2dx-core/Soomla/rewards/CCReward.h"
#include "../../soomla-cocos2dx-core/Soomla/domain/CCDomain.h"
#include "../../soomla-cocos2dx-core/Soomla/domain/CCSoomlaEntity.h"
#include "../../soomla-cocos2dx-core/Soomla/CCCoreService.h"
#include "../../soomla-cocos2dx-core/Soomla/CCServiceManager.h"

// ===== JSB helpers ======================================
#include "JSBEventHandler.h"
#include "JSBStoreAssets.h"

#endif /* !_Cocos2dxSoomla_H */

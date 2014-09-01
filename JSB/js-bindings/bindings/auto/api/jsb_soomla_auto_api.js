/**
 * @module soomla
 */
var soomla = soomla || {};

/**
 * @class CCDomain
 */
soomla.Domain = {

/**
 * @method initWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {bool}
 */
initWithDictionary : function (
__dictionary 
)
{
    return false;
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

};

/**
 * @class CCSoomlaEntity
 */
soomla.SoomlaEntity = {

/**
 * @method setDescription
 * @param {cc.__String} arg0
 */
setDescription : function (
__string 
)
{
},

/**
 * @method setName
 * @param {cc.__String} arg0
 */
setName : function (
__string 
)
{
},

/**
 * @method getName
 * @return {cc.__String}
 */
getName : function (
)
{
    return cc.__String;
},

/**
 * @method getDescription
 * @return {cc.__String}
 */
getDescription : function (
)
{
    return cc.__String;
},

/**
 * @method getId
 * @return {cc.__String}
 */
getId : function (
)
{
    return cc.__String;
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

/**
 * @method init
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @return {bool}
 */
init : function (
__string, 
__string, 
__string 
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {bool}
 */
initWithDictionary : function (
__dictionary 
)
{
    return false;
},

/**
 * @method setId
 * @param {cc.__String} arg0
 */
setId : function (
__string 
)
{
},

/**
 * @method CCSoomlaEntity
 * @constructor
 */
CCSoomlaEntity : function (
)
{
},

};

/**
 * @class CCVirtualItem
 */
soomla.VirtualItem = {

/**
 * @method save
 */
save : function (
)
{
},

/**
 * @method getItemId
 * @return {cc.__String}
 */
getItemId : function (
)
{
    return cc.__String;
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @return {soomla::CCVirtualItem}
 */
create : function (
__string, 
__string, 
__string 
)
{
    return soomla::CCVirtualItem;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCVirtualItem}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCVirtualItem;
},

};

/**
 * @class CCPurchaseType
 */
soomla.PurchaseType = {

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method create
 * @return {soomla::CCPurchaseType}
 */
create : function (
)
{
    return soomla::CCPurchaseType;
},

/**
 * @method CCPurchaseType
 * @constructor
 */
CCPurchaseType : function (
)
{
},

};

/**
 * @class CCPurchasableVirtualItem
 */
soomla.PurchasableVirtualItem = {

/**
 * @method getPurchaseType
 * @return {soomla::CCPurchaseType}
 */
getPurchaseType : function (
)
{
    return soomla::CCPurchaseType;
},

/**
 * @method setPurchaseType
 * @param {soomla::CCPurchaseType} arg0
 */
setPurchaseType : function (
ccpurchasetype 
)
{
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

/**
 * @method init
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {soomla::CCPurchaseType} arg3
 * @return {bool}
 */
init : function (
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {bool}
 */
initWithDictionary : function (
__dictionary 
)
{
    return false;
},

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {soomla::CCPurchaseType} arg3
 * @return {soomla::CCPurchasableVirtualItem}
 */
create : function (
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return soomla::CCPurchasableVirtualItem;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCPurchasableVirtualItem}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCPurchasableVirtualItem;
},

/**
 * @method CCPurchasableVirtualItem
 * @constructor
 */
CCPurchasableVirtualItem : function (
)
{
},

};

/**
 * @class CCVirtualGood
 */
soomla.VirtualGood = {

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {soomla::CCPurchaseType} arg3
 * @return {soomla::CCVirtualGood}
 */
create : function (
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return soomla::CCVirtualGood;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCVirtualGood}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCVirtualGood;
},

};

/**
 * @class CCLifetimeVG
 */
soomla.LifetimeVG = {

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {soomla::CCPurchaseType} arg3
 * @return {soomla::CCLifetimeVG}
 */
create : function (
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return soomla::CCLifetimeVG;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCLifetimeVG}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCLifetimeVG;
},

};

/**
 * @class CCEquippableVG
 */
soomla.EquippableVG = {

/**
 * @method setEquippingModel
 * @param {cc.__Integer} arg0
 */
setEquippingModel : function (
__integer 
)
{
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

/**
 * @method init
 * @param {cc.__Integer} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {cc.__String} arg3
 * @param {soomla::CCPurchaseType} arg4
 * @return {bool}
 */
init : function (
__integer, 
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return false;
},

/**
 * @method getEquippingModel
 * @return {cc.__Integer}
 */
getEquippingModel : function (
)
{
    return cc.__Integer;
},

/**
 * @method create
 * @param {cc.__Integer} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {cc.__String} arg3
 * @param {soomla::CCPurchaseType} arg4
 * @return {soomla::CCEquippableVG}
 */
create : function (
__integer, 
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return soomla::CCEquippableVG;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCEquippableVG}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCEquippableVG;
},

/**
 * @method CCEquippableVG
 * @constructor
 */
CCEquippableVG : function (
)
{
},

};

/**
 * @class CCMarketItem
 */
soomla.MarketItem = {

/**
 * @method getMarketTitle
 * @return {cc.__String}
 */
getMarketTitle : function (
)
{
    return cc.__String;
},

/**
 * @method setMarketDescription
 * @param {cc.__String} arg0
 */
setMarketDescription : function (
__string 
)
{
},

/**
 * @method setMarketTitle
 * @param {cc.__String} arg0
 */
setMarketTitle : function (
__string 
)
{
},

/**
 * @method getMarketDescription
 * @return {cc.__String}
 */
getMarketDescription : function (
)
{
    return cc.__String;
},

/**
 * @method setPrice
 * @param {cc.__Double} arg0
 */
setPrice : function (
__double 
)
{
},

/**
 * @method setMarketPrice
 * @param {cc.__String} arg0
 */
setMarketPrice : function (
__string 
)
{
},

/**
 * @method getMarketPrice
 * @return {cc.__String}
 */
getMarketPrice : function (
)
{
    return cc.__String;
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

/**
 * @method init
 * @param {cc.__String} arg0
 * @param {cc.__Integer} arg1
 * @param {cc.__Double} arg2
 * @return {bool}
 */
init : function (
__string, 
__integer, 
__double 
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {bool}
 */
initWithDictionary : function (
__dictionary 
)
{
    return false;
},

/**
 * @method getProductId
 * @return {cc.__String}
 */
getProductId : function (
)
{
    return cc.__String;
},

/**
 * @method getConsumable
 * @return {cc.__Integer}
 */
getConsumable : function (
)
{
    return cc.__Integer;
},

/**
 * @method setProductId
 * @param {cc.__String} arg0
 */
setProductId : function (
__string 
)
{
},

/**
 * @method getPrice
 * @return {cc.__Double}
 */
getPrice : function (
)
{
    return cc.__Double;
},

/**
 * @method setConsumable
 * @param {cc.__Integer} arg0
 */
setConsumable : function (
__integer 
)
{
},

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__Integer} arg1
 * @param {cc.__Double} arg2
 * @return {soomla::CCMarketItem}
 */
create : function (
__string, 
__integer, 
__double 
)
{
    return soomla::CCMarketItem;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCMarketItem}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCMarketItem;
},

/**
 * @method CCMarketItem
 * @constructor
 */
CCMarketItem : function (
)
{
},

};

/**
 * @class CCNonConsumableItem
 */
soomla.NonConsumableItem = {

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {soomla::CCPurchaseType} arg3
 * @return {soomla::CCNonConsumableItem}
 */
create : function (
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return soomla::CCNonConsumableItem;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCNonConsumableItem}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCNonConsumableItem;
},

/**
 * @method CCNonConsumableItem
 * @constructor
 */
CCNonConsumableItem : function (
)
{
},

};

/**
 * @class CCPurchaseWithMarket
 */
soomla.PurchaseWithMarket = {

/**
 * @method setMarketItem
 * @param {soomla::CCMarketItem} arg0
 */
setMarketItem : function (
ccmarketitem 
)
{
},

/**
 * @method getMarketItem
 * @return {soomla::CCMarketItem}
 */
getMarketItem : function (
)
{
    return soomla::CCMarketItem;
},

/**
 * @method initWithMarketItem
 * @param {soomla::CCMarketItem} arg0
 * @return {bool}
 */
initWithMarketItem : function (
ccmarketitem 
)
{
    return false;
},

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__Double} arg1
 * @return {soomla::CCPurchaseWithMarket}
 */
create : function (
__string, 
__double 
)
{
    return soomla::CCPurchaseWithMarket;
},

/**
 * @method createWithMarketItem
 * @param {soomla::CCMarketItem} arg0
 * @return {soomla::CCPurchaseWithMarket}
 */
createWithMarketItem : function (
ccmarketitem 
)
{
    return soomla::CCPurchaseWithMarket;
},

/**
 * @method CCPurchaseWithMarket
 * @constructor
 */
CCPurchaseWithMarket : function (
)
{
},

};

/**
 * @class CCPurchaseWithVirtualItem
 */
soomla.PurchaseWithVirtualItem = {

/**
 * @method getItemId
 * @return {cc.__String}
 */
getItemId : function (
)
{
    return cc.__String;
},

/**
 * @method getAmount
 * @return {cc.__Integer}
 */
getAmount : function (
)
{
    return cc.__Integer;
},

/**
 * @method setItemId
 * @param {cc.__String} arg0
 */
setItemId : function (
__string 
)
{
},

/**
 * @method init
 * @param {cc.__String} arg0
 * @param {cc.__Integer} arg1
 * @return {bool}
 */
init : function (
__string, 
__integer 
)
{
    return false;
},

/**
 * @method setAmount
 * @param {cc.__Integer} arg0
 */
setAmount : function (
__integer 
)
{
},

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__Integer} arg1
 * @return {soomla::CCPurchaseWithVirtualItem}
 */
create : function (
__string, 
__integer 
)
{
    return soomla::CCPurchaseWithVirtualItem;
},

/**
 * @method CCPurchaseWithVirtualItem
 * @constructor
 */
CCPurchaseWithVirtualItem : function (
)
{
},

};

/**
 * @class CCSingleUsePackVG
 */
soomla.SingleUsePackVG = {

/**
 * @method getGoodItemId
 * @return {cc.__String}
 */
getGoodItemId : function (
)
{
    return cc.__String;
},

/**
 * @method getGoodAmount
 * @return {cc.__Integer}
 */
getGoodAmount : function (
)
{
    return cc.__Integer;
},

/**
 * @method setGoodItemId
 * @param {cc.__String} arg0
 */
setGoodItemId : function (
__string 
)
{
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

/**
 * @method init
 * @param {cc.__String} arg0
 * @param {cc.__Integer} arg1
 * @param {cc.__String} arg2
 * @param {cc.__String} arg3
 * @param {cc.__String} arg4
 * @param {soomla::CCPurchaseType} arg5
 * @return {bool}
 */
init : function (
__string, 
__integer, 
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {bool}
 */
initWithDictionary : function (
__dictionary 
)
{
    return false;
},

/**
 * @method setGoodAmount
 * @param {cc.__Integer} arg0
 */
setGoodAmount : function (
__integer 
)
{
},

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__Integer} arg1
 * @param {cc.__String} arg2
 * @param {cc.__String} arg3
 * @param {cc.__String} arg4
 * @param {soomla::CCPurchaseType} arg5
 * @return {soomla::CCSingleUsePackVG}
 */
create : function (
__string, 
__integer, 
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return soomla::CCSingleUsePackVG;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCSingleUsePackVG}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCSingleUsePackVG;
},

/**
 * @method CCSingleUsePackVG
 * @constructor
 */
CCSingleUsePackVG : function (
)
{
},

};

/**
 * @class CCSingleUseVG
 */
soomla.SingleUseVG = {

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {soomla::CCPurchaseType} arg3
 * @return {soomla::CCSingleUseVG}
 */
create : function (
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return soomla::CCSingleUseVG;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCSingleUseVG}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCSingleUseVG;
},

};

/**
 * @class CCError
 */
soomla.Error = {

/**
 * @method getInfo
 * @return {char}
 */
getInfo : function (
)
{
    return 0;
},

/**
 * @method createWithObject
 * @param {cc.Ref} arg0
 * @return {soomla::CCError}
 */
createWithObject : function (
ref 
)
{
    return soomla::CCError;
},

};

/**
 * @class CCSoomlaStore
 */
soomla.SoomlaStore = {

/**
 * @method buyMarketItem
 * @param {char} arg0
 * @param {char} arg1
 * @param {soomla::CCError} arg2
 */
buyMarketItem : function (
char, 
char, 
ccerror 
)
{
},

/**
 * @method stopIabServiceInBg
 */
stopIabServiceInBg : function (
)
{
},

/**
 * @method refreshMarketItemsDetails
 * @param {soomla::CCError} arg0
 */
refreshMarketItemsDetails : function (
ccerror 
)
{
},

/**
 * @method restoreTransactions
 */
restoreTransactions : function (
)
{
},

/**
 * @method refreshInventory
 */
refreshInventory : function (
)
{
},

/**
 * @method startIabServiceInBg
 */
startIabServiceInBg : function (
)
{
},

/**
 * @method transactionsAlreadyRestored
 * @return {bool}
 */
transactionsAlreadyRestored : function (
)
{
    return false;
},

/**
 * @method getInstance
 * @return {soomla::CCSoomlaStore}
 */
getInstance : function (
)
{
    return soomla::CCSoomlaStore;
},

/**
 * @method CCSoomlaStore
 * @constructor
 */
CCSoomlaStore : function (
)
{
},

};

/**
 * @class CCUpgradeVG
 */
soomla.UpgradeVG = {

/**
 * @method getGoodItemId
 * @return {cc.__String}
 */
getGoodItemId : function (
)
{
    return cc.__String;
},

/**
 * @method setNextItemId
 * @param {cc.__String} arg0
 */
setNextItemId : function (
__string 
)
{
},

/**
 * @method getNextItemId
 * @return {cc.__String}
 */
getNextItemId : function (
)
{
    return cc.__String;
},

/**
 * @method getPrevItemId
 * @return {cc.__String}
 */
getPrevItemId : function (
)
{
    return cc.__String;
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

/**
 * @method init
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {cc.__String} arg3
 * @param {cc.__String} arg4
 * @param {cc.__String} arg5
 * @param {soomla::CCPurchaseType} arg6
 * @return {bool}
 */
init : function (
__string, 
__string, 
__string, 
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {bool}
 */
initWithDictionary : function (
__dictionary 
)
{
    return false;
},

/**
 * @method setGoodItemId
 * @param {cc.__String} arg0
 */
setGoodItemId : function (
__string 
)
{
},

/**
 * @method setPrevItemId
 * @param {cc.__String} arg0
 */
setPrevItemId : function (
__string 
)
{
},

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {cc.__String} arg3
 * @param {cc.__String} arg4
 * @param {cc.__String} arg5
 * @param {soomla::CCPurchaseType} arg6
 * @return {soomla::CCUpgradeVG}
 */
create : function (
__string, 
__string, 
__string, 
__string, 
__string, 
__string, 
ccpurchasetype 
)
{
    return soomla::CCUpgradeVG;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCUpgradeVG}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCUpgradeVG;
},

/**
 * @method CCUpgradeVG
 * @constructor
 */
CCUpgradeVG : function (
)
{
},

};

/**
 * @class CCVirtualCategory
 */
soomla.VirtualCategory = {

/**
 * @method setName
 * @param {cc.__String} arg0
 */
setName : function (
__string 
)
{
},

/**
 * @method setGoodItemIds
 * @param {cc.__Array} arg0
 */
setGoodItemIds : function (
__array 
)
{
},

/**
 * @method getName
 * @return {cc.__String}
 */
getName : function (
)
{
    return cc.__String;
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

/**
 * @method init
 * @param {cc.__String} arg0
 * @param {cc.__Array} arg1
 * @return {bool}
 */
init : function (
__string, 
__array 
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {bool}
 */
initWithDictionary : function (
__dictionary 
)
{
    return false;
},

/**
 * @method getGoodItemIds
 * @return {cc.__Array}
 */
getGoodItemIds : function (
)
{
    return cc.__Array;
},

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__Array} arg1
 * @return {soomla::CCVirtualCategory}
 */
create : function (
__string, 
__array 
)
{
    return soomla::CCVirtualCategory;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCVirtualCategory}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCVirtualCategory;
},

/**
 * @method CCVirtualCategory
 * @constructor
 */
CCVirtualCategory : function (
)
{
},

};

/**
 * @class CCStoreInfo
 */
soomla.StoreInfo = {

/**
 * @method getVirtualCurrencyPacks
 * @return {cc.__Array}
 */
getVirtualCurrencyPacks : function (
)
{
    return cc.__Array;
},

/**
 * @method getUpgradesForVirtualGood
 * @param {char} arg0
 * @return {cc.__Array}
 */
getUpgradesForVirtualGood : function (
char 
)
{
    return cc.__Array;
},

/**
 * @method getNonConsumableItems
 * @return {cc.__Array}
 */
getNonConsumableItems : function (
)
{
    return cc.__Array;
},

/**
 * @method getVirtualCategories
 * @return {cc.__Array}
 */
getVirtualCategories : function (
)
{
    return cc.__Array;
},

/**
 * @method getPurchasableItemWithProductId
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 * @return {soomla::CCPurchasableVirtualItem}
 */
getPurchasableItemWithProductId : function (
char, 
ccerror 
)
{
    return soomla::CCPurchasableVirtualItem;
},

/**
 * @method getItemByItemId
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 * @return {soomla::CCVirtualItem}
 */
getItemByItemId : function (
char, 
ccerror 
)
{
    return soomla::CCVirtualItem;
},

/**
 * @method getLastUpgradeForVirtualGood
 * @param {char} arg0
 * @return {soomla::CCUpgradeVG}
 */
getLastUpgradeForVirtualGood : function (
char 
)
{
    return soomla::CCUpgradeVG;
},

/**
 * @method getVirtualGoods
 * @return {cc.__Array}
 */
getVirtualGoods : function (
)
{
    return cc.__Array;
},

/**
 * @method init
 * @param {soomla::CCStoreAssets} arg0
 * @return {bool}
 */
init : function (
ccstoreassets 
)
{
    return false;
},

/**
 * @method getCategoryForVirtualGood
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 * @return {soomla::CCVirtualCategory}
 */
getCategoryForVirtualGood : function (
char, 
ccerror 
)
{
    return soomla::CCVirtualCategory;
},

/**
 * @method getFirstUpgradeForVirtualGood
 * @param {char} arg0
 * @return {soomla::CCUpgradeVG}
 */
getFirstUpgradeForVirtualGood : function (
char 
)
{
    return soomla::CCUpgradeVG;
},

/**
 * @method getVirtualCurrencies
 * @return {cc.__Array}
 */
getVirtualCurrencies : function (
)
{
    return cc.__Array;
},

/**
 * @method saveItem
 * @param {soomla::CCVirtualItem} arg0
 */
saveItem : function (
ccvirtualitem 
)
{
},

/**
 * @method sharedStoreInfo
 * @return {soomla::CCStoreInfo}
 */
sharedStoreInfo : function (
)
{
    return soomla::CCStoreInfo;
},

/**
 * @method createShared
 * @param {soomla::CCStoreAssets} arg0
 */
createShared : function (
ccstoreassets 
)
{
},

};

/**
 * @class CCStoreInventory
 */
soomla.StoreInventory = {

/**
 * @method upgradeGood
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 */
upgradeGood : function (
char, 
ccerror 
)
{
},

/**
 * @method takeItem
 * @param {char} arg0
 * @param {int} arg1
 * @param {soomla::CCError} arg2
 */
takeItem : function (
char, 
int, 
ccerror 
)
{
},

/**
 * @method nonConsumableItemExists
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 * @return {bool}
 */
nonConsumableItemExists : function (
char, 
ccerror 
)
{
    return false;
},

/**
 * @method isVirtualGoodEquipped
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 * @return {bool}
 */
isVirtualGoodEquipped : function (
char, 
ccerror 
)
{
    return false;
},

/**
 * @method unEquipVirtualGood
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 */
unEquipVirtualGood : function (
char, 
ccerror 
)
{
},

/**
 * @method addNonConsumableItem
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 */
addNonConsumableItem : function (
char, 
ccerror 
)
{
},

/**
 * @method equipVirtualGood
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 */
equipVirtualGood : function (
char, 
ccerror 
)
{
},

/**
 * @method buyItem
* @param {char|char} char
* @param {char|soomla::CCError} char
* @param {soomla::CCError} ccerror
*/
buyItem : function(
char,
char,
ccerror 
)
{
},

/**
 * @method giveItem
 * @param {char} arg0
 * @param {int} arg1
 * @param {soomla::CCError} arg2
 */
giveItem : function (
char, 
int, 
ccerror 
)
{
},

/**
 * @method getGoodCurrentUpgrade
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 * @return {String}
 */
getGoodCurrentUpgrade : function (
char, 
ccerror 
)
{
    return ;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method removeNonConsumableItem
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 */
removeNonConsumableItem : function (
char, 
ccerror 
)
{
},

/**
 * @method getItemBalance
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 * @return {int}
 */
getItemBalance : function (
char, 
ccerror 
)
{
    return 0;
},

/**
 * @method getGoodUpgradeLevel
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 * @return {int}
 */
getGoodUpgradeLevel : function (
char, 
ccerror 
)
{
    return 0;
},

/**
 * @method removeGoodUpgrades
 * @param {char} arg0
 * @param {soomla::CCError} arg1
 */
removeGoodUpgrades : function (
char, 
ccerror 
)
{
},

/**
 * @method sharedStoreInventory
 * @return {soomla::CCStoreInventory}
 */
sharedStoreInventory : function (
)
{
    return soomla::CCStoreInventory;
},

/**
 * @method CCStoreInventory
 * @constructor
 */
CCStoreInventory : function (
)
{
},

};

/**
 * @class CCVirtualCurrency
 */
soomla.VirtualCurrency = {

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @return {soomla::CCVirtualCurrency}
 */
create : function (
__string, 
__string, 
__string 
)
{
    return soomla::CCVirtualCurrency;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCVirtualCurrency}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCVirtualCurrency;
},

/**
 * @method CCVirtualCurrency
 * @constructor
 */
CCVirtualCurrency : function (
)
{
},

};

/**
 * @class CCVirtualCurrencyPack
 */
soomla.VirtualCurrencyPack = {

/**
 * @method setCurrencyAmount
 * @param {cc.__Integer} arg0
 */
setCurrencyAmount : function (
__integer 
)
{
},

/**
 * @method getCurrencyItemId
 * @return {cc.__String}
 */
getCurrencyItemId : function (
)
{
    return cc.__String;
},

/**
 * @method setCurrencyItemId
 * @param {cc.__String} arg0
 */
setCurrencyItemId : function (
__string 
)
{
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

/**
 * @method init
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {cc.__Integer} arg3
 * @param {cc.__String} arg4
 * @param {soomla::CCPurchaseType} arg5
 * @return {bool}
 */
init : function (
__string, 
__string, 
__string, 
__integer, 
__string, 
ccpurchasetype 
)
{
    return false;
},

/**
 * @method initWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {bool}
 */
initWithDictionary : function (
__dictionary 
)
{
    return false;
},

/**
 * @method getCurrencyAmount
 * @return {cc.__Integer}
 */
getCurrencyAmount : function (
)
{
    return cc.__Integer;
},

/**
 * @method create
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__String} arg2
 * @param {cc.__Integer} arg3
 * @param {cc.__String} arg4
 * @param {soomla::CCPurchaseType} arg5
 * @return {soomla::CCVirtualCurrencyPack}
 */
create : function (
__string, 
__string, 
__string, 
__integer, 
__string, 
ccpurchasetype 
)
{
    return soomla::CCVirtualCurrencyPack;
},

/**
 * @method createWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {soomla::CCVirtualCurrencyPack}
 */
createWithDictionary : function (
__dictionary 
)
{
    return soomla::CCVirtualCurrencyPack;
},

/**
 * @method CCVirtualCurrencyPack
 * @constructor
 */
CCVirtualCurrencyPack : function (
)
{
},

};

/**
 * @class CCStoreService
 */
soomla.StoreService = {

/**
 * @method init
 * @param {soomla::CCStoreAssets} arg0
 * @param {cc.__Dictionary} arg1
 * @return {bool}
 */
init : function (
ccstoreassets, 
__dictionary 
)
{
    return false;
},

/**
 * @method getInstance
 * @return {soomla::CCStoreService}
 */
getInstance : function (
)
{
    return soomla::CCStoreService;
},

/**
 * @method initShared
 * @param {soomla::CCStoreAssets} arg0
 * @param {map_object} arg1
 */
initShared : function (
ccstoreassets, 
map 
)
{
},

/**
 * @method CCStoreService
 * @constructor
 */
CCStoreService : function (
)
{
},

};

/**
 * @class CCReward
 */
soomla.Reward = {

/**
 * @method setName
 * @param {cc.__String} arg0
 */
setName : function (
__string 
)
{
},

/**
 * @method getRepeatable
 * @return {cc.__Bool}
 */
getRepeatable : function (
)
{
    return cc.__Bool;
},

/**
 * @method getName
 * @return {cc.__String}
 */
getName : function (
)
{
    return cc.__String;
},

/**
 * @method getType
 * @return {char}
 */
getType : function (
)
{
    return 0;
},

/**
 * @method toDictionary
 * @return {cc.__Dictionary}
 */
toDictionary : function (
)
{
    return cc.__Dictionary;
},

/**
 * @method init
 * @param {cc.__String} arg0
 * @param {cc.__String} arg1
 * @param {cc.__Bool} arg2
 * @return {bool}
 */
init : function (
__string, 
__string, 
__bool 
)
{
    return false;
},

/**
 * @method setRepeatable
 * @param {cc.__Bool} arg0
 */
setRepeatable : function (
__bool 
)
{
},

/**
 * @method setRewardId
 * @param {cc.__String} arg0
 */
setRewardId : function (
__string 
)
{
},

/**
 * @method getRewardId
 * @return {cc.__String}
 */
getRewardId : function (
)
{
    return cc.__String;
},

/**
 * @method initWithDictionary
 * @param {cc.__Dictionary} arg0
 * @return {bool}
 */
initWithDictionary : function (
__dictionary 
)
{
    return false;
},

};

/**
 * @class CCCoreService
 */
soomla.CoreService = {

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method getInstance
 * @return {soomla::CCCoreService}
 */
getInstance : function (
)
{
    return soomla::CCCoreService;
},

/**
 * @method initShared
 */
initShared : function (
)
{
},

/**
 * @method CCCoreService
 * @constructor
 */
CCCoreService : function (
)
{
},

};

/**
 * @class CCServiceManager
 */
soomla.ServiceManager = {

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setCommonParams
 * @param {map_object} arg0
 */
setCommonParams : function (
map 
)
{
},

/**
 * @method getInstance
 * @return {soomla::CCServiceManager}
 */
getInstance : function (
)
{
    return soomla::CCServiceManager;
},

};

/**
 * @class JSBEventHandler
 */
soomla.EventHandler = {

/**
 * @method setGoodBalanceChangedHandler
 * @param {function} arg0
 */
setGoodBalanceChangedHandler : function (
func 
)
{
},

/**
 * @method setGoodUnEquippedHandler
 * @param {function} arg0
 */
setGoodUnEquippedHandler : function (
func 
)
{
},

/**
 * @method setItemPurchaseStartedHandler
 * @param {function} arg0
 */
setItemPurchaseStartedHandler : function (
func 
)
{
},

/**
 * @method setRestoreTransactionsStartedHandler
 * @param {function} arg0
 */
setRestoreTransactionsStartedHandler : function (
func 
)
{
},

/**
 * @method setCurrencyBalanceChangedHandler
 * @param {function} arg0
 */
setCurrencyBalanceChangedHandler : function (
func 
)
{
},

/**
 * @method setMarketItemsRefreshedHandler
 * @param {function} arg0
 */
setMarketItemsRefreshedHandler : function (
func 
)
{
},

/**
 * @method setStoreControllerInitializedHandler
 * @param {function} arg0
 */
setStoreControllerInitializedHandler : function (
func 
)
{
},

/**
 * @method setGoodUpgradeHandler
 * @param {function} arg0
 */
setGoodUpgradeHandler : function (
func 
)
{
},

/**
 * @method setAndroidMarketRefundHandler
 * @param {function} arg0
 */
setAndroidMarketRefundHandler : function (
func 
)
{
},

/**
 * @method setItemPurchasedHandler
 * @param {function} arg0
 */
setItemPurchasedHandler : function (
func 
)
{
},

/**
 * @method setRestoreTransactionsFinishedHandler
 * @param {function} arg0
 */
setRestoreTransactionsFinishedHandler : function (
func 
)
{
},

/**
 * @method setMarketPurchaseVerificationHandler
 * @param {function} arg0
 */
setMarketPurchaseVerificationHandler : function (
func 
)
{
},

/**
 * @method setBillingSupportedHandler
 * @param {function} arg0
 */
setBillingSupportedHandler : function (
func 
)
{
},

/**
 * @method setBillingNotSupportedHandler
 * @param {function} arg0
 */
setBillingNotSupportedHandler : function (
func 
)
{
},

/**
 * @method setGoodEquippedHandler
 * @param {function} arg0
 */
setGoodEquippedHandler : function (
func 
)
{
},

/**
 * @method setAndroidIabServiceStartedHandler
 * @param {function} arg0
 */
setAndroidIabServiceStartedHandler : function (
func 
)
{
},

/**
 * @method setMarketPurchaseStartedHandler
 * @param {function} arg0
 */
setMarketPurchaseStartedHandler : function (
func 
)
{
},

/**
 * @method setUnexpectedErrorInStoreHandler
 * @param {function} arg0
 */
setUnexpectedErrorInStoreHandler : function (
func 
)
{
},

/**
 * @method setMarketPurchaseHandler
 * @param {function} arg0
 */
setMarketPurchaseHandler : function (
func 
)
{
},

/**
 * @method setMarketPurchaseCancelledHandler
 * @param {function} arg0
 */
setMarketPurchaseCancelledHandler : function (
func 
)
{
},

/**
 * @method setMarketItemsRefreshStartedHandler
 * @param {function} arg0
 */
setMarketItemsRefreshStartedHandler : function (
func 
)
{
},

/**
 * @method setAndroidIabServiceStoppedHandler
 * @param {function} arg0
 */
setAndroidIabServiceStoppedHandler : function (
func 
)
{
},

/**
 * @method getInstance
 * @return {soomla::JSBEventHandler}
 */
getInstance : function (
)
{
    return soomla::JSBEventHandler;
},

};

/**
 * @class JSBStoreAssets
 */
soomla.StoreAssets = {

/**
 * @method getNonConsumableItems
 * @return {cc.__Array}
 */
getNonConsumableItems : function (
)
{
    return cc.__Array;
},

/**
 * @method getCurrencyPacks
 * @return {cc.__Array}
 */
getCurrencyPacks : function (
)
{
    return cc.__Array;
},

/**
 * @method getCategories
 * @return {cc.__Array}
 */
getCategories : function (
)
{
    return cc.__Array;
},

/**
 * @method getCurrencies
 * @return {cc.__Array}
 */
getCurrencies : function (
)
{
    return cc.__Array;
},

/**
 * @method getVersion
 * @return {int}
 */
getVersion : function (
)
{
    return 0;
},

/**
 * @method getGoods
 * @return {cc.__Array}
 */
getGoods : function (
)
{
    return cc.__Array;
},

/**
 * @method JSBStoreAssets
 * @constructor
 * @param {map_object} arg0
 */
JSBStoreAssets : function (
map 
)
{
},

};

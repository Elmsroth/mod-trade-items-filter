

#ifndef MODTRADEITEMSFILTER_H_SPDRMGR
#define MODTRADEITEMSFILTER_H_SPDRMGR

#include "Common.h"
#include "Item.h"
#include <unordered_set>

enum ModTradeItemsFilterAcoreStrings {
    LANG_MOD_TRADE_ITEMS_FILTER_START = 35410,
    LANG_INITIATOR_TRADE_TRANSACTION_CANCELED = LANG_MOD_TRADE_ITEMS_FILTER_START + 0,
    LANG_TARGET_TRADE_TRANSACTION_CANCELED = LANG_MOD_TRADE_ITEMS_FILTER_START + 1,
    LANG_GM_ACCOUNT_SEC_TOO_LOW_TO_BYPASS_TRADE_ITEMS_RESTRICTIONS = LANG_MOD_TRADE_ITEMS_FILTER_START + 2,
    LANG_CANNOT_SEND_THIS_ITEM_BY_MAIL = LANG_MOD_TRADE_ITEMS_FILTER_START + 3
};

std::string GetLocalizedItemName(Item* item, int loc_idx);

class ModTradeItemsFilterMgr
{
public:
    static ModTradeItemsFilterMgr* instance();
    void Initialize();
    bool IsEnabled() const { return m_moduleEnabled; };
    uint8 GetMinAccountSecurityLevelToByPassForbiddenItems() const { return m_minAccountSecurityLevelToByPassForbiddenItems; };
    bool IsForbidden(uint32 itemID);

private:
    ModTradeItemsFilterMgr();
    ~ModTradeItemsFilterMgr();

    // Configuration options
    bool m_moduleEnabled;
    std::unordered_set<uint32> m_forbiddenItemIDs;
    uint8 m_minAccountSecurityLevelToByPassForbiddenItems;
};

#define sModTradeItemsFilterMgr ModTradeItemsFilterMgr::instance()

#endif

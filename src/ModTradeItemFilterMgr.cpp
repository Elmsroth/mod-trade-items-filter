#include "Log.h"
#include "Tokenize.h"
#include "StringConvert.h"
#include "Config.h"
#include "ObjectMgr.h"
#include "ModTradeItemFilterMgr.h"

ModTradeItemsFilterMgr::ModTradeItemsFilterMgr() : m_moduleEnabled(true), m_forbiddenItemIDs({}),
    m_minAccountSecurityLevelToByPassForbiddenItems(1)
{}

ModTradeItemsFilterMgr::~ModTradeItemsFilterMgr()
{}

void ModTradeItemsFilterMgr::Initialize()
{
    LOG_INFO("server.loading", " ");

    LOG_INFO("server.loading", "Load module config 'mod-trade-items-filter'...");
    // Load the config from config file
 
    // Determine wether the ùmodule is active or not
    m_moduleEnabled = sConfigMgr->GetOption<bool>("ModTradeItemsFilter.Common.ModuleEnabled", true);
    LOG_INFO("server.loading", ">> Module enabled : {}", m_moduleEnabled);

    // Set MinAccountSecurityLevelToByPassForbiddenItems
    m_minAccountSecurityLevelToByPassForbiddenItems = sConfigMgr->GetOption<uint8>("ModTradeItemsFilter.GameMasters.MinAccountSecurityLevelToByPassForbiddenItems", 1);
    LOG_INFO("server.loading", ">> MinAccountSecurityLevelToByPassForbiddenItems : {}", m_minAccountSecurityLevelToByPassForbiddenItems);

    // Load all forbidden item ids
    std::string forbiddenItemIDsConfigString = sConfigMgr->GetOption<std::string>("ModTradeItemsFilter.Common.ForbiddenItemsIDs", "");
    if (forbiddenItemIDsConfigString == "")
    {
        LOG_WARN("server.loading", ">> Loaded 0 forbidden item IDs !");
    }
    else
    {
        std::vector<std::string_view> forbiddenItemIDsAsString = Acore::Tokenize(forbiddenItemIDsConfigString, ',', false);

        for (auto& itr : forbiddenItemIDsAsString)
        {
            uint32 itemID = Acore::StringTo<uint32>(itr).value();
            m_forbiddenItemIDs.insert(itemID);
            LOG_INFO("server.loading", ">> Fobidden item ID : {}", itemID);

        }
    }

    LOG_INFO("server.loading", ">> Module initialization done.");
    LOG_INFO("server.loading", " ");

}

bool ModTradeItemsFilterMgr::IsForbidden(uint32 itemID)
{
    if (m_forbiddenItemIDs.find(itemID) != m_forbiddenItemIDs.end())
        return true;
    else
        return false;
}

ModTradeItemsFilterMgr* ModTradeItemsFilterMgr::instance()
{
    static ModTradeItemsFilterMgr instance;
    return &instance;
}

std::string GetLocalizedItemName(Item* item, int loc_idx)
{
    {
        uint32 itemId = item->GetEntry();
        ItemTemplate const* pProto = sObjectMgr->GetItemTemplate(itemId);
        std::string itemNameLocalized = pProto->Name1; // Default english name
        const ItemLocale* itemLocale = sObjectMgr->GetItemLocale(itemId);
        if (loc_idx >= 0)
        {
            if (ItemLocale const* il = sObjectMgr->GetItemLocale(pProto->ItemId))
            {
                ObjectMgr::GetLocaleString(il->Name, loc_idx, itemNameLocalized);
            }
        }
        return itemNameLocalized;
    };
}

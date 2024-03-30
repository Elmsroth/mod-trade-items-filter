/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "ModTradeItemFilterMgr.h"

// World script to handle singleton initialization
class ModTradeItemsFilterWorldScript : public WorldScript
{
public:
    ModTradeItemsFilterWorldScript() : WorldScript("ModTradeItemsFilterWorldScript") { }

    void OnBeforeWorldInitialized() override
    {
        // Do ModTradeItemFilterMgr singleton initialization
        sModTradeItemsFilterMgr->Initialize();
    }
};

// Player Script to handle trade event to filter
class ModTradeItemsFilterPlayerScript : public PlayerScript
{
public:
    ModTradeItemsFilterPlayerScript() : PlayerScript("ModTradeItemsFilterPlayerScript") { }

    bool CanSetTradeItem(Player* player, Item* tradedItem, uint8 tradeSlot) override
    {
        // If item is set in TRADE_SLOT_NONTRADED then the trade is allowed
        if (tradeSlot != TRADE_SLOT_NONTRADED
            && sModTradeItemsFilterMgr->IsEnabled()
            && sModTradeItemsFilterMgr->IsForbidden(tradedItem->GetEntry())
            && sModTradeItemsFilterMgr->GetMinAccountSecurityLevelToByPassForbiddenItems() > player->GetSession()->GetSecurity()
            )
        {
            // Notify the players the trade cannot be done due to forbidden item ID restriction
            Player* playerTradeInitiator = player;
            Player* playerTradeTarget = player->GetTrader();

            // Send message to trade initiator
            int tradeInitiatorDbLocaleIndex = playerTradeInitiator->GetSession()->GetSessionDbLocaleIndex();
            std::string tradeInitiatorItemName = GetLocalizedItemName(tradedItem, tradeInitiatorDbLocaleIndex);

            ChatHandler(playerTradeInitiator->GetSession()).PSendSysMessage(LANG_INITIATOR_TRADE_TRANSACTION_CANCELED,
                tradedItem->GetEntry(), tradeInitiatorItemName.c_str(), tradedItem->GetEntry(),
                ChatHandler(playerTradeInitiator->GetSession()).GetNameLink(playerTradeTarget).c_str());

            // Add specific message for low sec GM accounts that cannot bypass
            if (player->GetSession()->GetSecurity() > 0 && player->GetSession()->GetSecurity() < sModTradeItemsFilterMgr->GetMinAccountSecurityLevelToByPassForbiddenItems())
            {
                ChatHandler(playerTradeInitiator->GetSession()).PSendSysMessage(LANG_GM_ACCOUNT_SEC_TOO_LOW_TO_BYPASS_TRADE_ITEMS_RESTRICTIONS,
                    sModTradeItemsFilterMgr->GetMinAccountSecurityLevelToByPassForbiddenItems());
            }

            // Send message to trade target (perhaps the player has anotehr db locale because multi-lang realm)
            int tradeTargeDbLocaleIndex = playerTradeTarget->GetSession()->GetSessionDbLocaleIndex();
            std::string tradeTargetItemName = GetLocalizedItemName(tradedItem, tradeTargeDbLocaleIndex);

            ChatHandler(playerTradeTarget->GetSession()).PSendSysMessage(LANG_TARGET_TRADE_TRANSACTION_CANCELED,
                ChatHandler(playerTradeTarget->GetSession()).GetNameLink(playerTradeInitiator).c_str(),
                tradedItem->GetEntry(), tradeTargetItemName.c_str(), tradedItem->GetEntry());

            return false;
        }
        else return true;
    }

    bool CanSendMail(Player* player, ObjectGuid /*receiverGuid*/, ObjectGuid /*mailbox*/, std::string& /*subject*/,
        std::string& /*body*/, uint32 /*money*/, uint32 /*COD*/, Item* item) override
    {
        if (sModTradeItemsFilterMgr->IsEnabled()
            && sModTradeItemsFilterMgr->IsForbidden(item->GetEntry()))
        {
            int dbLocaleIndex = player->GetSession()->GetSessionDbLocaleIndex();
            std::string itemName = GetLocalizedItemName(item, dbLocaleIndex);
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_CANNOT_SEND_THIS_ITEM_BY_MAIL, item->GetEntry(), itemName, item->GetEntry());
            return false;
        }
        return true;
    }
};

// Filtering items in mail sending

// Filtering items in auction house

// Command script for reloading

// Add all scripts in one
void AddModTradeItemsFilterScripts()
{
    new ModTradeItemsFilterWorldScript();
    new ModTradeItemsFilterPlayerScript();
}

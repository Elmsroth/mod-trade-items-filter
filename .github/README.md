<!-- Cartouche header for module  -->
<div style="display:flex;flex-direction:row;gap:20px;">
<img src="https://avatars.githubusercontent.com/u/20147732?s=200&v=4" width="100" style="border-radius:12px;" />
<div>
    <h1 style="border-bottom:none;margin-bottom:0;padding-bottom:5px;font-size:24px;font-weight:normal;">AzerothCore : mod-trade-items-filter </h1>
    <span style="color:rgb(99, 108, 118);">
    Custom module for AzerothCore allowinf filtering in game items exchanges
    </span>
</div>
</div>

<hr>

## 🎈 What does this module do ?

This modules allows you to filter in game item exchanges by setting a "no-trade" items list.

Filtering is applied for :

- In game "trade " (using /trade player command) ;
- Items in mails attachments ;

🚧 Soon this module will also filter items in auctions.

## ⚙️ Available options

See [mod-trade-items-filter.conf.dist](../conf/mod-trade-items-filter.conf.dist) for customizable options.

**⚠️ REMINDER** : Make a copy and rename the file in `mod-trade-items-filter.conf` before making your modifications and running the server.

## 🚩 Involved hooks

This modules uses the following hooks in ScriptMgr:

- `CanSetTradeItem` (in [PlayerScript.h](https://github.com/azerothcore/azerothcore-wotlk/blob/master/src/server/game/Scripting/ScriptDefines/PlayerScript.h#L432))
- `CanSendMail` (in [PlayerScript.h](https://github.com/azerothcore/azerothcore-wotlk/blob/master/src/server/game/Scripting/ScriptDefines/PlayerScript.h#L312))

## 💻 In-Game Screenshots

### Mail items filtering preview
<a href="../pics/filter_mail_item.png">
<img src="../pics/filter_mail_item.png" width="600" />
</a>

### Trade items filtering preview

From a GM who have a low security level and who cannot bypass the `ModTradeItemsFilter.GameMasters.MinAccountSecurityLevelToByPassForbiddenItems` restriction :

<a href="../pics/filter_trade_gm_item.png">
<img src="../pics/filter_trade_gm_item.png" width="600" />
</a>

From a player point of view :

<a href="../pics/filter_trade_player_item.png">
<img src="../pics/filter_trade_player_item.png" width="600" />
</a>


## Licensing

MIT License

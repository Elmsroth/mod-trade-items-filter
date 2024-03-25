# mod-trade-items-filter AzerothCore Custom Module

This modules allow you to filter items in game that are allowed to be traded and sent by mail.

See [config file](../conf/mod-trade-items-filter.conf.dist) for customizable options.

This modules uses `CanSetTradeItem` & `CanSendMail` hooks.


## Mail items filtering preview
<a href="../pics/filter_mail_item.png">
<img src="../pics/filter_mail_item.png" width="600" />
</a>

## Trade items filtering preview

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

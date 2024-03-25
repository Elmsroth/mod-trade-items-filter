
-- Strings that are used in the `acore_string` table for the mod-trade-items-filter custom module
-- /!\ WARNING : You should consider changing the entries if they collide with another custom module.
-- If changed, it must also be done in the .cpp file in order to reflect the modification
SET @ENTRY_START:=35410;
DELETE FROM `acore_string` WHERE `entry` IN(
@ENTRY_START +0,
@ENTRY_START +1,
@ENTRY_START +2,
@ENTRY_START +3

);

INSERT INTO `acore_string` (`entry`, `content_default`, `locale_frFR`) VALUES
(@ENTRY_START + 0, 'The transaction has been canceled because you are trying to trade item |cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]|h|r (ID : %d) with %s but it is forbidden in game trading.', 
'La transaction a été annulée car vous essayez d\'échanger l\'item  |cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]|h|r (ID : %d) avec %s mais il est interdit dans les échanges en jeu.')
, (@ENTRY_START + 1, 'The transaction has been canceled because %s is trying to trade item |cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]|h|r (ID : %d) with you but it is forbidden in game trading.', 
'La transaction a été annulée car %s essaye d\'échanger l\'item  |cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]|h|r (ID : %d) avec vous mais il est interdit dans les échanges en jeu.')
, (@ENTRY_START + 2, 'In order to bypass the trade restriction your GM account security level should be at least %d',
 'Afin de pouvoir bypasser les rectriction d\'échange d\'objet vous devez avoir un compte MJ avec un de niveau de sécurité minimum de %d.')
, (@ENTRY_START + 3, 'You cannot sent the item by mail |cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]|h|r (ID : %d) because it is forbidden in game mail.', 
'Vous ne pouvez-pas envoyer l\'objet |cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]|h|r (ID : %d)car il est interdit dans les mails en jeu.')
;

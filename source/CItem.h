#ifndef __CITEM_H__
#define __CITEM_H__

#include "CItemCache.h"

#define MAX_ITEMS			61

enum ItemType
{
	ITEM_NONE,
	ITEM_A_HOT_WATER_BOTTLE,
	ITEM_BLANK_BULLETS,
	ITEM_A_CANDLESTICK,
	ITEM_THE_WILL,					// Clue #1
	ITEM_A_KNIFE,					// Clue #8
	ITEM_NEWSPAPER_CUTTING,
	ITEM_A_NOTE,					// Clue #4
	ITEM_A_SMALL_BOTTLE,			// Clue #6
	ITEM_A_CRAVATE,					// Clue #3
	ITEM_A_SOGGY_ENVELOPE,
	ITEM_A_LETTER,
	ITEM_SCALPELS,
	ITEM_A_SYRINGE,					// Clue #9
	ITEM_A_BOTTLE_OF_PILLS,
	ITEM_A_HAMMER,
	ITEM_A_BUNCH_OF_KEYS,
	ITEM_A_BIG_IRON_KEY,
	ITEM_A_SILVER_TRAY,
	ITEM_A_BOTTLE_OF_WINE,
	ITEM_A_COMB,
	ITEM_A_HARDBACK_BOOK,
	ITEM_A_FOLDED_DOCUMENT,			// Clue #2
	ITEM_AN_ELEPHANT_GUN,
	ITEM_A_DIARY,
	ITEM_A_BLACK_BAG,
	ITEM_COLOGNE,
	ITEM_A_SMALL_BOOK,
	ITEM_DIRTY_PLATES,
	ITEM_A_PICTURE,
	ITEM_A_WAD_OF_NOTES,			// Clue #5
	ITEM_A_LOCKET,
	ITEM_A_SCREWDRIVER,
	ITEM_AN_OPEN_LOCKET,			// Clue #10
	ITEM_BROKEN_PLATES,
	ITEM_BROKEN_GLASS,
	ITEM_SHREDDED_PAPER,
	ITEM_BOOKS1,
	ITEM_BOOKS2,
	ITEM_A_LETTER_OPENER,
	ITEM_A_JACKET,
	ITEM_NOTEBOOKS,
	ITEM_PLANS,
	ITEM_A_MIRROR,
	ITEM_CUTLERY,
	ITEM_A_PIECE_OF_CARD,
	ITEM_A_BRIEFCASE,
	ITEM_A_FOLDER,
	ITEM_A_PAPERWEIGHT,
	ITEM_PADDED_ENVELOPES,
	ITEM_A_BOMB,					// Clue #7
	ITEM_A_SMALL_KEY,
	ITEM_BULLETS,
	ITEM_A_SWORD,
	ITEM_A_BALL_ON_CHAIN,
	ITEM_AN_HOURGLASS,
	ITEM_A_GOLDEN_SKULL,
	ITEM_A_RED_KEY,
	ITEM_A_VACUUM_CLEANER,
	ITEM_WASHING_POWDER,
	ITEM_A_DIRTY_SHIRT,
	ITEM_ANGUS_MCFUNGUS
};

enum ItemAttributes
{
	ITEMATTRIB_NONE = 0,
	ITEMATTRIB_EVIDENCE = BIT(0),
	ITEMATTRIB_OPEN = BIT(1),
	ITEMATTRIB_SHOOT = BIT(2),
	ITEMATTRIB_USE_KEY = BIT(3),
	ITEMATTRIB_READ = BIT(4),
	ITEMATTRIB_CONSUME = BIT(5)
};

enum UseType
{
	USETYPE_OPEN,
	USETYPE_BREAK,
	USETYPE_CUT,
	USETYPE_EXAMINE
};

typedef struct
{
	UseType ItemUse;
	CItem* ItemSrc;
	CItem* ItemDst;
} USEITEM, *PUSEITEM;

class CItem
{
public:
	CItem(ItemType itemType, int itemAttribs);
	CItem(ItemType itemType, int itemAttribs, int itemCount);
	~CItem();
	
	void AddItems(CItem* item1, CItem* item2, CItem* item3, CItem* item4, CItem* item5) { m_itemCache->AddItems(item1, item2, item3, item4, item5); }
	void ClearItems() { m_itemCache->ClearItems(); }
	CItemCache* GetItemCache() const { return m_itemCache; }
	
	ItemType GetItemType() const { return m_itemType; }
	int GetItemAttribs() const { return m_itemAttribs; }
	
	void SetParent(CItemCache* pItemCache) { m_parent = pItemCache; }
	CItemCache* GetParent() const { return m_parent; }
	
	void SetKeyItemType(ItemType keyItemType) { m_keyItemType = keyItemType; }
	
	void SetLocked(bool locked) { m_locked = locked; }
	bool GetLocked() const { return m_locked; }
	
private:
	ItemType m_itemType;
	int m_itemAttribs;
	
	CItemCache* m_parent;
	CItemCache* m_itemCache;
	
	bool m_locked;
	
	ItemType m_keyItemType;
};

#endif

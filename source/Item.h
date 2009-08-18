#ifndef __CITEM_H__
#define __CITEM_H__

#include "TDG.h"

#define MAX_ITEMS				32

enum ItemType
{
	ITEM_SEALED_ENVELOPE,
	ITEM_PICTURE,
	ITEM_WILL,				// Clue #1
	ITEM_BOOK,
	ITEM_FOLDED_DOCUMENT,	// Clue #2
	ITEM_CRAVATE,			// Clue #3
	ITEM_SMALL_KEY,
	ITEM_BRIEFCASE,
	ITEM_NOTE,				// Clue #4
	ITEM_BLACK_BAG,
	ITEM_WAD_OF_NOTES,		// Clue #5
	ITEM_SMALL_BOTTLE,		// Clue #6
	ITEM_BOMB,				// Clue #7
	ITEM_KNIFE,				// Clue #8
	ITEM_SYRINGE,			// Clue #9
	ITEM_LOCKET,
	ITEM_SCREWDRIVER,
	ITEM_OPEN_LOCKET,		// Clue #10
	ITEM_BLANK_BULLETS,
	ITEM_BULLETS,
	ITEM_ELEPHANT_GUN,
	ITEM_BENTLEYS_JACKET,
	ITEM_KEYS
};

class CItem
{
public:
	CItem(ItemType itemType);
	~CItem();
	
	void ClearItems();
	bool AddItem(CItem* pItem);
	bool RemoveItem(CItem* pItem);

private:
	ItemType m_itemType;
	CItem* m_itemArray[MAX_ITEMS];
};

#endif

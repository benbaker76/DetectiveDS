#include <nds.h>
#include "CItem.h"
#include "CItemCache.h"

CItem::CItem(ItemType itemType, int itemAttribs)
{
	m_itemType = itemType;
	m_itemAttribs = itemAttribs;
	m_parent = NULL;
	m_itemCache = NULL;
	m_keyItemType = ITEM_NONE;
	m_locked = false;
	
	if(itemAttribs & ITEMATTRIB_OPEN)
		m_itemCache = new CItemCache(ITEMLOCATION_ITEM, this);
}

CItem::CItem(ItemType itemType, int itemAttribs, int itemCount)
{
	m_itemType = itemType;
	m_itemAttribs = itemAttribs;
	m_parent = NULL;
	m_itemCache = NULL;
	m_keyItemType = ITEM_NONE;
	m_locked = false;
	
	if(itemAttribs & ITEMATTRIB_OPEN)
		m_itemCache = new CItemCache(ITEMLOCATION_ITEM, itemCount, this);
}

CItem::~CItem()
{
}

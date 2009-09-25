#include <nds.h>
#include "CItem.h"
#include "CItemCache.h"

CItem::CItem(ItemType itemType, int itemAttribs)
{
	m_itemType = itemType;
	m_itemAttribs = itemAttribs;
	m_parent = NULL;
	m_itemCache = NULL;
}

CItem::~CItem()
{
}

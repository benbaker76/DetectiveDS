#include <nds.h>
#include "CItem.h"
#include "CItemCache.h"

CItem::CItem(ItemType itemType, ItemAttributes itemAttribs, ItemActions itemActions)
{
	m_itemType = itemType;
	m_itemAttribs = itemAttribs;
	m_itemActions = itemActions;
}

CItem::~CItem()
{
}

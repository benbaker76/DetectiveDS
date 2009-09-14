#include <nds.h>
#include "CItem.h"

CItem::CItem(ItemType itemType, bool evidence)
{
	m_itemType = itemType;
	m_evidence = evidence;
}

CItem::~CItem()
{
}

#include <nds.h>
#include "CItem.h"

CItem::CItem(ItemType itemType)
{
	m_itemType = itemType;
	ClearItems();
}

CItem::~CItem()
{
}

void CItem::ClearItems()
{
	for(int i=0; i<MAX_ITEMS; i++)
		m_itemArray[i] = NULL;
}

bool CItem::AddItem(CItem* pItem)
{
	bool retVal = false;
	
	for(int i=0; i<MAX_ITEMS; i++)
	{
		if(m_itemArray[i] == NULL)
		{
			m_itemArray[i] = pItem;
			retVal = true;
			break;
		}
	}
	
	return retVal;
}
	
bool CItem::RemoveItem(CItem* pItem)
{
	bool retVal = false;
	
	for(int i=0; i<MAX_ITEMS; i++)
	{
		if(m_itemArray[i] == pItem)
		{
			m_itemArray[i] = NULL;
			retVal = true;
			break;
		}
	}
	
	return retVal;
}

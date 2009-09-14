#include "CItemManager.h"
#include "CItem.h"

CItemManager::CItemManager()
{
	ClearItems();
}

CItemManager::~CItemManager()
{
}

void CItemManager::ClearItems()
{
	for(int i=0; i<ITEM_CAPACITY; i++)
		m_itemArray[i] = NULL;
}

bool CItemManager::AddItem(CItem* pItem)
{
	bool retVal = false;
	
	for(int i=0; i<ITEM_CAPACITY; i++)
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
	
bool CItemManager::RemoveItem(CItem* pItem)
{
	bool retVal = false;
	
	for(int i=0; i<ITEM_CAPACITY; i++)
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

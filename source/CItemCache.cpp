#include "CItemCache.h"

CItemCache::CItemCache()
{
	m_itemCache = ITEMCACHE_NONE;
}

CItemCache::CItemCache(ItemCache itemCache)
{
	m_itemCache = itemCache;
	
	for(int i=0; i<MAX_ITEM_ARRAY; i++)
		m_itemArray[i] = NULL;
}

CItemCache::CItemCache(CItem* itemArray[])
{
	m_itemCache = ITEMCACHE_NONE;
	
	for(int i=0; i<MAX_ITEM_ARRAY; i++)
		m_itemArray[i] = itemArray[i];
}

CItemCache::CItemCache(ItemCache itemCache, CItem* itemArray[])
{
	m_itemCache = itemCache;
	
	for(int i=0; i<MAX_ITEM_ARRAY; i++)
		m_itemArray[i] = itemArray[i];
}

CItemCache::~CItemCache()
{
}

void CItemCache::ClearItems()
{
	for(int i=0; i<MAX_ITEM_ARRAY; i++)
		m_itemArray[i] = NULL;
}

bool CItemCache::AddItem(CItem* pItem)
{
	bool retVal = false;
	
	for(int i=0; i<MAX_ITEM_ARRAY; i++)
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
	
bool CItemCache::RemoveItem(CItem* pItem)
{
	bool retVal = false;
	
	for(int i=0; i<MAX_ITEM_ARRAY; i++)
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

#include <stdio.h>
#include "CItem.h"
#include "CItemCache.h"
#include "CSave.h"

CItemCache::CItemCache(ItemLocation itemLocation, void* pParent)
{
	m_itemLocation = itemLocation;
	m_pParent = pParent;
	m_colType = COL_NOTHING_HERE;
	m_itemCount = 5;
	
	ClearItems();
}

CItemCache::CItemCache(ItemLocation itemLocation, int itemCount, void* pParent)
{
	m_itemLocation = itemLocation;
	m_itemCount = itemCount;
	m_pParent = pParent;
	m_colType = COL_NOTHING_HERE;
	
	ClearItems();
}

CItemCache::CItemCache(ItemLocation itemLocation, CollisionType colType, void* pParent)
{
	m_itemLocation = itemLocation;
	m_colType = colType;
	m_pParent = pParent;
	m_itemCount = 5;
	
	ClearItems();
}

CItemCache::~CItemCache()
{
}

void CItemCache::ClearItems()
{
	for(int i=0; i<m_itemCount; i++)
		m_itemArray[i] = NULL;
}

bool CItemCache::IsSpaceAvailable()
{
	for(int i=0; i<m_itemCount; i++)
		if(m_itemArray[i] == NULL)
			return true;
	
	return false;
}

void CItemCache::AddItems(CItem* itemArray[])
{
	for(int i=0; i<m_itemCount; i++)
	{
		m_itemArray[i] = itemArray[i];
		
		if(m_itemArray[i] != NULL)
			m_itemArray[i]->SetParent(this);
	}
}

void CItemCache::AddItems(CItem* item1, CItem* item2, CItem* item3, CItem* item4, CItem* item5)
{
	m_itemArray[0] = item1;
	m_itemArray[1] = item2;
	m_itemArray[2] = item3;
	m_itemArray[3] = item4;
	m_itemArray[4] = item5;
	
	for(int i=0; i<m_itemCount; i++)
		if(m_itemArray[i] != NULL)
			m_itemArray[i]->SetParent(this);
}

bool CItemCache::AddItem(CItem* pItem)
{
	if(IsSpaceAvailable())
	{
		if(pItem->GetParent() != NULL)
			pItem->GetParent()->RemoveItem(pItem);
		
		pItem->SetParent(this);
	
		for(int i=0; i<m_itemCount; i++)
		{
			if(m_itemArray[i] == NULL)
			{
				m_itemArray[i] = pItem;
				
				return true;
			}
		}
	}
	
	return false;
}

bool CItemCache::AddItem(CItem* pItem, bool force)
{
	if(!IsSpaceAvailable() && force)
		RemoveItem(0);
	
	AddItem(pItem);
	
	return false;
}
	
bool CItemCache::RemoveItem(CItem* pItem)
{
	for(int i=0; i<m_itemCount; i++)
	{
		if(m_itemArray[i] == pItem)
		{	
			for(int j = i; j<m_itemCount-1; j++)
				m_itemArray[j] = m_itemArray[j + 1];
			
			m_itemArray[m_itemCount-1] = NULL;
			
			return true;
		}
	}
	
	return false;
}

bool CItemCache::RemoveItem(int index)
{
	for(int j = index; j<m_itemCount-1; j++)
		m_itemArray[j] = m_itemArray[j + 1];
	
	m_itemArray[m_itemCount-1] = NULL;
	
	return true;
}

bool CItemCache::ContainsItem(CItem* pItem)
{
	for(int i=0; i<m_itemCount; i++)
		if(m_itemArray[i] == pItem)
			return true;
	
	return false;
}

bool CItemCache::ReplaceItem(CItem* pOldItem, CItem* pNewItem)
{
	for(int i=0; i<m_itemCount; i++)
	{
		if(m_itemArray[i] == pOldItem)
		{
			m_itemArray[i] = pNewItem;
			m_itemArray[i]->SetParent(this);
			
			return true;
		}
	}
	
	return false;
}

void CItemCache::Save(CSave* pSave)
{
	for(int i=0; i<m_itemCount; i++)
		pSave->WriteItem(m_itemArray[i]);
}

void CItemCache::Load(CSave* pSave)
{
	for(int i=0; i<m_itemCount; i++)
	{
		pSave->ReadItem(&m_itemArray[i]);
		
		if(m_itemArray[i] != NULL)
			m_itemArray[i]->SetParent(this);
	}
}

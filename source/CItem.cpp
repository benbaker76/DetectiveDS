#include <nds.h>
#include "CItem.h"
#include "CItemCache.h"
#include "CSave.h"

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

void CItem::Save(CSave* pSave)
{
	pSave->WriteBool(m_locked);
	
	if(m_itemCache != NULL)
		m_itemCache->Save(pSave);
}

void CItem::Load(CSave* pSave)
{
	pSave->ReadBool(&m_locked);
	
	if(m_itemCache != NULL)
		m_itemCache->Load(pSave);
}


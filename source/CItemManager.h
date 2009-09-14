#ifndef __CITEMMANAGER_H__
#define __CITEMMANAGER_H__

#include "CItem.h"

#define ITEM_CAPACITY			5

class CItemManager
{
public:
	CItemManager();
	~CItemManager();
	
	void ClearItems();
	bool AddItem(CItem* pItem);
	bool RemoveItem(CItem* pItem);
	
private:
	CItem* m_itemArray[ITEM_CAPACITY];
};

#endif

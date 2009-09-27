#ifndef __CITEMCACHE_H__
#define __CITEMCACHE_H__

#include "ColMap.h"

#define MAX_ITEM_CACHE		8
#define MAX_ITEM_ARRAY		10

enum ItemLocation
{
	ITEMLOCATION_NONE,
	ITEMLOCATION_CHARACTER,
	ITEMLOCATION_ITEM,
	ITEMLOCATION_ROOM
};

class CCharacter;
class CItem;
class CRoom;

class CItemCache
{
public:
	CItemCache(ItemLocation itemLocation, void* pParent);
	CItemCache(ItemLocation itemLocation, int itemCount, void* pParent);
	CItemCache(ItemLocation itemLocation, CollisionType colType, void* pParent);
	~CItemCache();
	
	void ClearItems();
	bool IsSpaceAvailable();
	void AddItems(CItem* item1, CItem* item2, CItem* item3, CItem* item4, CItem* item5);
	void AddItems(CItem* itemArray[]);
	bool AddItem(CItem* pItem);
	bool RemoveItem(CItem* pItem);
	bool ContainsItem(CItem* pItem);
	bool ReplaceItem(CItem* pOldItem, CItem* pNewItem);
	
	ItemLocation GetItemLocation() const { return m_itemLocation; }
	void SetItemLocation(ItemLocation itemLocation) { m_itemLocation = itemLocation; }
	
	CollisionType GetItemColType() const { return m_colType; }
	CItem* GetItem(int index) const { return m_itemArray[index]; }
	
	int ItemCount() const { return m_itemCount; }
	
private:
	CollisionType m_colType;
	ItemLocation m_itemLocation;
	CItem* m_itemArray[MAX_ITEM_ARRAY];
	
	int m_itemCount;
	
	void* m_pParent;
};

#endif

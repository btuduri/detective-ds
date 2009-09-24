#include <stdio.h>
#include "CItem.h"
#include "CItemCache.h"

CItemCache::CItemCache(ItemLocation itemLocation, int itemCount, void* pParent)
{
	m_itemLocation = itemLocation;
	m_itemCount = itemCount;
	m_pParent = pParent;
	m_colType = COL_NOTHING_HERE;
	
	ClearItems();
}

CItemCache::CItemCache(ItemLocation itemLocation, void* pParent)
{
	m_itemLocation = itemLocation;
	m_pParent = pParent;
	m_colType = COL_NOTHING_HERE;
	m_itemCount = 5;
	
	ClearItems();
}

CItemCache::CItemCache(ItemLocation itemLocation, CItem* itemArray[], void* pParent)
{
	m_itemLocation = itemLocation;
	m_pParent = pParent;
	m_colType = COL_NOTHING_HERE;
	m_itemCount = 5;
	
	for(int i=0; i<m_itemCount; i++)
	{
		m_itemArray[i] = itemArray[i];
		
		if(m_itemArray[i] != NULL)
			m_itemArray[i]->SetParent(this);
	}
}

CItemCache::CItemCache(ItemLocation itemLocation, CollisionType colType, void* pParent)
{
	m_itemLocation = itemLocation;
	m_colType = colType;
	m_pParent = pParent;
	m_itemCount = 5;
	
	ClearItems();
}

CItemCache::CItemCache(ItemLocation itemLocation, CollisionType colType, CItem* itemArray[], void* pParent)
{
	m_itemLocation = itemLocation;
	m_colType = colType;
	m_pParent = pParent;
	m_itemCount = 5;
	
	for(int i=0; i<m_itemCount; i++)
	{
		m_itemArray[i] = itemArray[i];
		
		if(m_itemArray[i] != NULL)
			m_itemArray[i]->SetParent(this);
	}
}

CItemCache::~CItemCache()
{
}

void CItemCache::ClearItems()
{
	for(int i=0; i<m_itemCount; i++)
		m_itemArray[i] = NULL;
}

bool CItemCache::AddItem(CItem* pItem)
{
	bool retVal = false;
	
	for(int i=0; i<m_itemCount; i++)
	{
		if(m_itemArray[i] == NULL)
		{
			m_itemArray[i] = pItem;
			
			pItem->GetParent()->RemoveItem(pItem);
			pItem->SetParent(this);
			retVal = true;
			break;
		}
	}
	
	return retVal;
}
	
bool CItemCache::RemoveItem(CItem* pItem)
{
	bool retVal = false;
	
	for(int i=0; i<m_itemCount; i++)
	{
		if(m_itemArray[i] == pItem)
		{
			m_itemArray[i] = NULL;
			
			for(int j = i + 1; j<m_itemCount-1; j++)
				m_itemArray[i] = m_itemArray[j];
			
			m_itemArray[m_itemCount-1] = NULL;
			
			retVal = true;
			break;
		}
	}
	
	return retVal;
}

bool CItemCache::ReplaceItem(CItem* pOldItem, CItem* pNewItem)
{
	bool retVal = false;
	
	for(int i=0; i<m_itemCount; i++)
	{
		if(m_itemArray[i] == pOldItem)
		{
			m_itemArray[i] = pNewItem;
			
			retVal = true;
			break;
		}
	}
	
	return retVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Implementation of Map from KEY to VALUE
//
/////////////////////////////////////////////////////////////////////////////

#include "afxcoll.h"
#pragma hdrstop

#include "plex.h"

#ifdef AFX_COLL_SEG
#pragma code_seg(AFX_COLL_SEG)
#endif


IMPLEMENT_DYNAMIC(CMapPtrToPtr, CObject);

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////

 
CMapPtrToPtr::CMapPtrToPtr(int nBlockSize)
{
	ASSERT(nBlockSize > 0);

	m_pHashTable = NULL;
	m_nHashTableSize = 17;      // default size
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
}

 
inline UINT CMapPtrToPtr::HashKey(void* key) const
{
	// default identity hash - works for most primitive values
	return _AFX_FP_OFF(key) >> 4;
}


 
void CMapPtrToPtr::InitHashTable(UINT nHashSize)
//
// Used to force allocation of a hash table or to override the default
//   hash table size of (which is fairly small)
{
	ASSERT_VALID(this);
	ASSERT(m_nCount == 0);
	ASSERT(nHashSize > 0);

	// if had a hash table - get rid of it
	if (m_pHashTable != NULL)
		delete m_pHashTable;
	m_pHashTable = NULL;

	m_pHashTable = new CAssoc* [nHashSize];
	memset(m_pHashTable, 0, sizeof(CAssoc*) * nHashSize);
	m_nHashTableSize = nHashSize;
}

 
void CMapPtrToPtr::RemoveAll()
{
	ASSERT_VALID(this);

	if (m_pHashTable != NULL)
	{


		// free hash table
		delete m_pHashTable;
		m_pHashTable = NULL;
	}

	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

 
CMapPtrToPtr::~CMapPtrToPtr()
{
	RemoveAll();
	ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Assoc helpers
// same as CList implementation except we store CAssoc's not CNode's
//    and CAssoc's are singly linked all the time

 
CMapPtrToPtr::CAssoc* CMapPtrToPtr::NewAssoc()
{
	if (m_pFreeList == NULL)
	{
		// add another block
		CPlex* newBlock = CPlex::Create(m_pBlocks, m_nBlockSize, sizeof(CMapPtrToPtr::CAssoc));
		// chain them into free list
		register CMapPtrToPtr::CAssoc* pAssoc = (CMapPtrToPtr::CAssoc*) newBlock->data();
		// free in reverse order to make it easier to debug
		pAssoc += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
		{
			pAssoc->pNext = m_pFreeList;
			m_pFreeList = pAssoc;
		}
	}
	ASSERT(m_pFreeList != NULL); // we must have something

	CMapPtrToPtr::CAssoc* pAssoc = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	m_nCount++;
	ASSERT(m_nCount > 0);       // make sure we don't overflow
	memset(&pAssoc->key, 0, sizeof(void*));

	memset(&pAssoc->value, 0, sizeof(void*));

	return pAssoc;
}

 
void CMapPtrToPtr::FreeAssoc(CMapPtrToPtr::CAssoc* pAssoc)
{

	pAssoc->pNext = m_pFreeList;
	m_pFreeList = pAssoc;
	m_nCount--;
	ASSERT(m_nCount >= 0);      // make sure we don't underflow
}

 
CMapPtrToPtr::CAssoc*
CMapPtrToPtr::GetAssocAt(void* key, UINT& nHash) const
// find association (or return NULL)
{
	nHash = HashKey(key) % m_nHashTableSize;

	if (m_pHashTable == NULL)
		return NULL;

	// see if it exists
	register CAssoc* pAssoc;
	for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (pAssoc->key == key)
			return pAssoc;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////

 
BOOL CMapPtrToPtr::Lookup(void* key, void*& rValue) const
{
	ASSERT_VALID(this);

	UINT nHash;
	register CAssoc* pAssoc = GetAssocAt(key, nHash);
	if (pAssoc == NULL)
		return FALSE;       // not in map

	rValue = pAssoc->value;
	return TRUE;
}

 
void*& CMapPtrToPtr::operator[](void* key)
{
	ASSERT_VALID(this);

	UINT nHash;
	register CAssoc* pAssoc;
	if ((pAssoc = GetAssocAt(key, nHash)) == NULL)
	{
		if (m_pHashTable == NULL)
			InitHashTable(m_nHashTableSize);

		// it doesn't exist, add a new Association
		pAssoc = NewAssoc();
		pAssoc->nHashValue = nHash;
		pAssoc->key = key;
		// 'pAssoc->value' is a constructed object, nothing more

		// put into hash table
		pAssoc->pNext = m_pHashTable[nHash];
		m_pHashTable[nHash] = pAssoc;
	}
	return pAssoc->value;           // return new reference
}


 
BOOL CMapPtrToPtr::RemoveKey(void* key)
// remove key - return TRUE if removed
{
	ASSERT_VALID(this);

	if (m_pHashTable == NULL)
		return FALSE;       // nothing in the table

	register CAssoc** ppAssocPrev;
	ppAssocPrev = &m_pHashTable[HashKey(key) % m_nHashTableSize];

	CAssoc* pAssoc;
	for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (pAssoc->key == key)
		{
			// remove it
			*ppAssocPrev = pAssoc->pNext;       // remove from list
			FreeAssoc(pAssoc);
			return TRUE;
		}
		ppAssocPrev = &pAssoc->pNext;
	}
	return FALSE;   // not found
}


/////////////////////////////////////////////////////////////////////////////
// Iterating

 
void CMapPtrToPtr::GetNextAssoc(POSITION& rNextPosition,
	void*& rKey, void*& rValue) const
{
	ASSERT_VALID(this);
	ASSERT(m_pHashTable != NULL);       // never call on empty map

	register CAssoc* pAssocRet = (CAssoc*)rNextPosition;
	ASSERT(pAssocRet != NULL);

	if (pAssocRet == (CAssoc*) BEFORE_START_POSITION)
	{
		// find the first association
		for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
				break;
		ASSERT(pAssocRet != NULL);  // must find something
	}

	// find next association
	CAssoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL)
	{
		// go to next bucket
		for (UINT nBucket = pAssocRet->nHashValue + 1;
		  nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
				break;
	}

	rNextPosition = (POSITION) pAssocNext;

	// fill in return data
	rKey = pAssocRet->key;
	rValue = pAssocRet->value;
}

/////////////////////////////////////////////////////////////////////////////
// Serialization


/////////////////////////////////////////////////////////////////////////////
// Diagnostics

#ifdef _DEBUG

 
void CMapPtrToPtr::Dump(CDumpContext& dc) const
{
	ASSERT_VALID(this);

#define MAKESTRING(x) #x
	dc << "a " MAKESTRING(CMapPtrToPtr) " with " << m_nCount << " elements";
#undef MAKESTRING
	if (dc.GetDepth() > 0)
	{
		// Dump in format "[key] -> value"
		POSITION pos = GetStartPosition();
		void* key;
		void* val;

		dc << "\n";
		while (pos != NULL)
		{
			GetNextAssoc(pos, key, val);
			dc << "\n\t[" << key << "] = " << val;
		}
	}
}

 
void CMapPtrToPtr::AssertValid() const
{
	CObject::AssertValid();

	ASSERT(m_nHashTableSize > 0);
	ASSERT(m_nCount == 0 || m_pHashTable != NULL);
			 // non-empty map should have hash table
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
//
// Implementation of List of TYPEs
//
/////////////////////////////////////////////////////////////////////////////

#include "afxcoll.h"
#pragma hdrstop

#include "plex.h"

#ifdef AFX_COLL_SEG
#pragma code_seg(AFX_COLL_SEG)
#endif


IMPLEMENT_DYNAMIC(CPtrList, CObject);

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////

  
CPtrList::CPtrList(int nBlockSize)
{
	ASSERT(nBlockSize > 0);

	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
}

  
void CPtrList::RemoveAll()
{
	ASSERT_VALID(this);

	// destroy elements


	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

  
CPtrList::~CPtrList()
{
	RemoveAll();
	ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Node helpers
/*
 * Implementation note: CNode's are stored in CPlex blocks and
 *  chained together. Free blocks are maintained in a singly linked list
 *  using the 'pNext' member of CNode with 'm_pNodeFree' as the head.
 *  Used blocks are maintained in a doubly linked list using both 'pNext'
 *  and 'pPrev' as links and 'm_pNodeHead' and 'm_pNodeTail'
 *   as the head/tail.
 *
 * We never free a CPlex block unless the List is destroyed or RemoveAll()
 *  is used - so the total number of CPlex blocks may grow large depending
 *  on the maximum past size of the list.
 */

  
CPtrList::CNode*
CPtrList::NewNode(CPtrList::CNode* pPrev, CPtrList::CNode* pNext)
{
	if (m_pNodeFree == NULL)
	{
		// add another block
		CPlex* pNewBlock = CPlex::Create(m_pBlocks, m_nBlockSize,
				 sizeof(CNode));

		// chain them into free list
		CNode* pNode = (CNode*) pNewBlock->data();
		// free in reverse order to make it easier to debug
		pNode += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pNode--)
		{
			pNode->pNext = m_pNodeFree;
			m_pNodeFree = pNode;
		}
	}
	ASSERT(m_pNodeFree != NULL); // we must have something

	register CPtrList::CNode* pNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNode->pPrev = pPrev;
	pNode->pNext = pNext;
	m_nCount++;
	ASSERT(m_nCount > 0);       // make sure we don't overflow


	memset(&pNode->data, 0, sizeof(void*));         // zero fill

	return pNode;
}

  
void CPtrList::FreeNode(CPtrList::CNode* pNode)
{

	pNode->pNext = m_pNodeFree;
	m_pNodeFree = pNode;
	m_nCount--;
	ASSERT(m_nCount >= 0);      // make sure we don't underflow
}

/////////////////////////////////////////////////////////////////////////////

  
POSITION CPtrList::AddHead(void* newElement)
{
	ASSERT_VALID(this);

	CNode* pNewNode = NewNode(NULL, m_pNodeHead);
	pNewNode->data = newElement;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = pNewNode;
	else
		m_pNodeTail = pNewNode;
	m_pNodeHead = pNewNode;
	return (POSITION) pNewNode;
}

  
POSITION CPtrList::AddTail(void* newElement)
{
	ASSERT_VALID(this);

	CNode* pNewNode = NewNode(m_pNodeTail, NULL);
	pNewNode->data = newElement;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;
	m_pNodeTail = pNewNode;
	return (POSITION) pNewNode;
}

  
void CPtrList::AddHead(CPtrList* pNewList)
{
	ASSERT_VALID(this);

	ASSERT(pNewList != NULL);
	ASSERT(pNewList->IsKindOf(RUNTIME_CLASS(CPtrList)));
	ASSERT_VALID(pNewList);

	// add a list of same elements to head (maintain order)
	POSITION pos = pNewList->GetTailPosition();
	while (pos != NULL)
		AddHead(pNewList->GetPrev(pos));
}

  
void CPtrList::AddTail(CPtrList* pNewList)
{
	ASSERT_VALID(this);
	ASSERT(pNewList != NULL);
	ASSERT(pNewList->IsKindOf(RUNTIME_CLASS(CPtrList)));
	ASSERT_VALID(pNewList);

	// add a list of same elements
	POSITION pos = pNewList->GetHeadPosition();
	while (pos)
		AddTail(pNewList->GetNext(pos));
}

  
void* CPtrList::RemoveHead()
{
	ASSERT_VALID(this);
	ASSERT(m_pNodeHead != NULL);    // don't call on empty list !!!

	CNode* pOldNode = m_pNodeHead;
	ASSERT(pOldNode != NULL);
	void* returnValue = pOldNode->data;

	m_pNodeHead = pOldNode->pNext;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = NULL;
	else
		m_pNodeTail = NULL;
	FreeNode(pOldNode);
	return returnValue;
}

  
void* CPtrList::RemoveTail()
{
	ASSERT_VALID(this);
	ASSERT(m_pNodeTail != NULL);    // don't call on empty list !!!

	CNode* pOldNode = m_pNodeTail;
	ASSERT(pOldNode != NULL);
	void* returnValue = pOldNode->data;

	m_pNodeTail = pOldNode->pPrev;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;
	FreeNode(pOldNode);
	return returnValue;
}

  
POSITION CPtrList::InsertBefore(POSITION position, void* newElement)
{
	ASSERT_VALID(this);

	if (position == NULL)
		return AddHead(newElement); // insert before nothing -> head of the list

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
	pNewNode->data = newElement;

	if (pOldNode->pPrev != NULL)
	{
		pOldNode->pPrev->pNext = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeHead);
		m_pNodeHead = pNewNode;
	}
	pOldNode->pPrev = pNewNode;
	return (POSITION) pNewNode;
}

  
POSITION CPtrList::InsertAfter(POSITION position, void* newElement)
{
	ASSERT_VALID(this);

	if (position == NULL)
		return AddTail(newElement); // insert after nothing -> tail of the list

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = NewNode(pOldNode, pOldNode->pNext);
	pNewNode->data = newElement;

	if (pOldNode->pNext != NULL)
	{
		pOldNode->pNext->pPrev = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeTail);
		m_pNodeTail = pNewNode;
	}
	pOldNode->pNext = pNewNode;
	return (POSITION) pNewNode;
}

  
void CPtrList::RemoveAt(POSITION position)
{
	ASSERT_VALID(this);
	ASSERT(position != NULL);

	CNode* pOldNode = (CNode*) position;

	// remove pOldNode from list
	if (pOldNode == m_pNodeHead)
		m_pNodeHead = pOldNode->pNext;
	else
		pOldNode->pPrev->pNext = pOldNode->pNext;
	if (pOldNode == m_pNodeTail)
		m_pNodeTail = pOldNode->pPrev;
	else
		pOldNode->pNext->pPrev = pOldNode->pPrev;
	FreeNode(pOldNode);
}


/////////////////////////////////////////////////////////////////////////////
// slow operations

  
POSITION CPtrList::FindIndex(int nIndex) const
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0);

	if (nIndex >= m_nCount)
		return NULL;        // went too far

	register CNode* pNode = m_pNodeHead;
	while (nIndex--)
		pNode = pNode->pNext;
	return (POSITION) pNode;
}

  
POSITION CPtrList::Find(void* searchValue, POSITION startAfter) const
{
	ASSERT_VALID(this);

	register CNode* pNode = (CNode*) startAfter;
	if (pNode == NULL)
		pNode = m_pNodeHead;        // start at head
	else
		pNode = pNode->pNext;       // start after the one specified

	for (; pNode != NULL; pNode = pNode->pNext)
		if (pNode->data == searchValue)
			return (POSITION) pNode;
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Serialization


/////////////////////////////////////////////////////////////////////////////
// Diagnostics

#ifdef _DEBUG
  
void CPtrList::Dump(CDumpContext& dc) const
{
	ASSERT_VALID(this);

#define MAKESTRING(x) #x
	dc << "a " MAKESTRING(CPtrList) " with " << m_nCount << " elements";
#undef MAKESTRING
	if (dc.GetDepth() > 0)
	{
		POSITION pos = GetHeadPosition();
		dc << "\n";

		while (pos != NULL)
			dc << "\n\t" << GetNext(pos);
	}
}

  
void CPtrList::AssertValid() const
{
	CObject::AssertValid();

	if (m_nCount == 0)
	{
		// empty list
		ASSERT(m_pNodeHead == NULL);
		ASSERT(m_pNodeTail == NULL);
	}
	else
	{
		// non-empty list
		ASSERT(m_pNodeHead != NULL);
		ASSERT(m_pNodeTail != NULL);
	}
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
//
// Implementation of Array of TYPEs
//
/////////////////////////////////////////////////////////////////////////////
// NOTE: we allocate an array of 'm_nMaxSize' elements, but only
//  the current size 'm_nSize' contains properly constructed
//  objects.

#include "afxcoll.h"
#pragma hdrstop

#ifdef AFX_COLL_SEG
#pragma code_seg(AFX_COLL_SEG)
#endif

#include <limits.h>
#define SIZE_T_MAX  UINT_MAX            /* max size for a size_t */


IMPLEMENT_SERIAL(CWordArray, CObject, 0);

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////

 
CWordArray::CWordArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

 
CWordArray::~CWordArray()
{
	ASSERT_VALID(this);

	delete [] (BYTE*)m_pData;
}

  
void CWordArray::SetSize(int nNewSize, int nGrowBy /* = -1 */)
{
	ASSERT_VALID(this);
	ASSERT(nNewSize >= 0);

	if (nGrowBy != -1)
		m_nGrowBy = nGrowBy;    // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		delete [] (BYTE*)m_pData;
		m_pData = NULL;
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create one with exact size
#ifdef SIZE_T_MAX
		ASSERT((long)nNewSize * sizeof(WORD) <= SIZE_T_MAX);    // no overflow
#endif
		m_pData = (WORD*) new BYTE[nNewSize * sizeof(WORD)];

		memset(m_pData, 0, nNewSize * sizeof(WORD));        // zero fill

		m_nSize = m_nMaxSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements

			memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(WORD));

		}

		m_nSize = nNewSize;
	}
	else
	{
		// Otherwise grow array
		int nNewMax;
		if (nNewSize < m_nMaxSize + m_nGrowBy)
			nNewMax = m_nMaxSize + m_nGrowBy;   // granularity
		else
			nNewMax = nNewSize; // no slush

#ifdef SIZE_T_MAX
		ASSERT((long)nNewMax * sizeof(WORD) <= SIZE_T_MAX); // no overflow
#endif
		WORD* pNewData = (WORD*) new BYTE[nNewMax * sizeof(WORD)];

		// copy new data from old
		memcpy(pNewData, m_pData, m_nSize * sizeof(WORD));

		// construct remaining elements
		ASSERT(nNewSize > m_nSize);

		memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(WORD));


		// get rid of old stuff (note: no destructors called)
		delete [] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

  
void CWordArray::FreeExtra()
{
	ASSERT_VALID(this);

	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
#ifdef SIZE_T_MAX
		ASSERT((long)m_nSize * sizeof(WORD) <= SIZE_T_MAX); // no overflow
#endif
		WORD* pNewData = (WORD*) new BYTE[m_nSize * sizeof(WORD)];
		// copy new data from old
		memcpy(pNewData, m_pData, m_nSize * sizeof(WORD));

		// get rid of old stuff (note: no destructors called)
		delete [] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

/////////////////////////////////////////////////////////////////////////////

  
void CWordArray::SetAtGrow(int nIndex, WORD newElement)
{
	ASSERT(nIndex >= 0);
	if (nIndex >= m_nSize)
		SetSize(nIndex+1);
	m_pData[nIndex] = newElement;
}

  
void CWordArray::InsertAt(int nIndex, WORD newElement, int nCount /*=1*/)
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0);        // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);       // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount); // grow it to new size
		// shift old data up to fill gap
		memmove(&m_pData[nIndex+nCount], &m_pData[nIndex],
			(nOldSize-nIndex) * sizeof(WORD));

		// re-init slots we copied from

		memset(&m_pData[nIndex], 0, nCount * sizeof(WORD));

	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);
	while (nCount--)
		m_pData[nIndex++] = newElement;
}

  
void CWordArray::RemoveAt(int nIndex, int nCount /* = 1 */)
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	ASSERT(nIndex + nCount <= m_nSize);

	// just remove a range
	int nMoveCount = m_nSize - (nIndex + nCount);

	if (nMoveCount)
		memcpy(&m_pData[nIndex], &m_pData[nIndex + nCount],
			nMoveCount * sizeof(WORD));
	m_nSize -= nCount;
}

  
void CWordArray::InsertAt(int nStartIndex, CWordArray* pNewArray)
{
	ASSERT_VALID(this);
	ASSERT(pNewArray != NULL);
	ASSERT(pNewArray->IsKindOf(RUNTIME_CLASS(CWordArray)));
	ASSERT_VALID(pNewArray);
	ASSERT(nStartIndex >= 0);

	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}

/////////////////////////////////////////////////////////////////////////////
// Serialization

 

void CWordArray::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << (WORD) m_nSize;
		for (int i = 0; i < m_nSize; i++)
			ar << m_pData[i];
	}
	else
	{
		WORD    nOldSize;
		ar >> nOldSize;
		SetSize(nOldSize);

		for (int i = 0; i < m_nSize; i++)
			ar >> m_pData[i];
	}
}

/////////////////////////////////////////////////////////////////////////////
// Diagnostics

#ifdef _DEBUG
  
void CWordArray::Dump(CDumpContext& dc) const
{
	ASSERT_VALID(this);

#define MAKESTRING(x) #x
	dc << "a " MAKESTRING(CWordArray) " with " << m_nSize << " elements";
#undef MAKESTRING
	if (dc.GetDepth() > 0)
	{
		dc << "\n";
		for (int i = 0; i < m_nSize; i++)
			dc << "\n\t[" << i << "] = " << m_pData[i];
	}
}

  
void CWordArray::AssertValid() const
{
	CObject::AssertValid();
	if (m_pData == NULL)
	{
		ASSERT(m_nSize == 0);
		ASSERT(m_nMaxSize == 0);
	}
	else
	{
		ASSERT(m_nSize <= m_nMaxSize);
	}
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////


/*
    Copyright (c) 2007-2011 Cyrus Daboo. All rights reserved.
    
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
    
        http://www.apache.org/licenses/LICENSE-2.0
    
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


// Source for CAddressView class

#include "CAddressView.h"

#include "CAddressPreviewAdvanced.h"
#include "CGroupPreview.h"
#include "CPreferences.h"

// Static members

cdmutexprotect<CAddressView::CAddressViewList> CAddressView::sAddressViews;

// C O N S T R U C T I O N / D E S T R U C T I O N  M E T H O D S

// Default constructor
CAddressView::CAddressView()
{
	mCurrent = NULL;

	// Add to list
	{
		cdmutexprotect<CAddressViewList>::lock _lock(sAddressViews);
		sAddressViews->push_back(this);
	}
}

// Constructor from stream
CAddressView::CAddressView(LStream *inStream)
		: CBaseView(inStream)
{
	mCurrent = NULL;

	// Add to list
	{
		cdmutexprotect<CAddressViewList>::lock _lock(sAddressViews);
		sAddressViews->push_back(this);
	}
}

// Default destructor
CAddressView::~CAddressView()
{
	// Remove from list
	cdmutexprotect<CAddressViewList>::lock _lock(sAddressViews);
	CAddressViewList::iterator found = std::find(sAddressViews->begin(), sAddressViews->end(), this);
	if (found != sAddressViews->end())
		sAddressViews->erase(found);
}

// O T H E R  M E T H O D S ____________________________________________________________________________

// Get details of sub-panes
void CAddressView::FinishCreateSelf(void)
{
	// Do inherited
	CBaseView::FinishCreateSelf();

	InitPreviews();
	SetOpen();
}

// Get details of sub-panes
void CAddressView::InitPreviews(void)
{
	// Find commander in super view hierarchy
	LView* super = GetSuperView();
	while(super && !dynamic_cast<LCommander*>(super))
		super = super->GetSuperView();
	LCommander* cmdr = dynamic_cast<LCommander*>(super);

	// Read the address view resource
	mAddressPreview = static_cast<CAddressPreviewAdvanced*>(UReanimator::CreateView(paneid_AddressPreviewAdvanced, this, cmdr));
	ExpandSubPane(mAddressPreview, true, true);
	mAddressPreview->Hide();

	// Read the group view resource
	mGroupPreview = static_cast<CGroupPreview*>(UReanimator::CreateView(paneid_GroupPreview, this, cmdr));
	ExpandSubPane(mGroupPreview, true, true);
	mGroupPreview->Hide();
	
	// Now force address preview to be visible but empty
	SetAddress(NULL, NULL);
}

// Check for window
bool CAddressView::ViewExists(const CAddressView* wnd)
{
	cdmutexprotect<CAddressViewList>::lock _lock(sAddressViews);
	CAddressViewList::iterator found = std::find(sAddressViews->begin(), sAddressViews->end(), wnd);
	return found != sAddressViews->end();
}

void CAddressView::DoClose()
{
	// Close any existing items
	if (mCurrent)
		mCurrent->Close();
	mCurrent = NULL;
	
	// Clear out address/group
	ClearAddress();
	ClearGroup();
	
	// Make sure preview items are NULL
	mAddressPreview->SetAddressBook(NULL);
	mAddressPreview->SetAddress(NULL);
	mGroupPreview->SetAddressBook(NULL);
	mGroupPreview->SetGroup(NULL);
}

void CAddressView::SetAddress(CAddressBook* adbk, CAdbkAddress* addr, bool refresh)
{
	// Close any existing items if not refreshing
	if (mCurrent && !refresh)
		mCurrent->Close();
	
	// Hide the group and empty it
	mGroupPreview->Hide();
	mGroupPreview->Disable();
	mGroupPreview->SetGroup(NULL);
	
	// Set the address and show
	mAddressPreview->SetAddressBook(adbk);
	mAddressPreview->SetAddress(addr);
	mAddressPreview->Enable();
	mAddressPreview->Show();
	mCurrent = mAddressPreview;

	// Focus on the preview if requested
	if (addr && GetViewOptions().GetSelectAddressPane())
		Focus();

	// Broadcast change to listeners
	Broadcast_Message(eBroadcast_ViewChanged, this);
}

// Address removed by someone else
void CAddressView::ClearAddress()
{
	mAddressPreview->ClearAddress();
	mAddressPreview->Disable();
}

CAdbkAddress* CAddressView::GetAddress() const
{
	return mAddressPreview->GetAddress();
}

void CAddressView::SetGroup(CAddressBook* adbk, CGroup* grp, bool refresh)
{
	// Close any existing items if not refreshing
	if (mCurrent && !refresh)
		mCurrent->Close();
	
	// Hide the address and empty it
	mAddressPreview->Hide();
	mAddressPreview->Disable();
	mAddressPreview->SetAddress(NULL);
	
	// Set the address and show
	mGroupPreview->SetAddressBook(adbk);
	mGroupPreview->SetGroup(grp);
	mGroupPreview->Enable();
	mGroupPreview->Show();
	mCurrent = mGroupPreview;

	// Focus on the preview if requested
	if (grp && GetViewOptions().GetSelectAddressPane())
		Focus();

	// Broadcast change to listeners
	Broadcast_Message(eBroadcast_ViewChanged, this);
}

// Address removed by someone else
void CAddressView::ClearGroup()
{
	mGroupPreview->ClearGroup();
	mGroupPreview->Disable();
}

CGroup* CAddressView::GetGroup() const
{
	return mGroupPreview->GetGroup();
}

bool CAddressView::HasFocus() const
{
	// Switch target to the text (will focus)
	return false;
}

void CAddressView::Focus()
{
	if (IsVisible() && mCurrent)
		// Switch target to the text (will focus)
		mCurrent->Focus();
}

// Get options for this view
const CAddressViewOptions& CAddressView::GetViewOptions() const
{
	return CPreferences::sPrefs->Get3PaneOptions().GetValue().GetAddressViewOptions();
}

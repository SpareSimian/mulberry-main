/*
    Copyright (c) 2007 Cyrus Daboo. All rights reserved.
    
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


// Header for CPropCalendarGeneral class

#ifndef __CPropCalendarGeneral__MULBERRY__
#define __CPropCalendarGeneral__MULBERRY__

#include "CCalendarPropPanel.h"

// Classes
namespace calstore
{
class CCalendarStoreNode;
}

class CStaticText;
class JXImageWidget;
class JXTextButton;

class CPropCalendarGeneral : public CCalendarPropPanel
{
public:
		CPropCalendarGeneral(JXContainer* enclosure,
				 const HSizingOption hSizing, const VSizingOption vSizing,
				 const JCoordinate x, const JCoordinate y,
				 const JCoordinate w, const JCoordinate h)
			: CCalendarPropPanel(enclosure, hSizing, vSizing, x, y, w, h) {}

	virtual void	OnCreate();								// Do odds & ends
	virtual void	SetCalList(calstore::CCalendarStoreNodeList* cal_list);		// Set cal list
	virtual void	SetProtocol(calstore::CCalendarProtocol* proto);			// Set protocol
	virtual void	ApplyChanges(void);						// Force update of mboxes

protected:
// begin JXLayout1

    JXImageWidget* mIconState;
    CStaticText*   mName;
    CStaticText*   mServer;
    CStaticText*   mHierarchy;
    CStaticText*   mSeparator;
    CStaticText*   mSize;
    JXTextButton*  mCalculateBtn;
    CStaticText*   mStatus;
    CStaticText*   mLastSync;

// end JXLayout1

	virtual void	Receive(JBroadcaster* sender, const Message& message);
	
private:
	virtual void	SetCalendar(calstore::CCalendarStoreNode* node);					// Set mbox item
			void	CheckSize();
};

#endif

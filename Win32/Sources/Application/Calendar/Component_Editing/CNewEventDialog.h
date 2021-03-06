/*
    Copyright (c) 2007-2009 Cyrus Daboo. All rights reserved.
    
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

#ifndef H_CNewEventDialog
#define H_CNewEventDialog
#pragma once

#include "CNewComponentDialog.h"

#include "CPopupButton.h"

#include "CICalendarVEvent.h"

// ===========================================================================
//	CNewEventDialog

class CNewEventDialog : public CNewComponentDialog
{
public:
	static void StartNew(const iCal::CICalendarDateTime& dtstart, const iCal::CICalendar* calin = NULL);
	static void StartEdit(const iCal::CICalendarVEvent& vevent, const iCal::CICalendarComponentExpanded* expanded);
	static void StartDuplicate(const iCal::CICalendarVEvent& vevent);

						CNewEventDialog();
	virtual				~CNewEventDialog();

protected:

// Dialog Data
	//{{AFX_DATA(CNewEventDialog)
	enum { IDD = IDD_CALENDAR_NEWEVENT };
	CPopupButton			mStatus;
	CButton					mAvailability;
	//}}AFX_DATA

	static void StartModeless(iCal::CICalendarVEvent& vevent, const iCal::CICalendarComponentExpanded* expanded, EModelessAction action);

			void		InitPanels();
	
			virtual void	SetComponent(iCal::CICalendarComponentRecur& vcomponent, const iCal::CICalendarComponentExpanded* expanded);
			virtual void	GetComponent(iCal::CICalendarComponentRecur& vcomponent);

			void	SetReadOnly(bool read_only);

			virtual void	ChangedMyStatus(const iCal::CICalendarProperty& attendee, const cdstring& new_status);

			bool	DoNewOK();
			bool	DoEditOK();
			void	DoCancel();

	// Generated message map functions
	//{{AFX_MSG(CNewEventDialog)
	virtual BOOL	OnInitDialog();
	afx_msg void	OnOrganiserEdit();
	afx_msg void	OnAvailability();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

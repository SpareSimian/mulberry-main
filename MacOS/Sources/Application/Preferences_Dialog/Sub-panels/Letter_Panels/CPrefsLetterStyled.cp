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


// Source for CPrefsLetterStyled class

#include "CPrefsLetterStyled.h"

#include "CAdminLock.h"
#include "CPreferences.h"

#include <LCheckBox.h>
#include <LPopupButton.h>


// C O N S T R U C T I O N / D E S T R U C T I O N  M E T H O D S

// Default constructor
CPrefsLetterStyled::CPrefsLetterStyled()
{
}

// Constructor from stream
CPrefsLetterStyled::CPrefsLetterStyled(LStream *inStream)
		: CPrefsTabSubPanel(inStream)
{
}

// Default destructor
CPrefsLetterStyled::~CPrefsLetterStyled()
{
}

// O T H E R  M E T H O D S ____________________________________________________________________________

// Get details of sub-panes
void CPrefsLetterStyled::FinishCreateSelf(void)
{
	// Do inherited
	CPrefsTabSubPanel::FinishCreateSelf();

	mComposeAs = (LPopupButton*) FindPaneByID(paneid_LSComposeAs);

	mEnrichedPlain = (LCheckBox*) FindPaneByID(paneid_LSEnrPlain);
	mEnrichedHTML = (LCheckBox*) FindPaneByID(paneid_LSEnrHTML);
	mHTMLPlain = (LCheckBox*) FindPaneByID(paneid_LSHTMLPlain);
	mHTMLEnriched = (LCheckBox*) FindPaneByID(paneid_LSHTMLEnr);

	if (!CAdminLock::sAdminLock.mAllowStyledComposition)
	{
		mComposeAs->Disable();
		mEnrichedPlain->Disable();
		mEnrichedHTML->Disable();
		mHTMLPlain->Disable();
		mHTMLEnriched->Disable();
	}

	mFormatFlowed = (LCheckBox*) FindPaneByID(paneid_LSFormatFlowed);
}

// Set prefs
void CPrefsLetterStyled::SetData(void* data)
{
	CPreferences* copyPrefs = (CPreferences*) data;

	// Copy info to into panel
	if (CAdminLock::sAdminLock.mAllowStyledComposition)
	{
		mComposeAs->SetValue(copyPrefs->compose_as.GetValue());

		mEnrichedPlain->SetValue(copyPrefs->enrMultiAltPlain.GetValue());
		mEnrichedHTML->SetValue(copyPrefs->enrMultiAltHTML.GetValue());
		mHTMLPlain->SetValue(copyPrefs->htmlMultiAltPlain.GetValue());
		mHTMLEnriched->SetValue(copyPrefs->htmlMultiAltEnriched.GetValue());
	}
	mFormatFlowed->SetValue(copyPrefs->mFormatFlowed.GetValue());
}

// Force update of prefs
void CPrefsLetterStyled::UpdateData(void* data)
{
	CPreferences* copyPrefs = (CPreferences*) data;

	// Copy info from panel into prefs
	if (CAdminLock::sAdminLock.mAllowStyledComposition)
	{
		copyPrefs->compose_as.SetValue((EContentSubType) mComposeAs->GetValue());

		copyPrefs->enrMultiAltPlain.SetValue((mEnrichedPlain->GetValue()==1));
		copyPrefs->htmlMultiAltEnriched.SetValue((mHTMLEnriched->GetValue()==1));
		copyPrefs->enrMultiAltHTML.SetValue((mEnrichedHTML->GetValue()==1));
		copyPrefs->htmlMultiAltPlain.SetValue((mHTMLPlain->GetValue()==1));
	}
	copyPrefs->mFormatFlowed.SetValue((mFormatFlowed->GetValue()==1));
}

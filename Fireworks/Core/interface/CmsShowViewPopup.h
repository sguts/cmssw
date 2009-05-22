#ifndef Fireworks_Core_CmsShowViewPopup_h
#define Fireworks_Core_CmsShowViewPopup_h
// -*- C++ -*-
//
// Package:     Core
// Class  :     CmsShowViewPopup
//
/**\class CmsShowViewPopup CmsShowViewPopup.h Fireworks/Core/interface/CmsShowViewPopup.h

   Description: <one line class summary>

   Usage:
    <usage>

 */
//
// Original Author:
//         Created:  Wed Jun 25 15:15:12 EDT 2008
// $Id: CmsShowViewPopup.h,v 1.7 2009/04/13 16:12:44 chrjones Exp $
//

// system include files
#include <vector>
#include <boost/shared_ptr.hpp>
#include "TGFrame.h"

// user include files
#include "Fireworks/Core/interface/FWParameterSetterEditorBase.h"

// forward declarations
class FWViewBase;
class TGLabel;
class TGTextButton;
class TGButton;
class TGFrame;
class FWParameterSetterBase;
class FWColorManager;
class FWGUISubviewArea;

class CmsShowViewPopup : public TGTransientFrame, public FWParameterSetterEditorBase
{

public:
   CmsShowViewPopup(const TGWindow* p = 0, UInt_t w = 0, UInt_t h = 0, FWColorManager* cm=0, FWViewBase* v = 0, FWGUISubviewArea *sva = 0);
   virtual ~CmsShowViewPopup();

   // ---------- const member functions ---------------------

   // ---------- static member functions --------------------

   // ---------- member functions ---------------------------
   virtual void CloseWindow();

   void reset(FWViewBase* iView, FWGUISubviewArea* sva);
   void removeView();

   void saveImage();
   void changeBackground();
   void backgroundColorWasChanged();
private:
   CmsShowViewPopup(const CmsShowViewPopup&);    // stop default

   const CmsShowViewPopup& operator=(const CmsShowViewPopup&);    // stop default

   // ---------- member data --------------------------------
   TGLabel* m_viewLabel;
   TGTextButton* m_removeButton;
   TGCompositeFrame* m_viewContentFrame;
   TGButton* m_saveImageButton;
   TGTextButton* m_changeBackground;
   FWViewBase* m_view;
   std::vector<boost::shared_ptr<FWParameterSetterBase> > m_setters;
   FWColorManager* m_colorManager;

   FWGUISubviewArea* m_viewArea;
};


#endif

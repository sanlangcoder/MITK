/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "TestPerspective.h"

TestPerspective::TestPerspective()
{
}

void TestPerspective::CreateInitialLayout(berry::IPageLayout::Pointer layout)
{
  layout->AddView("org.mitk.views.minimalview", 0, 0.33f, layout->GetEditorArea());
  layout->GetViewLayout("org.mitk.views.minimalview")->SetCloseable(false);
  layout->SetEditorAreaVisible(true);
}

/*===================================================================

BlueBerry Platform

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "tweaklets/berryWorkbenchTweaklet.h"

#include "berryShowViewHandler.h"
#include "berryHandlerUtil.h"

#include "dialogs/berryIShowViewDialog.h"

#include "berryUIException.h"
#include "berryIWorkbenchPage.h"
#include "berryIViewDescriptor.h"
#include "berryPlatformUI.h"

#include <berryCommandExceptions.h>

#include <vector>

namespace berry
{

const QString ShowViewHandler::PARAMETER_NAME_VIEW_ID = "org.blueberry.ui.views.showView.viewId";

ShowViewHandler::ShowViewHandler()
{
}

Object::Pointer ShowViewHandler::Execute(const ExecutionEvent::ConstPointer& event)
{
  IWorkbenchWindow::ConstPointer window = HandlerUtil::GetActiveWorkbenchWindowChecked(event);
  // Get the view identifier, if any.
  const ExecutionEvent::ParameterMap& parameters = event->GetParameters();
  ExecutionEvent::ParameterMap::const_iterator result = parameters.find(PARAMETER_NAME_VIEW_ID);
  QString value;
  if (result != parameters.end()) value = result.value();

  if (value.isEmpty())
  {
    this->OpenOther(window);
  }
  else
  {
    try
    {
      this->OpenView(value, window);
    }
    catch (const PartInitException& e)
    {
      throw ExecutionException("Part could not be initialized", e);
    }
  }

  return Object::Pointer(0);
}

void ShowViewHandler::OpenOther(IWorkbenchWindow::ConstPointer window)
{
  const IWorkbenchPage::Pointer page = window->GetActivePage();
  if (page.IsNull())
  {
    return;
  }

  IShowViewDialog::Pointer dialog = Tweaklets::Get(WorkbenchTweaklet::KEY)->CreateStandardDialog(WorkbenchTweaklet::DIALOG_ID_SHOW_VIEW).Cast<IShowViewDialog>();
  if (dialog.IsNull()) return;

  int returnCode = dialog->Open();

  if (returnCode == IDialog::CANCEL)
  {
    return;
  }

  const QList<IViewDescriptor::Pointer> descriptors =
      dialog->GetSelection();
  for (int i = 0; i < descriptors.size(); ++i)
  {
    try
    {
      this->OpenView(descriptors[i]->GetId(), window);
    }
    catch (PartInitException e)
    {
//      StatusUtil.handleStatus(e.getStatus(),
//          WorkbenchMessages.ShowView_errorTitle
//          + ": " + e.getMessage(), //$NON-NLS-1$
//          StatusManager.SHOW);
    }
  }
}

void ShowViewHandler::OpenView(const QString& viewId, IWorkbenchWindow::ConstPointer activeWorkbenchWindow)
{
  const IWorkbenchPage::Pointer activePage = activeWorkbenchWindow->GetActivePage();
  if (activePage.IsNull())
  {
    return;
  }

  activePage->ShowView(viewId);
}

}

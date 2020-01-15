/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/


#ifndef BERRYUITESTWORKBENCHWINDOWADVISOR_H_
#define BERRYUITESTWORKBENCHWINDOWADVISOR_H_

#include <berryWorkbenchWindowAdvisor.h>

namespace berry {

class UITestWorkbenchWindowAdvisor : public WorkbenchWindowAdvisor
{
public:

  UITestWorkbenchWindowAdvisor(const SmartPointer<IWorkbenchWindowConfigurer>& configurer);
};

}

#endif /* BERRYUITESTWORKBENCHWINDOWADVISOR_H_ */

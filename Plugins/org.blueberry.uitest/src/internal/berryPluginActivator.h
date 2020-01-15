/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/


#ifndef BERRYPLUGINACTIVATOR_H
#define BERRYPLUGINACTIVATOR_H

#include <ctkPluginActivator.h>

namespace berry {

class org_blueberry_uitest_Activator :
  public QObject, public ctkPluginActivator
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org_blueberry_uitest")
  Q_INTERFACES(ctkPluginActivator)

public:
  org_blueberry_uitest_Activator();

  void start(ctkPluginContext* context);
  void stop(ctkPluginContext* context);
};

typedef org_blueberry_uitest_Activator PluginActivator;

}

#endif // BERRYPLUGINACTIVATOR_H

/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef mitkColorPropertySerializer_h_included
#define mitkColorPropertySerializer_h_included

#include "mitkBasePropertySerializer.h"
#include "mitkColorProperty.h"
#include "mitkStringsToNumbers.h"
#include <mitkLocaleSwitch.h>

namespace mitk
{
  class ColorPropertySerializer : public BasePropertySerializer
  {
  public:
    mitkClassMacro(ColorPropertySerializer, BasePropertySerializer);
    itkFactorylessNewMacro(Self) itkCloneMacro(Self)

      TiXmlElement *Serialize() override
    {
      if (const ColorProperty *prop = dynamic_cast<const ColorProperty *>(m_Property.GetPointer()))
      {
        LocaleSwitch localeSwitch("C");

        auto element = new TiXmlElement("color");
        Color color = prop->GetValue();
        element->SetAttribute("r", boost::lexical_cast<std::string>(color[0]));
        element->SetAttribute("g", boost::lexical_cast<std::string>(color[1]));
        element->SetAttribute("b", boost::lexical_cast<std::string>(color[2]));
        return element;
      }
      else
        return nullptr;
    }

    BaseProperty::Pointer Deserialize(TiXmlElement *element) override
    {
      if (!element)
        return nullptr;

      LocaleSwitch localeSwitch("C");

      std::string c_string[3];
      if (element->QueryStringAttribute("r", &c_string[0]) != TIXML_SUCCESS)
        return nullptr;
      if (element->QueryStringAttribute("g", &c_string[1]) != TIXML_SUCCESS)
        return nullptr;
      if (element->QueryStringAttribute("b", &c_string[2]) != TIXML_SUCCESS)
        return nullptr;
      Color c;
      try
      {
        StringsToNumbers<double>(3, c_string, c);
      }
      catch (boost::bad_lexical_cast &e)
      {
        MITK_ERROR << "Could not parse string as number: " << e.what();
        return nullptr;
      }

      return ColorProperty::New(c).GetPointer();
    }

  protected:
    ColorPropertySerializer() {}
    ~ColorPropertySerializer() override {}
  };

} // namespace

// important to put this into the GLOBAL namespace (because it starts with 'namespace mitk')
MITK_REGISTER_SERIALIZER(ColorPropertySerializer);

#endif

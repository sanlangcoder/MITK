/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "mitkUIDGenerator.h"
#include <mitkLogMacros.h>
#include <mitkTestFixture.h>
#include <mitkTestingMacros.h>

class mitkUIDGeneratorTestSuite : public mitk::TestFixture
{
  CPPUNIT_TEST_SUITE(mitkUIDGeneratorTestSuite);
  MITK_TEST(UIDGeneratorInstanceRenewalSucceed);
  MITK_TEST(UIDGeneratorMultipleInstancesSucceed);

  CPPUNIT_TEST_SUITE_END();

  unsigned short m_UidLengthStart = 5;
  unsigned short m_UidLengthEnd = 20;


  void UIDGeneratorInstanceRenewalSucceed()
  {
    for (auto k = m_UidLengthStart; k < m_UidLengthEnd; ++k)
    {
      mitk::UIDGenerator uidGen1("UID_", k);
      auto uid1_1 = uidGen1.GetUID();

      uidGen1 = mitk::UIDGenerator("UID_", k);
      auto uid2_1 = uidGen1.GetUID();

      CPPUNIT_ASSERT_MESSAGE("Different UIDs are not allowed to be equal", uid1_1 != uid2_1);
    }
  }

  void UIDGeneratorMultipleInstancesSucceed()
  {
    for (auto k = m_UidLengthStart; k < m_UidLengthEnd; ++k)
    {
      mitk::UIDGenerator uidGen1("UID_", k);
      mitk::UIDGenerator uidGen2("UID_", k);

      auto uid1_1 = uidGen1.GetUID();
      auto uid2_1 = uidGen2.GetUID();

      CPPUNIT_ASSERT_MESSAGE("Different UIDs are not allowed to be equal", uid1_1 != uid2_1);
    }
  }
};

MITK_TEST_SUITE_REGISTRATION(mitkUIDGenerator)

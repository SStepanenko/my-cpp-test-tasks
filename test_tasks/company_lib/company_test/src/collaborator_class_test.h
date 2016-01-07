////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file collaborator_class_test.h
/// @brief Test of Collaborator class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COLLABORATOR_CLASS_TEST_H
#define COLLABORATOR_CLASS_TEST_H

#include "gtest/gtest.h"

class CollaboratorClassTest : public ::testing::Test 
{
public:

  // Verifies date and time.
  static void verify_calendar_date_time(const tm& date_time, int32_t year_expected, int32_t month_expected,
    int32_t day_expected, int32_t hour_expected, int32_t minute_expected, int32_t second_expected);
};

#endif // COLLABORATOR_CLASS_TEST_H


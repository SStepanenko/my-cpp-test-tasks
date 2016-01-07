////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file pch.h
/// @brief Precompiled Header File.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PCH_H_F61A9E91_DAB0_4359_AA12_F97FE41624E3
#define PCH_H_F61A9E91_DAB0_4359_AA12_F97FE41624E3

// Enable some deprecated methods.
#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdint.h>
#include <string>
#include <ctime>
#include <memory>
#include <vector>

#include "gtest/gtest.h"

#include "company/collaborator.h"
#include "company/employee.h"
#include "company/manager.h"
#include "company/sales.h"
#include "company/company.h"

#include "test_utils.h"

#endif // PCH_H_F61A9E91_DAB0_4359_AA12_F97FE41624E3

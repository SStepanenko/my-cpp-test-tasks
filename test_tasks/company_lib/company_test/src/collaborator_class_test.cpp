////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file collaborator_class_test.cpp
/// @brief Test of Collaborator class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "collaborator_class_test.h"

using namespace std;

using namespace My_company;

void CollaboratorClassTest::verify_calendar_date_time(const tm& date_time, int32_t year_expected,
  int32_t month_expected, int32_t day_expected, int32_t hour_expected, int32_t minute_expected,
  int32_t second_expected)
{
  EXPECT_EQ(year_expected, date_time.tm_year + Collaborator::s_base_year);
  EXPECT_EQ(month_expected, date_time.tm_mon + 1);
  EXPECT_EQ(day_expected, date_time.tm_mday);
  EXPECT_EQ(hour_expected, date_time.tm_hour);
  EXPECT_EQ(minute_expected, date_time.tm_min);
  EXPECT_EQ(second_expected, date_time.tm_sec);
}

TEST(CollaboratorClassTest, CreateAndConvertTime)
{
  time_t time = 0;
  tm calendar_time;

  time = Collaborator::create_time_t(2015, 10, 15, 14, 19, 23);
  Collaborator::convert_to_calendar_date_time(time, calendar_time);
  CollaboratorClassTest::verify_calendar_date_time(calendar_time, 2015, 10, 15, 14, 19, 23);

  time = Collaborator::create_time_t(1990, 1, 1, 0, 0, 0);
  Collaborator::convert_to_calendar_date_time(time, calendar_time);
  CollaboratorClassTest::verify_calendar_date_time(calendar_time, 1990, 1, 1, 0, 0, 0);

  time = Collaborator::create_time_t(2015, 12, 31, 23, 59, 59);
  Collaborator::convert_to_calendar_date_time(time, calendar_time);
  CollaboratorClassTest::verify_calendar_date_time(calendar_time, 2015, 12, 31, 23, 59, 59);

  EXPECT_THROW(Collaborator::create_time_t(1899, 12, 31, 23, 59, 59), invalid_argument);
  EXPECT_THROW(Collaborator::create_time_t(2015, 0, 31, 23, 59, 59), invalid_argument);
  EXPECT_THROW(Collaborator::create_time_t(2015, 13, 31, 23, 59, 59), invalid_argument);
  EXPECT_THROW(Collaborator::create_time_t(2015, 12, 0, 23, 59, 59), invalid_argument);
  EXPECT_THROW(Collaborator::create_time_t(2015, 12, 32, 23, 59, 59), invalid_argument);
  EXPECT_THROW(Collaborator::create_time_t(2015, 12, 31, -1, 59, 59), invalid_argument);
  EXPECT_THROW(Collaborator::create_time_t(2015, 12, 31, 24, 59, 59), invalid_argument);
  EXPECT_THROW(Collaborator::create_time_t(2015, 12, 31, 23, -1, 59), invalid_argument);
  EXPECT_THROW(Collaborator::create_time_t(2015, 12, 31, 23, 60, 59), invalid_argument);
  EXPECT_THROW(Collaborator::create_time_t(2015, 12, 31, 23, 59, -1), invalid_argument);
  EXPECT_THROW(Collaborator::create_time_t(2015, 12, 31, 23, 59, 60), invalid_argument);

  // ToDo: add additional test cases...
}

TEST(CollaboratorClassTest, CalculateTotalWorkYears)
{
  time_t start_time = 0;
  time_t end_time = 0;
  int32_t work_years = 0;

  start_time = Collaborator::create_time_t(2015, 10, 15, 14, 19, 23);
  end_time = Collaborator::create_time_t(2015, 10, 14, 14, 19, 23);
  EXPECT_THROW(Collaborator::calculate_total_work_years(start_time, end_time), invalid_argument);

  start_time = Collaborator::create_time_t(2015, 1, 1, 0, 0, 0);
  end_time = Collaborator::create_time_t(2015, 12, 31, 23, 59, 59);
  work_years = -1;
  work_years = Collaborator::calculate_total_work_years(start_time, end_time);
  EXPECT_EQ(0, work_years);

  start_time = Collaborator::create_time_t(2015, 1, 1, 0, 0, 0);
  end_time = Collaborator::create_time_t(2016, 1, 1, 0, 0, 0);
  work_years = -1;
  work_years = Collaborator::calculate_total_work_years(start_time, end_time);
  EXPECT_EQ(0, work_years);

  start_time = Collaborator::create_time_t(2015, 1, 1, 0, 0, 0);
  end_time = Collaborator::create_time_t(2016, 1, 2, 0, 0, 0);
  work_years = -1;
  work_years = Collaborator::calculate_total_work_years(start_time, end_time);
  EXPECT_EQ(1, work_years);

  start_time = Collaborator::create_time_t(2015, 10, 15, 0, 0, 0);
  end_time = Collaborator::create_time_t(2019, 9, 16, 0, 0, 0);
  work_years = -1;
  work_years = Collaborator::calculate_total_work_years(start_time, end_time);
  EXPECT_EQ(3, work_years);

  start_time = Collaborator::create_time_t(2015, 10, 15, 0, 0, 0);
  end_time = Collaborator::create_time_t(2019, 10, 15, 0, 0, 0);
  work_years = -1;
  work_years = Collaborator::calculate_total_work_years(start_time, end_time);
  EXPECT_EQ(3, work_years);

  start_time = Collaborator::create_time_t(2015, 10, 15, 0, 0, 0);
  end_time = Collaborator::create_time_t(2019, 10, 16, 0, 0, 0);
  work_years = -1;
  work_years = Collaborator::calculate_total_work_years(start_time, end_time);
  EXPECT_EQ(4, work_years);

  // ToDo: add additional test cases...
}

// Verifies constructor Collaborator::Collaborator().
TEST(CollaboratorClassTest, Constructor)
{
  EXPECT_NO_THROW(Employee("Linus Torvalds"));

  Employee employee("Steve Jobs");

  Collaborator& collaborator = employee;

  EXPECT_STREQ(collaborator.get_name().c_str(), "Steve Jobs");
  EXPECT_EQ(collaborator.get_hire_date_time(), 0);
  EXPECT_DOUBLE_EQ(collaborator.get_base_rate(), Collaborator::s_default_base_rate);
  EXPECT_EQ(collaborator.get_chief().expired(), true);
  EXPECT_EQ(collaborator.get_subordinates().size(), 0);

  EXPECT_THROW(Employee(""), invalid_argument);
}

// Verifies functions: Collaborator::get_name(), Collaborator::set_name().
TEST(CollaboratorClassTest, NameProperty)
{
  Employee employee("Unknown");

  Collaborator& collaborator = employee;

  EXPECT_STREQ(collaborator.get_name().c_str(), "Unknown");

  EXPECT_THROW(collaborator.set_name(""), invalid_argument);
  EXPECT_STREQ(collaborator.get_name().c_str(), "Unknown");
  
  EXPECT_NO_THROW(collaborator.set_name("Bill Gates"));
  EXPECT_STREQ(collaborator.get_name().c_str(), "Bill Gates");
}

// Verifies functions: Collaborator::get_hire_date_time(), Collaborator::set_hire_date_time().
TEST(CollaboratorClassTest, HireDateTimeProperty)
{
  Employee employee("Unknown");

  Collaborator& collaborator = employee;

  EXPECT_EQ(collaborator.get_hire_date_time(), 0);

  collaborator.set_hire_date_time(666);
  EXPECT_EQ(collaborator.get_hire_date_time(), 666);
}

// Verifies functions: Collaborator::get_base_rate(), Collaborator::set_base_rate().
TEST(CollaboratorClassTest, BaseRateProperty)
{
  Employee employee("Unknown");

  Collaborator& collaborator = employee;

  EXPECT_DOUBLE_EQ(collaborator.get_base_rate(), Collaborator::s_default_base_rate);

  EXPECT_THROW(collaborator.set_base_rate(Collaborator::s_min_base_rate - FLT_EPSILON), invalid_argument);
  EXPECT_DOUBLE_EQ(collaborator.get_base_rate(), Collaborator::s_default_base_rate);
  
  EXPECT_NO_THROW(collaborator.set_base_rate(Collaborator::s_min_base_rate));
  EXPECT_DOUBLE_EQ(collaborator.get_base_rate(), Collaborator::s_min_base_rate);

  EXPECT_NO_THROW(collaborator.set_base_rate(Collaborator::s_min_base_rate + FLT_EPSILON));
  EXPECT_DOUBLE_EQ(collaborator.get_base_rate(), Collaborator::s_min_base_rate + FLT_EPSILON);

  EXPECT_NO_THROW(collaborator.set_base_rate(Collaborator::s_max_base_rate - FLT_EPSILON));
  EXPECT_DOUBLE_EQ(collaborator.get_base_rate(), Collaborator::s_max_base_rate - FLT_EPSILON);

  EXPECT_NO_THROW(collaborator.set_base_rate(Collaborator::s_max_base_rate));
  EXPECT_DOUBLE_EQ(collaborator.get_base_rate(), Collaborator::s_max_base_rate);

  EXPECT_THROW(collaborator.set_base_rate(Collaborator::s_max_base_rate + FLT_EPSILON), invalid_argument);
  EXPECT_DOUBLE_EQ(collaborator.get_base_rate(), Collaborator::s_max_base_rate);
}

// Verifies functions: Collaborator::get_chief(), Collaborator::_set_chief().
TEST(CollaboratorClassTest, ChiefProperty)
{
  shared_ptr<Collaborator> employee = make_shared<Employee>("Some Employee");

  EXPECT_EQ(employee->get_chief().expired(), true);

  shared_ptr<Collaborator> manager = make_shared<Manager>("Some Manager");

  Company company;
  company.hire(employee);
  company.hire(manager);
  company.add_subordinate(manager, employee);

  EXPECT_EQ(employee->get_chief().lock()== manager, true);
}

// Verifies functions: Collaborator::get_subordinates(), Collaborator::_add_subordinate().
// Collaborator::_remove_subordinate(), Collaborator::_remove_all_subordinates().
TEST(CollaboratorClassTest, SubordinatesProperty)
{
  shared_ptr<Collaborator> employee1 = make_shared<Employee>("Some Employee 1");

  EXPECT_EQ(employee1->get_subordinates().size(), 0);

  shared_ptr<Collaborator> employee2 = make_shared<Employee>("Some Employee 2");

  EXPECT_EQ(employee2->get_subordinates().size(), 0);

  shared_ptr<Collaborator> employee3 = make_shared<Employee>("Some Employee 3");  

  EXPECT_EQ(employee3->get_subordinates().size(), 0);

  shared_ptr<Collaborator> manager1 = make_shared<Manager>("Some Manager 1");

  EXPECT_EQ(manager1->get_subordinates().size(), 0);

  shared_ptr<Collaborator> manager2 = make_shared<Manager>("Some Manager 2");

  EXPECT_EQ(manager2->get_subordinates().size(), 0);

  shared_ptr<Collaborator> sales1 = make_shared<Sales>("Some Sales 1");

  EXPECT_EQ(sales1->get_subordinates().size(), 0);

  shared_ptr<Collaborator> sales2 = make_shared<Sales>("Some Sales 2");

  EXPECT_EQ(sales2->get_subordinates().size(), 0);
  
  Company company;
  company.hire(employee1);
  company.hire(employee2);
  company.hire(employee3);
  company.hire(manager1);
  company.hire(manager2);
  company.hire(sales1);
  company.hire(sales2);

  const auto& manager1_subordinates = manager1->get_subordinates();
  company.add_subordinate(manager1, employee1);
  company.add_subordinate(manager1, employee2);

  EXPECT_EQ(manager1_subordinates.size(), 2);
  EXPECT_EQ(manager1_subordinates[0] == employee1, true);
  EXPECT_EQ(manager1_subordinates[1] == employee2, true);

  const auto& sales1_subordinates = sales1->get_subordinates();
  company.add_subordinate(sales1, employee3);
  company.add_subordinate(sales1, manager2);
  company.add_subordinate(sales1, sales2);

  EXPECT_EQ(sales1_subordinates.size(), 3);
  EXPECT_EQ(sales1_subordinates[0] == employee3, true);
  EXPECT_EQ(sales1_subordinates[1] == manager2, true);
  EXPECT_EQ(sales1_subordinates[2] == sales2, true);

  EXPECT_EQ(sales1->has_in_subordination(manager2), true);
  company.remove_subordinate(sales1, manager2);
  EXPECT_EQ(sales1_subordinates.size(), 2);
  EXPECT_EQ(sales1->has_in_subordination(manager2), false);

  company.remove_all_subordinates(sales1);
  EXPECT_EQ(sales1_subordinates.size(), 0);
}

// Verifies function: Collaborator::has_in_subordination().
TEST(CollaboratorClassTest, HasInSubordination)
{
  shared_ptr<Collaborator> employee1 = make_shared<Employee>("Some Employee 1");

  shared_ptr<Collaborator> employee2 = make_shared<Employee>("Some Employee 2");

  shared_ptr<Collaborator> employee3 = make_shared<Employee>("Some Employee 3");

  shared_ptr<Collaborator> manager1 = make_shared<Manager>("Some Manager 1");

  shared_ptr<Collaborator> manager2 = make_shared<Manager>("Some Manager 2");

  shared_ptr<Collaborator> manager3 = make_shared<Manager>("Some Manager 3");

  shared_ptr<Collaborator> sales1 = make_shared<Sales>("Some Sales 1");

  shared_ptr<Collaborator> sales2 = make_shared<Sales>("Some Sales 2");

  Company company;
  company.hire(employee1);
  company.hire(employee2);
  company.hire(employee3);
  company.hire(manager1);
  company.hire(manager2);
  company.hire(manager3);
  company.hire(sales1);
  company.hire(sales2);  

  EXPECT_EQ(manager1->has_in_subordination(employee1), false); 
  company.add_subordinate(manager1, employee1);
  EXPECT_EQ(manager1->has_in_subordination(employee1), true);

  EXPECT_EQ(manager1->has_in_subordination(employee2), false);
  company.add_subordinate(manager1, employee2);
  EXPECT_EQ(manager1->has_in_subordination(employee2), true);

  EXPECT_EQ(manager1->has_in_subordination(manager2), false);
  company.add_subordinate(manager1, manager2);
  EXPECT_EQ(manager1->has_in_subordination(manager2), true);

  EXPECT_EQ(sales1->has_in_subordination(employee3), false);
  company.add_subordinate(sales1, employee3);
  EXPECT_EQ(sales1->has_in_subordination(employee3), true);

  EXPECT_EQ(sales1->has_in_subordination(manager3), false);
  company.add_subordinate(sales1, manager3);
  EXPECT_EQ(sales1->has_in_subordination(manager3), true);

  EXPECT_EQ(sales1->has_in_subordination(sales2), false);
  company.add_subordinate(sales1, sales2);
  EXPECT_EQ(sales1->has_in_subordination(sales2), true);
}

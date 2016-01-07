////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file manager_class_test.cpp
/// @brief Test of Manager class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "manager_class_test.h"

using namespace std;

using namespace My_company;

// Verifies function Manager::get_collaborator_type().
TEST(ManagerClassTest, GetCollaboratorType)
{
  Manager manager("Manager");

  EXPECT_EQ(manager.get_collaborator_type(), Collaborator_type::manager);
}

// Verifies function Manager::calculate_salary() for the case when manager has no subordinates.
TEST(ManagerClassTest, CalculateSalaryWithoutSubordinates)
{
  Manager manager("Manager");

  time_t hiring_time = 0;
  time_t salary_calculation_time = 0;
  double salary_actual = 0.0;
  double salary_expected = 0.0;

  // Invalid calculation time: earlier than hire time.
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  manager.set_hire_date_time(hiring_time);
  salary_calculation_time = hiring_time - 1;
  EXPECT_THROW(manager.calculate_salary(salary_calculation_time), invalid_argument);

  // 0 working years (0% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  manager.set_hire_date_time(hiring_time);
  salary_calculation_time = hiring_time;
  salary_expected = Test_utils::calculate_manager_salary(manager, salary_calculation_time);
  salary_actual = manager.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 0 working years (0% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  manager.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2016, 10, 18, 0, 0, 0);
  salary_expected = Test_utils::calculate_manager_salary(manager, salary_calculation_time);
  salary_actual = manager.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 1 working year (5% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  manager.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2016, 10, 19, 0, 0, 0);
  salary_expected = Test_utils::calculate_manager_salary(manager, salary_calculation_time);
  salary_actual = manager.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 7 working years (35% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  manager.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2022, 10, 19, 0, 0, 0);
  salary_expected = Test_utils::calculate_manager_salary(manager, salary_calculation_time);
  salary_actual = manager.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 8 working years (40% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  manager.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2023, 10, 19, 0, 0, 0);
  salary_expected = Test_utils::calculate_manager_salary(manager, salary_calculation_time);
  salary_actual = manager.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 9 working years (40% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  manager.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2024, 10, 19, 0, 0, 0);
  salary_expected = Test_utils::calculate_manager_salary(manager, salary_calculation_time);
  salary_actual = manager.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);
}

// Verifies function Manager::calculate_salary() for the case when manager has subordinates.
TEST(ManagerClassTest, CalculateSalaryWithSubordinates)
{
  shared_ptr<Collaborator> employee1 = make_shared<Employee>("Some Employee 1");
  employee1->set_hire_date_time(Collaborator::create_time_t(2014, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> employee2 = make_shared<Employee>("Some Employee 2");
  employee2->set_hire_date_time(Collaborator::create_time_t(2013, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> manager1 = make_shared<Manager>("Some Manager 1");
  manager1->set_hire_date_time(Collaborator::create_time_t(2012, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> manager2 = make_shared<Manager>("Some Manager 2");
  manager2->set_hire_date_time(Collaborator::create_time_t(2011, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> sales1 = make_shared<Sales>("Some Sales 1");
  sales1->set_hire_date_time(Collaborator::create_time_t(2010, 10, 18, 0, 0, 0));

  Company company;
  company.hire(employee1);
  company.hire(employee2);
  company.hire(manager1);
  company.hire(manager2);
  company.hire(sales1);

  company.add_subordinate(manager1, employee1);
  company.add_subordinate(manager1, manager2);
  company.add_subordinate(manager1, sales1);
  company.add_subordinate(manager2, employee2);
  
  time_t salary_calculation_time = Collaborator::create_time_t(2015, 10, 19, 0, 0, 0);
  double salary_expected = Test_utils::calculate_collaborator_salary(manager1, salary_calculation_time);
  double salary_actual = manager1->calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);
}

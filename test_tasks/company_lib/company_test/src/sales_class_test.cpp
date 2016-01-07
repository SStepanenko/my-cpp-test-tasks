////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file sales_class_test.cpp
/// @brief Test of Sales class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "sales_class_test.h"

using namespace std;

using namespace My_company;

// Verifies function Sales::get_collaborator_type().
TEST(SalesClassTest, GetCollaboratorType)
{
  Sales sales("Sales");

  EXPECT_EQ(sales.get_collaborator_type(), Collaborator_type::sales);
}

// Verifies function Sales::calculate_salary() for the case when sales has no subordinates.
TEST(SalesClassTest, CalculateSalaryWithoutSubordinates)
{
  Sales sales("Sales");

  time_t hiring_time = 0;
  time_t salary_calculation_time = 0;
  double salary_actual = 0.0;
  double salary_expected = 0.0;

  // Invalid calculation time: earlier than hire time.
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  sales.set_hire_date_time(hiring_time);
  salary_calculation_time = hiring_time - 1;
  EXPECT_THROW(sales.calculate_salary(salary_calculation_time), invalid_argument);

  // 0 working years (0% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  sales.set_hire_date_time(hiring_time);
  salary_calculation_time = hiring_time;
  salary_expected = Test_utils::calculate_sales_salary(sales, salary_calculation_time);
  salary_actual = sales.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 0 working years (0% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  sales.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2016, 10, 18, 0, 0, 0);
  salary_expected = Test_utils::calculate_sales_salary(sales, salary_calculation_time);
  salary_actual = sales.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 1 working year (1% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  sales.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2016, 10, 19, 0, 0, 0);
  salary_expected = Test_utils::calculate_sales_salary(sales, salary_calculation_time);
  salary_actual = sales.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 34 working years (34% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  sales.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2049, 10, 19, 0, 0, 0);
  salary_expected = Test_utils::calculate_sales_salary(sales, salary_calculation_time);
  salary_actual = sales.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 35 working years (35% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  sales.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2050, 10, 19, 0, 0, 0);
  salary_expected = Test_utils::calculate_sales_salary(sales, salary_calculation_time);
  salary_actual = sales.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 36 working years (35% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 18, 0, 0, 0);
  sales.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2051, 10, 19, 0, 0, 0);
  salary_expected = Test_utils::calculate_sales_salary(sales, salary_calculation_time);
  salary_actual = sales.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);
}

// Verifies function Sales::calculate_salary() for the case when sales has subordinates.
TEST(SalesClassTest, CalculateSalaryWithSubordinates)
{
  shared_ptr<Collaborator> employee1 = make_shared<Employee>("Some Employee 1");
  employee1->set_hire_date_time(Collaborator::create_time_t(2014, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> employee2 = make_shared<Employee>("Some Employee 2");
  employee2->set_hire_date_time(Collaborator::create_time_t(2013, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> employee3 = make_shared<Employee>("Some Employee 3");
  employee3->set_hire_date_time(Collaborator::create_time_t(2012, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> manager1 = make_shared<Manager>("Some Manager 1");
  manager1->set_hire_date_time(Collaborator::create_time_t(2011, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> manager2 = make_shared<Manager>("Some Manager 2");
  manager2->set_hire_date_time(Collaborator::create_time_t(2010, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> manager3 = make_shared<Manager>("Some Manager 3");
  manager3->set_hire_date_time(Collaborator::create_time_t(2009, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> sales1 = make_shared<Sales>("Some Sales 1");
  sales1->set_hire_date_time(Collaborator::create_time_t(2008, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> sales2 = make_shared<Sales>("Some Sales 2");
  sales2->set_hire_date_time(Collaborator::create_time_t(2007, 10, 18, 0, 0, 0));

  Company company;
  company.hire(employee1);
  company.hire(employee2);
  company.hire(employee3);
  company.hire(manager1);
  company.hire(manager2);
  company.hire(manager3);
  company.hire(sales1);
  company.hire(sales2);

  company.add_subordinate(sales1, employee1);
  company.add_subordinate(sales1, manager1);
  company.add_subordinate(sales1, sales2);
  company.add_subordinate(manager1, employee2);
  company.add_subordinate(sales2, manager2);
  company.add_subordinate(manager2, employee3);
  company.add_subordinate(manager2, manager3);  

  time_t salary_calculation_time = Collaborator::create_time_t(2015, 10, 19, 0, 0, 0);
  double salary_expected = Test_utils::calculate_collaborator_salary(manager1, salary_calculation_time);
  double salary_actual = manager1->calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);
}

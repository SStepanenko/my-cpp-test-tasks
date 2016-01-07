////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file employee_class_test.cpp
/// @brief Test of Employee class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "employee_class_test.h"

using namespace std;

using namespace My_company;

// Verifies function Employee::get_collaborator_type().
TEST(EmployeeClassTest, GetCollaboratorType)
{
  Employee employee("Employee");
  
  EXPECT_EQ(employee.get_collaborator_type(), Collaborator_type::employee);
}

// Verifies function Employee::calculate_salary().
TEST(EmployeeClassTest, CalculateSalary)
{
  Employee employee("Employee");

  time_t hiring_time = 0;
  time_t salary_calculation_time = 0;  
  double salary_actual = 0.0;
  double salary_expected = 0.0;

  // Invalid calculation time: earlier than hire time.
  hiring_time = Collaborator::create_time_t(2015, 10, 15, 14, 19, 23);
  employee.set_hire_date_time(hiring_time);
  salary_calculation_time = hiring_time - 1;
  EXPECT_THROW(employee.calculate_salary(salary_calculation_time), invalid_argument);

  // 0 working years (0% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 15, 14, 19, 23);
  employee.set_hire_date_time(hiring_time);
  salary_calculation_time = hiring_time;  
  salary_expected = Test_utils::calculate_employee_salary(employee, salary_calculation_time);
  salary_actual = employee.calculate_salary(salary_calculation_time);  
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 0 working years (0% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 15, 14, 19, 23);
  employee.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2016, 10, 15, 14, 19, 23);
  salary_expected = Test_utils::calculate_employee_salary(employee, salary_calculation_time);
  salary_actual = employee.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 1 working year (3% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 15, 14, 19, 23);
  employee.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2016, 10, 16, 14, 19, 23);
  salary_expected = Test_utils::calculate_employee_salary(employee, salary_calculation_time);
  salary_actual = employee.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 9 working years (27% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 15, 14, 19, 23);
  employee.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2024, 10, 16, 14, 19, 23);
  salary_expected = Test_utils::calculate_employee_salary(employee, salary_calculation_time);
  salary_actual = employee.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 10 working years (30% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 15, 14, 19, 23);
  employee.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2024, 10, 16, 14, 19, 23);
  salary_expected = Test_utils::calculate_employee_salary(employee, salary_calculation_time);
  salary_actual = employee.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  // 11 working years (30% salary increment for working years).
  hiring_time = Collaborator::create_time_t(2015, 10, 15, 14, 19, 23);
  employee.set_hire_date_time(hiring_time);
  salary_calculation_time = Collaborator::create_time_t(2026, 10, 16, 14, 19, 23);
  salary_expected = Test_utils::calculate_employee_salary(employee, salary_calculation_time);
  salary_actual = employee.calculate_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);
}

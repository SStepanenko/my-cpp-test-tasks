////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file test_utils.cpp
/// @brief Implementation of the Test_utils class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

using namespace std;

using namespace My_company;

double Test_utils::calculate_collaborator_salary(const shared_ptr<Collaborator>& collaborator,
  time_t calculation_time)
{
  assert(collaborator != nullptr);

  double salary = 0.0;

  switch (collaborator->get_collaborator_type())
  {
    case Collaborator_type::employee:
    {
      const Employee& employee = *(dynamic_cast<Employee*>(collaborator.get()));
      salary = calculate_employee_salary(employee, calculation_time);
      break;
    }    
    
    case Collaborator_type::manager:
    {
      const Manager& manager = *(dynamic_cast<Manager*>(collaborator.get()));
      salary = calculate_manager_salary(manager, calculation_time);  
      break;
    }    
    
    case Collaborator_type::sales:
    {
      const Sales& sales = *(dynamic_cast<Sales*>(collaborator.get()));
      salary = calculate_sales_salary(sales, calculation_time);      
      break;
    }    
      
    default:
    {
      // Unexpected case.
      assert(false);      
      break;
    }    
  }

  return salary;
}

double Test_utils::calculate_employee_salary(const My_company::Employee& employee, time_t calculation_time)
{
  int32_t work_years = Collaborator::calculate_total_work_years(employee.get_hire_date_time(), calculation_time);

  double salary_increment_percent = Employee::s_salary_increment_per_year_percent * work_years;

  if (salary_increment_percent > Employee::s_max_salary_increment_percent)
  {
    salary_increment_percent = Employee::s_max_salary_increment_percent;
  }

  double salary = employee.get_base_rate();
  salary += employee.get_base_rate() * (salary_increment_percent / 100.0);

  return salary;
}

double Test_utils::calculate_manager_salary(const Manager& manager, time_t calculation_time)
{
  int32_t work_years = Collaborator::calculate_total_work_years(manager.get_hire_date_time(), calculation_time);

  double salary_increment_percent = Manager::s_salary_increment_per_year_percent * work_years;

  if (salary_increment_percent > Manager::s_max_salary_increment_percent)
  {
    salary_increment_percent = Manager::s_max_salary_increment_percent;
  }

  double subordinates_salary = _calculate_total_first_level_subordinates_salary(manager, calculation_time);

  double salary = manager.get_base_rate();
  salary += manager.get_base_rate() * (salary_increment_percent / 100.0);
  salary += subordinates_salary * (Manager::s_first_level_subordinates_salary_increment_percent / 100.0);

  return salary;
}

double Test_utils::calculate_sales_salary(const Sales& sales, time_t calculation_time)
{
  int32_t work_years = Collaborator::calculate_total_work_years(sales.get_hire_date_time(), calculation_time);

  double salary_increment_percent = Sales::s_salary_increment_per_year_percent * work_years;

  if (salary_increment_percent > Sales::s_max_salary_increment_percent)
  {
    salary_increment_percent = Sales::s_max_salary_increment_percent;
  }

  double subordinates_salary = _calculate_total_all_levels_subordinates_salary(sales, calculation_time);

  double salary = sales.get_base_rate();
  salary += sales.get_base_rate() * (salary_increment_percent / 100.0);
  salary += subordinates_salary * (Sales::s_all_levels_subordinates_salary_increment_percent / 100.0);

  return salary;
}

double Test_utils::calculate_company_salary(const Company& company, time_t calculation_time)
{
  double total_salary = 0.0;

  const auto& collaborators = company.get_collaborators();

  for (const auto& collaborator : collaborators)
  {
    total_salary += Test_utils::calculate_collaborator_salary(collaborator, calculation_time);
  }

  return total_salary;
}

double Test_utils::_calculate_total_first_level_subordinates_salary(const Manager& manager, time_t calculation_time)
{
  double total_salary = 0.0;

  const vector<shared_ptr<Collaborator>>& subordinates = manager.get_subordinates();

  for (const shared_ptr<Collaborator>& collaborator : subordinates)
  {
    total_salary += calculate_collaborator_salary(collaborator, calculation_time);
  }

  return total_salary;
}

double Test_utils::_calculate_total_all_levels_subordinates_salary(const Sales& sales, time_t calculation_time)
{
  double total_salary = 0.0;

  const vector<shared_ptr<Collaborator>>& subordinates = sales.get_subordinates();

  for (const shared_ptr<Collaborator>& subordinate : subordinates)
  {
    _add_own_salary_and_all_levels_subordinates_salary(subordinate, calculation_time, total_salary);
  }

  return total_salary;
}

void Test_utils::_add_own_salary_and_all_levels_subordinates_salary(const shared_ptr<Collaborator>& collaborator,
  time_t calculation_time, double& total_salary)
{
  assert(collaborator != nullptr);

  total_salary += calculate_collaborator_salary(collaborator, calculation_time);

  const vector<shared_ptr<Collaborator>>& subordinates = collaborator->get_subordinates();

  for (const shared_ptr<Collaborator>& subordinate : subordinates)
  {
    _add_own_salary_and_all_levels_subordinates_salary(subordinate, calculation_time, total_salary);
  }
}

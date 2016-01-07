////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file employee.cpp
/// @brief Implementation of the Employee class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

namespace My_company
{

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Employee class members.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const float Employee::s_salary_increment_per_year_percent = 3.0f;

const float Employee::s_max_salary_increment_percent = 30.0f;

Employee::Employee(const std::string& name) :
 Collaborator(name)
{

}

Employee::~Employee()
{

}

Collaborator_type Employee::get_collaborator_type() const
{
  return Collaborator_type::employee;
}

double Employee::calculate_salary(time_t date_time) const
{
  if (date_time< get_hire_date_time())
  {
    throw invalid_argument("Argument date_time is invalid");
  }

  double salary_increment_percent = _get_salary_increment_for_work_years_percent(date_time); // exception

  double salary = get_base_rate();
  salary += get_base_rate() * (salary_increment_percent / 100.0);

  return salary;
}

float Employee::_get_salary_increment_for_work_years_percent(time_t date_time) const
{
  assert(date_time >= get_hire_date_time());

  int32_t work_years = Collaborator::calculate_total_work_years(get_hire_date_time(), date_time); // exception
  assert(work_years >= 0);

  float salary_increment_percent = s_salary_increment_per_year_percent * work_years;

  if (salary_increment_percent > s_max_salary_increment_percent)
  {
    salary_increment_percent = s_max_salary_increment_percent;
  }

  return salary_increment_percent;
}

} // My_company

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file sales.cpp
/// @brief Implementation of the Sales class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

namespace My_company
{

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sales class members.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const float Sales::s_salary_increment_per_year_percent = 1.0f;

const float Sales::s_max_salary_increment_percent = 35.0f;

const float Sales::s_all_levels_subordinates_salary_increment_percent = 0.3f;

Sales::Sales(const std::string& name) :
  Collaborator(name)
{

}

Sales::~Sales()
{

}

Collaborator_type Sales::get_collaborator_type() const
{
  return Collaborator_type::sales;
}

double Sales::calculate_salary(time_t date_time) const
{
  if (date_time< get_hire_date_time())
  {
    throw invalid_argument("Argument date_time is invalid");
  }

  double salary_increment_percent = _get_salary_increment_for_work_years_percent(date_time); // exception

  double subordinates_salary = _calculate_total_subordinates_salary(date_time); // exception

  double salary = get_base_rate();
  salary += get_base_rate() * (salary_increment_percent / 100.0);
  salary += subordinates_salary * (s_all_levels_subordinates_salary_increment_percent / 100.0);

  return salary;
}

float Sales::_get_salary_increment_for_work_years_percent(time_t date_time) const
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

double Sales::_calculate_total_subordinates_salary(time_t date_time) const
{
  double total_salary = 0.0;

  const vector<shared_ptr<Collaborator>>& subordinates = get_subordinates();

  for (const shared_ptr<Collaborator>& subordinate : subordinates)
  {
    subordinate->add_own_salary_and_all_levels_subordinates_salary(date_time, total_salary); // exception
  }

  return total_salary;
}

} // My_company

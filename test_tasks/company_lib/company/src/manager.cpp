////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file manager.cpp
/// @brief Implementation of the Manager class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

namespace My_company
{

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Manager class members.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const float Manager::s_salary_increment_per_year_percent = 5.0f;

const float Manager::s_max_salary_increment_percent = 40.0f;

const float Manager::s_first_level_subordinates_salary_increment_percent = 0.5f;

Manager::Manager(const std::string& name) :
  Collaborator(name)
{

}

Manager::~Manager()
{

}

Collaborator_type Manager::get_collaborator_type() const
{
  return Collaborator_type::manager;
}

double Manager::calculate_salary(time_t date_time) const
{
  if (date_time< get_hire_date_time())
  {
    throw invalid_argument("Argument date_time is invalid");
  }

  double salary_increment_percent = _get_salary_increment_for_work_years_percent(date_time); // exception

  double subordinates_salary = _calculate_total_first_level_subordinates_salary(date_time); // exception

  double salary = get_base_rate();
  salary += get_base_rate() * (salary_increment_percent / 100.0);
  salary += subordinates_salary * (s_first_level_subordinates_salary_increment_percent / 100.0);

  return salary;
}

float Manager::_get_salary_increment_for_work_years_percent(time_t date_time) const
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

double Manager::_calculate_total_first_level_subordinates_salary(time_t date_time) const
{
  double total_salary = 0.0;

  const vector<shared_ptr<Collaborator>>& subordinates = get_subordinates();

  for (const shared_ptr<Collaborator>& subordinate : subordinates)
  {
    total_salary += subordinate->calculate_salary(date_time); // exception
  }

  return total_salary;
}

} // My_company

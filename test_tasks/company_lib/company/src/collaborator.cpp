////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file collaborator.cpp
/// @brief Implementation of the Collaborator class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

namespace My_company
{

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Collaborator class members.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const double Collaborator::s_default_base_rate = 2000.0f;

const double Collaborator::s_min_base_rate = 1000.0f;

const double Collaborator::s_max_base_rate = 5000.0f;

const int32_t Collaborator::s_base_year = 1900;

const int32_t Collaborator::s_min_second = 0;

const int32_t Collaborator::s_max_second = 59;

const int32_t Collaborator::s_min_minute = 0;

const int32_t Collaborator::s_max_minute = 59;

const int32_t Collaborator::s_min_hour = 0;

const int32_t Collaborator::s_max_hour = 23;

const int32_t Collaborator::s_min_month_day = 1;

const int32_t Collaborator::s_max_month_day = 31;

const int32_t Collaborator::s_min_month = 1;

const int32_t Collaborator::s_max_month = 12;

time_t Collaborator::create_time_t(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute,
  int32_t second)
{
  if (year < 1900)
  {
    throw invalid_argument("Argument is out of range: year");
  }

  if (month < s_min_month || month > s_max_month)
  {
    throw invalid_argument("Argument is out of range: month");
  }

  if (day < s_min_month_day || day > s_max_month_day)
  {
    throw invalid_argument("Argument is out of range: day");
  }

  if (hour < s_min_hour || hour > s_max_hour)
  {
    throw invalid_argument("Argument is out of range: hour");
  }

  if (minute < s_min_minute || minute > s_max_minute)
  {
    throw invalid_argument("Argument is out of range: minute");
  }

  if (second < s_min_second || second > s_max_second)
  {
    throw invalid_argument("Argument is out of range: second");
  }

  // Create tm structure using given values.
  tm calendar_time;
  calendar_time.tm_sec = second;
  calendar_time.tm_min = minute;
  calendar_time.tm_hour = hour;
  calendar_time.tm_mday = day;
  calendar_time.tm_mon = month - 1;
  calendar_time.tm_year = year - s_base_year;
  calendar_time.tm_wday = 0; // not used
  calendar_time.tm_yday = 0; // not used
  calendar_time.tm_isdst = -1;
  
  // Create time_t value from calendar time.
  // Convert calendar time to a time since epoch as a time_t object
  time_t time = mktime(&calendar_time);
  
  if (time < 0)
  {
    throw runtime_error("Failed to create valid time from given components");
  }

  return time;
}

void Collaborator::convert_to_calendar_date_time(const time_t& time, tm& date_time)
{
  tm* date_time_ptr = localtime(&time);

  if (date_time_ptr == nullptr)
  {
    throw runtime_error("Time conversion error");
  }

  memcpy(&date_time, // destination
    date_time_ptr, // source
    sizeof(tm));
}

int32_t Collaborator::calculate_total_work_years(time_t start_time, time_t end_time)
{
  if (end_time < start_time)
  {
    throw invalid_argument("End time can't be earlier than start time");
  }

  tm start_date_time;
  convert_to_calendar_date_time(start_time, start_date_time); // exception

  tm end_date_time;
  convert_to_calendar_date_time(end_time, end_date_time); // exception  

  int32_t work_years = 0;

  int32_t years_difference = end_date_time.tm_year - start_date_time.tm_year;

  if (years_difference > 0)
  {
    if (end_date_time.tm_mon - start_date_time.tm_mon >= 0)
    {
      if (end_date_time.tm_mday - start_date_time.tm_mday > 0)
      {
        work_years = years_difference;
      }
      else
      {
        work_years = years_difference - 1;
      }      
    }
    else
    {
      work_years = years_difference - 1;
    }
  } // else do nothing  

  return work_years;
}

Collaborator::Collaborator(const std::string& name) : 
  m_hire_date_time(0),
  m_base_rate(s_default_base_rate)
{
  if (!_validate_name(name))
  {
    throw invalid_argument("Argument name is invalid");
  }

  m_name = name; // exception
}

Collaborator::~Collaborator()
{

}

const std::string& Collaborator::get_name() const
{
  return m_name;
}

void Collaborator::set_name(const std::string name)
{
  if (!_validate_name(name))
  {
    throw invalid_argument("Argument name is invalid");
  }

  m_name = name; // exception
}

const std::time_t Collaborator::get_hire_date_time() const
{
  return m_hire_date_time;
}

void Collaborator::set_hire_date_time(const std::time_t& hire_date_time)
{
  m_hire_date_time = hire_date_time;
}

double Collaborator::get_base_rate() const
{
  return m_base_rate;
}

void Collaborator::set_base_rate(double base_rate)
{
  if (base_rate < s_min_base_rate ||
    base_rate > s_max_base_rate)
  {
    throw invalid_argument("Argument base_rate is out of range");
  }

  m_base_rate = base_rate;
}

const weak_ptr<Collaborator>& Collaborator::get_chief() const
{
  return m_cheif;
}

const vector<shared_ptr<Collaborator>>& Collaborator::get_subordinates() const
{
  return m_subordinates;
}

bool Collaborator::has_in_subordination(const shared_ptr<Collaborator>& collaborator) const
{  
  auto iterator = find(m_subordinates.begin(), m_subordinates.end(), collaborator);

  bool result = (iterator != m_subordinates.end());

  return result;
}

void Collaborator::add_own_salary_and_all_levels_subordinates_salary(time_t date_time, double& total_salary) const
{
  total_salary += calculate_salary(date_time); // exception

  const vector<shared_ptr<Collaborator>>& subordinates = get_subordinates();

  for (const shared_ptr<Collaborator>& collaborator : subordinates)
  {
    collaborator->add_own_salary_and_all_levels_subordinates_salary(date_time, total_salary); // exception
  }
}

void Collaborator::_set_chief(const weak_ptr<Collaborator>& chief)
{ 
  // Employee can't be a chief.
  assert(chief.expired() || chief.lock()->get_collaborator_type() != Collaborator_type::employee);

  m_cheif = chief;
}

void Collaborator::_add_subordinate(const shared_ptr<Collaborator>& subordinate)
{
  // Employee can't have subordinates.
  assert(get_collaborator_type() != Collaborator_type::employee);
  assert(subordinate != nullptr);
  assert(subordinate->get_chief().expired());
  assert(!has_in_subordination(subordinate));

  m_subordinates.push_back(subordinate); // exception

  // Note: chief for subordinate should be set outside because we don't have shared_ptr to chief.  
}

void Collaborator::_remove_subordinate(const std::shared_ptr<Collaborator>& subordinate)
{
  // Employee can't have subordinates.
  assert(get_collaborator_type() != Collaborator_type::employee);
  assert(subordinate != nullptr);  

  auto subordinate_position_iterator = find(m_subordinates.begin(), m_subordinates.end(), subordinate);

  if (subordinate_position_iterator == m_subordinates.end())
  {
    throw invalid_argument("Given subordinate doesn't exist");
  }

  m_subordinates.erase(subordinate_position_iterator);
  
  subordinate->_set_chief(weak_ptr<Collaborator>());
}

void Collaborator::_remove_all_subordinates()
{
  // Employee can't have subordinates.
  assert(get_collaborator_type() != Collaborator_type::employee);

  for (const auto& collaborator : m_subordinates)
  {
    collaborator->_set_chief(weak_ptr<Collaborator>());
  }

  m_subordinates.clear();
}

bool Collaborator::_validate_name(const std::string& name)
{
  return !name.empty();
}

} // My_company

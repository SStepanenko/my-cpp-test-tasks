////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file company.cpp
/// @brief Implementation of the Company class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

namespace My_company
{

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Company class members.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Company::Company()
{

}

Company::~Company()
{

}

const vector<shared_ptr<Collaborator>>& Company::get_collaborators() const
{
  return m_collaborators;
}

void Company::hire(const shared_ptr<Collaborator>& new_collaborator)
{
  if (new_collaborator == nullptr)
  {
    throw invalid_argument("Argument new_collaborator is null");
  }

  if (is_in_staff(new_collaborator))
  {
    throw invalid_argument("New collaborator is already in staff");
  }

  if (!new_collaborator->get_chief().expired())
  {
    throw invalid_argument("New collaborator already has chief");
  }

  if (!new_collaborator->get_subordinates().empty())
  {
    throw invalid_argument("New collaborator already has subordinates");
  }

  m_collaborators.push_back(new_collaborator); // exception
}

void Company::fire(const std::shared_ptr<Collaborator>& collaborator)
{
  if (collaborator == nullptr)
  {
    throw invalid_argument("Argument collaborator is null");
  }

  auto collaborator_position_iterator = find(m_collaborators.begin(), m_collaborators.end(), collaborator);

  if (collaborator_position_iterator == m_collaborators.end())
  {
    throw invalid_argument("Given collaborator is not in staff");
  }

  // If chief exists remove this collaborator from chief's subordinates.
  if (!collaborator->get_chief().expired())
  {
    remove_subordinate(collaborator->get_chief().lock(), collaborator); // exception   
  }
  
  // Reset chief for all subordinates.
  for (const auto& subordinate : collaborator->get_subordinates())
  {
    subordinate->_set_chief(weak_ptr<Collaborator>());
  }

  // Remove collaborator from collection.
  m_collaborators.erase(collaborator_position_iterator);
}

void Company::remove_all_collaborators()
{
  m_collaborators.clear();
}

void Company::add_subordinate(const std::shared_ptr<Collaborator>& chief,
  const std::shared_ptr<Collaborator>& subordinate)
{
  if (chief == nullptr)
  {
    throw invalid_argument("Argument chief is null");
  }

  if (subordinate == nullptr)
  {
    throw invalid_argument("Argument subordinate is null");
  }

  if (chief->get_collaborator_type() == Collaborator_type::employee)
  {
    throw invalid_argument("Employee can't have subordinates");
  }

  if (!is_in_staff(chief))
  {
    throw invalid_argument("Chief is not in company's staff");
  }

  if (!is_in_staff(subordinate))
  {
    throw invalid_argument("Subordinate is not in company's staff");
  }

  if (!subordinate->get_chief().expired())
  {
    throw invalid_argument("Subordinate already has a chief");
  }

  if (chief->has_in_subordination(subordinate))
  {
    throw invalid_argument("Subordinate is already in chief's subordination");
  }

  chief->_add_subordinate(subordinate); // exception

  subordinate->_set_chief(weak_ptr<Collaborator>(chief));
}

void Company::remove_subordinate(const shared_ptr<Collaborator>& chief, const shared_ptr<Collaborator>& subordinate)
{
  if (chief == nullptr)
  {
    throw invalid_argument("Argument chief is null");
  }

  if (subordinate == nullptr)
  {
    throw invalid_argument("Argument subordinate is null");
  }

  if (chief->get_collaborator_type() == Collaborator_type::employee)
  {
    throw invalid_argument("Employee can't have subordinates");
  }

  if (!is_in_staff(chief))
  {
    throw invalid_argument("Chief is not in company's staff");
  }

  if (!is_in_staff(subordinate))
  {
    throw invalid_argument("Subordinate is not in company's staff");
  }

  if (subordinate->get_chief().lock() != chief)
  {
    throw invalid_argument("Subordinate has another chief");
  }

  chief->_remove_subordinate(subordinate); // exception
}

void Company::remove_all_subordinates(const std::shared_ptr<Collaborator>& chief)
{
  if (chief == nullptr)
  {
    throw invalid_argument("Argument chief is null");
  }

  if (chief->get_collaborator_type() == Collaborator_type::employee)
  {
    throw invalid_argument("Employee can't have subordinates");
  }

  chief->_remove_all_subordinates();
}

bool Company::is_in_staff(const std::shared_ptr<Collaborator>& collaborator) const
{
  auto collaborator_iterator = find(m_collaborators.begin(), m_collaborators.end(), collaborator);

  bool result = (collaborator_iterator != m_collaborators.end());

  return result;
}

double Company::calculate_total_salary(time_t date_time) const
{
  double total_salary = 0.0;

  for (const auto& collaborator : m_collaborators)
  {
    total_salary += collaborator->calculate_salary(date_time); // exception
  }

  return total_salary;
}

} // My_company
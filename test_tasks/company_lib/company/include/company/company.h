////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file company.h
/// @brief Interface of the Company class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMPANY_H_1BFE478A_EE53_487C_A8C2_711965F082ED
#define COMPANY_H_1BFE478A_EE53_487C_A8C2_711965F082ED

namespace My_company
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Company class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Company final
{
public:

  // Constructor.
  Company();

  // Destructor.
  ~Company();

  /// @brief Gets collaborators.
  /// @return Collection of collaborators.
  const std::vector<std::shared_ptr<Collaborator>>& get_collaborators() const;

  /// @brief Hires new collaborator.
  /// @param new_collaborator New collaborator.
  /// @exception invalid_argument: input argument is invalid.
  /// @exception bad_alloc: memory allocation error.
  void hire(const std::shared_ptr<Collaborator>& new_collaborator);

  /// @brief Fires collaborator.
  /// @param collaborator Ñollaborator which should be fired.
  /// @exception invalid_argument: input argument is invalid (null or not in staff).
  void fire(const std::shared_ptr<Collaborator>& collaborator);

  /// @brief Removes all collaborators.
  void remove_all_collaborators();

  /// @brief Adds subordinate to chief.
  ///        Note: Both chief and subordinate should be in company's staff.
  ///              Employee can't be a chief.
  ///              Subordinate shouldn't have a chief.
  ///              Chief shouldn't have this subordinate in subordination.
  /// @param chief Pointer to chief to whom subordinate should be added.
  /// @param subordinate Pointer to subordinate.
  /// @exception invalid_argument: either of input arguments is invalid.
  ///            bad_alloc: memory allocation error.        
  void add_subordinate(const std::shared_ptr<Collaborator>& chief, const std::shared_ptr<Collaborator>& subordinate);

  /// @brief Removes subordinate from chief's list of subordinates.
  ///        Both chief and subordinate should be in company's staff.
  ///        Subordinate should be in chief's subordination.
  /// @param chief Pointer to chief which has given subordinate.
  /// @param subordinate Pointer to subordinate.
  /// @exception invalid_argument: either of input arguments is invalid.
  void remove_subordinate(const std::shared_ptr<Collaborator>& chief, const std::shared_ptr<Collaborator>& subordinate);

  /// @brief Removes all subordinate from chief's list of subordinates.
  ///        Note: Employee can't be a chief.
  /// @param chief Pointer to chief.
  /// @exception invalid_argument: input arguments is invalid.
  void remove_all_subordinates(const std::shared_ptr<Collaborator>& chief);

  /// @brief Checks if given collaborator is in company's staff.
  /// @param collaborator Pointer to collaborator.
  /// @return Result of check.
  /// @exception invalid_argument: input argument is invalid.
  bool is_in_staff(const std::shared_ptr<Collaborator>& collaborator) const;

  /// @brief Calculates total salary of all collaborators.
  /// @param date_time Date and time moment for which salary should be calculated.
  /// @return Total salary of all collaborators.
  /// @exception invalid_argument: input argument is invalid
  ///            (time of calculation can't be earlier than hire date time of any collaborator).
  double calculate_total_salary(time_t date_time) const;

private:

  // Private methods.

  // Private copy constructor without implementation to prohibit using it.
  Company(const Company&);

  // Private assignment operator without implementation to prohibit using it.
  Company& operator=(const Company&);  

  // Private fields.

  std::vector<std::shared_ptr<Collaborator>> m_collaborators; ///< Collaborators.

};

} // My_company

#endif // COMPANY_H_1BFE478A_EE53_487C_A8C2_711965F082ED
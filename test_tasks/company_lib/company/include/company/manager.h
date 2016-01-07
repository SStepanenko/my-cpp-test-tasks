////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file manager.h
/// @brief Interface of the Manager class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MANAGER_H_22E8160B_B351_4DB8_A3EB_D4C55EF273E8
#define MANAGER_H_22E8160B_B351_4DB8_A3EB_D4C55EF273E8

namespace My_company
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Manager class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Manager final : public Collaborator
{
public:

  // Public methods.

  /// @brief Constructor.
  /// @param name Collaborator name.
  /// @exception invalid_argument: argument name is invalid (empty string).
  /// @exception bad_alloc.
  Manager(const std::string& name);

  /// @brief Destructor.
  virtual ~Manager();

  /// @brief Gets type of collaborator.
  /// @return Collaborator type.
  virtual Collaborator_type get_collaborator_type() const override;

  /// @brief Calculates salary for given date and time.
  /// @param date_time Date and time moment for which salary should be calculated.
  /// @return Calculated salary.
  /// @exception invalid_argument: date_time is out of range (can't be earlier then hiring time).
  /// @exception runtime_error: other error occurred.
  virtual double calculate_salary(time_t date_time) const override;  

  // Public static constants.

  static const float s_salary_increment_per_year_percent; ///< Salary increment (in percents) 
                                                          ///  for each year of working in a company.

  static const float s_max_salary_increment_percent; ///< Maximum salary increment in percents.

  static const float s_first_level_subordinates_salary_increment_percent; ///< Percent of total salary of
                                                                          ///  1-st level subordinates.

private:

  // Private methods.  

  // Private copy constructor without implementation to prohibit using it.
  Manager(const Manager&);

  // Private assignment operator without implementation to prohibit using it.
  Manager& operator=(const Manager&);

  // Gets salary increment for working years in percent from the base rate.
  // param date_time Date and time moment for which salary increment be calculated.
  // return Salary increment.
  // exception invalid_argument: date_time is out of range (can't be earlier then hiring time).
  // exception runtime_error: time conversion error.
  float _get_salary_increment_for_work_years_percent(time_t date_time) const;

  // Calculates total salary of the 1-st level subordinates.
  // param date_time Date and time moment for which salary should be calculated.
  // return Calculated total salary.
  // exception invalid_argument: date_time is out of range (can't be earlier then hiring time).
  // exception runtime_error: time conversion error.
  double _calculate_total_first_level_subordinates_salary(time_t date_time) const;
};

} // My_company

#endif // MANAGER_H_22E8160B_B351_4DB8_A3EB_D4C55EF273E8

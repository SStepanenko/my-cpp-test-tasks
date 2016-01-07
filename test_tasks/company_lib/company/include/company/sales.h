////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file sales.h
/// @brief Interface of the Sales class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SALES_H_D75761F5_8B66_410A_A212_F1F59F6CE59E
#define SALES_H_D75761F5_8B66_410A_A212_F1F59F6CE59E

namespace My_company
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sales class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Sales final : public Collaborator
{
public:

  // Public methods.

  /// @brief Constructor.
  /// @param name Collaborator name.
  /// @exception invalid_argument: argument name is invalid (empty string).
  /// @exception bad_alloc.
  Sales(const std::string& name);

  /// @brief Destructor.
  virtual ~Sales();

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

  static const float s_all_levels_subordinates_salary_increment_percent; ///< Percent of total salary of
                                                                         ///  all levels subordinates.

private:

  // Private methods.  

  // Private copy constructor without implementation to prohibit using it.
  Sales(const Sales&);

  // Private assignment operator without implementation to prohibit using it.
  Sales& operator=(const Sales&);

  // Gets salary increment for working years in percent from the base rate.
  // param date_time Date and time moment for which salary increment be calculated.
  // return Salary increment.
  // exception invalid_argument: date_time is out of range (can't be earlier then hiring time).
  // exception runtime_error: time conversion error.
  float _get_salary_increment_for_work_years_percent(time_t date_time) const;

  // Calculates total salary of all levels subordinates.
  // param date_time Date and time moment for which salary should be calculated.
  // return Calculated total salary.
  // exception invalid_argument: date_time is out of range (can't be earlier then hiring time).
  // exception runtime_error: time conversion error.
  double _calculate_total_subordinates_salary(time_t date_time) const;
};

} // My_company

#endif // SALES_H_D75761F5_8B66_410A_A212_F1F59F6CE59E

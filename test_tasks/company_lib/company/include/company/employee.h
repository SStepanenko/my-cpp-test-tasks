////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file employee.h
/// @brief Interface of the Employee class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EMPLOYEE_H_2B48FA96_3B29_4FE7_A251_73B7DA82C80B
#define EMPLOYEE_H_2B48FA96_3B29_4FE7_A251_73B7DA82C80B

namespace My_company
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Employee class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Employee final : public Collaborator
{
public:

  // Public methods.

  /// @brief Constructor.
  /// @param name Collaborator name.
  /// @exception invalid_argument: argument name is invalid (empty string).
  /// @exception bad_alloc.
  Employee(const std::string& name);

  /// @brief Destructor.
  virtual ~Employee();  

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

private:

  // Private methods.  

  // Private copy constructor without implementation to prohibit using it.
  Employee(const Employee&);

  // Private assignment operator without implementation to prohibit using it.
  Employee& operator=(const Employee&);

  // Gets salary increment for working years in percent from the base rate.
  // param date_time Date and time moment for which salary increment should be calculated.
  // return Calculated salary.
  // exception invalid_argument: date_time is out of range (can't be earlier then hiring time).
  // exception runtime_error: time conversion error.
  float _get_salary_increment_for_work_years_percent(time_t date_time) const;
};

} // My_company

#endif // EMPLOYEE_H_2B48FA96_3B29_4FE7_A251_73B7DA82C80B

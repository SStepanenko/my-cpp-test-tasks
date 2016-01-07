////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file collaborator.h
/// @brief Interface of the Collaborator class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COLLABORATOR_H_BF31C781_DC2D_4D6B_AD85_EAFBBF328DC8
#define COLLABORATOR_H_BF31C781_DC2D_4D6B_AD85_EAFBBF328DC8

namespace My_company
{

// Prior declaration.
class Company;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Enumeration Collaborator_type: defines type of collaborator.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class Collaborator_type
{
  employee, ///< Employee.
  manager,  ///< Manager.
  sales     ///< Sales.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Collaborator class: abstract class of collaborator.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Collaborator
{
  friend class Company;

public:

  // Public static methods.

  /// @brief Creates time_t value form given components.
  /// @exception invalid_argument: input argument is out of range.
  /// @exception runtime_error: failed to create valid time from given components.
  static time_t create_time_t(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second);

  /// @brief Converts time in time_t format to calendar date and time.
  ///        Note: function is thread unsafe.
  /// @param time Time in time_t format.
  /// @param [out] Calendar date and time in (tm structure).
  /// @exception runtime_error: time conversion error.
  static void convert_to_calendar_date_time(const time_t& time, tm& date_time);

  /// @brief Calculates total work years between two date and time values.
  /// @param start_time Start time.
  /// @param end_time End time.
  /// @exception invalid_argument: end time is earlier than start time.
  /// @exception runtime_error: error of time conversion.
  static int32_t calculate_total_work_years(time_t start_time, time_t end_time);  

  // Public methods.

  /// @brief Constructor.
  /// @param name Collaborator name.
  /// @exception invalid_argument: argument name is invalid (empty string).
  /// @exception bad_alloc.
  Collaborator(const std::string& name);
  
  /// @brief Destructor.
  virtual ~Collaborator();

  /// @brief Gets name.
  /// @return Name.
  const std::string& get_name() const;

  /// @brief Sets name.
  /// @param name Collaborator name.
  /// @exception invalid_argument: argument name is invalid (empty string).
  /// @exception bad_alloc.
  void set_name(const std::string name);

  /// @brief Gets date and time when collaborator was hired.
  /// @return Date and time.
  const std::time_t get_hire_date_time() const;

  /// @brief Sets date and time when collaborator was hired.
  /// @param hire_date_time Hiring date and time.
  void set_hire_date_time(const std::time_t& hire_date_time);

  /// @brief Gets base rate.
  /// @return Base rate.
  double get_base_rate() const;

  /// @brief Sets base rate.
  /// @param base_rate Base rate.
  /// @exception invalid_argument: input argument is out of range.
  void set_base_rate(double base_rate);

  /// @brief Gets chief.
  /// @return Pointer to chief.
  const std::weak_ptr<Collaborator>& get_chief() const;

  /// @brief Gets subordinates.
  /// @return Collection of subordinates.
  const std::vector<std::shared_ptr<Collaborator>>& get_subordinates() const;

  /// @brief Checks if given collaborator is in subordination.
  /// @return Result of check.
  bool has_in_subordination(const std::shared_ptr<Collaborator>& collaborator) const;

  /// @brief Adds own salary and salary of all levels subordinates to the output total_salary.
  /// @param date_time Date and time moment for which salary should be calculated.
  /// @param [in, out] total_salary Total salary.
  /// @exception invalid_argument: date_time is out of range (can't be earlier then hiring time).
  /// @exception runtime_error: other error occurred.
  void add_own_salary_and_all_levels_subordinates_salary(time_t date_time, double& total_salary) const;

  /// @brief Gets type of collaborator.
  /// @return Collaborator type.
  virtual Collaborator_type get_collaborator_type() const = 0;

  /// @brief Calculates salary for given date and time.
  /// @param date_time Date and time moment for which salary should be calculated.
  /// @return Calculated salary.
  /// @exception invalid_argument: date_time is out of range (can't be earlier then hiring time).
  /// @exception runtime_error: other error occurred.
  virtual double calculate_salary(time_t date_time) const = 0;

  // Public static constants.

  static const double s_default_base_rate; ///< Collaborator's default base rate.

  static const double s_min_base_rate; ///< Minimum valid base rate.

  static const double s_max_base_rate; ///< Maximum valid base rate.

  static const int32_t s_base_year; ///< Base year (1900).

  static const int32_t s_min_second; ///< Minimum valid seconds value.

  static const int32_t s_max_second; ///< Maximum valid seconds value.

  static const int32_t s_min_minute; ///< Minimum valid minutes value.

  static const int32_t s_max_minute; ///< Maximum valid minutes value.

  static const int32_t s_min_hour; ///< Minimum valid hours value.

  static const int32_t s_max_hour; ///< Maximum valid hours value.

  static const int32_t s_min_month_day; ///< Minimum valid day of month value.

  static const int32_t s_max_month_day; ///< Maximum valid day of month value.

  static const int32_t s_min_month; ///< Minimum valid month value.

  static const int32_t s_max_month; ///< Maximum valid month value.

protected:

  // Protected methods.

  // Sets chief.
  // param chief Pointer to chief.
  void _set_chief(const std::weak_ptr<Collaborator>& chief);  

  // Adds subordinate.
  // param subordinate Subordinate to add.
  // exception bad_alloc: memory allocation error.
  void _add_subordinate(const std::shared_ptr<Collaborator>& subordinate);
 
  // Removes subordinate.
  // param subordinate Subordinate to remove.
  // exception invalid_argument: Given subordinate doesn't exist.
  void _remove_subordinate(const std::shared_ptr<Collaborator>& subordinate);

  // Removes all subordinates.
  void _remove_all_subordinates();  

private:  

  // Private static methods.

  // Validates name and returns true if it is valid, otherwise -false.
  // Currently it just checks that name is not empty, but additional restrictions can be added if necessary.
  // param name Name for validation.
  // return Result of validation.
  static bool _validate_name(const std::string& name);  

  // Private methods.

  // Private copy constructor without implementation to prohibit using it.
  Collaborator(const Collaborator&);

  // Private assignment operator without implementation to prohibit using it.
  Collaborator& operator=(const Collaborator&);  

  // Private fields.

  std::string m_name; ///< Collaborator name.

  std::time_t m_hire_date_time; ///< Date and time when collaborator was hired.

  double m_base_rate; ///< Base rate.

  std::weak_ptr<Collaborator> m_cheif; ///< Chief.

  std::vector<std::shared_ptr<Collaborator>> m_subordinates; ///< Subordinates.
};

} // My_company

#endif // COLLABORATOR_H_BF31C781_DC2D_4D6B_AD85_EAFBBF328DC8

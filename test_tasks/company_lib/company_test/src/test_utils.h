////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file test_utils.h
/// @brief Interface of the Test_utils class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

class Test_utils final
{
public:

  // Public static methods.

  // Calculates collaborator's expected salary without using of Collaborator::calculate_salary() function.
  static double calculate_collaborator_salary(const std::shared_ptr<My_company::Collaborator>& collaborator,
    time_t calculation_time);
  
  // Calculates employee's expected salary without using of Collaborator::calculate_salary() function.
  static double calculate_employee_salary(const My_company::Employee& employee, time_t calculation_time);  

  // Calculates manager's expected salary without using of Collaborator::calculate_salary() function.
  static double calculate_manager_salary(const My_company::Manager& manager, time_t calculation_time);

  // Calculates sales's expected salary without using of Collaborator::calculate_salary() function.
  static double calculate_sales_salary(const My_company::Sales& sales, time_t calculation_time);

  // Calculates total salary of the whole company without using Company::calculate_total_salary() function.
  static double calculate_company_salary(const My_company::Company& company, time_t calculation_time);

private:

  // Private static methods.

  // Calculates total salary of the 1-st level subordinates.  
  static double _calculate_total_first_level_subordinates_salary(const My_company::Manager& manager,
    time_t calculation_time);

  // Calculates total salary of all levels subordinates.  
  static double _calculate_total_all_levels_subordinates_salary(const My_company::Sales& sales,
    time_t calculation_time);

  /// Adds own salary and salary of all levels subordinates to the output total_salary.  
  static void _add_own_salary_and_all_levels_subordinates_salary(
    const std::shared_ptr<My_company::Collaborator>& collaborator, time_t calculation_time, double& total_salary);
};

#endif // TEST_UTILS_H

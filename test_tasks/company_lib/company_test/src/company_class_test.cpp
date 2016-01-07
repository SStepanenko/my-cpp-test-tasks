////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file company_class_test.cpp
/// @brief Test of Company class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "company_class_test.h"

using namespace std;

using namespace My_company;

// Verifies constructor of the Company class.
TEST(CompanyClassTest, Constructor)
{  
  EXPECT_NO_THROW(Company());

  Company company;

  EXPECT_EQ(company.get_collaborators().size(), 0);
}

// Verifies function Company::get_collaborators().
TEST(CompanyClassTest, GetCollaborators)
{
  // ToDo: add test cases...
}

// Verifies function Company::hire().
TEST(CompanyClassTest, Hire)
{
  // ToDo: add test cases...
}

// Verifies function Company::fire().
TEST(CompanyClassTest, Fire)
{
  // ToDo: add test cases...
}

// Verifies function Company::remove_all_collaborators().
TEST(CompanyClassTest, RemoveAllCollaborators)
{
  // ToDo: add test cases...
}

// Verifies function Company::add_subordinate().
TEST(CompanyClassTest, AddSubordinate)
{
  // ToDo: add test cases...
}

// Verifies function Company::remove_subordinate().
TEST(CompanyClassTest, RemoveSubordinate)
{
  // ToDo: add test cases...
}

// Verifies function Company::remove_all_subordinates().
TEST(CompanyClassTest, RemoveAllSubordinates)
{
  // ToDo: add test cases...
}

// Verifies function Company::is_in_staff().
TEST(CompanyClassTest, IsInStaff)
{
  // ToDo: add test cases...
}

// Verifies function Company::calculate_total_salary().
TEST(CompanyClassTest, CalculateTotalSalary)
{
  shared_ptr<Collaborator> employee1 = make_shared<Employee>("Some Employee 1");
  employee1->set_hire_date_time(Collaborator::create_time_t(2014, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> employee2 = make_shared<Employee>("Some Employee 2");
  employee2->set_hire_date_time(Collaborator::create_time_t(2013, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> employee3 = make_shared<Employee>("Some Employee 3");
  employee3->set_hire_date_time(Collaborator::create_time_t(2012, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> manager1 = make_shared<Manager>("Some Manager 1");
  manager1->set_hire_date_time(Collaborator::create_time_t(2011, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> manager2 = make_shared<Manager>("Some Manager 2");
  manager2->set_hire_date_time(Collaborator::create_time_t(2010, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> manager3 = make_shared<Manager>("Some Manager 3");
  manager3->set_hire_date_time(Collaborator::create_time_t(2009, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> sales1 = make_shared<Sales>("Some Sales 1");
  sales1->set_hire_date_time(Collaborator::create_time_t(2008, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> sales2 = make_shared<Sales>("Some Sales 2");
  sales2->set_hire_date_time(Collaborator::create_time_t(2007, 10, 18, 0, 0, 0));

  shared_ptr<Collaborator> sales3 = make_shared<Sales>("Some Sales 3");
  sales3->set_hire_date_time(Collaborator::create_time_t(2006, 10, 18, 0, 0, 0));

  Company company;

  time_t salary_calculation_time = Collaborator::create_time_t(2015, 10, 19, 0, 0, 0);

  double salary_expected = 0.0;
  double salary_actual = company.calculate_total_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);

  company.hire(employee1);
  company.hire(employee2);
  company.hire(employee3);
  company.hire(manager1);
  company.hire(manager2);
  company.hire(manager3);
  company.hire(sales1);
  company.hire(sales2);
  company.hire(sales3);

  company.add_subordinate(sales1, employee1);
  company.add_subordinate(sales1, manager1);
  company.add_subordinate(sales1, sales2);
  company.add_subordinate(manager1, employee2);
  company.add_subordinate(sales2, manager2);
  company.add_subordinate(manager2, employee3);
  company.add_subordinate(manager2, manager3);
  company.add_subordinate(manager2, sales3);

  salary_expected = Test_utils::calculate_company_salary(company, salary_calculation_time);
  salary_actual = company.calculate_total_salary(salary_calculation_time);
  EXPECT_DOUBLE_EQ(salary_expected, salary_actual);
}

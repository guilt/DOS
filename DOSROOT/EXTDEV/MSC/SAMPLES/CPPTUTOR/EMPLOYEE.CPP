// EMPLOYEE.CPP

#include "employee.h"
#include <string.h>

// Employee member functions

Employee::Employee( const char *nm )
{
    strncpy( name, nm, 30 );
    name[29] = '\0';
}

char *Employee::getName() const
{
    return name;
}

// WageEmployee member functions

WageEmployee::WageEmployee( const char *nm )
    : Employee( nm )
{
    wage = 0.0;
    hours = 0.0;
}

void WageEmployee::setWage( float wg )
{
    wage = wg;
}

void WageEmployee::setHours( float hrs )
{
    hours = hrs;
}

float WageEmployee::computePay() const
{
    return wage * hours;
}

// SalesPerson member functions

SalesPerson::SalesPerson( const char *nm )
    : WageEmployee( nm )
{
    commission = 0.0;
    salesMade = 0.0;
}

void SalesPerson::setCommission( float comm )
{
    commission = comm;
}

void SalesPerson::setSales( float sales )
{
    salesMade = sales;
}

float SalesPerson::computePay() const
{
    // Call base class's version of computePay
    return WageEmployee::computePay() +
           commission * salesMade;
}

// Manager member functions

Manager::Manager( const char *nm )
    : Employee( nm )
{
    weeklySalary = 0.0;
}

void Manager::setSalary( float salary )
{
    weeklySalary = salary;
}

float Manager::computePay() const
{
    return weeklySalary;
}


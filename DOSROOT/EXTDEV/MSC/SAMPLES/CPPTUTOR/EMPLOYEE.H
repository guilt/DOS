// EMPLOYEE.H

// This is the final version of an example class from Chapter 7 of the
//     C++ Tutorial. This class demonstrates inheritance, overriding
//     members of a base class, and virtual functions (including a
//     pure virtual function).

#if !defined( _EMPLOYEE_H_ )

#define _EMPLOYEE_H_

class Employee
{
public:
    Employee( const char *nm );
    char *getName() const;
    virtual float computePay() const = 0;      // Pure virtual function
    virtual ~Employee() {}
private:
    char name[30];
};

class WageEmployee : public Employee
{
public:
    WageEmployee( const char *nm );
    void setWage( float wg );
    void setHours( float hrs );
    float computePay() const;     // Implicitly virtual
private:
    float wage;
    float hours;
};

class SalesPerson : public WageEmployee
{
public:
    SalesPerson( const char *nm );
    void setCommission( float comm );
    void setSales( float sales );
    float computePay() const;     // Implicitly virtual
private:
    float commission;
    float salesMade;
};

class Manager : public Employee
{
public:
    Manager( const char *nm );
    void setSalary( float salary );
    float computePay() const;     // Implicitly virtual
private:
    float weeklySalary;
};

#endif  // _EMPLOYEE_H_


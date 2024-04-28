// EMPLIST.CPP

// This is an example program that uses the Employee class from
//     Chapter 7 of the C++ Tutorial. This program defines the
//     EmployeeList class, which stores an array of Employee pointers,
//     and the EmpIter class, which defines an iterator for the
//     EmployeeList class. (See the PhoneList example class from Chapter
//     6 for more information about friend classes and iterators.)
//     The main function in this program allocates three different
//     types of Employee and adds them to an EmployeeList. The
//     computePayroll function adds up the salaries of all the Employees
//     in the list by calling the virtual computePay member function.

#include "employee.h"
#include <string.h>
#include <iostream.h>

const int MAXLENGTH = 100;

class EmployeeList
{
friend class EmpIter;
public:
    EmployeeList();
    int add( Employee *newEmp );
    Employee *search( const char *searchKey );
private:
    Employee *aray[MAXLENGTH];
    int firstEmpty;          // First unused element
};

class EmpIter
{
public:
    EmpIter( EmployeeList &m );
    Employee *getFirst();
    Employee *getLast();
    Employee *getNext();
    Employee *getPrev();
private:
    EmployeeList *const mine;     // Constant pointer to EmployeeList object
    int currIndex;
};


EmployeeList::EmployeeList()
{
    firstEmpty = 0;
}

int EmployeeList::add( Employee *newEmp )
{
    if( firstEmpty < MAXLENGTH - 1 )
    {
        aray[firstEmpty++] = newEmp;
        return 1;   // Indicate success
    }
    else return 0;
}

Employee *EmployeeList::search( const char *searchKey )
{
    for( int i = 0; i < firstEmpty; i++ )
        if( !strcmp( aray[i]->getName(), searchKey ) )
            return aray[i];

    return 0;
}

EmpIter::EmpIter( EmployeeList &m )
    : mine( &m )          // Initialize the constant member
{
    currIndex = 0;
}

Employee *EmpIter::getFirst()
{
    currIndex = 0;
    return mine->aray[currIndex];
}

Employee *EmpIter::getLast()
{
    currIndex = mine->firstEmpty - 1;
    return mine->aray[currIndex];
}

Employee *EmpIter::getNext()
{
    if( currIndex < mine->firstEmpty - 1 )
    {
        currIndex++;
        return mine->aray[currIndex];
    } 
    else return 0;
}

Employee *EmpIter::getPrev()
{
    if( currIndex > 0 )
    {
        currIndex--;
        return mine->aray[currIndex];
    }
    else return 0;
}

float computePayroll( EmployeeList &dept )
{
    float payroll = 0;
    Employee *person;
    EmpIter anIter( dept );

    person = anIter.getFirst();
    payroll += person->computePay();
    while( person = anIter.getNext() )
    {
        // Call appropriate function
        //     for each type of employee
        payroll += person->computePay();
    }

    return payroll;
}

void main()
{
    EmployeeList myDept;
    WageEmployee *wagePtr;
    SalesPerson *salePtr;
    Manager *mgrPtr;

    wagePtr = new WageEmployee( "Bill Shapiro" );
    wagePtr->setWage( 8.00 );
    wagePtr->setHours( 40.0 );
    salePtr = new SalesPerson( "John Smith" );
    salePtr->setWage( 8.00 );
    salePtr->setHours( 40.0 );
    salePtr->setSales( 2000.00 );
    salePtr->setCommission( 0.05 );
    mgrPtr = new Manager( "Mary Brown" );
    mgrPtr->setSalary( 1000.00 );

    myDept.add( wagePtr );
    myDept.add( salePtr );
    myDept.add( mgrPtr );

    cout << "payroll: " << computePayroll( myDept ) << '\n';
}

/* Module: Person
 * ----------
 * COMP.CS.110 FALL 2025
 * ----------
 * Implementation of the Person class.
 *
 * Author: Nabid Hasan
 * Student number: 152754330
 * Username: vmn388
 * E-Mail: nabid.hasan@tuni.fi
 * */

#include "person.hh"
#include "visit.hh"
#include <iostream>

Person::Person(string name) :
    name_(name)
{
    // cout << "Person constructor" << endl;
}

Person::~Person()
{
    // cout << "Person destructor" << endl;
}

string Person::getName() const
{
    return name_;
}

void Person::addVisit(shared_ptr<Visit> visit)
{
    visits_.push_back(visit);
}

const vector<shared_ptr<Visit>>& Person::getVisits() const
{
    return visits_;
}

shared_ptr<Visit> Person::getCurrentVisit() const
{
    for ( const auto& visit : visits_ )
    {
        if ( !visit->isClosed() )
        {
            return visit;
        }
    }
    return nullptr;
}

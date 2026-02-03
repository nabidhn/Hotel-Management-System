/* Module: Visit
 * ----------
 * COMP.CS.110 FALL 2025
 * ----------
 * Implementation of the Visit class.
 *
 * Author: Nabid Hasan
 * Student number: 152754330
 * Username: vmn388
 * E-Mail: nabid.hasan@tuni.fi
 * */

#include "visit.hh"
#include "utils.hh"
#include <iostream>

Visit::Visit(shared_ptr<Person> guest, shared_ptr<Room> room, const Date& start_date) :
    guest_(guest),
    room_(room),
    start_(start_date),
    end_(Date()) // Default date signifies an open visit
{
    // cout << "Visit constructor" << endl;
}

Visit::~Visit()
{
    // cout << "Visit destructor" << endl;
}

void Visit::setEndDate(const Date& end_date)
{
    end_ = end_date;
}

bool Visit::isClosed() const
{
    return !end_.is_default();
}

shared_ptr<Person> Visit::getGuest() const
{
    return guest_;
}

shared_ptr<Room> Visit::getRoom() const
{
    return room_;
}

Date Visit::getStartDate() const
{
    return start_;
}

Date Visit::getEndDate() const
{
    return end_;
}

/* Module: Room
 * ----------
 * COMP.CS.110 FALL 2025
 * ----------
 * Implementation of the Room struct.
 *
 * Author: Nabid Hasan
 * Student number: 152754330
 * Username: vmn388
 * E-Mail: nabid.hasan@tuni.fi
 *
 * */

#include "room.hh"
#include "person.hh"
#include <algorithm>

Room::Room(unsigned int id, unsigned int size) :
    id_(id),
    size_(size)
{
    // cout << "Room constructor" << endl;
}

unsigned int Room::getAvailableSpace() const
{
    return size_ - current_guests_.size();
}

bool Room::isFull() const
{
    return getAvailableSpace() == 0;
}

void Room::addGuest(shared_ptr<Person> guest)
{
    current_guests_.push_back(guest);
}

void Room::removeGuest()
{
    if ( !current_guests_.empty() )
    {
        current_guests_.pop_back();
    }
}

/* Module: Hotel
 * ----------
 * COMP.CS.110 FALL 2025
 * ----------
 * Implementation of the Hotel class.
 *
 * Author: Nabid Hasan
 * Student number: 152754330
 * Username: vmn388
 * E-Mail: nabid.hasan@tuni.fi
 * */

#include "hotel.hh"
#include "utils.hh"
#include <iostream>
#include <fstream>

// Error and information outputs
const string FILE_NOT_FOUND = "Error: Input file not found."s;
const string WRONG_FORMAT = "Error: Wrong format in file."s;
const string NOT_NUMERIC = "Error: Wrong type of parameters."s;
const string ALREADY_EXISTS = "Error: Already exists: "s;
const string CANT_FIND = "Error: Can't find anything matching: "s;
const string GUEST_ENTERED = "A new guest has entered."s;
const string GUEST_LEFT = "Guest left hotel, visit closed."s;
const string FULL = "Error: Can't book, no such rooms available."s;

const string NO_GUESTS = "None"s;

Hotel::Hotel()
{
    //cout << "Hotel constructor" << endl;
}

Hotel::~Hotel()
{
    //cout << "Hotel destructor" << endl;
}

bool Hotel::init()
{
    cout << "Input file: ";
    string file_name = "";
    getline(cin, file_name);
    ifstream file(file_name);
    if ( not file )
    {
        cout << FILE_NOT_FOUND << endl;
        return false;
    }

    string line = "";
    unsigned int room_counter = 1;
    while ( getline(file, line) )
    {
        vector<string> parts = utils::split(line, ';');
        if ( parts.size() != 2 )
        {
            cout << WRONG_FORMAT << endl;
            return false;
        }
        if ( not ( utils::is_numeric(parts.at(0), false) and
                utils::is_numeric(parts.at(1), false) ) )
        {
            cout << NOT_NUMERIC << endl;
            return false;
        }

        unsigned int amount = stoi(parts.at(1));
        for ( unsigned int i = 0; i < amount; ++i )
        {
            unsigned int size = stoi(parts.at(0));
            shared_ptr<Room> new_room = make_shared<Room>(room_counter, size);
            rooms_.push_back(new_room);
            ++room_counter;
        }
    }
    return true;
}

void Hotel::set_date(Params params)
{
    string day = params.at(0);
    string month = params.at(1);
    string year = params.at(2);
    if ( not utils::is_numeric(day, false) or
         not utils::is_numeric(month, false) or
         not utils::is_numeric(year, false) )
    {
        cout << NOT_NUMERIC << endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    cout << "Date has been set to ";
    utils::today.print();
    cout << endl;
}

void Hotel::advance_date(Params params)
{
    string amount = params.at(0);
    if ( not utils::is_numeric(amount, true) )
    {
        cout << NOT_NUMERIC << endl;
        return;
    }
    utils::today.advance(stoi(amount));
    cout << "New date is ";
    utils::today.print();
    cout << endl;
}

void Hotel::print_rooms(Params /*params*/)
{
    for ( const auto& room : rooms_ )
    {
        cout << "Room " << room->id_ << " : for " << room->size_ << " person(s) : ";
        if ( room->isFull() )
        {
            cout << "full" << endl;
        }
        else
        {
            cout << "available for " << room->getAvailableSpace() << " person(s)" << endl;
        }
    }
}

void Hotel::book(Params params)
{
    string guest_id = params.at(0);
    string room_size_str = params.at(1);
    if ( !utils::is_numeric(room_size_str, false) )
    {
        cout << NOT_NUMERIC << endl;
        return;
    }
    unsigned int room_size = stoi(room_size_str);

    if ( current_guests_.find(guest_id) != current_guests_.end() )
    {
        cout << ALREADY_EXISTS << guest_id << endl;
        return;
    }

    shared_ptr<Room> booked_room = find_best_room(room_size);
    if ( booked_room == nullptr )
    {
        cout << FULL << endl;
        return;
    }

    shared_ptr<Person> guest_ptr = nullptr;
    if ( all_guests_.find(guest_id) == all_guests_.end() )
    {
        guest_ptr = make_shared<Person>(guest_id);
        all_guests_[guest_id] = guest_ptr;
    }
    else
    {
        guest_ptr = all_guests_[guest_id];
    }

    shared_ptr<Visit> new_visit = make_shared<Visit>(guest_ptr, booked_room, utils::today);
    guest_ptr->addVisit(new_visit);
    booked_room->addGuest(guest_ptr);
    current_guests_[guest_id] = guest_ptr;

    cout << GUEST_ENTERED << endl;
}

void Hotel::leave(Params params)
{
    string guest_id = params.at(0);
    if ( current_guests_.find(guest_id) == current_guests_.end() )
    {
        cout << CANT_FIND << guest_id << endl;
        return;
    }

    shared_ptr<Person> guest_ptr = current_guests_[guest_id];
    shared_ptr<Visit> current_visit = guest_ptr->getCurrentVisit();
    if ( current_visit != nullptr )
    {
        current_visit->setEndDate(utils::today);
        current_visit->getRoom()->removeGuest();
    }
    current_guests_.erase(guest_id);

    cout << GUEST_LEFT << endl;
}


void Hotel::print_guest_info(Params params)
{
    string guest_id = params.at(0);
    if ( all_guests_.find(guest_id) == all_guests_.end() )
    {
        cout << CANT_FIND << guest_id << endl;
        return;
    }

    shared_ptr<Person> guest_ptr = all_guests_[guest_id];

    // Do NOT print the guest name here (fix)
    for ( const auto& visit : guest_ptr->getVisits() )
    {
        cout << "* Visit: ";
        visit->getStartDate().print();
        cout << " - ";
        if ( visit->isClosed() )
        {
            visit->getEndDate().print();
        }
        cout << endl;
    }
}

void Hotel::print_all_visits(Params /*params*/)
{
    if ( all_guests_.empty() )
    {
        cout << NO_GUESTS << endl;
        return;
    }

    vector<string> guest_names;
    for ( const auto& pair : all_guests_ )
    {
        guest_names.push_back(pair.first);
    }
    sort(guest_names.begin(), guest_names.end());

    for ( const string& name : guest_names )
    {
        // Print the guest name here
        cout << name << endl;
        print_guest_info({name});
    }
}


void Hotel::print_current_visits(Params /*params*/)
{
    if ( current_guests_.empty() )
    {
        cout << NO_GUESTS << endl;
        return;
    }

    vector<string> guest_names;
    for ( const auto& pair : current_guests_ )
    {
        guest_names.push_back(pair.first);
    }
    sort(guest_names.begin(), guest_names.end());

    for ( const string& name : guest_names )
    {
        shared_ptr<Person> guest_ptr = current_guests_[name];
        shared_ptr<Visit> current_visit = guest_ptr->getCurrentVisit();
        cout << name << " is boarded in Room " << current_visit->getRoom()->id_ << endl;
    }
}

void Hotel::print_honor_guests(Params /*params*/)
{
    if ( all_guests_.empty() )
    {
        cout << NO_GUESTS << endl;
        return;
    }

    unsigned int max_visits = 0;
    for ( const auto& pair : all_guests_ )
    {
        unsigned int visit_count = pair.second->getVisits().size();
        if ( visit_count > max_visits )
        {
            max_visits = visit_count;
        }
    }

    vector<string> honor_guests;
    for ( const auto& pair : all_guests_ )
    {
        if ( pair.second->getVisits().size() == max_visits )
        {
            honor_guests.push_back(pair.first);
        }
    }
    sort(honor_guests.begin(), honor_guests.end());

    cout << "With " << max_visits << " visit(s), the following guest(s) get(s) honorary award:" << endl;
    for ( const string& name : honor_guests )
    {
        cout << "* " << name << endl;
    }
}

shared_ptr<Room> Hotel::find_best_room(unsigned int size)
{
    shared_ptr<Room> best_room = nullptr;
    unsigned int min_guests = -1; // -1 to act as infinity for comparison

    for ( const auto& room : rooms_ )
    {
        if ( room->size_ == size )
        {
            if ( room->getAvailableSpace() > 0 )
            {
                if ( room->current_guests_.size() < min_guests )
                {
                    min_guests = room->current_guests_.size();
                    best_room = room;
                }
            }
        }
    }
    return best_room;
}

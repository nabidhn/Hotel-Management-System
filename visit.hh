/* Class Visit
 * ----------
 * COMP.CS.110 FALL 2025
 * ----------
 * Class for describing a guest's visit in hotel.
 *
 * File: visit.hh
 * Purpose: Defines the Visit class used in the Hotel project.
 *
 * Author: Nabid Hasan
 * Student number: 152754330
 * Username: vmn388
 * E-Mail: nabid.hasan@tuni.fi
 *
 * Notes about the program and its implementation:
 * This header defines the Visit class, which represents a guest’s visit
 * to the hotel. Each visit links a guest and a room,
 * along with the start and end dates of their stay.
 *
 * The class provides methods for:
 * Setting and checking the visit’s end date
 * Retrieving guest and room information
 * Accessing start and end dates
 *
 * Smart pointers are used to manage Person and Room associations safely,
 * ensuring automatic memory management
 *
 */

#ifndef VISIT_HH
#define VISIT_HH

#include "date.hh"
#include "person.hh"
#include "room.hh"

using namespace std;

class Visit
{
public:
    // TODO: Add parameters for the constructor if needed
    /**
     * @brief Visit
     * @param guest A shared pointer to the guest.
     * @param room A shared pointer to the room.
     * @param start_date The start date of the visit.
     */
    explicit Visit(shared_ptr<Person> guest, shared_ptr<Room> room, const Date& start_date);

    /**
     * @brief ~Visit
     * Destructor.
     */
    ~Visit();

    /**
     * @brief setEndDate
     * @param end_date The end date of the visit.
     * Sets the end date, closing the visit.
     */
    void setEndDate(const Date& end_date);

    /**
     * @brief isClosed
     * @return True if the visit has an end date, otherwise false.
     */
    bool isClosed() const;

    /**
     * @brief getGuest
     * @return A shared pointer to the guest of this visit.
     */
    shared_ptr<Person> getGuest() const;

    /**
     * @brief getRoom
     * @return A shared pointer to the room of this visit.
     */
    shared_ptr<Room> getRoom() const;

    /**
     * @brief getStartDate
     * @return The start date of the visit.
     */
    Date getStartDate() const;

    /**
     * @brief getEndDate
     * @return The end date of the visit.
     */
    Date getEndDate() const;



    // TODO: More public methods

private:
    shared_ptr<Person> guest_;
    shared_ptr<Room> room_;
    Date start_;
    Date end_;

    // TODO: More attributes and private methods
};

#endif // VISIT_HH

/* Class Person
 * ----------
 * COMP.CS.110 FALL 2025
 * ----------
 * File: person.hh
 * Purpose: Class for describing a guest in the hotel. Each guest has a unique
 * name and a record of all their visits.
 *
 * Author: Nabid Hasan
 * Student number: 152754330
 * Username: vmn388
 * E-Mail: nabid.hasan@tuni.fi
 *
 * Notes about the program and its implementation:
 * This header defines the Person class, which represents a hotel guest.
 * Each guest has a unique name and a list of all visits they have made
 * to the hotel. The class provides methods for adding visits, retrieving
 * all visits, and finding the guest’s current visit.
 *
 * Smart pointers are used to manage Visit objects safely and efficiently,
 * ensuring proper memory handling throughout the program.
 *
 */


#ifndef PERSON_HH
#define PERSON_HH

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Visit;

using namespace std;

class Person
{
public:
    /**
     * @brief Person
     * @param name The unique identifier of the guest.
     */
    explicit Person(string name);

    /**
     * @brief Destructor
     */
    ~Person();

    /**
     * @brief getName
     * @return The name of the guest.
     */
    string getName() const;

    /**
     * @brief addVisit
     * @param visit A shared pointer to the new visit.
     * Adds a new visit to the guest's record.
     */
    void addVisit(shared_ptr<Visit> visit);

    /**
     * @brief getVisits
     * @return A vector of shared pointers to all of the guest's visits.
     */
    const vector<shared_ptr<Visit>>& getVisits() const;

    /**
     * @brief getCurrentVisit
     * @return A shared pointer to the guest's current, open visit, or nullptr if none exists.
     */
    shared_ptr<Visit> getCurrentVisit() const;

private:
    string name_;
    vector<shared_ptr<Visit>> visits_;
};

#endif // PERSON_HH

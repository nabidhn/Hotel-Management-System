/* Struct Room
 * ----------
 * COMP.CS.110 FALL 2025
 *
 * File: room.hh
 * Purpose: Struct for describing a hotel room..
 *
 * Author: Nabid Hasan
 * Student number: 152754330
 * Username: vmn388
 * E-Mail: nabid.hasan@tuni.fi
 *
 * Notes about the program and its implementation:
 * This header defines the Room structure, which represents a single hotel room.
 * Each room has a fixed size (capacity) and can have one or more guests at a time.
 * The struct provides basic functionality for checking available space,
 * adding guests, and removing them when they leave.
 * Uses smart pointer to track guests, allowing multiple guests per room.
 * This approach enables accurate space calculation
 *
 * */



#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <memory>
#include <iostream>

class Person;

using namespace std;

struct Room
{
    /**
     * @brief Room
     * @param id The unique room number.
     * @param size The maximum number of guests the room can accommodate.
     */
    explicit Room(unsigned int id, unsigned int size);

    /**
     * @brief getAvailableSpace
     * @return The number of available spots in the room.
     */
    unsigned int getAvailableSpace() const;

    /**
     * @brief isFull
     * @return True if the room is full, otherwise false.
     */
    bool isFull() const;

    /**
     * @brief addGuest
     * @param guest A shared pointer to the guest to be added.
     * Adds a guest to the room's current occupants.
     */
    void addGuest(shared_ptr<Person> guest);

    /**
     * @brief removeGuest
     * Removes a guest from the room's current occupants.
     */
    void removeGuest();

    unsigned int id_;
    unsigned int size_;
    vector<shared_ptr<Person>> current_guests_;
};

#endif // ROOM_H

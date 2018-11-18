#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <stdexcept>
#include <SFML/Graphics.hpp>

using namespace std::literals;

#include "defs.h"

class Manager_Error : public std::logic_error
{
    using std::logic_error::logic_error;
};

/*
 * A templated class which handles resources of type 'T'.
 * Requirements on T:
 * - must be default-constructible
 * - must have a function named 'loadFromFile' which takes only a string as argument.
 * The function 'load' opens a resource and returns a reference to it.
 * If load on this file has already been called, then it will return the same instance
 * that was loaded before, instead of opening it again.
 *
 * When working with many external resources such as images,
 * fonts, sounds etc. we want to make sure that we only load each resource into
 * memory only once. If we open the same file multiple times this could lead
 * to memory leaks (for example if we load a file each iteration of the game-loop),
 * and could also slow down the game quite alot since we have to load the same
 * data over and over again.
 *
 * This type of class might therefore be useful to help us handle SFML-specific
 * resources and counteract the potential troubles we might run into when doing
 * the work manually.
 *
 * Usage:
 * Say that we want to load the player sprite which is located in the file
 * 'player.png'. Then we simply call 'Manager<sf::Texture>::load ("player.png")'
 * and a texture reference will be returned. This texture can now be passed on
 * to, for example a sprite as such:
 * sprite.setTexture (Manager<sf::Texture>::load ("player.png"));
 *
 */
template <typename T>
class Manager
{

public:

    /*
     * Loads an external resource into memory by calling 'loadFromFile'
     * on the class which represents the resource (i.e. the type T).
     */
    static T & load (const std::string & file);

    /*
     * Unloads the external resource if it is not needed anymore.
     * Very important to call whenever possible so that we reduce
     * the memory footprint of our game.
     *
     * Warning: this will invalidate all references to the resource being
     * unloaded.
     */
    static void unload (const std::string & file);

private:

    /*
     * Store all opened resources in memory associated with its filename.
     * Since the order it is stored in is of no relevance we use an
     * unordered_map instead of a regular map.
     *
     * std::unordered_map is in general more efficient than std::map
     * since we do not care in what order it is stored, thus allowing
     * it to store in whatever way the implementers of the standard
     * library decided was the most efficient.
     */
    static std::unordered_map <std::string, ptr<T>> table;
    
};

/*
 * Some aliases are supplied to increase the readability of the code.
 */
using Texture_Manager = Manager <sf::Texture>;
using Font_Manager    = Manager <sf::Font>;

// Since this is a templated class, the implementation must be
// available in all translation units. Therefore we include the
// implementation in the header file.
#include "details/Manager.tpp"

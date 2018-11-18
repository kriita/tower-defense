#pragma once

#include <SFML/Graphics.hpp>

#include <string>

/*
 * A spritesheet is a image which contains many,
 * smaller subimages. Spritesheets are a useful way to
 * reduce the amount of images we have to load in order
 * to retrieve all the necessary graphics for the game.
 *
 * They also increase performance of the game since
 * we do not need to open a new image file whenever
 * we want to change a sprite.
 *
 * Spritesheets are often constructed in a grid of
 * equally sized images. Often animations of sprites
 * are stored in sequence within these spritesheets
 * which means that animations are quite easy to
 * manage, since we simply look at the next sprite
 * in the spritesheet.
 *
 * This class loads an image into memory and can,
 * using the specified sprite size, create sprites
 * from the subimages in the spritesheet.
 *
 * A very basic example of a spritesheet can be
 * seen in "resources/images/balls.png"
 */
class Spritesheet
{

public:

    /*
     * Construct a new spritesheet ontop of the 'file' image,
     * where each sprite has the specified 'width' and 'height'.
     */
    Spritesheet (std::string const & file, unsigned width, unsigned height);

    /*
     * This functions creates a new sprite instance from the
     * spritesheet.
     *
     * The returned sprite will be of the image at the specified
     * 'row' and column 'col' within the grid in the spritesheet.
     */
    sf::Sprite get_sprite (unsigned row, unsigned col) const;

    /*
     * Get how big sprites in this spritesheet are.
     */
    sf::Vector2u sprite_size () const;

    /*
     * Get the size of the grid in the spritesheet.
     */
    sf::Vector2u sheet_size () const;
    
private:

    /*
     * Helper function which creates a rectangle of appropriate
     * size in the spritesheet at the specified sprite in the
     * grid.
     */
    sf::IntRect create_rect (unsigned row, unsigned col) const;

    /*
     * Keep a reference of the loaded texture which contains
     * the spritesheet.
     */
    sf::Texture & texture;

    /*
     * Remember how big each sprite in the spritesheet is.
     */
    unsigned      width;
    unsigned      height;
    
};

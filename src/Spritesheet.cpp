#include "Spritesheet.h"
#include "Manager.h"

using namespace sf;

/*
 * Use the Texture_Manager (see Manager.h for details) to
 * load the specified image 'file'.
 */
Spritesheet :: Spritesheet (std::string const & file,
                            unsigned            width,
                            unsigned            height)
    : texture { Texture_Manager :: load (file) },
      width { width },
      height { height }
{
}

/*
 * sf::Sprite represents a smaller image on screen
 * which has a position, size, rotation etc. (see
 * SFML documentaion for more details).
 *
 * In this function we use built-in functionality
 * of sf::Sprite which allows it to only show
 * a smaller part of the full texture.
 *
 * The first argument to the sf::Sprite constructor
 * is the texture which it should draw, and the
 * second argument specifies the area of the texture
 * which should be visible (by default it its the
 * entire texture, but in this case we only want
 * a small part, since this is a spritesheet).
 */
Sprite Spritesheet :: get_sprite (unsigned row,
                                  unsigned col) const
{
    return Sprite { texture, create_rect (row, col) };
}

Vector2u Spritesheet :: sprite_size () const
{
    return Vector2u { width, height };
}

Vector2u Spritesheet :: sheet_size () const
{
    auto size { texture.getSize () };
    return Vector2u { size.x / width, size.y / height };
}

IntRect Spritesheet :: create_rect (unsigned row,
                                    unsigned col) const
{
    // sf::Sprite requires sf::IntRects, so we have
    // to down-cast our unsigned values to int
    return IntRect {
        static_cast<int> (width * col),
	static_cast<int> (height * row),
        static_cast<int> (width),
        static_cast<int> (height)
    };
}

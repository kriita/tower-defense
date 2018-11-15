#include <SFML/Graphics.hpp>
#include "map.h"
#include "tile.h"
#include "tower.h"

using namespace sf;

int const width  {800};
int const height {600};

int main()
{
    bool fullscreen {false};

    RenderWindow window {
        VideoMode { width, height },
        "SFML DEMO"
    };

    Map m {"map.dat"};

    Clock clock;
    double const fps {60.0};
    auto const target {milliseconds (1000.0 / fps)};

    while (window.isOpen ())
    {
        clock.restart ();
        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed)
            {
                window.close ();
            }
        }
        if (Keyboard::isKeyPressed (Keyboard::Key::F))
        {
            fullscreen = !fullscreen;
            window.create(
                VideoMode { width, height },
                "SFML DEMO",
                (fullscreen ? Style::Fullscreen : Style::Close)
            );
        }

        window.clear();
        m.render(window);
        window.display ();

        auto wait_time {target - clock.getElapsedTime ()};
        sleep (wait_time);
    }
}
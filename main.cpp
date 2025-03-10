// Copyright 2024 Sanjana Singh
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
    // Create the render window
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Scooby Doo in SFML");

    // Red circle shape
    sf::CircleShape shape(80.f);
    shape.setFillColor(sf::Color::Red);
    float window_width = window.getSize().x;
    float circle_width = shape.getGlobalBounds().width;
    shape.setPosition(window_width - circle_width, 40);

    // Load background texture from file
    sf::Texture bg_texture;
    if (!bg_texture.loadFromFile("background.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite background(bg_texture);

    // Load sprite texture from file
    sf::Texture sprite_texture;
    if (!sprite_texture.loadFromFile("sprite.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(sprite_texture);
    sprite.setScale(0.3f, 0.3f);
    sprite.setPosition(50, 50);

    // Load ghost texture from file
    sf::Texture ghost_texture;
    if (!ghost_texture.loadFromFile("ghost.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite ghost(ghost_texture);
    ghost.setScale(0.05f, 0.05f);
    sf::Vector2f initial_position(20, 20);
    ghost.setPosition(initial_position);

    // Speed movements
    float ghost_speed = 1.0f;
    float speed = 2.0f;

    // Load sound for ghost
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sound.wav")) {
        return EXIT_FAILURE;
    }
    sf::Sound ghost_sound;
    ghost_sound.setBuffer(buffer);
    ghost_sound.play();
    ghost_sound.setLoop(true);  // Set sound to loop

    while (window.isOpen()) {
        sf::Event event;
        std::cout << "X = " << sprite.getPosition().x
                  << " Y = " << sprite.getPosition().y << std::endl;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Move sprite based on key pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            if (sprite.getPosition().x > 0) {
                sprite.move(-speed, 0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (sprite.getPosition().x < 792) {
                sprite.move(speed, 0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
            if (sprite.getPosition().y > 2) {
                sprite.move(0, -speed);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (sprite.getPosition().y < 280) {
                sprite.move(0, speed);
            }
        }

        // Move ghost across the window and reset
        ghost.move(ghost_speed, 0);
        if (ghost.getPosition().x > window.getSize().x) {
            ghost.setPosition(initial_position);
        }

        // Clear and draw everything
        window.clear();
        window.draw(background);
        window.draw(sprite);
        window.draw(shape);
        window.draw(ghost);
        window.display();
    }

    return 0;
}

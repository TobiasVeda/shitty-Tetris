#include "controller/Process.h"
#include <SFML/Graphics.hpp>


//TODO: QUICK: Error handling when not finding texture(throw catch), Blockbag cant be static -1y
//TODO: QUICK: Lisens, gule linjer (destructor),

//TODO: MID(maybe): fix collision,
//TODO: SLOW: resize:(
//join, detach,
//spør: gule linjer (destructor), mutex, UI magic numbers
// tre mutex?, hvis ja fiks winner/loser i loop

int main(){

    sf::RenderWindow window;
    window.create(sf::VideoMode(1920, 1080), "shitty Tetris");

    auto process = new Process(&window);

    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                process->closed();
            }

            if (event.type == sf::Event::KeyReleased){
               process->key_released(event.key.code);
            }
            if (event.type == sf::Event::LostFocus){
                process->lost_focus();
            } else if (event.type == sf::Event::GainedFocus){
                process->gained_focus();
            }

            if (event.type == sf::Event::Resized){
                process->resized(event.size.width, event.size.height);
            }

            if (event.type == sf::Event::MouseButtonPressed){
                process->mouse_pressed(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::MouseMoved){
                process->mouse_moved(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::JoystickButtonPressed){
                process->joystick_pressed(event.joystickButton.joystickId, event.joystickButton.button);
            }
            if (event.type == sf::Event::JoystickMoved){
                unsigned int id = event.joystickButton.joystickId;
                float x = sf::Joystick::getAxisPosition(id, sf::Joystick::X);
                float y = sf::Joystick::getAxisPosition(id, sf::Joystick::Y);
                process->joystick_moved(id, x, y);
            }

            if (event.type == sf::Event::KeyPressed){
                process->key_pressed(event.key.code);
            }
        }
    }
}
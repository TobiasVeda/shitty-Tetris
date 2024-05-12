//
// Created by tobia on 20.04.2024.
//
#include <SFML/Graphics.hpp>
#include "Base_shape.h"
#include "../Constants.h"
#include <list>

std::list<sf::RectangleShape> Base_shape::get_rectangle_list() {
    return std::list<sf::RectangleShape>{_r1, _r2, _r3, _r4};
}

void Base_shape::place(){
    _placed = true;
}

bool Base_shape::intersects(sf::RectangleShape &rectangle){
    bool r1_intersect = _r1.getGlobalBounds().intersects(rectangle.getGlobalBounds());
    bool r2_intersect = _r2.getGlobalBounds().intersects(rectangle.getGlobalBounds());
    bool r3_intersect = _r3.getGlobalBounds().intersects(rectangle.getGlobalBounds());
    bool r4_intersect = _r4.getGlobalBounds().intersects(rectangle.getGlobalBounds());

    if (r1_intersect || r2_intersect || r3_intersect || r4_intersect){
        return true;
    } else{
        return false;
    }
}

void Base_shape::rotate(int angle){
    _r1.rotate(angle);
    _r2.rotate(angle);
    _r3.rotate(angle);
    _r4.rotate(angle);
}


void Base_shape::move(sf::Vector2f) {
    if (direction == Constants::Down) {

        _r1.move(down);
        _r2.move(down);
        _r3.move(down);
        _r4.move(down);

    } else if (direction == Constants::Right) {

        _r1.move(right);
        _r2.move(right);
        _r3.move(right);
        _r4.move(right);
    } else if (direction == Constants::Left) {

        _r1.move(left);
        _r2.move(left);
        _r3.move(left);
        _r4.move(left);
    }
}
bool Base_shape::is_placed() const{
    return _placed;
}

void Base_shape::draw(sf::RenderTarget& target, sf::RenderStates states) const{
        states.texture = &_sprite;
        target.draw(_r1, states);

        states.texture = &_sprite;
        target.draw(_r2, states);

        states.texture = &_sprite;
        target.draw(_r3, states);

        states.texture = &_sprite;
        target.draw(_r4, states);
}

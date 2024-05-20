//
// Created by tobia on 20.04.2024.
//
#include <SFML/Graphics.hpp>
#include "Base_shape.h"
#include <list>

std::list<sf::RectangleShape> Base_shape::get_rectangle_list() {
    return std::list<sf::RectangleShape>{_r1, _r2, _r3, _r4};
}

void Base_shape::place(){
    _placed = true;
}

bool Base_shape::intersects(sf::RectangleShape &rectangle) const{
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

void Base_shape::rotate(float degree){
    _r1.rotate(degree);
    _r2.rotate(degree);
    _r3.rotate(degree);
    _r4.rotate(degree);
}

void Base_shape::move(sf::Vector2f direction){
        _r1.move(direction);
        _r2.move(direction);
        _r3.move(direction);
        _r4.move(direction);
}

void Base_shape::set_position(sf::Vector2f position){
        _r1.setPosition(position);
        _r2.setPosition(position);
        _r3.setPosition(position);
        _r4.setPosition(position);
}

bool Base_shape::is_placed() const{
    return _placed;
}

Constants::Block_types Base_shape::get_blocktype() const{
    return _type;
}

void Base_shape::draw(sf::RenderTarget& target, sf::RenderStates states) const{

        states.texture = &_texture;
        target.draw(_r1, states);

        states.texture = &_texture;
        target.draw(_r2, states);

        states.texture = &_texture;
        target.draw(_r3, states);

        states.texture = &_texture;
        target.draw(_r4, states);
}

bool Base_shape::load() {
    return true;
}

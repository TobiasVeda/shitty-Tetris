//
// Created by tobia on 20.04.2024.
//

#ifndef TILEMAP_BASE_SHAPE_H
#define TILEMAP_BASE_SHAPE_H

#include <SFML/Graphics.hpp>
#include "../Constants.h"
#include <list>


class Base_shape : public sf::Drawable, public sf::Transformable{

protected:
    sf::RectangleShape _r1;
    sf::RectangleShape _r2;
    sf::RectangleShape _r3;
    sf::RectangleShape _r4;

    sf::Transform _transform;
    sf::Texture _sprite;
    bool _placed;

public:
    std::list<sf::RectangleShape> get_rectangle_list();
    void place();
    void rotate(int);
    void move(sf::Vector2f);
    bool intersects(sf::RectangleShape&);
    [[nodiscard]] bool is_placed() const;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif //TILEMAP_BASE_SHAPE_H

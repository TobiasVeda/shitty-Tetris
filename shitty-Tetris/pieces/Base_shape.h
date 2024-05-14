//
// Created by tobia on 20.04.2024.
//

#ifndef TILEMAP_BASE_SHAPE_H
#define TILEMAP_BASE_SHAPE_H

#include <SFML/Graphics.hpp>
#include <list>
#include "../Constants.h"


class Base_shape : public sf::Drawable, public sf::Transformable{

protected:
    Constants::Block_types _type;

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
    void rotate(float);
    void move(sf::Vector2f);
    [[nodiscard]] bool intersects(sf::RectangleShape&) const;
    [[nodiscard]] bool is_placed() const;
    [[nodiscard]] Constants::Block_types get_blocktype() const;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif //TILEMAP_BASE_SHAPE_H

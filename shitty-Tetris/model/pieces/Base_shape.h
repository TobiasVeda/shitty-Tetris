//
// Created by tobia on 20.04.2024.
//

#ifndef TILEMAP_BASE_SHAPE_H
#define TILEMAP_BASE_SHAPE_H

#include "../../Enumerations.h"
#include <SFML/Graphics.hpp>
#include <list>

class Base_shape : public sf::Drawable{

protected:
    Block_types _type;

    sf::RectangleShape _r1;
    sf::RectangleShape _r2;
    sf::RectangleShape _r3;
    sf::RectangleShape _r4;

    static inline sf::Image _tileset;
    sf::Texture _texture;
    bool _placed;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

public:
    Base_shape();

    void set_position(sf::Vector2f);
    void move(sf::Vector2f);
    void rotate(float);
    void place();

    [[nodiscard]] bool intersects(sf::RectangleShape&) const;
    [[nodiscard]] bool is_placed() const;
    [[nodiscard]] Block_types get_blocktype() const;
    [[nodiscard]] std::list<sf::RectangleShape> get_rectangle_list();
};

#endif //TILEMAP_BASE_SHAPE_H

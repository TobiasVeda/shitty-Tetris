//
// Created by tobia on 20.04.2024.
//

#ifndef TILEMAP_BASE_SHAPE_H
#define TILEMAP_BASE_SHAPE_H

#include "../Constants.h"
#include <SFML/Graphics.hpp>
#include <list>

class Base_shape : public sf::Drawable{

protected:
    Constants::Block_types _type;

    sf::RectangleShape _r1;
    sf::RectangleShape _r2;
    sf::RectangleShape _r3;
    sf::RectangleShape _r4;

    sf::Texture _texture;
    bool _placed;

public:
    std::list<sf::RectangleShape> get_rectangle_list();
    void place();
    void rotate(float);
    void move(sf::Vector2f);
    void set_position(sf::Vector2f);
    [[nodiscard]] bool intersects(sf::RectangleShape&) const;
    [[nodiscard]] bool is_placed() const;
    [[nodiscard]] Constants::Block_types get_blocktype() const;
    virtual bool load();
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif //TILEMAP_BASE_SHAPE_H

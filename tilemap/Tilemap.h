//
// Created by tobia on 17.04.2024.
//

#ifndef TILEMAP_TILEMAP_H
#define TILEMAP_TILEMAP_H

#include <SFML/Graphics.hpp>

class Tilemap : public sf::Drawable {
            //allows window.draw(object)

private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

public:
//    Tilemap();

    bool load();
};


#endif //TILEMAP_TILEMAP_H

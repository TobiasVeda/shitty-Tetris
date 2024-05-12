//
// Modified by tobia on 17.04.2024 from:
// SFML: Designing your own entities with vertex arrays
// Source: https://www.sfml-dev.org/tutorials/2.6/graphics-vertex-array.php
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
    void apply_error_texture();
};


#endif //TILEMAP_TILEMAP_H

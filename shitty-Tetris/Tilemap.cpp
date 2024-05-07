//
// Created by tobia on 17.04.2024.
//

#include "Tilemap.h"
#include "Constants.h"


    void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
//        called when window.draw(object)
        states.texture = &m_tileset; // apply texture
        target.draw(m_vertices, states); // draw tilemap
    }


    bool Tilemap::load(){


        // load the tileset texture
        if (!m_tileset.loadFromFile(Constants::texture_name))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(Constants::tile_count_x * Constants::tile_count_y * 4);
//        4. one for each side of a quad. width*height for multiple quads

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < Constants::tile_count_x; ++i)
            for (unsigned int j = 0; j < Constants::tile_count_y; ++j)
            {
                // get the current tile
                //Assuming first collumn i=0, j=j
                //j will iterate through the tiles array one by one, but that would only give row,
                //so we multiply by the width of the level to skip to the next row.
                //when j iterates, it iterates downwards. when i iterates it adds 1 and then j will iterate one to the left
                int tileNumber = Constants::level_map[i + j * Constants::tile_count_x];
//                i=collum j=row, i=x j=y

                // find its position in the tileset texture
                // gets the entire width of the texture and divides it by the width of a single tile
                int tu = tileNumber % (m_tileset.getSize().x / Constants::tilesize.x);
                int tv = tileNumber / (m_tileset.getSize().x / Constants::tilesize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * Constants::tile_count_x) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * Constants::tilesize.x, j * Constants::tilesize.y);
                quad[1].position = sf::Vector2f((i + 1) * Constants::tilesize.x, j * Constants::tilesize.y);
                quad[2].position = sf::Vector2f((i + 1) * Constants::tilesize.x, (j + 1) * Constants::tilesize.y);
                quad[3].position = sf::Vector2f(i * Constants::tilesize.x, (j + 1) * Constants::tilesize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * Constants::tilesize.x, tv * Constants::tilesize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * Constants::tilesize.x, tv * Constants::tilesize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * Constants::tilesize.x, (tv + 1) * Constants::tilesize.y);
                quad[3].texCoords = sf::Vector2f(tu * Constants::tilesize.x, (tv + 1) * Constants::tilesize.y);
            }

        return true;
    }


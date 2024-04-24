//
// Created by tobia on 23.04.2024.
//

#ifndef TILEMAP_PIECE_COLLECTION_H
#define TILEMAP_PIECE_COLLECTION_H

#include <SFML/Graphics.hpp>
#include <list>

class Piece_collection {
private:
    std::list<std::list<sf::RectangleShape*>*> _piece_collection;

public:
    void add_to_collection(std::list<sf::RectangleShape*>);
};


#endif //TILEMAP_PIECE_COLLECTION_H

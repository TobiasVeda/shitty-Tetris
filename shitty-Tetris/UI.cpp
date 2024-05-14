//
// Created by tobia on 14.05.2024.
//

#include "UI.h"
#include "Constants.h"

UI::UI(){
    _hold_container.setOutlineColor(sf::Color::Black);
    _hold_container.setOutlineThickness(2);

    _next_container.setOutlineColor(sf::Color::Black);
    _next_container.setOutlineThickness(2);

    _hold_container.setSize(sf::Vector2f(
            (Constants::tilesize.x *4) + (Constants::tilesize.x /2) - _hold_container.getOutlineThickness(),
            (Constants::tilesize.y *4) + (Constants::tilesize.y /2) - _hold_container.getOutlineThickness()
            ));

    _next_container.setSize(sf::Vector2f(
            (Constants::tilesize.x *4) + (Constants::tilesize.x /2) - _next_container.getOutlineThickness(),
            (Constants::tilesize.y * Constants::tile_count_y) - (Constants::tilesize.x *4) + (Constants::tilesize.x /2) - Constants::tilesize.y  - _next_container.getOutlineThickness()
            ));

    _hold_container.setPosition(
            (Constants::tilesize.x * Constants::tile_count_x) + (Constants::tilesize.x /2) - _hold_container.getOutlineThickness(),
            _hold_container.getOutlineThickness()
            );

    _next_container.setPosition(
            (Constants::tilesize.x * Constants::tile_count_x) + (Constants::tilesize.x /2)  - _next_container.getOutlineThickness(),
            _hold_container.getSize().y + Constants::tilesize.y
    );

}

void UI::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(_hold_container, states);
    target.draw(_next_container, states);
}
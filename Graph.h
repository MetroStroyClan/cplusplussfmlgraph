#ifndef GENALGORITHM_G1_GRAPH_H
#define GENALGORITHM_G1_GRAPH_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <limits>

namespace g_h {




}

class Graph {
public:

    Graph(
            sf::RenderWindow *window,
            sf::Vector2f position,
            sf::Vector2f scale,
            int dotsCount,
            int fontSize
            );
    ~Graph();

    void Render();

    void AddDot(float value);

private:

    sf::RenderWindow *_window;
    sf::Vector2f _position;
    sf::Vector2f _scale;
    int _dotsCount;
    int _dotsContain;
    int _fontSize;

    float* _dots;

    void InitArrays();
    void DestructArrays();

    sf::Vector2f GetDotPositionOnScreen(int id);

    float TopDotValue();
    float MinDotValue();

};


#endif //GENALGORITHM_G1_GRAPH_H

#include "Graph.h"

Graph::Graph(
        sf::RenderWindow *window,
        sf::Vector2f position,
        sf::Vector2f scale,
        int dotsCount,
        int fontSize) {

    _window = window;
    _position = position;
    _scale = scale;
    _dotsCount = dotsCount;
    _fontSize = fontSize;
    _dotsContain = 0;

    InitArrays();

}

Graph::~Graph() {

    DestructArrays();

}

void Graph::Render() {

    sf::Vertex *vertex = new sf::Vertex [_dotsCount];

    for(int i = 0; i < _dotsCount; i++) {

        sf::Vector2f pos = GetDotPositionOnScreen(i);
        vertex[i] = sf::Vertex(pos);

    }

    sf::Vertex *zeroLine = new sf::Vertex[2];
    zeroLine[0] = sf::Vertex(sf::Vector2f(
            _position.x, _position.y
            ));
    zeroLine[1] = sf::Vertex(sf::Vector2f(
            _position.x + _scale.x, _position.y
            ));

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/type1/gsfonts/a010015l.pfb");

    sf::Text maxText;
    sf::Text minText;
    sf::Text zeroText;

    maxText.setFont(font);
    minText.setFont(font);
    zeroText.setFont(font);

    maxText.setCharacterSize(_fontSize);
    minText.setCharacterSize(_fontSize);
    zeroText.setCharacterSize(_fontSize);

    maxText.setString("max: " + std::to_string(TopDotValue()));
    minText.setString("min: " +std::to_string(MinDotValue()));
    zeroText.setString("0");

    maxText.setPosition(_position.x, _position.y + _scale.y - (_fontSize * 2));
    minText.setPosition(_position.x, _position.y + (_fontSize * 2));
    zeroText.setPosition(_position.x - _fontSize, _position.y);

    _window->draw(maxText);
    _window->draw(minText);
    _window->draw(zeroText);

    _window->draw(vertex, _dotsCount, sf::LineStrip);
    _window->draw(zeroLine, 2, sf::Lines);

    delete [] zeroLine;
    delete [] vertex;

}

void Graph::AddDot(float value) {

    if(_dotsContain == _dotsCount) {

        for(int i = 0; i < _dotsCount - 1; i++) {

            _dots[i] = _dots[i + 1];

        }

        _dots[_dotsCount - 1] = value;

    } else {

        _dots[_dotsContain] = value;
        _dotsContain++;

    }

}

void Graph::InitArrays() {

    _dots = new float[_dotsCount];

    for(int i = 0; i < _dotsCount; i++) {

        _dots[i] = 0.0f;

    }

}

void Graph::DestructArrays() {

    delete [] _dots;

}

sf::Vector2f Graph::GetDotPositionOnScreen(int id) {

    float maxV = TopDotValue();

    float x = (
            ( (float)id / (float)_dotsCount ) *
            _scale.x + _position.x
            );

    float y = (
            ( _dots[id] / maxV ) *
            _scale.y + _position.y
            );

    return sf::Vector2f(x, y);

}

float Graph::TopDotValue() {

    float topValue = 0.0f;

    for(int i = 0; i < _dotsCount; i++) {

        if(_dots[i] > topValue) {

            topValue = _dots[i];

        }

    }

    return topValue;

}

float Graph::MinDotValue() {

    float minV = std::numeric_limits<float>::max();

    for(int i = 0; i < _dotsCount; i++) {

        if(_dots[i] < minV) {

            minV = _dots[i];

        }

    }

    return minV;

}

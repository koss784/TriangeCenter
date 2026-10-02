#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "InnerOuterCircle");
    sf::Font font;
    font.openFromFile("Roboto-Medium.ttf");
    std::string textMessage = "";
    sf::Text text(font, textMessage);

    text.setPosition({200.f, 300.f});
    text.setFillColor(sf::Color::Red);
    std::vector<sf::Vector2f> points;

    float outerRadius = 0;
    float innerRadius = 50;

    sf::VertexArray triangle(sf::PrimitiveType::LineStrip, 4);
    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;

    sf::CircleShape outerCircle(outerRadius, 40);
    outerCircle.setOutlineColor(sf::Color::Red);
    outerCircle.setOutlineThickness(2.f);
    outerCircle.setFillColor(sf::Color::Transparent);

    sf::CircleShape innerCircle(innerRadius, 40);
    innerCircle.setOutlineColor(sf::Color::Blue);
    innerCircle.setOutlineThickness(2.f);
    innerCircle.setFillColor(sf::Color::Transparent);



    while (window.isOpen())
    {

        window.clear(sf::Color::White);



        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
            {
                float x = (float)mouseClick->position.x;
                float y = (float)mouseClick->position.y;
                points.push_back({x,y});
                if (points.size() > 3) {
                    points.erase(points.begin());
                }

            }
        }



        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            text.setPosition({(float)mousePos.x, (float)mousePos.y});
        }


        if (points.size() >= 3) {

            double dx1 = points[1].x - points[2].x;
            double dy1 = points[1].y - points[2].y;
            float d1 = sqrt(dx1 * dx1 + dy1 * dy1);
            double dx2 = points[2].x - points[0].x;
            double dy2 = points[2].y - points[0].y;
            float d2 = sqrt(dx2 * dx2 + dy2 * dy2);
            double dx3 = points[1].x - points[0].x;
            double dy3 = points[1].y - points[0].y;
            float d3 = sqrt(dx3 * dx3 + dy3 * dy3);

            float x1 = points[0].x;
            float y1 = points[0].y;
            float x2 = points[1].x;
            float y2 = points[1].y;
            float x3 = points[2].x;
            float y3 = points[2].y;

            float D = 2.0f * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

            float outerCenterX = 0;
            float outerCenterY = 0;

            if (std::abs(D) > 50) {
                float sq1 = x1 * x1 + y1 * y1;
                float sq2 = x2 * x2 + y2 * y2;
                float sq3 = x3 * x3 + y3 * y3;
                outerCenterX = (sq1 * (y2 - y3) + sq2 * (y3 - y1) + sq3 * (y1 - y2)) / D;
                outerCenterY = (sq1 * (x3 - x2) + sq2 * (x1 - x3) + sq3 * (x2 - x1)) / D;
            } else {
                outerCenterX = (x1 + x2 + x3) / 3.0f;
                outerCenterY = (y1 + y2 + y3) / 3.0f;
            }

            float dx = outerCenterX - x1;
            float dy = outerCenterY - y1;
            outerRadius = std::sqrt(dx * dx + dy * dy);


            triangle[0].position = points[0];
            triangle[1].position = points[1];
            triangle[2].position = points[2];
            triangle[3].position = points[0];


            outerCircle.setPosition({(outerCenterX - outerRadius), (outerCenterY - outerRadius)});
            outerCircle.setRadius(outerRadius);

            //INNER CIRCLE
            float sp = (d1 + d2 + d3)/2.0f; //semi-perimeter

            float innerCenterX = (d1 * points[0].x + d2 * points[1].x + d3 * points[2].x) / (sp * 2);
            float innerCenterY = (d1 * points[0].y + d2 * points[1].y + d3 * points[2].y) / (sp * 2);

            innerRadius = sqrt(sp*(sp-d1)*(sp-d2)*(sp-d3))/sp;


            innerCircle.setRadius(innerRadius);
            innerCircle.setOrigin({innerRadius, innerRadius});
            innerCircle.setPosition({innerCenterX, innerCenterY});

            window.draw(innerCircle);



            float mid1_x = (points[1].x + points[2].x) / 2.0f;
            float mid1_y = (points[1].y + points[2].y) / 2.0f;

            float mid2_x = (points[2].x + points[0].x) / 2.0f;
            float mid2_y = (points[2].y + points[0].y) / 2.0f;

            float mid3_x = (points[1].x + points[0].x) / 2.0f;
            float mid3_y = (points[1].y + points[0].y) / 2.0f;



            // //LENGTH OF SIDES
            // textMessage = std::to_string(d1).substr(0, 4);
            // textMessage.pop_back();
            // text.setString(textMessage);
            // text.setPosition({mid1_x, mid1_y});
            // window.draw(text);
            //
            // textMessage = std::to_string(d2).substr(0, 4);
            // textMessage.pop_back();
            // text.setString(textMessage);
            // text.setPosition({mid2_x, mid2_y});
            // window.draw(text);
            //
            // textMessage = std::to_string(d3).substr(0, 4);
            // textMessage.pop_back();
            // text.setString(textMessage);
            // text.setPosition({mid3_x, mid3_y});
            // window.draw(text);
            //

            textMessage = std::to_string(innerRadius).substr(0, 4);
            textMessage.pop_back();
            text.setString("Inner Radius\n" +textMessage + "mm");
            text.setPosition({600,200});
            window.draw(text);

            textMessage = std::to_string(outerRadius).substr(0, 4);
            textMessage.pop_back();
            text.setString("Outer Radius\n" +textMessage + "mm");
            text.setPosition({600,400});
            window.draw(text);


            //DRAW

            window.draw(triangle);
            window.draw(outerCircle);
            outerRadius = 0;
        }

        //RENDER DOTS
        for (const auto& point : points) {
            sf::CircleShape dot(5.5f);
            dot.setFillColor(sf::Color::Black);
            dot.setPosition({point.x - 5.5f , point.y - 5.5f});
            window.draw(dot);
        }


        window.display();
    }
}
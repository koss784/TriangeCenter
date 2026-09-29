#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "InnerOuterCircle");
    sf::Font font;
    font.openFromFile("Roboto-Medium.ttf");
    std::string textMessage = "";
    sf::Text text(font, textMessage);
    sf::Text text_d1(font, textMessage);
    sf::Text text_d2(font, textMessage);
    sf::Text text_d3(font, textMessage);

    text.setPosition({200.f, 300.f});
    text.setFillColor(sf::Color::Red);
    std::vector<sf::Vector2f> points;





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
            sf::VertexArray triangle(sf::PrimitiveType::LineStrip, 4);


            double dx1 = points[1].x - points[2].x;
            double dy1 = points[1].y - points[2].y;
            int d1 = sqrt(dx1 * dx1 + dy1 * dy1);
            double dx2 = points[2].x - points[0].x;
            double dy2 = points[2].y - points[0].y;
            int d2 = sqrt(dx2 * dx2 + dy2 * dy2);
            double dx3 = points[1].x - points[0].x;
            double dy3 = points[1].y - points[0].y;
            int d3 = sqrt(dx3 * dx3 + dy3 * dy3);


            // define the position of the triangle's points
            triangle[0].position = points[0];
            triangle[1].position = points[1];
            triangle[2].position = points[2];
            triangle[3].position = points[0];

            triangle[0].color = sf::Color::Red;
            triangle[1].color = sf::Color::Blue;
            triangle[2].color = sf::Color::Green;


            float mid1_x = (points[1].x + points[2].x) / 2.0f;
            float mid1_y = (points[1].y + points[2].y) / 2.0f;

            // Midpoint between points 2 and 0 (d2 side)
            float mid2_x = (points[2].x + points[0].x) / 2.0f;
            float mid2_y = (points[2].y + points[0].y) / 2.0f;

            // Midpoint between points 1 and 0 (d3 side)
            float mid3_x = (points[1].x + points[0].x) / 2.0f;
            float mid3_y = (points[1].y + points[0].y) / 2.0f;

            // 4. Draw Texts at Midpoints
            textMessage = std::to_string(d1);
            textMessage.pop_back();
            text.setString(textMessage);
            text.setPosition({mid1_x, mid1_y});
            window.draw(text);

            textMessage = std::to_string(d2);
            textMessage.pop_back();
            text.setString(textMessage);
            text.setPosition({mid2_x, mid2_y});
            window.draw(text);

            textMessage = std::to_string(d3);
            textMessage.pop_back();
            text.setString(textMessage);
            text.setPosition({mid3_x, mid3_y});
            window.draw(text);




            std::cout << d1 << std::endl;
            std::cout << d2 << std::endl;
            std::cout << d3 << std::endl;



            window.draw(triangle);
        }


        for (const auto& point : points) {

            sf::CircleShape dot(5.5f);
            dot.setFillColor(sf::Color::Black);
            dot.setPosition({point.x - 5.5f , point.y - 5.5f});
            window.draw(dot);
        }




        window.display();
    }
}
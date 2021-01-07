#include <SFML/Graphics.hpp>
#include <iostream>

#include <Windows.h>
#include <fstream>
#include <strstream>

#include "Camera.h"
#include "Mesh.h"

constexpr float sensitivity = 3;

void HandleEvents(sf::Window& window, Camera& camera);

Mesh load_model(std::string file_name)
{
    std::ifstream f(file_name);
    if (!f.is_open())
        throw std::exception("not found");

    std::vector<Vec3> verts;
    std::vector<Vec3> vertices;

    while (!f.eof())
    {
        char line[128];
        f.getline(line, 128);

        std::strstream s;
        s << line;

        char junk;

        if (line[0] == 'v')
        {
            Vec3 v(0, 0, 0);
            s >> junk >> v[0] >> v[1] >> v[2];
            verts.push_back(v);
        }
        if (line[0] == 'f')
        {
            int f[3];
            s >> junk >> f[0] >> f[1] >> f[2];
            vertices.push_back(verts[f[0] - 1]);
            vertices.push_back(verts[f[1] - 1]);
            vertices.push_back(verts[f[2] - 1]);
        }
    }

    return Mesh(vertices);
}

int main()
{
    sf::Clock clock;
    Screen screen{ 1280, 720, "3D Test" }; 
    auto& window = screen.GetWindow();
    window.setMouseCursorVisible(false);

    Camera camera{ Vec3(0, 0, 0), Vec3(0, 0, 0), 60 };
    
    Mesh cube(
        {
            //top
            {10, -2, 4}, {12, -2, 4}, {12, 2, 4},
            {12, 2, 4}, {10, 2, 4}, {10, -2, 4},

            //back
            {12, 2, 4}, {12, -2, 4}, {12, -2, 0},
            {12, -2, 0}, {12, 2, 0}, {12, 2, 4},

            //left
            {10, -2, 4}, {10, -2, 0}, {12, -2, 0},
            {12, -2, 4}, {10, -2, 4}, {12, -2, 0},

            //right
            {10, 2, 4}, {12, 2, 4}, {12, 2, 0},
            {12, 2, 0}, {10, 2, 0}, {10, 2, 4},

            //front
            {10, -2, 4}, {10, 2, 4}, {10, 2, 0},
            {10, 2, 0}, {10, -2, 0}, {10, -2, 4},

            //bottom
            {10, 2, 0}, {12, -2, 0}, {12, 2, 0},
            {12, 2, 0}, {10, 2, 0}, {10, -2, 0}
        }
    );

    Mesh test = load_model("testmodel.txt");
    
    while (window.isOpen())
    {
        HandleEvents(window, camera);

        auto frameTime = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        window.setTitle("fps: " + std::to_string(1000.0f / frameTime));

        window.clear();
        cube.Draw(camera, screen);
        test.Draw(camera, screen);
        window.display();
    }

    return 0;
}

void HandleEvents(sf::Window& window, Camera& camera)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseMoved)
        {
            float distX = event.mouseMove.x - window.getSize().x / 2.0;
            float distY = event.mouseMove.y - window.getSize().y / 2.0;

            camera.Rotate({
                2 * camera.GetFOV() / window.getSize().x * distX * sensitivity * 0.1f,
                -2 * camera.GetFOV() / window.getSize().y * distY * sensitivity * 0.1f,
                0 });

            sf::Mouse::setPosition(
                sf::Vector2i(window.getSize().x / 2.0,window.getSize().y / 2.0),
                window);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        camera.MoveLeft(0.1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        camera.MoveRight(0.1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        camera.MoveForward(0.1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        camera.MoveBackward(0.1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && 
        sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        camera.Move({ 0, 0, -0.1 });
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        camera.Move({ 0, 0, 0.1 });
}
#include <Game/Application/Application.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

int main()
{
    //sf::Font f;
    //bool a = f.loadFromFile("../../Data/Fonts/MS Serif.ttf");
    //const sf::Texture& texture = f.getTexture(50);

    //sf::Text t;
    //t.setFont(f);
    //t.setString("a");
    //t.setCharacterSize(50);
    //auto b = t.getLocalBounds();
    //auto m_window = std::make_shared<sf::RenderWindow>();
    //m_window->create(sf::VideoMode(960, 960), "RUN & FIRE & 2");
    //m_window->setKeyRepeatEnabled(false); // https://www.sfml-dev.org/tutorials/2.5/window-events.php
    //m_window->setFramerateLimit(60);

    //sf::Event event;
    //sf::Clock frameClock;
    //while (m_window->isOpen())
    //{
    //    while (m_window->pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //        {
    //            m_window->close();
    //        }
    //    }

    //    m_window->clear();
    //    m_window->draw(t);
    //    m_window->display();
    //}




    Application::CreateInstance();

    auto& application = Application::GetInstanceRef();

    application.Initialize();
    application.Run();
    application.Shutdown();

    Application::DestroyInstance();
    return 0;
}

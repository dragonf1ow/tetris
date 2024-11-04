#include "tetris.h" 
#include <iostream> 
#include "Windows.h" 

Tetris::Tetris()
{
    // ������������� ��������� ���� 
    rectFigure = new sf::RectangleShape(sf::Vector2f(34, 34));
    rect1 = sf::RectangleShape(sf::Vector2f(360, 720));  	rect1.setOutlineColor(sf::Color::Blue);  	rect1.setOutlineThickness(2);  	rect1.setFillColor(sf::Color::Black);  	rect1.setPosition(2, 3);

    rect2 = sf::RectangleShape(sf::Vector2f(190, 190));  	rect2.setOutlineColor(sf::Color::Yellow);  	rect2.setOutlineThickness(4);  	rect2.setFillColor(sf::Color(100, 10, 150));
    rect2.setPosition(370, 4);

    rect3 = sf::RectangleShape(sf::Vector2f(190, 514));  	rect3.setOutlineColor(sf::Color::Yellow);  	rect3.setOutlineThickness(4);  	rect3.setFillColor(sf::Color(100, 10, 10));  	rect3.setPosition(370, 204);

    // �������� ������ 
    if (!font.loadFromFile("Arial.ttf"))
    {
        // ����� �� ��������. �����. 
        std::cout << "Font isnt loaded!" << std::endl;  	 	system("pause");  	 	exit(1);
    }
    // ������������� ��������� �����  	
    txtScore.setFont(font);  	txtScore.setPosition(410.f, 230.f); txtScore.setString(sf::String(L"����: ") + std::to_string(score)); txtScore.setCharacterSize(30); txtScore.setOutlineThickness(3); txtScore.setOutlineColor(sf::Color::Blue);
    txtGameOver.setFont(font); txtGameOver.setPosition(30.f, 300.f); txtGameOver.setString("GAME OVER"); txtGameOver.setCharacterSize(50); txtGameOver.setOutlineThickness(3); txtGameOver.setOutlineColor(sf::Color::Red);

    txtPaused.setFont(font);  	txtPaused.setPosition(100.f, 300.f);  	txtPaused.setString(L"�����");  	txtPaused.setCharacterSize(50);  	txtPaused.setOutlineThickness(3);  	txtPaused.setOutlineColor(sf::Color::Yellow);

    txtButtonNewGame.setFont(font);  	txtButtonNewGame.setPosition(380.f, 460.f);  	txtButtonNewGame.setString(L"����� ����");  	txtButtonNewGame.setCharacterSize(30);  	txtButtonNewGame.setOutlineThickness(3);  	txtButtonNewGame.setOutlineColor(sf::Color::Blue);

    txtButtonHelp.setFont(font);  	txtButtonHelp.setPosition(400.f, 520.f);  	txtButtonHelp.setString(L"�������");  	txtButtonHelp.setCharacterSize(30);
    txtButtonHelp.setOutlineThickness(3);  	txtButtonHelp.setOutlineColor(sf::Color::Blue);

    txtButtonAuthor.setFont(font); txtButtonAuthor.setPosition(415.f, 350.f); txtButtonAuthor.setString(L"�����");      txtButtonAuthor.setCharacterSize(30); txtButtonAuthor.setOutlineThickness(3); txtButtonAuthor.setOutlineColor(sf::Color::Blue);

    txtButtonPause.setFont(font);  	txtButtonPause.setPosition(415.f, 580.f);  	txtButtonPause.setString(L"�����");  	txtButtonPause.setCharacterSize(30);  	txtButtonPause.setOutlineThickness(3);  	txtButtonPause.setOutlineColor(sf::Color::Blue);

    txtButtonExit.setFont(font);  	txtButtonExit.setPosition(415.f, 640.f);  	txtButtonExit.setString(L"�����");  	txtButtonExit.setCharacterSize(30);  	txtButtonExit.setOutlineThickness(3);  	txtButtonExit.setOutlineColor(sf::Color::Blue);

    // ����� ������� ���������� 
    resetGameParams();

    // ������� ����  	
    window = new sf::RenderWindow(sf::VideoMode(565, 725), L"������", sf::Style::Titlebar | sf::Style::Close);
}

Tetris::~Tetris()
{
    delete window;
    delete rectFigure;
}

void Tetris::events()
{
    // ��������� ����� 
    float time = clock.getElapsedTime().asSeconds();
    // �������� ������  	
    clock.restart();
    // ��������� ������� ������� 
    timerCount += time;

    auto e = sf::Event();
    // ����, ���� �� ��� ������� ����������  
    while (window->pollEvent(e))
    {
        // ������� ���� 
        if (e.type == sf::Event::Closed)
            if (MessageBox(nullptr, L"�����", L"���������",
                MB_ICONQUESTION | MB_YESNO) == IDYES)
            {
                window->close();
                return;
            }
        // ������ ������� 
        if (e.type == sf::Event::KeyPressed)
        {
            // ������� ���� 
            if (e.key.code == sf::Keyboard::Escape)  	 	 	 	
                if (MessageBox(nullptr, L"�����", L"���������", MB_ICONQUESTION | MB_YESNO) == IDYES)
                {
                window->close();
                return;
                }
            // ���������/����� ����� 
            if (e.key.code == sf::Keyboard::Space && !bGameover)
            {
                bPaused = !bPaused;
                break;
            }
            // ��������� ������  	 	 	
            if (e.key.code == sf::Keyboard::Up)
                bRotate = true;
            // ����������� ������ 
            else if (e.key.code == sf::Keyboard::Right)
                ++dirx;
            else if (e.key.code == sf::Keyboard::Left)
                --dirx;
        }
        // �������� ������ ���� 
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (isMouseClick(txtButtonAuthor.getGlobalBounds()))
            {
                MessageBox(nullptr, L"�����: ����������� ���� \n������: ����-04-23", L"�����", MB_OK);
            }
            // ������ ����� ���� 
            if (isMouseClick(txtButtonNewGame.getGlobalBounds()))
            {
                resetGameParams();
            }
            // ������ ������� 
            if (isMouseClick(txtButtonHelp.getGlobalBounds()))
            {
                MessageBox(nullptr, L"����������.\n������� ������, ����� - ����������� �� �����������\n������� ����� - ���������\n������ - �����\nEsc - �����", L"�������", MB_OK);
            }
            // ������ ����� 
            if (isMouseClick(txtButtonPause.getGlobalBounds()))
            {
                bPaused = !bPaused;
                break;
            }
            // ������ ����� 
            if (isMouseClick(txtButtonExit.getGlobalBounds()))
            {
                if (MessageBox(nullptr, L"�����", L"���������", MB_ICONQUESTION | MB_YESNO) == IDYES)  	 	 	 	window->close();
            }
        }
    }
    // �������� ������ 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        delay = 0.05f;
    }
}

bool Tetris::isMouseClick(const sf::FloatRect rect) const
{
    // ����������� ��������� ������� 
    sf::Vector2i mouseCoords = sf::Mouse::getPosition(*window);
    // �� ������ ����� ������ ���� 
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        return false;
    sf::Vector2u winSize = window->getSize();  	
    if ((unsigned)mouseCoords.x < winSize.x && (unsigned)mouseCoords.y < winSize.y &&
        (unsigned)mouseCoords.x > rect.left && (unsigned)mouseCoords.x < rect.left + rect.width &&
        (unsigned)mouseCoords.y > rect.top && (unsigned)mouseCoords.y < rect.top + rect.height)
    {
        // ������ ��� ������� 
        return true;
    }
    return false;

}
void Tetris::resetGameParams()
{
    // ������������� �������� ����   	
    for (std::size_t i = 0; i < lines; ++i)
        for (std::size_t j = 0; j < columns; ++j)
            area[i][j] = 0;

    // ������������� ������� ����������  	
    dirx = score = 0;
    bRotate = bGameover = bPaused = false;  	timerCount = 0.f;
    delay = 0.3f;
    currentColor = std::rand() % numberColors + 1;

    // ��������� ������ 
    std::uint32_t number = std::rand() % numberForms;
    for (std::size_t i = 0; i < squares; ++i)
    {
        currentPosition[i].x = forms[number][i] % 2 + 4;
        currentPosition[i].y = forms[number][i] / 2;
    }
    // ��������� ������  	
    number = std::rand() % numberForms;
    nextColor = std::rand() % numberColors + 1;
    for (std::size_t i = 0; i < squares; ++i) {
        nextFigure[i].x = forms[number][i] % 2 + 4; nextFigure[i].y = forms[number][i] / 2;
    }
}
void Tetris::draw() const
{
    // �������� ���� 
    window->clear(sf::Color::Black);

    // ���������� ���  	
    window->draw(rect1);
    window->draw(rect2);
    window->draw(rect3);

    // ���������� ������������ ������  	
    for (std::size_t i = 0; i < lines; ++i)
        for (std::size_t j = 0; j < columns; ++j)
            if (area[i][j] != 0)
            {
                rectFigure->setFillColor(figureColors[area[i][j] - 1]);
                rectFigure->setPosition(j * 36 + 3, i * 36 + 3);
                window->draw(*rectFigure);
            }
    // ���������� ���������� ������  	
    for (std::size_t i = 0; i < squares; ++i)
    {
        rectFigure->setFillColor(figureColors[currentColor - 1]);   
        rectFigure->setPosition(currentPosition[i].x * 36 + 3, currentPosition[i].y * 36 + 3);
        window->draw(*rectFigure);
    }

    // ���������� ��������� ������  	
    for (std::size_t i = 0; i < squares; ++i)
    {
        rectFigure->setFillColor(figureColors[nextColor - 1]);  	 	
        rectFigure->setPosition((nextFigure[i].x - 4) * 36 + 420, nextFigure[i].y * 36 + 20);
        window->draw(*rectFigure);
    }

    // ���������� ��������� �����  	
    window->draw(txtScore);
    if (bGameover)
        window->draw(txtGameOver);
    if (bPaused)
        window->draw(txtPaused);


    window->draw(txtButtonNewGame);
    window->draw(txtButtonHelp);
    window->draw(txtButtonAuthor);
    window->draw(txtButtonPause);
    window->draw(txtButtonExit);  	// ������������ ���� 
    window->display();
}
void Tetris::run()
{
    // ���� ���� ������� 
    while (window->isOpen()) { // ��������� ���������� ������� 
        events();
        // ���� �� ����� ���� 
        if (!bGameover && !bPaused)
        {
            // ����������� ������ �� �����������  	 	
            changePosition();
            // ��������� ������  	 	
            setRotate();
            // �������� ���� ������ 
            moveToDown();
            // �������� ���� ����  	 	 	
            setScore();
            // �������� ��������� 
            resetValues();
        }
        // ���������� ���������� ���� 
        draw();
    }
}

void Tetris::moveToDown()
{
    // ����� �������� �����  	
    if (timerCount > delay)
    {
        // ����������� ������ �� ���� ������ ����  	 	
        for (std::size_t i = 0; i < squares; ++i)
        {
            lastPosition[i] = currentPosition[i];
            ++currentPosition[i].y;
        }
        // ���� ������ ����� �� ������� �������� ���� ���  	 	// �������� ������� ������� ������������ �����  	 	
        if (checkPosition()) {
            for (std::size_t i = 0; i < squares; ++i)
                area[lastPosition[i].y][lastPosition[i].x] = currentColor;
                currentColor = nextColor;  	 	 	
            for (std::size_t i = 0; i < squares; ++i)
                currentPosition[i] = nextFigure[i];

            // ��������� ����� ������  	 	 	
            nextColor = std::rand() % numberColors + 1;
            std::uint32_t number = std::rand() % numberForms;
            for (std::size_t i = 0; i < squares; ++i)
            {
                nextFigure[i].x = forms[number][i] % 2 + 4;
                nextFigure[i].y = forms[number][i] / 2;
            }
        }
        timerCount = 0;
    }
}



void Tetris::setRotate() {

    
    Coords coords = currentPosition[1];
    // ���� ���������� ��������� ������  	
    if (bRotate)
        
        for (std::size_t i = 0; i < squares; ++i) {
            int x = currentPosition[i].y - coords.y;
            int y = currentPosition[i].x - coords.x;
            currentPosition[i].x = coords.x - x;
            currentPosition[i].y = coords.y + y;
        }
    if (checkPosition())
        for (std::size_t i = 0; i < squares; ++i) {
            currentPosition[i] = lastPosition[i];
        }
}
void Tetris::resetValues()
{
    dirx = 0;  	
    bRotate = false;
    delay = 0.3f;
}
void Tetris::changePosition()
{
    // ��������� ������� ���������� ������ 
    for (std::size_t i = 0; i < squares; ++i)
    {
        lastPosition[i] = currentPosition[i];
        currentPosition[i].x += dirx;
    }
    if (checkPosition())
        // ������� ���������� ��������� ������  	 	
        for (std::size_t i = 0; i < squares; ++i)
            currentPosition[i] = lastPosition[i];
}
bool Tetris::checkPosition() const
{
    for (std::size_t i = 0; i < squares; ++i)  	 	
        if (currentPosition[i].x < 0 || currentPosition[i].x >= columns || currentPosition[i].y >= lines || area[currentPosition[i].y][currentPosition[i].x])
        return true;  	
    return false;
}
void Tetris::setScore()
{
    // ������ � ������ ����� �����  	
    std::uint32_t match = lines - 1;
    for (std::size_t i = match; i >= 1; --i)
    {
        // ��������� ���������� ������� ��������� �� ������ ����� 
        std::uint32_t sum = 0;
        for (std::size_t j = 0; j < columns; ++j)
        {
            if (area[i][j])
            {
                if (i == 1)  	 	 	 	 	
                    bGameover = true;
                ++sum;
            }
            area[match][j] = area[i][j];
        }
        // ���� �� ��� ����� ���������  	 	
        if (sum < columns)
            // ������� � ��������� ����� 
            --match;
        else // ����� 
            // ��������� ���� ���� 
            txtScore.setString(sf::String(L"����: ") + std::to_string(++score));
    }
}



#include "tetris.h" 
#include <iostream> 
#include "Windows.h" 

Tetris::Tetris()
{
    // Инициализация элементов окна 
    rectFigure = new sf::RectangleShape(sf::Vector2f(34, 34));
    rect1 = sf::RectangleShape(sf::Vector2f(360, 720));  	rect1.setOutlineColor(sf::Color::Blue);  	rect1.setOutlineThickness(2);  	rect1.setFillColor(sf::Color::Black);  	rect1.setPosition(2, 3);

    rect2 = sf::RectangleShape(sf::Vector2f(190, 190));  	rect2.setOutlineColor(sf::Color::Yellow);  	rect2.setOutlineThickness(4);  	rect2.setFillColor(sf::Color(100, 10, 150));
    rect2.setPosition(370, 4);

    rect3 = sf::RectangleShape(sf::Vector2f(190, 514));  	rect3.setOutlineColor(sf::Color::Yellow);  	rect3.setOutlineThickness(4);  	rect3.setFillColor(sf::Color(100, 10, 10));  	rect3.setPosition(370, 204);

    // Загрузка шрифта 
    if (!font.loadFromFile("Arial.ttf"))
    {
        // Шрифт не загружен. Выход. 
        std::cout << "Font isnt loaded!" << std::endl;  	 	system("pause");  	 	exit(1);
    }
    // Инициализация текстовых меток  	
    txtScore.setFont(font);  	txtScore.setPosition(410.f, 230.f); txtScore.setString(sf::String(L"СЧЕТ: ") + std::to_string(score)); txtScore.setCharacterSize(30); txtScore.setOutlineThickness(3); txtScore.setOutlineColor(sf::Color::Blue);
    txtGameOver.setFont(font); txtGameOver.setPosition(30.f, 300.f); txtGameOver.setString("GAME OVER"); txtGameOver.setCharacterSize(50); txtGameOver.setOutlineThickness(3); txtGameOver.setOutlineColor(sf::Color::Red);

    txtPaused.setFont(font);  	txtPaused.setPosition(100.f, 300.f);  	txtPaused.setString(L"ПАУЗА");  	txtPaused.setCharacterSize(50);  	txtPaused.setOutlineThickness(3);  	txtPaused.setOutlineColor(sf::Color::Yellow);

    txtButtonNewGame.setFont(font);  	txtButtonNewGame.setPosition(380.f, 460.f);  	txtButtonNewGame.setString(L"Новая игра");  	txtButtonNewGame.setCharacterSize(30);  	txtButtonNewGame.setOutlineThickness(3);  	txtButtonNewGame.setOutlineColor(sf::Color::Blue);

    txtButtonHelp.setFont(font);  	txtButtonHelp.setPosition(400.f, 520.f);  	txtButtonHelp.setString(L"Справка");  	txtButtonHelp.setCharacterSize(30);
    txtButtonHelp.setOutlineThickness(3);  	txtButtonHelp.setOutlineColor(sf::Color::Blue);

    txtButtonAuthor.setFont(font); txtButtonAuthor.setPosition(415.f, 350.f); txtButtonAuthor.setString(L"Автор");      txtButtonAuthor.setCharacterSize(30); txtButtonAuthor.setOutlineThickness(3); txtButtonAuthor.setOutlineColor(sf::Color::Blue);

    txtButtonPause.setFont(font);  	txtButtonPause.setPosition(415.f, 580.f);  	txtButtonPause.setString(L"Пауза");  	txtButtonPause.setCharacterSize(30);  	txtButtonPause.setOutlineThickness(3);  	txtButtonPause.setOutlineColor(sf::Color::Blue);

    txtButtonExit.setFont(font);  	txtButtonExit.setPosition(415.f, 640.f);  	txtButtonExit.setString(L"Выход");  	txtButtonExit.setCharacterSize(30);  	txtButtonExit.setOutlineThickness(3);  	txtButtonExit.setOutlineColor(sf::Color::Blue);

    // Сброс игровых параметров 
    resetGameParams();

    // Создать окно  	
    window = new sf::RenderWindow(sf::VideoMode(565, 725), L"Тетрис", sf::Style::Titlebar | sf::Style::Close);
}

Tetris::~Tetris()
{
    delete window;
    delete rectFigure;
}

void Tetris::events()
{
    // Прошедшее время 
    float time = clock.getElapsedTime().asSeconds();
    // Сбросить таймер  	
    clock.restart();
    // Увеличить счетчик времени 
    timerCount += time;

    auto e = sf::Event();
    // Цикл, пока не все события обработаны  
    while (window->pollEvent(e))
    {
        // Закрыть окно 
        if (e.type == sf::Event::Closed)
            if (MessageBox(nullptr, L"Выход", L"Сообщение",
                MB_ICONQUESTION | MB_YESNO) == IDYES)
            {
                window->close();
                return;
            }
        // Нажата клавиша 
        if (e.type == sf::Event::KeyPressed)
        {
            // Закрыть окно 
            if (e.key.code == sf::Keyboard::Escape)  	 	 	 	
                if (MessageBox(nullptr, L"Выход", L"Сообщение", MB_ICONQUESTION | MB_YESNO) == IDYES)
                {
                window->close();
                return;
                }
            // Поставить/снять паузу 
            if (e.key.code == sf::Keyboard::Space && !bGameover)
            {
                bPaused = !bPaused;
                break;
            }
            // Повернуть фигуру  	 	 	
            if (e.key.code == sf::Keyboard::Up)
                bRotate = true;
            // Передвинуть фигуру 
            else if (e.key.code == sf::Keyboard::Right)
                ++dirx;
            else if (e.key.code == sf::Keyboard::Left)
                --dirx;
        }
        // Проверка клавиш мыши 
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (isMouseClick(txtButtonAuthor.getGlobalBounds()))
            {
                MessageBox(nullptr, L"Автор: Могильников Иван \nГруппа: КВБО-04-23", L"Автор", MB_OK);
            }
            // Кнопка Новая игра 
            if (isMouseClick(txtButtonNewGame.getGlobalBounds()))
            {
                resetGameParams();
            }
            // Кнопка Справка 
            if (isMouseClick(txtButtonHelp.getGlobalBounds()))
            {
                MessageBox(nullptr, L"Управление.\nСтрелки вправо, влево - перемещение по горизонтали\nстрелка вверх - повернуть\nпробел - пауза\nEsc - выход", L"Справка", MB_OK);
            }
            // Кнопка Пауза 
            if (isMouseClick(txtButtonPause.getGlobalBounds()))
            {
                bPaused = !bPaused;
                break;
            }
            // Кнопка Выход 
            if (isMouseClick(txtButtonExit.getGlobalBounds()))
            {
                if (MessageBox(nullptr, L"Выход", L"Сообщение", MB_ICONQUESTION | MB_YESNO) == IDYES)  	 	 	 	window->close();
            }
        }
    }
    // Опустить фигуру 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        delay = 0.05f;
    }
}

bool Tetris::isMouseClick(const sf::FloatRect rect) const
{
    // Определение координат курсора 
    sf::Vector2i mouseCoords = sf::Mouse::getPosition(*window);
    // Не нажата левая кнопка мыши 
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        return false;
    sf::Vector2u winSize = window->getSize();  	
    if ((unsigned)mouseCoords.x < winSize.x && (unsigned)mouseCoords.y < winSize.y &&
        (unsigned)mouseCoords.x > rect.left && (unsigned)mouseCoords.x < rect.left + rect.width &&
        (unsigned)mouseCoords.y > rect.top && (unsigned)mouseCoords.y < rect.top + rect.height)
    {
        // Курсор над кнопкой 
        return true;
    }
    return false;

}
void Tetris::resetGameParams()
{
    // Инициализация игрового поля   	
    for (std::size_t i = 0; i < lines; ++i)
        for (std::size_t j = 0; j < columns; ++j)
            area[i][j] = 0;

    // Инициализация игровых параметров  	
    dirx = score = 0;
    bRotate = bGameover = bPaused = false;  	timerCount = 0.f;
    delay = 0.3f;
    currentColor = std::rand() % numberColors + 1;

    // Случайная фигура 
    std::uint32_t number = std::rand() % numberForms;
    for (std::size_t i = 0; i < squares; ++i)
    {
        currentPosition[i].x = forms[number][i] % 2 + 4;
        currentPosition[i].y = forms[number][i] / 2;
    }
    // Следующая фигура  	
    number = std::rand() % numberForms;
    nextColor = std::rand() % numberColors + 1;
    for (std::size_t i = 0; i < squares; ++i) {
        nextFigure[i].x = forms[number][i] % 2 + 4; nextFigure[i].y = forms[number][i] / 2;
    }
}
void Tetris::draw() const
{
    // Очистить окно 
    window->clear(sf::Color::Black);

    // Нарисовать фон  	
    window->draw(rect1);
    window->draw(rect2);
    window->draw(rect3);

    // Нарисовать поставленные фигуры  	
    for (std::size_t i = 0; i < lines; ++i)
        for (std::size_t j = 0; j < columns; ++j)
            if (area[i][j] != 0)
            {
                rectFigure->setFillColor(figureColors[area[i][j] - 1]);
                rectFigure->setPosition(j * 36 + 3, i * 36 + 3);
                window->draw(*rectFigure);
            }
    // Нарисовать движущуюся фигуру  	
    for (std::size_t i = 0; i < squares; ++i)
    {
        rectFigure->setFillColor(figureColors[currentColor - 1]);   
        rectFigure->setPosition(currentPosition[i].x * 36 + 3, currentPosition[i].y * 36 + 3);
        window->draw(*rectFigure);
    }

    // Нарисовать следующую фигуру  	
    for (std::size_t i = 0; i < squares; ++i)
    {
        rectFigure->setFillColor(figureColors[nextColor - 1]);  	 	
        rectFigure->setPosition((nextFigure[i].x - 4) * 36 + 420, nextFigure[i].y * 36 + 20);
        window->draw(*rectFigure);
    }

    // Отобразить текстовые метки  	
    window->draw(txtScore);
    if (bGameover)
        window->draw(txtGameOver);
    if (bPaused)
        window->draw(txtPaused);


    window->draw(txtButtonNewGame);
    window->draw(txtButtonHelp);
    window->draw(txtButtonAuthor);
    window->draw(txtButtonPause);
    window->draw(txtButtonExit);  	// Перерисовать окно 
    window->display();
}
void Tetris::run()
{
    // Пока окно открыто 
    while (window->isOpen()) { // Выполнить обработчик событий 
        events();
        // Если не конец игры 
        if (!bGameover && !bPaused)
        {
            // Передвинуть фигуру по горизонтали  	 	
            changePosition();
            // Повернуть фигуру  	 	
            setRotate();
            // Сдвинуть вниз фигуру 
            moveToDown();
            // Изменить счет игры  	 	 	
            setScore();
            // Сбросить параметры 
            resetValues();
        }
        // Отобразить содержимое окна 
        draw();
    }
}

void Tetris::moveToDown()
{
    // Время задержки вышло  	
    if (timerCount > delay)
    {
        // Передвинуть фигуру на одну клетку вниз  	 	
        for (std::size_t i = 0; i < squares; ++i)
        {
            lastPosition[i] = currentPosition[i];
            ++currentPosition[i].y;
        }
        // Если фигура вышла за пределы игрового поля или  	 	// достигла верхней границы поставленных фигур  	 	
        if (checkPosition()) {
            for (std::size_t i = 0; i < squares; ++i)
                area[lastPosition[i].y][lastPosition[i].x] = currentColor;
                currentColor = nextColor;  	 	 	
            for (std::size_t i = 0; i < squares; ++i)
                currentPosition[i] = nextFigure[i];

            // Генерация новой фигуры  	 	 	
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
    // Если необходимо повернуть фигуру  	
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
    // Запомнить текущие координаты фигуры 
    for (std::size_t i = 0; i < squares; ++i)
    {
        lastPosition[i] = currentPosition[i];
        currentPosition[i].x += dirx;
    }
    if (checkPosition())
        // Вернуть предыдущее положение фигуры  	 	
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
    // Начать с нижней линии вверх  	
    std::uint32_t match = lines - 1;
    for (std::size_t i = match; i >= 1; --i)
    {
        // Посчитать количество занятых элементов на каждой линии 
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
        // Если не вся линия заполнена  	 	
        if (sum < columns)
            // Перейти к следующей линии 
            --match;
        else // Иначе 
            // Увеличить счет игры 
            txtScore.setString(sf::String(L"СЧЕТ: ") + std::to_string(++score));
    }
}



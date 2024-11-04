#pragma once 
#include <SFML/Graphics.hpp> 

/**
*	\brief Структура Координаты объекта
*/ struct Coords {
    sf::Int32 x, y;
};

/**
*	\brief Класс Игра Тетрис
 */ class Tetris {
private:
    /**
*	\brief Размер игрового поля в высоту
     */
    static const sf::Int32 lines = 20;

    /**
*	\brief Размер игрового поля в ширину
     */
    static const sf::Int32 columns = 10;

    /**
*	\brief Размер фигуры в квадратах
     */
    static const sf::Int32 squares = 4;

    /**
*	\brief Количество цветов фигур
     */
    static const sf::Int32 numberColors = 7;

    /**
*	\brief Количество типов фигур
     */
    static const sf::Int32 numberForms = 7;

    /**
*	\brief Игровое поле
     */
    sf::Int32 area[lines][columns];
    /**
*	\brief Список фигур
     */
    sf::Int32 forms[numberForms][squares]{
      {1,3,5,7}, // I 
      {2,4,5,7}, // Z 
      {3,5,4,6}, // S 
      {3,5,4,7}, // T 
      {2,3,5,7}, // L 
      {3,5,7,6}, // J 
      {2,3,4,5}, // O 
    };

    /**
    *	\brief Текущее положение фигуры
     */
    Coords currentPosition[squares];
    /**
    *	\brief Предыдущее положение фигуры
     */
    Coords lastPosition[squares];
    /**
    *	\brief Следующая фигура
         */
    Coords nextFigure[squares];

    /**
*	\brief Указатель на окно
     */
    sf::RenderWindow* window;

    /**
*	\brief Элемент фигуры
     */
    sf::RectangleShape* rectFigure;

    /**
*	\brief Доступные цвета фигур
     */
    sf::Color figureColors[numberColors]
    {
        sf::Color::Blue,  	 	
        sf::Color::Cyan,  	 	
        sf::Color::Green,  	 	
        sf::Color::Magenta,  	 	
        sf::Color::Red,  	 	
        sf::Color::White,  	 	
        sf::Color::Yellow
    };

    /**
*	\brief Обрамление игрового поля
     */
    sf::RectangleShape rect1;

    /**
*	\brief Обрамление следующей фигуры
     */
    sf::RectangleShape rect2;

    /**
*	\brief Обрамление кнопок
     */
    sf::RectangleShape rect3;

    /**
*	\brief Таймер
     */
    sf::Clock clock;
    /**
    *	\brief Шрифт  */ 
    sf::Font  font; /**
    *	\brief Текст счета игры
     */ 
    sf::Text txtScore;
     /**
     *	\brief Текст окончания игры
      */ 
    sf::Text txtGameOver;
      /**
      *	\brief Текст паузы игры
           */
    sf::Text txtPaused;

      /**
  *	\brief Текст кнопки Пауза
       */
    sf::Text txtButtonPause;

      /**
  *	\brief Текст кнопки Справка
       */
    sf::Text txtButtonHelp;

    sf::Text txtButtonAuthor;

      /**
  *	\brief Текст кнопки Новая игра
       */
    sf::Text txtButtonNewGame;

      /**
  *	\brief Текст кнопки Выход
       */
    sf::Text txtButtonExit;

      /**
  *	\brief Смещение фигуры по горизонтали
       */
    int dirx;

      /**
  *	\brief Цвет текущей фигуры
       */
    int currentColor;
      /**
  *	\brief Цвет следующей фигуры
       */
    int nextColor;

      /**
  *	\brief Счет игры
       */
    int score;

      /**
  *	\brief Признак поворота фигуры
   */ 
    bool bRotate;
   /**
   *	\brief Признак конца игры
    */ 
    bool bGameover; /**
   *	\brief Признак паузы
    */ 
    bool bPaused;
    /**
    *	\brief Счетчик времени
     */ 
    float timerCount;
     /**
 *	\brief Задержка анимации
      */
    float delay; public:
        /**
    *	\brief Конструктор
         */
        Tetris();

        /**
    *	\brief Деструктор
         */
        ~Tetris();

        /**
    *	\brief Основной метод программы
         */
        void run();
 protected:
     /**
 *	\brief Обработчик событий
      */
    void events();


   
    bool isMouseClick(sf::FloatRect rect) const;

 
    void resetGameParams();

     /**
 *	\brief Отображение элементов окна
      */
    void draw() const;

     /**
 *	\brief Передвинуть фигуру вниз
      */
    void moveToDown();
     /**
     *	\brief Повернуть фигуру
      */ 
    void setRotate(); /**
     *	\brief Сбросить параметры текущей фигуры
      */ 
    void resetValues();
      /**
      *	\brief Передвинуть фигуру по горизонтали
       */
    void changePosition();
      /**
      *	\brief Вышла ли фигура за пределы игрового поля
      *	или достигла верхней границы заполненного игрового поля
      *	\return true, если фигура вышла за пределы игрового поля
           */
    bool checkPosition() const;

      /**
  *	\brief Посчитать счет и проверить конец игры
       */
    void setScore();
};

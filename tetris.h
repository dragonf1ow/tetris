#pragma once 
#include <SFML/Graphics.hpp> 

/**
*	\brief ��������� ���������� �������
*/ struct Coords {
    sf::Int32 x, y;
};

/**
*	\brief ����� ���� ������
 */ class Tetris {
private:
    /**
*	\brief ������ �������� ���� � ������
     */
    static const sf::Int32 lines = 20;

    /**
*	\brief ������ �������� ���� � ������
     */
    static const sf::Int32 columns = 10;

    /**
*	\brief ������ ������ � ���������
     */
    static const sf::Int32 squares = 4;

    /**
*	\brief ���������� ������ �����
     */
    static const sf::Int32 numberColors = 7;

    /**
*	\brief ���������� ����� �����
     */
    static const sf::Int32 numberForms = 7;

    /**
*	\brief ������� ����
     */
    sf::Int32 area[lines][columns];
    /**
*	\brief ������ �����
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
    *	\brief ������� ��������� ������
     */
    Coords currentPosition[squares];
    /**
    *	\brief ���������� ��������� ������
     */
    Coords lastPosition[squares];
    /**
    *	\brief ��������� ������
         */
    Coords nextFigure[squares];

    /**
*	\brief ��������� �� ����
     */
    sf::RenderWindow* window;

    /**
*	\brief ������� ������
     */
    sf::RectangleShape* rectFigure;

    /**
*	\brief ��������� ����� �����
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
*	\brief ���������� �������� ����
     */
    sf::RectangleShape rect1;

    /**
*	\brief ���������� ��������� ������
     */
    sf::RectangleShape rect2;

    /**
*	\brief ���������� ������
     */
    sf::RectangleShape rect3;

    /**
*	\brief ������
     */
    sf::Clock clock;
    /**
    *	\brief �����  */ 
    sf::Font  font; /**
    *	\brief ����� ����� ����
     */ 
    sf::Text txtScore;
     /**
     *	\brief ����� ��������� ����
      */ 
    sf::Text txtGameOver;
      /**
      *	\brief ����� ����� ����
           */
    sf::Text txtPaused;

      /**
  *	\brief ����� ������ �����
       */
    sf::Text txtButtonPause;

      /**
  *	\brief ����� ������ �������
       */
    sf::Text txtButtonHelp;

    sf::Text txtButtonAuthor;

      /**
  *	\brief ����� ������ ����� ����
       */
    sf::Text txtButtonNewGame;

      /**
  *	\brief ����� ������ �����
       */
    sf::Text txtButtonExit;

      /**
  *	\brief �������� ������ �� �����������
       */
    int dirx;

      /**
  *	\brief ���� ������� ������
       */
    int currentColor;
      /**
  *	\brief ���� ��������� ������
       */
    int nextColor;

      /**
  *	\brief ���� ����
       */
    int score;

      /**
  *	\brief ������� �������� ������
   */ 
    bool bRotate;
   /**
   *	\brief ������� ����� ����
    */ 
    bool bGameover; /**
   *	\brief ������� �����
    */ 
    bool bPaused;
    /**
    *	\brief ������� �������
     */ 
    float timerCount;
     /**
 *	\brief �������� ��������
      */
    float delay; public:
        /**
    *	\brief �����������
         */
        Tetris();

        /**
    *	\brief ����������
         */
        ~Tetris();

        /**
    *	\brief �������� ����� ���������
         */
        void run();
 protected:
     /**
 *	\brief ���������� �������
      */
    void events();


   
    bool isMouseClick(sf::FloatRect rect) const;

 
    void resetGameParams();

     /**
 *	\brief ����������� ��������� ����
      */
    void draw() const;

     /**
 *	\brief ����������� ������ ����
      */
    void moveToDown();
     /**
     *	\brief ��������� ������
      */ 
    void setRotate(); /**
     *	\brief �������� ��������� ������� ������
      */ 
    void resetValues();
      /**
      *	\brief ����������� ������ �� �����������
       */
    void changePosition();
      /**
      *	\brief ����� �� ������ �� ������� �������� ����
      *	��� �������� ������� ������� ������������ �������� ����
      *	\return true, ���� ������ ����� �� ������� �������� ����
           */
    bool checkPosition() const;

      /**
  *	\brief ��������� ���� � ��������� ����� ����
       */
    void setScore();
};

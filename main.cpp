

#include "settings.h"
#include <ctime>
using namespace sf;

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FPS);
	//создание объектов игры
	//ракетки
	RectangleShape leftBat, rightBat;
	leftBat.setSize(batSize);
	rightBat.setSize(batSize);
	leftBat.setFillColor(leftBatColor);
	rightBat.setFillColor(rightBatColor);
	leftBat.setPosition(batOffset, (WINDOW_HEIGHT - batHeight) / 2);
	rightBat.setPosition(WINDOW_WIDTH - batOffset, (WINDOW_HEIGHT - batHeight) / 2);
	float leftBatSpeedy = 0.f;
	float rightBatSpeedy = 0.f;


	//шарик
	CircleShape ball(ballRadius);
	ball.setFillColor(ballColor);
	ball.setPosition((WINDOW_WIDTH - 2 * ballRadius) / 2,
		(WINDOW_HEIGHT - 2 * ballRadius) / 2);

	srand(time(nullptr));
	float arr_speed[]{ -5.f,-4.f,-3.f,-2.f,-1.f,1.f,2.f,3.f,4.f,5.f };
	int index = rand() % 10;
	float ball_speedx = arr_speed[index];
	index = rand() % 10;
	float ball_speedy = arr_speed[index];
	float ball_dx = 2.f;
	float ball_dy = 2.f;

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		//1 Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}

		//2 Обновление объектов
		//шарик
		ball.move(ball_speedx, ball_speedy);
		if (ball.getPosition().x<=0||ball.getPosition().x >= (WINDOW_WIDTH - 2 * ballRadius))
		{
			ball_speedx = -ball_speedx;
		}
		if (ball.getPosition().y <= 0 || ball.getPosition().y >= (WINDOW_HEIGHT - 2 * ballRadius))
		{
			ball_speedy = -ball_speedy;
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			leftBatSpeedy = -batSpeed;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			leftBatSpeedy = batSpeed;
		}
		leftBat.move(0, leftBatSpeedy);
		leftBatSpeedy = 0.f;
		
		if (leftBat.getPosition().y <= 0 || leftBat.getPosition().y >= WINDOW_WIDTH)
		{
			leftBat.setPosition(batOffset, 0);
		}
		if (leftBat.getPosition().y +80 >= WINDOW_HEIGHT || leftBat.getPosition().y+80 >= WINDOW_WIDTH)
		{
			leftBat.setPosition(batOffset, WINDOW_HEIGHT -80);
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			rightBatSpeedy = -batSpeed;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			rightBatSpeedy = batSpeed;
		}
		rightBat.move(0, rightBatSpeedy);
		rightBatSpeedy = 0.f;
		if (rightBat.getPosition().y <= 0 || rightBat.getPosition().y >= WINDOW_WIDTH)
		{
			rightBat.setPosition(WINDOW_WIDTH-batOffset, 0);
		}
		if (rightBat.getPosition().y + 80 >= WINDOW_HEIGHT || rightBat.getPosition().y + 80 >= WINDOW_WIDTH)
		{
			rightBat.setPosition(WINDOW_WIDTH - batOffset, WINDOW_HEIGHT - 80);
		}
		//3 Отрисовка окна
		//3.1 Очистка окна
		window.clear(Color{ 135, 206, 250 });
		//3.2 Отрисовка объектов (В ПАМЯТИ!)
		window.draw(leftBat);
		window.draw(rightBat);
		window.draw(ball);
		//3.3 вывод на экран
		window.display();
	}

	return 0;
}

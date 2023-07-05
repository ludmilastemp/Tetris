#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <chrono>

int field_f[30][20]; int n = 0; int x = 0; int y = 0; int t = 1000; int redstr = 1;
int width = 10; int figures[16];
int list_figures[6][16] = { {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

//доп фигуры   лента справа      красная полоса+-, ускорение+, ширина+, доп фигура

void Field(sf::RenderWindow& window, sf::Image& img) {
	for (int k = 0; k < 20; ++k) {
		for (int i = 0; i < 900; ++i) {
			img.setPixel(i, k * 30, sf::Color::Black);
		}
	}
	for (int k = 0; k < 30; ++k) {
		for (int i = 0; i < 600; ++i) {
			img.setPixel(k * 30, i, sf::Color::Black);
		}
	}
}

void DrawSquare(int a, int b, sf::RenderWindow& window, sf::Image& img) {
	sf::ConvexShape square(4);
	square.setPoint(0, sf::Vector2f(b * 30, a * 30));
	square.setPoint(1, sf::Vector2f(b * 30 + 30, a * 30));
	square.setPoint(2, sf::Vector2f(b * 30 + 30, a * 30 + 30));
	square.setPoint(3, sf::Vector2f(b * 30, a * 30 + 30));
	square.setFillColor(sf::Color::Black);
	window.draw(square);
}

void DrawSquare1(int a, int b, sf::RenderWindow& window, sf::Image& img) {
	sf::ConvexShape square(4);
	square.setPoint(0, sf::Vector2f(b * 30, a * 30));
	square.setPoint(1, sf::Vector2f(b * 30 + 30, a * 30));
	square.setPoint(2, sf::Vector2f(b * 30 + 30, a * 30 + 30));
	square.setPoint(3, sf::Vector2f(b * 30, a * 30 + 30));
	square.setFillColor(sf::Color::Blue);
	window.draw(square);
}

void DrawFigures(sf::RenderWindow& window, sf::Image& img) {
	for (int i = 0; i < 16; ++i) {
		if (figures[i] == 1) DrawSquare(i / 4 + y, i % 4 + x, window, img);
	}
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (field_f[i][j] == 1) DrawSquare1(j, i, window, img);
		}
	}
	for (int i = width; i < 30; ++i) {
		for (int j = 0; j < 20; ++j) {
			sf::ConvexShape rectangle(4);
			rectangle.setPoint(0, sf::Vector2f(i * 30 + 1, j * 30 + 1));
			rectangle.setPoint(1, sf::Vector2f(i * 30 + 30, j * 30 + 1));
			rectangle.setPoint(2, sf::Vector2f(i * 30 + 30, j * 30 + 30));
			rectangle.setPoint(3, sf::Vector2f(i * 30 + 1, j * 30 + 30));
			rectangle.setFillColor(sf::Color::Red);
			window.draw(rectangle);
		}
	}
}

void TurnFigures(sf::RenderWindow& window, sf::Image& img) {
	int a[16]; 
	a[0] = figures[12];   a[1] = figures[8];   a[2] = figures[4];   a[3] = figures[0];
	a[4] = figures[13];   a[5] = figures[9];   a[6] = figures[5];   a[7] = figures[1];
	a[8] = figures[14];   a[9] = figures[10];   a[10] = figures[6];   a[11] = figures[2];
	a[12] = figures[15];   a[13] = figures[11];   a[14] = figures[7];   a[15] = figures[3];
	for (int i = 0; i < 16; ++i) if ((field_f[x + (i % 4)][y + (x / 4)] == 1 && a[i] == 1) || y > 16) return;
	for (int i = 0; i < 16; ++i) figures[i] = a[i];
	if (x > width - 4) x = width - 4; else if (x < 0) x = 0;
}

void MovementFigures(int k, sf::RenderWindow& window, sf::Image& img) {
	if (k == 1) { //вправо
		if (figures[3] == 1) { if (x + 4 < width && field_f[x + 4][y] == 0) {} else return; }
		else if (figures[2] == 1) { if (x + 3 < width && field_f[x + 3][y] == 0) {} else return; }
		else if (figures[1] == 1) { if (x + 2 < width && field_f[x + 2][y] == 0) {} else return; }
		else if (figures[0] == 1) { if (x + 1 < width && field_f[x + 1][y] == 0) {} else return; }
		if (figures[7] == 1) { if (x + 4 < width && field_f[x + 4][y + 1] == 0) {} else return; }
		else if (figures[6] == 1) { if (x + 3 < width && field_f[x + 3][y + 1] == 0) {} else return; }
		else if (figures[5] == 1) { if (x + 2 < width && field_f[x + 2][y + 1] == 0) {} else return; }
		else if (figures[4] == 1) { if (x + 1 < width && field_f[x + 1][y + 1] == 0) {} else return; }
		if (figures[11] == 1) { if (x + 4 < width && field_f[x + 4][y + 2] == 0) {} else return; }
		else if (figures[10] == 1) { if (x + 3 < width && field_f[x + 3][y + 2] == 0) {} else return; }
		else if (figures[9] == 1) { if (x + 2 < width && field_f[x + 2][y + 2] == 0) {} else return; }
		else if (figures[8] == 1) { if (x + 1 < width && field_f[x + 1][y + 2] == 0) {} else return; }
		if (figures[15] == 1) { if (x + 4 < width && field_f[x + 4][y + 3] == 0) {} else return; }
		else if (figures[14] == 1) { if (x + 3 < width && field_f[x + 3][y + 3] == 0) {} else return; }
		else if (figures[13] == 1) { if (x + 2 < width && field_f[x + 2][y + 3] == 0) {} else return; }
		else if (figures[12] == 1) { if (x + 1 < width && field_f[x + 1][y + 3] == 0) {} else return; }
		++x;
	}
	if (k == 3) { //влево
		if (figures[0] == 1) { if (field_f[x - 1][y] == 0) {} else return; }
		else if (figures[1] == 1) { if (x > 0 && field_f[x][y] == 0) {} else return; }
		else if (figures[2] == 1) { if (x + 1 > 0 && field_f[x + 1][y] == 0) {} else return; }
		else if (figures[3] == 1) { if (x + 2 > 0 && field_f[x + 2][y] == 0) {} else return; }
		if (figures[4] == 1) { if (field_f[x - 1][y] == 0) {} else return; }
		else if (figures[5] == 1) { if (x > 0 && field_f[x][y + 1] == 0) {} else return; }
		else if (figures[6] == 1) { if (x + 1 > 0 && field_f[x + 1][y + 1] == 0) {} else return; }
		else if (figures[7] == 1) { if (x + 2 > 0 && field_f[x + 2][y + 1] == 0) {} else return; }
		if (figures[8] == 1) { if (field_f[x - 1][y + 2] == 0) {} else return; }
		else if (figures[9] == 1) { if (x > 0 && field_f[x][y + 2] == 0) {} else return; }
		else if (figures[10] == 1) { if (x + 1 > 0 && field_f[x + 1][y + 2] == 0) {} else return; }
		else if (figures[11] == 1) { if (x + 2 > 0 && field_f[x + 2][y + 2] == 0) {} else return; }
		if (figures[12] == 1) { if (field_f[x - 1][y + 3] == 0) {} else return; }
		else if (figures[13] == 1) { if (x > 0 && field_f[x][y + 3] == 0) {} else return; }
		else if (figures[14] == 1) { if (x + 1 > 0 && field_f[x + 1][y + 3] == 0) {} else return; }
		else if (figures[15] == 1) { if (x + 2 > 0 && field_f[x + 2][y + 3] == 0) {} else return; }
		if (x > 0) --x;
	}
}

void DownFigures(sf::RenderWindow& window, sf::Image& img) {
	if (figures[12] == 1) { if (y + 4 < 20 && field_f[x][y + 4] == 0) {} else return; }
	else if (figures[8] == 1) { if (y + 3 < 20 && field_f[x][y + 3] == 0) {} else return; }
	else if (figures[4] == 1) { if (y + 2 < 20 && field_f[x][y + 2] == 0) {} else return; }
	else if (figures[0] == 1) { if (y + 1 < 20 && field_f[x][y + 1] == 0) {} else return; }
	if (figures[13] == 1) { if (y + 4 < 20 && field_f[x + 1][y + 4] == 0) {} else return; }
	else if (figures[9] == 1) { if (y + 3 < 20 && field_f[x + 1][y + 3] == 0) {} else return; }
	else if (figures[5] == 1) { if (y + 2 < 20 && field_f[x + 1][y + 2] == 0) {} else return; }
	else if (figures[1] == 1) { if (y + 1 < 20 && field_f[x + 1][y + 1] == 0) {} else return; }
	if (figures[14] == 1) { if (y + 4 < 20 && field_f[x + 2][y + 4] == 0) {} else return; }
	else if (figures[10] == 1) { if (y + 3 < 20 && field_f[x + 2][y + 3] == 0) {} else return; }
	else if (figures[6] == 1) { if (y + 2 < 20 && field_f[x + 2][y + 2] == 0) {} else return; }
	else if (figures[2] == 1) { if (y + 1 < 20 && field_f[x + 2][y + 1] == 0) {} else return; }
	if (figures[15] == 1) { if (y + 4 < 20 && field_f[x + 3][y + 4] == 0) {} else return; }
	else if (figures[11] == 1) { if (y + 3 < 20 && field_f[x + 3][y + 3] == 0) {} else return; }
	else if (figures[7] == 1) { if (y + 2 < 20 && field_f[x + 3][y + 2] == 0) {} else return; }
	else if (figures[3] == 1) { if (y + 1 < 20 && field_f[x + 3][y + 1] == 0) {} else return; }
	++y;
}

void FixFigures(sf::RenderWindow& window, sf::Image& img) {
	int ch = 0; for (int i = 0; i < 1; ++i) {
		if (figures[12] == 1) { if (!(y + 4 < 20 && field_f[x][y + 4] == 0)) break; } 
		else if (figures[8] == 1) { if (!(y + 3 < 20 && field_f[x][y + 3] == 0)) break; } 
		else if (figures[4] == 1) { if (!(y + 2 < 20 && field_f[x][y + 2] == 0)) break; } 
		else if (figures[0] == 1) { if (!(y + 1 < 20 && field_f[x][y + 1] == 0)) break; } 
		if (figures[13] == 1) { if (!(y + 4 < 20 && field_f[x + 1][y + 4] == 0)) break; }
		else if (figures[9] == 1) { if (!(y + 3 < 20 && field_f[x + 1][y + 3] == 0)) break; } 
		else if (figures[5] == 1) { if (!(y + 2 < 20 && field_f[x + 1][y + 2] == 0)) break; } 
		else if (figures[1] == 1) { if (!(y + 1 < 20 && field_f[x + 1][y + 1] == 0)) break; } 
		if (figures[14] == 1) { if (!(y + 4 < 20 && field_f[x + 2][y + 4] == 0)) break; } 
		else if (figures[10] == 1) { if (!(y + 3 < 20 && field_f[x + 2][y + 3] == 0)) break; } 
		else if (figures[6] == 1) { if (!(y + 2 < 20 && field_f[x + 2][y + 2] == 0)) break; } 
		else if (figures[2] == 1) { if (!(y + 1 < 20 && field_f[x + 2][y + 1] == 0)) break; } 
		if (figures[15] == 1) { if (!(y + 4 < 20 && field_f[x + 3][y + 4] == 0)) break; } 
		else if (figures[11] == 1) { if (!(y + 3 < 20 && field_f[x + 3][y + 3] == 0)) break; } 
		else if (figures[7] == 1) { if (!(y + 2 < 20 && field_f[x + 3][y + 2] == 0)) break; } 
		else if (figures[3] == 1) { if (!(y + 1 < 20 && field_f[x + 3][y + 1] == 0)) break; } 
		++ch;
	}
	if (ch == 1) return;
	for (int i = 0; i < 16; ++i) {
		if (figures[i] == 1) field_f[x + (i % 4)][y + (i / 4)] = 1;
		figures[i] = 0;
	}
	x = width / 2; y = 0; n = rand() % 5; t -= 5;
	for (int i = 0; i < 16; ++i) figures[i] = list_figures[n][i];
}

void DeleteLine(sf::RenderWindow& window, sf::Image& img) {
	int ch;
	for (int i = 0; i < 20; ++i) {
		ch = 0;
		for (int j = 0; j < width; ++j) if (field_f[j][i] == 1) ++ch;
		if (ch == width) {
			for (int m = i; m > 0; --m) {
				for (int k = 0; k < width; ++k) {
					field_f[k][m] = field_f[k][m - 1];
				}
			}
			for (int k = 0; k < width; ++k) field_f[k][0] = 0;
		}
	}
}

void Loss(sf::RenderWindow& window, sf::Image& img) {
	int ch = 0; 
	for (int i = 0; i < width; ++i) if (field_f[i][0] == 1) ++ch;
	if (ch > 0) window.close();
}

void DrawFunction(sf::RenderWindow& window, sf::Image& img, sf::Font& font) {
	sf::Text text;
	text.setFont(font);
	text.setString("Setting");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(265, 20);
	window.draw(text);
	text.setFont(font);
	text.setString("Show the following shares");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(30, 70);
	window.draw(text);
	text.setFont(font);
	text.setString("Speed up                            time = ");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(30, 120);
	window.draw(text);
	text.setFont(font);
	text.setFont(font);
	text.setString(std::to_string(t));
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(370, 120);
	window.draw(text);
	text.setFont(font);
	text.setString("Increase the width            width =");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(30, 170);
	window.draw(text);
	text.setFont(font);
	text.setString(std::to_string(width));
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(385, 170);
	window.draw(text);
	text.setFont(font);
	text.setString("Add your own shape");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(30, 220);
	window.draw(text);

}

void DrawFunction1(sf::RenderWindow& window, sf::Image& img) {
	if (redstr == 1) {
		sf::ConvexShape rectangle(4);
		rectangle.setPoint(0, sf::Vector2f(350, 78));
		rectangle.setPoint(1, sf::Vector2f(380, 78));
		rectangle.setPoint(2, sf::Vector2f(380, 92));
		rectangle.setPoint(3, sf::Vector2f(350, 92));
		rectangle.setFillColor(sf::Color::Red);
		window.draw(rectangle);
		sf::ConvexShape right_button(4);
		right_button.setPoint(0, sf::Vector2f(373, 85));
		right_button.setPoint(1, sf::Vector2f(380, 78));
		right_button.setPoint(2, sf::Vector2f(387, 85));
		right_button.setPoint(3, sf::Vector2f(380, 92));
		right_button.setFillColor(sf::Color::Red);
		window.draw(right_button);
	}
	if (redstr == 0) {
		sf::ConvexShape rectangle(4);
		rectangle.setPoint(0, sf::Vector2f(350, 78));
		rectangle.setPoint(1, sf::Vector2f(380, 78));
		rectangle.setPoint(2, sf::Vector2f(380, 92));
		rectangle.setPoint(3, sf::Vector2f(350, 92));
		rectangle.setFillColor(sf::Color::Yellow);
		window.draw(rectangle);
		sf::ConvexShape right_button(4);
		right_button.setPoint(0, sf::Vector2f(373, 85));
		right_button.setPoint(1, sf::Vector2f(380, 78));
		right_button.setPoint(2, sf::Vector2f(387, 85));
		right_button.setPoint(3, sf::Vector2f(380, 92));
		right_button.setFillColor(sf::Color::Yellow);
		window.draw(right_button);
	}
	sf::ConvexShape left_button(4);
	left_button.setPoint(0, sf::Vector2f(343, 85));
	left_button.setPoint(1, sf::Vector2f(350, 78));
	left_button.setPoint(2, sf::Vector2f(357, 85));
	left_button.setPoint(3, sf::Vector2f(350, 92));
	left_button.setFillColor(sf::Color::Red);
	window.draw(left_button);
	sf::ConvexShape button1(4);
	button1.setPoint(0, sf::Vector2f(430, 132));
	button1.setPoint(1, sf::Vector2f(437, 124));
	button1.setPoint(2, sf::Vector2f(444, 132));
	button1.setPoint(3, sf::Vector2f(437, 140));
	button1.setFillColor(sf::Color::Red);
	window.draw(button1);
	sf::ConvexShape button2(4);
	button2.setPoint(0, sf::Vector2f(430, 182));
	button2.setPoint(1, sf::Vector2f(437, 174));
	button2.setPoint(2, sf::Vector2f(444, 182));
	button2.setPoint(3, sf::Vector2f(437, 190));
	button2.setFillColor(sf::Color::Red);
	window.draw(button2);
}

void Setting(sf::RenderWindow& window1, sf::Image& img1) {
	/*for (int i = 0; i < 460; ++i) {
		for (int j = 0; j < 160; ++j) {
			if (redstr == 1) {
				if (i > 350 && i < 380 && j > 77 && j < 93) img1.setPixel(i, j, sf::Color::Red);
				if ((i - 350) * (i - 350) + (j - 85) * (j - 85) < 64) img1.setPixel(i, j, sf::Color::Red);
				if ((i - 380) * (i - 380) + (j - 85) * (j - 85) < 64) img1.setPixel(i, j, sf::Color::Black);
			}
			else if (redstr == 0) {
				if (i > 350 && i < 380 && j > 77 && j < 93) img1.setPixel(i, j, sf::Color::Yellow);
				if ((i - 350) * (i - 350) + (j - 85) * (j - 85) < 64) img1.setPixel(i, j, sf::Color::Black);
				if ((i - 380) * (i - 380) + (j - 85) * (j - 85) < 64) img1.setPixel(i, j, sf::Color::Yellow);
			}
		}
	}*/
	sf::Font font1;
	if (!font1.loadFromFile("D:/Proga/Calender/Raleway-Regular.ttf"));
	sf::Texture texture1;
	texture1.loadFromImage(img1);
	sf::Sprite sprite1;
	sprite1.setTexture(texture1, true);
	while (window1.isOpen()) {
		sf::Event event;
		while (window1.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window1.close();
			else if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left) {
				if (event.mouseButton.x > 340 && event.mouseButton.x < 390 && event.mouseButton.y > 75 && event.mouseButton.y < 95) {
					if (redstr == 1) redstr = 0; else redstr = 1;
				}
				if (event.mouseButton.x > 430 && event.mouseButton.x < 445 && event.mouseButton.y > 123 && event.mouseButton.y < 141) {
					--t;
				}
				if (event.mouseButton.x > 430 && event.mouseButton.x < 445 && event.mouseButton.y > 173 && event.mouseButton.y < 191) {
					if (width < 30) ++width;
				}
				if (event.mouseButton.x > 870 && event.mouseButton.x < 870 && event.mouseButton.y > 870 && event.mouseButton.y < 30) {}

			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) window1.close();
		}
		window1.clear();
		window1.draw(sprite1);
		DrawFunction(window1, img1, font1);
		DrawFunction1(window1, img1);
		window1.display();

	}
}

void Event(sf::RenderWindow& window, sf::Image& img) {
	auto begin = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	sf::Font font;
	if (!font.loadFromFile("D:/Proga/Calender/Raleway-Regular.ttf"));
	sf::Texture texture;
	texture.loadFromImage(img);
	sf::Sprite sprite;
	sprite.setTexture(texture, true);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left) {
				if (event.mouseButton.x > 870 && event.mouseButton.y < 30) {
					sf::RenderWindow window1(sf::VideoMode(600, 400), "!");
					sf::Image img1;
					img1.create(600, 400, sf::Color::White);
					Setting(window1, img1);
				}
			}
			//else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) cd = 1;
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
				MovementFigures(1, window, img);
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
				for (int i = 0; i < 20; ++i) DownFigures(window, img);
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
				MovementFigures(3, window, img);
			else if (event.type == sf::Event::TextEntered && event.text.unicode == 113)
				for (int i = 0; i < 3; ++i) TurnFigures(window, img);
			else if (event.type == sf::Event::TextEntered && event.text.unicode == 101) TurnFigures(window, img);
			else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift)) {
				
			}
		}
		window.clear();
		window.draw(sprite);
		DrawFigures(window, img);
		FixFigures(window, img);
		DeleteLine(window, img);
		Loss(window, img);
		window.display();
		if (time.count() > t) {
			DownFigures(window, img);
			begin = std::chrono::high_resolution_clock::now();
		}
		end = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	}
}

int main()
{
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < 20; ++j) {
			field_f[i][j] = 0;
		}
	}
	for (int i = 0; i < 16; ++i) figures[i] = list_figures[n][i];
	x = width / 2;
	sf::RenderWindow window(sf::VideoMode(900, 600), "!");
	sf::Image img;
	img.create(900, 600, sf::Color::White);
	Field(window, img);
	Event(window, img);
	return 0;
}
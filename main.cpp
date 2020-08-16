#include <SFML\Graphics.hpp>
#include <ctime>
using namespace sf;
const int W = 5;
int grid[W][W];
int width = 142, height = 142;
bool backEnd = false,//picture of end of the game
	 win = false,//picture of win
	 start = true;//picture of start

void randPosition() {//Randow position square wich has value 2
	int row = rand() % W + 1;
	int col = rand() % W + 1;
	if (!grid[row][col]) grid[row][col] = 2;
}

void startGame() {
	randPosition(); randPosition();//Start game
	start = false; //Rmove picture of starting game
	backEnd = false;//We remove the background to lose
	win = false;//Remove picture about win the game
}

void winGame() {
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < W; j++) {
			if (grid[i][j] == 2048) {
				win = true;
			}
		}
	}
}

void finishGame() {
	int countFree = 0;
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < W; j++) {
			if (!grid[i][j]) countFree++;
		}
	}
	if (!countFree) backEnd = true;
}

void moveUp(Sprite s) {//Mowe Up
	int row;
	for (int i = 0; i < W; i++) {
		for (int j = 1; j < W; j++) {
			if (grid[j][i]) {
				row = j;
				while (row > 0) {
					if (!grid[row-1][i]) {
						grid[row - 1][i] = grid[row][i];
						grid[row][i] = 0;
						row--;
						
					}
					else if (grid[row - 1][i] == grid[row][i]) {
						grid[row - 1][i] *= 2;
						grid[row][i] = 0;
						
						break;
					}
					else break;
				}
			}
		}
	}
	randPosition(); winGame(); finishGame();

}

void moveDown() {//Move down
	int row;
	for (int i = 0; i < W; i++) {
		for (int j = W - 2; j >= 0; j--) {
			if (grid[j][i]) {
				row = j;
				while (row + 1 < W) {
					if (!grid[row + 1][i]) {
						grid[row + 1][i] = grid[row][i];
						grid[row][i] = 0;
						row++;
					}
					else if (grid[row + 1][i] == grid[row][i]) {
						grid[row + 1][i] *= 2;
						grid[row][i] = 0;
						
						break;
					}
					else break;
				}
			}
		}
	}
	randPosition(); winGame(); finishGame();
}

void moveRight() {//Move right
	int coll;
	for (int i = 0; i < W; i++) {
		for (int j = W - 2; j >= 0; j--) {
			if (grid[i][j]) {
				coll = j;
				while (coll + 1 < W) {
					if (!grid[i][coll + 1]) {
						grid[i][coll + 1] = grid[i][coll];
						grid[i][coll] = 0;
						coll++;
					}
					else if (grid[i][coll + 1] == grid[i][coll]) {
						grid[i][coll + 1] *= 2;
						grid[i][coll] = 0;
						
						break;
					}
					else break;
				}
			}
		}
	}
	randPosition(); winGame();  finishGame();

}

void moveLeft() {//Move left
	int coll;
	for (int i = 0; i < W; i++) {
		for (int j = 1; j < W; j++) {
			if (grid[i][j]) {
				coll = j;
				while (coll - 1 >= 0) {
					if (!grid[i][coll - 1]) {
						grid[i][coll - 1] = grid[i][coll];
						grid[i][coll] = 0;
						coll--;
					}
					else if (grid[i][coll - 1] == grid[i][coll]) {
						grid[i][coll - 1] *= 2;
						grid[i][coll] = 0;
						break;
					}
					else break;
				}
			}
		}
	}
	randPosition(); winGame();  finishGame();
}


int main() {
	srand(time(NULL));

	RenderWindow window(sf::VideoMode(710, 710), "2048");

	window.setFramerateLimit(60);//60 fps

	///////////////////////Images/////////////////////////
	Texture map_texture, end_texture, win_texture, start_texture;
	map_texture.loadFromFile("images/MAP.png");
	end_texture.loadFromFile("images/end.jpg");
	win_texture.loadFromFile("images/win.jpg");
	start_texture.loadFromFile("images/start.jpg");
	Sprite map(map_texture), sEnd(end_texture), sWin(win_texture), sStart(start_texture);
	///////////////////////////////////////////////////////////////

	int time = 150;//delay time

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Up)) { moveUp(map); sleep(milliseconds (time)); }//move UP
		if (Keyboard::isKeyPressed(Keyboard::Down)) { moveDown(); sleep(milliseconds(time)); }//move Down
		if (Keyboard::isKeyPressed(Keyboard::Left)) { moveLeft();  sleep(milliseconds(time));} //move Left
		if (Keyboard::isKeyPressed(Keyboard::Right)) { moveRight();  sleep(milliseconds(time));}//move Right
		if (Keyboard::isKeyPressed(Keyboard::Space)) {//restart game
			for (int i = 0; i < W; i++) {
				for (int j = 0; j < W; j++) {
					grid[i][j] = 0; //empty square
				}
			}
			startGame();//start game
			sleep(milliseconds(time));//pause 
		}
		

		window.clear();

		////////////////////////////Draw squares//////////////////////////
		for (int i = 0; i < W; i++) {
			for (int j = 0; j < W; j++) {
				if (grid[i][j] == 0) map.setTextureRect(IntRect(0, 0, 142, 142));
				if (grid[i][j] == 2) map.setTextureRect(IntRect(142, 0, 142, 142));
				if (grid[i][j] == 4) map.setTextureRect(IntRect(291, 0, 142, 142));
				if (grid[i][j] == 8) map.setTextureRect(IntRect(435, 0, 142, 142));
				if (grid[i][j] == 16) map.setTextureRect(IntRect(581, 0, 142, 142));
				if (grid[i][j] == 32) map.setTextureRect(IntRect(726, 0, 142, 142));
				if (grid[i][j] == 64) map.setTextureRect(IntRect(869, 0, 142, 142));
				if (grid[i][j] == 128) map.setTextureRect(IntRect(1014, 0, 142, 142));
				if (grid[i][j] == 256) map.setTextureRect(IntRect(1158, 0, 142, 142));
				if (grid[i][j] == 512) map.setTextureRect(IntRect(1302, 0, 142, 142));
				if (grid[i][j] == 1024) map.setTextureRect(IntRect(1446, 0, 142, 142));
				if (grid[i][j] == 2048) map.setTextureRect(IntRect(1591, 0, 142, 142));
				map.setPosition(j*142, i*142);
				window.draw(map);
			}
		}
		if (backEnd) window.draw(sEnd); //draw picture of lose
		if (win) window.draw(sWin); //draw picture of win
		if (start) window.draw(sStart);//draw picture of start
		/////////////////////////////////////////////////////////

		
		window.display();
	}
	return 0;
}
#ifndef GAME_H
#define GAME_H

class Game
{
public:
	static Game* instance(){
		if (!instance){
			inst = new Game();
		}
		return inst;
	}
	~Game(void);
	int run(int, char**);

protected:
	Game(void);
	static Game* inst;

	int WIN_WIDTH, WIN_HEIGHT;
};

#endif
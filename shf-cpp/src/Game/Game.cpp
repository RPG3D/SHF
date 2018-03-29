#include "Game.h"
#include "Config\Config.h"


Game::Game()
{
}

Game::~Game()
{
}

int Game::run()
{	
	int w = DEFAULT_WINDOW_WIDTH, h = DEFAULT_WINDOW_HEIGHT;
	Config::getInstance()->getWindowSize(&w, &h);
	if (Engine::getInstance()->init(gameTitle, w, h, Config::getInstance()->fullScreen) != initOK)
	{
		return -1;
	}

	//�������壬s�Ŀռ佻�����洦������delete
	char * s = NULL;
	int len = PakFile::readFile(gameFont, &s);
	if (s != NULL && len > 0)
	{
		Engine::getInstance()->setFontFromMem(s, len);
	}
	
	//���������ʽ
	IMPImage * mouseImage = IMP::createIMPImage("mpc\\ui\\common\\mouse.mpc");
	Engine::getInstance()->setMouseFromImpImage(mouseImage);
	IMP::clearIMPImage(mouseImage);
	delete mouseImage;

	Title * title = new Title;
	int ret = title->run();
	delete title;
	printf("Release Engine!\n");
	Engine::getInstance()->destroyEngine();
	printf("Game End!\n");
	return ret;
}

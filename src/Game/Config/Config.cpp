#include "Config.h"

bool Config::fullScreen = true;
bool Config::playerAlpha = true;
bool Config::canChangeDisplayMode = false;
int Config::windowWidth = DEFAULT_WINDOW_WIDTH;
int Config::windowHeight = DEFAULT_WINDOW_HEIGHT;
double Config::gameSpeed = SPEED_TIME_DEFAULT;

Config::Config()
{
}

Config::~Config()
{
}

void Config::load()
{
	std::string fileName = CONFIG_INI;
	GameLog::write("load config \n");
	INIReader ini(fileName);
	GameLog::write("load config file done \n");
	fullScreen = ini.GetBoolean("game", "fullScreen", fullScreen);
	playerAlpha = ini.GetBoolean("game", "playeralpha", playerAlpha);
	canChangeDisplayMode = ini.GetBoolean("game", "canchangedisplaymode", canChangeDisplayMode);

	windowWidth = ini.GetInteger("game", "windowwidth", windowWidth);
	windowHeight = ini.GetInteger("game", "windowheight", windowHeight);

	auto speed = ini.GetInteger("game", "speed", convSpeedToInt(gameSpeed));
	gameSpeed = convSpeedToDouble(speed);

	float musicVolume = ((float)ini.GetInteger("game", "musicvolume", 100)) / 100.0f;
	float soundVolume = ((float)ini.GetInteger("game", "soundvolume", 100)) / 100.0f;
	if (musicVolume < 0.0f)
	{
		musicVolume = 0.0f;
	}
	else if (musicVolume > 1.0f)
	{
		musicVolume = 1.0f;
	}
	Engine::getInstance()->setBGMVolume(musicVolume);
	if (soundVolume < 0.0f)
	{
		soundVolume = 0.0f;
	}
	else if (soundVolume > 1.0f)
	{
		soundVolume = 1.0f;
	}
	Engine::getInstance()->setSoundVolume(soundVolume);
}

void Config::save()
{
	std::string fileName = CONFIG_INI;
	INIReader ini(fileName);
	ini.SetBoolean("game", "fullscreen", fullScreen);
	ini.SetBoolean("game", "canchangedisplaymode", canChangeDisplayMode);
	ini.SetBoolean("game", "playeralpha", playerAlpha);
	float musicVolume = Engine::getInstance()->getBGMVolume();
	float soundVolume = Engine::getInstance()->getSoundVolume();
	//ini.SetReal("game", "speed", gameSpeed);
	ini.SetInteger("game", "speed", convSpeedToInt(gameSpeed));
	if (musicVolume < 0.0f)
	{
		musicVolume = 0.0f;
	}
	else if (musicVolume > 1.0f)
	{
		musicVolume = 1.0f;
	}
	if (soundVolume < 0.0f)
	{
		soundVolume = 0.0f;
	}
	else if (soundVolume > 1.0f)
	{
		soundVolume = 1.0f;
	}
	ini.SetInteger("game", "musicvolume", (int)(musicVolume * 100));
	ini.SetInteger("game", "soundvolume", (int)(soundVolume * 100));
	ini.SetInteger("game", "windowwidth", windowWidth);
	ini.SetInteger("game", "windowheight", windowHeight);
	ini.saveToFile(fileName);
}

float Config::getMusicVolume()
{
	return Engine::getInstance()->getBGMVolume();
}

float Config::getSoundVolume()
{
	return Engine::getInstance()->getSoundVolume();
}

float Config::setMusicVolume(float volume)
{
	Engine::getInstance()->setBGMVolume(volume);
	return getMusicVolume();
}

float Config::setSoundVolume(float volume)
{
	Engine::getInstance()->setSoundVolume(volume);
	return getSoundVolume();
}

void Config::getWindowSize(int& w, int& h)
{
	w = windowWidth;
	h = windowHeight;
}

void Config::setDefaultWindowSize(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
}

double Config::getGameSpeed()
{
	return gameSpeed;
}

double Config::setGameSpeed(double speed)
{
	if (speed <= SPEED_TIME_MIN)
	{
		gameSpeed = SPEED_TIME_MIN;
	}
	else if(speed >= SPEED_TIME_MAX)
	{
		gameSpeed = SPEED_TIME_MAX;
	}
	else
	{
		gameSpeed = speed;
	}
	return gameSpeed;
}

double Config::convSpeedToDouble(int speed)
{
	const int speed_min_int = 0;
	const int speed_max_int = 100;
	if (speed <= speed_min_int)
	{
		return SPEED_TIME_MIN;
	}
	if (speed >= speed_max_int)
	{
		return SPEED_TIME_MAX;
	}
	auto ret = ((double)(speed - speed_min_int)) / (speed_max_int - speed_min_int) * (SPEED_TIME_MAX - SPEED_TIME_MIN) + SPEED_TIME_MIN;
	if (ret <= SPEED_TIME_MIN)
	{
		return SPEED_TIME_MIN;
	}
	else if (ret >= SPEED_TIME_MAX)
	{
		return SPEED_TIME_MAX;
	}
	return ret;
}

int Config::convSpeedToInt(double speed)
{
	const int speed_min_int = 0;
	const int speed_max_int = 100;
	if (speed <= SPEED_TIME_MIN)
	{
		return speed_min_int;
	}
	else if (speed >= SPEED_TIME_MAX)
	{
		return speed_max_int;
	}
	auto ret = (int)round((speed - SPEED_TIME_MIN) / (SPEED_TIME_MAX - SPEED_TIME_MIN) * (speed_max_int - speed_min_int)) + speed_min_int;
	if (ret <= speed_min_int)
	{
		return speed_min_int;
	}
	if (ret >= speed_max_int)
	{
		return speed_max_int;
	}
	return ret;
}


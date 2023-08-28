#include "state_game.h"

#include "music.h"
#include "gui.h"
#include "player.h"
#include "map.h"
#include "statusbar.h"
#include <SFML\Window\Mouse.hpp>

#include "state_menu.h"


game::~game()
{
	delete mmap;
	delete mmusic;
	delete player_first;
	delete player_second;
	delete hp;
	delete mp;
}

void game::Run()
{
	std::cout << "enter the map name: ";
	std::string sav_name;
	std::cin >> sav_name;

	mmap = new map(window, sav_name);
	if (!mmap->is_load()) {
		std::cout << "error while loading map,\n";
		corestate->SetState(new menu);
		return;
	}
	font.add("arial");

	mmusic = new music;
	mmusic->volume(0);
	mmusic->play("music.flac");


	sf::Keyboard::Key* keys = new sf::Keyboard::Key[16];
	keys[0] = sf::Keyboard::A;
	keys[1] = sf::Keyboard::D;
	keys[2] = sf::Keyboard::W;
	keys[3] = sf::Keyboard::S;
	keys[4] = sf::Keyboard::LControl;
	keys[5] = sf::Keyboard::LShift;
	keys[6] = sf::Keyboard::Q;
	keys[7] = sf::Keyboard::E;
	keys[8] = sf::Keyboard::Left;
	keys[9] = sf::Keyboard::Right;
	keys[10] = sf::Keyboard::Up;
	keys[11] = sf::Keyboard::Down;
	keys[12] = sf::Keyboard::N;
	keys[13] = sf::Keyboard::M;
	keys[14] = sf::Keyboard::J;
	keys[15] = sf::Keyboard::K;

	tex.loadTexture("player", "player.png");
	tex.loadTexture("weapon", "weapon.png");
	tex.loadTexture("beam", "beam.png");
	tex.loadTexture("statusbar", "statusbar.png");

	player_first = new player(25, 25, &tex.getRef("player"), window, mmap);
	player_first->settitle("first");
	player_first->setgod(true);
	player_first->key_set(keys);
	player_first->action_add(&player::key);
	player_first->weapon_get().load(&tex.getRef("weapon"), &tex.getRef("beam"));


	player_second = new player(25, 25, &tex.getRef("player"), window, mmap);
	player_second->settitle("Karol II Kremownik");
	player_second->key_set(&(keys[8]));
	player_second->action_add(&player::key);
	player_second->action_add(&player::show);
	player_second->action_add(&player::center);
	player_second->weapon_get().load(&tex.getRef("weapon"), &tex.getRef("beam"));

	hp = new statusbar(&tex.getRef("statusbar"));
	hp->color(sf::Color::Red);
	mp = new statusbar(&tex.getRef("statusbar"));
	mp->color(sf::Color::Blue);
	mp->orgin(false);


	texture* gtex = g.tex();
	gtex->loadTexture("button", "test.png");

	font.add("arial");
	g.button(500, 0, "button", "option", font.get("arial"));


	stor.push_back(player_first);
	stor.push_back(player_second);
}

void game::Update()
{


	const sf::Vector2i mouse = sf::Mouse::getPosition(*window);


	player_first->update();
	player_second->update();

	mmap->update();

	hp->update(player_second->get_hp(),
		sf::Vector2f(window->getSize().x/2, window->getSize().y));

	if (g.get(0)->collision(mouse))
		corestate->SetState(new menu);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		corestate->SetState(new menu);

}

void game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto it : stor) mmap->draw(it);
	target.draw(*mmap);
	target.draw(g);
	target.draw(*hp);
	target.draw(*mp);
}



void game::Destroy()
{
}

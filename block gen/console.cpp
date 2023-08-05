#include "console.h"
#include "id.h"

void console::update()
{
	while (true)
	{
		std::string command;
		std::cin >> command;
		if (command == "add") handle->id_load();
	}

}
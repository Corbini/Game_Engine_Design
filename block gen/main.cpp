#include "id.h"
#include "block.h"
#include "console.h"

int main()
{
	id tools;
	tools.window.setActive(false);
	tools.id_load(3, "grass");
	//tools.id_load(4, "");

	console con(&tools);
	block blocks(&tools);

	while (blocks.update());

}
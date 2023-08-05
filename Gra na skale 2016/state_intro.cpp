#include "state_intro.h"

#include <iostream>

#include "state_menu.h"


intro::~intro()
{
}

void intro::Run()
{

}

void intro::Update()
{
	corestate->SetState(new menu);
}


void intro::Destroy()
{

}
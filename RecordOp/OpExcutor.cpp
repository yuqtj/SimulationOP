#include "OpExcutor.h"



OpExcutor::OpExcutor()
{
}


OpExcutor::~OpExcutor()
{
	clear();
}

void OpExcutor::run()
{
	if (opProjects.size() == 0)
	{
		return;
	}

	for each (auto opProject in opProjects)
	{
		if (0 == opProject->excuteOP())
		{
			break;
		}
	}

	clear();
}

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

	for (int i = 0; i < operateTimes; i++)
	{
		for each (auto opProject in opProjects)
		{
			if (0 == opProject->excuteOP())
			{
				break;
			}
		}
	}

	clear();
}

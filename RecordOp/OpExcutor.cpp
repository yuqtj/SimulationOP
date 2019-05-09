#include "OpExcutor.h"



OpExcutor::OpExcutor()
{
}


OpExcutor::~OpExcutor()
{
	clear();
}

void OpExcutor::runOp()
{
	for (int i = 0; i < operateTimes; i++)
	{
		for each (auto opProject in opProjects)
		{
			if (0 == opProject->excuteOP())
			{
				return;
			}
		}
	}
}

void OpExcutor::run()
{
	if (opProjects.size() == 0)
	{
		return;
	}

	runOp();
	clear();
}

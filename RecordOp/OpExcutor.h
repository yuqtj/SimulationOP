#pragma once

#include <QThread>
#include "OpProject.h"

class OpExcutor : public QThread
{
public:
	OpExcutor();
	~OpExcutor();

	inline void addOpProject(OpProject* project)
	{
		opProjects.append(project);
	}

	inline int opProjectSize()
	{
		return opProjects.size();
	}

	inline void setOperateTimes(int times)
	{
		operateTimes = times;
	}

	inline void clear()
	{
		opProjects.clear();
		operateTimes = 1;
	}

private:
	void runOp();

private:
	QList<OpProject*> opProjects;
	int operateTimes = 1;

protected:
	virtual void run() override;

};


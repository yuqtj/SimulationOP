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

	inline void clear()
	{
		opProjects.clear();
	}

private:
	QList<OpProject*> opProjects;

protected:
	virtual void run() override;

};


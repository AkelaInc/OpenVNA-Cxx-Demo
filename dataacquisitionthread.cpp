#include "dataacquisitionthread.h"
#include <QMutex>

class pdDataAcquisitionThread
{
	public:
		int refresh;
		bool measuring;
		bool running;
		VNALibrary lib;
		TaskHandle task;
		QMutex measureLock;
		QMutex runLock;

		pdDataAcquisitionThread() :
			refresh(false), measuring(false),
			running(false)
		{}
};

DataAcquisitionThread::DataAcquisitionThread()
{
	d = new pdDataAcquisitionThread();
}

DataAcquisitionThread::~DataAcquisitionThread()
{
	delete d;
}

void DataAcquisitionThread::loadLibrary()
{
	d->lib.load("vnadll.dll");

	if(d->lib.isOK())
	{
		d->task = d->lib.createTask();
		emit loadLibraryOK();
	}
	else
		emit loadLibraryFail();
}
void DataAcquisitionThread::startMeasuring(int minRefreshTime, VNALibrary lib, TaskHandle task)
{
	d->refresh = minRefreshTime;
	d->measuring = true;
	d->lib = lib;
	d->task = task;
}

void DataAcquisitionThread::stopMeasuring()
{
	d->measureLock.lock();
	d->measuring = false;
	d->measureLock.unlock();
}

void DataAcquisitionThread::halt()
{
	d->runLock.lock();
	d->running = false;
	d->runLock.unlock();
}

void DataAcquisitionThread::run()
{
	int f = 0;
	d->running = true;
	bool localRun = true;

	bool localMeasure;

	do
	{
		d->measureLock.lock();
		localMeasure = d->measuring;
		d->measureLock.unlock();

		if(localMeasure)
		{
			//collect data
			this->msleep(500);
			printf("f = %d\n", f++);
		}
		else
			this->msleep(100);

		d->runLock.lock();
		localRun = d->running;
		d->runLock.unlock();
	}
	while(localRun);
}

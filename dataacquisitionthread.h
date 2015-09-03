#ifndef DATAACQUISITIONTHREAD
#define DATAACQUISITIONTHREAD

#include <QThread>
#include "vnalibrary.h"

class pdDataAcquisitionThread;
class DataAcquisitionThread : public QThread
{
		Q_OBJECT

		void run();

		pdDataAcquisitionThread *d;

	public:
		DataAcquisitionThread();
		~DataAcquisitionThread();

		void loadLibrary();
		VNALibrary& getLibrary();

		void setupMeasurement();


	signals:
		void measuredData(ComplexData a, ComplexData b, ComplexData c, ComplexData d, ComplexData e);
		void loadLibraryOK();
		void loadLibraryFail();
		void setupMeasurementOK();
		void setupMeasurementFail(QString reason);

	public slots:
		void startMeasuring(int minRefreshTime, VNALibrary lib, TaskHandle task);
		void stopMeasuring();
		void halt();
};

#endif // DATAACQUISITIONTHREAD


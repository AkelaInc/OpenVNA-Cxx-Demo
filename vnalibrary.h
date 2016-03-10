#ifndef VNALIBRARY_H
#define VNALIBRARY_H

/*
 * This class loads the VNA DLL's functions
 * and exposes them to the caller.
*/

#include "../../../vnadll/akela_vna_dll.h"
#include <QObject>
#include <QString>
#include "wrapperclasses.h"

class PrivateData;
class VNALibrary : public QObject
{
		Q_OBJECT

	private:
		PrivateData* d;

	public slots:
		void loadAsync(QString path);
		void initializeAsync(QtTaskHandle t, Qtvoidptr user);
		void startAsync(QtTaskHandle t);
		void stopAsync(QtTaskHandle t);
		void utilPingUnitAsync(QtTaskHandle t);
        void measureUncalibratedAsync(QtTaskHandle t, QtComplexData T1R1, QtComplexData T1R2,
		                              QtComplexData T2R1, QtComplexData T2R2,
		                              QtComplexData Ref);
		void measure2PortCalibratedAsync(QtTaskHandle t,
		                                 QtComplexData S11, QtComplexData S21,
		                                 QtComplexData S12, QtComplexData S22);
		void measureCalibrationStepAsync(QtTaskHandle t, QtCalibrationStep step);
		void importCalibrationAsync(QtTaskHandle t,const double* freqs, const unsigned int N,
		                            const QtComplexData e00,		/* EDF */
		                            const QtComplexData e11,		/* ESF */
		                            const QtComplexData e10e01,     /* ERF */
		                            const QtComplexData e30,		/* EXF */
		                            const QtComplexData e22,		/* ELF */
		                            const QtComplexData e10e32,     /* ETF */
		                            const QtComplexData ep33,		/* EDR */
		                            const QtComplexData ep22,		/* ESR */
		                            const QtComplexData ep23ep32,	/* ERR */
		                            const QtComplexData ep03,		/* EXR */
		                            const QtComplexData ep11,		/* ELR */
		                            const QtComplexData ep23ep01	/* ETR */);

	signals:
		void loadFinished(bool result);
		void initializeFinished(QtErrCode result);
		void initializeProgress(int percent, Qtvoidptr user);
		void startFinished(QtErrCode result);
		void stopFinished(QtErrCode result);
		void utilPingUnitFinished(QtErrCode result);
		void measureUncalibratedFinished(QtErrCode result);
		void measure2PortCalibratedFinished(QtErrCode result);
		void measureCalibrationStepFinished(QtErrCode result);
		void importCalibrationFinished(QtErrCode result);


	public:
		VNALibrary();
		~VNALibrary();

		bool load(QString path);
		bool unload();
		bool isOK();

		int ERR_OK;
		int ERR_BAD_ATTEN;
		int ERR_BAD_CAL;
		int ERR_BAD_HANDLE;
		int ERR_BAD_HOP;
		int ERR_BAD_PATH;
		int ERR_BAD_PROM;
		int ERR_BYTES;
		int ERR_FREQ_OUT_OF_BOUNDS;
		int ERR_INTERRUPTED;
		int ERR_NO_RESPONSE;
		int ERR_MISSING_IP;
		int ERR_MISSING_PORT;
		int ERR_MISSING_HOP;
		int ERR_MISSING_ATTEN;
		int ERR_MISSING_FREQS;
		int ERR_PROG_OVERFLOW;
		int ERR_SOCKET;
		int ERR_TOO_MANY_POINTS;
		int ERR_WRONG_STATE;

		QString ErrToString(int code);

		int HOP_UNDEFINED;
		int HOP_45K;
		int HOP_30K;
		int HOP_15K;
		int HOP_7K;
		int HOP_3K;
		int HOP_2K;
		int HOP_1K;
		int HOP_550;
		int HOP_312;
		int HOP_156;
		int HOP_78;
		int HOP_39;
		int HOP_20;

		int ATTEN_UNDEFINED;
		int ATTEN_0;
		int ATTEN_1;
		int ATTEN_2;
		int ATTEN_3;
		int ATTEN_4;
		int ATTEN_5;
		int ATTEN_6;
		int ATTEN_7;
		int ATTEN_8;
		int ATTEN_9;
		int ATTEN_10;
		int ATTEN_11;
		int ATTEN_12;
		int ATTEN_13;
		int ATTEN_14;
		int ATTEN_15;
		int ATTEN_16;
		int ATTEN_17;
		int ATTEN_18;
		int ATTEN_19;
		int ATTEN_20;
		int ATTEN_21;
		int ATTEN_22;
		int ATTEN_23;
		int ATTEN_24;
		int ATTEN_25;
		int ATTEN_26;
		int ATTEN_27;
		int ATTEN_28;
		int ATTEN_29;
		int ATTEN_30;
		int ATTEN_31;

		int TASK_UNINITIALIZED;
		int TASK_STOPPED;
		int TASK_STARTED;

		int PATH_T1R1;
		int PATH_T1R2;
		int PATH_T2R1;
		int PATH_T2R2;
		int PATH_REF;

		int PARAM_S11;
		int PARAM_S21;
		int PARAM_S12;
		int PARAM_S22;

		int STEP_P1_OPEN;
		int STEP_P1_SHORT;
		int STEP_P1_LOAD;
		int STEP_P2_OPEN;
		int STEP_P2_SHORT;
		int STEP_P2_LOAD;
		int STEP_THRU;
		int STEP_OFFSET_P1_OPEN;
		int STEP_OFFSET_P1_SHORT;
		int STEP_OFFSET_P2_OPEN;
		int STEP_OFFSET_P2_SHORT;

		const char* versionString();
		TaskHandle createTask();
		void deleteTask(TaskHandle t);
		ErrCode initialize(TaskHandle t, progress_callback callback, void* user);
		ErrCode start(TaskHandle t);
		ErrCode stop(TaskHandle t);
		ErrCode setIPAddress(TaskHandle t, const char* ipv4);
		ErrCode setIPPort(TaskHandle t, const int port);
		ErrCode setTimeout(TaskHandle t, const unsigned int timeout);
		ErrCode setHopRate(TaskHandle t, const HopRate rate);
		ErrCode setAttenuation(TaskHandle t, const Attenuation atten);
		ErrCode setFrequencies(TaskHandle t, const double* freqs, const unsigned int N);
		TaskState getState(TaskHandle t);
		unsigned int getTimeout(TaskHandle t);
		const char* getIPAddress(TaskHandle t);
		int getIPPort(TaskHandle t);
		HopRate getHopRate(TaskHandle t);
		Attenuation getAttenuation(TaskHandle t);
		unsigned int getNumberOfFrequencies(TaskHandle t);
		const double* getFrequencies(TaskHandle t);
		HardwareDetails getHardwareDetails(TaskHandle t);
		ErrCode utilNearestLegalFreq(TaskHandle t, double& freq);
		ErrCode utilFixLinearSweepLimits(TaskHandle t, double& startFreq, double& endFreq, const unsigned int N);
		ErrCode utilPingUnit(TaskHandle t);
		ErrCode utilGenerateLinearSweep(TaskHandle t, const double startFreq, const double endFreq, const unsigned int N);
        ErrCode measureUncalibrated(TaskHandle t, ComplexData T1R1, ComplexData T1R2,
		                            ComplexData T2R1, ComplexData T2R2,
		                            ComplexData Ref);
		ErrCode measure2PortCalibrated(TaskHandle t,
		                               ComplexData S11, ComplexData S21,
		                               ComplexData S12, ComplexData S22);
		ErrCode measureCalibrationStep(TaskHandle t, CalibrationStep step);
		bool haveCalP1Open(TaskHandle t);
		bool haveCalP1Short(TaskHandle t);
		bool haveCalP1Load(TaskHandle t);
		bool haveCalP2Open(TaskHandle t);
		bool haveCalP2Short(TaskHandle t);
		bool haveCalP2Load(TaskHandle t);
		bool haveCalThru(TaskHandle t);
		ErrCode interruptMeasurement(TaskHandle t);
		ErrCode clearCalibration(TaskHandle t);
		bool isCalibrationComplete(TaskHandle t);
		unsigned int getCalibrationNumberOfFrequencies(TaskHandle t);
		const double* getCalibrationFrequencies(TaskHandle t);
		ErrCode exportCalibration(TaskHandle t,
		                          ComplexData e00,		/* EDF */
		                          ComplexData e11,		/* ESF */
		                          ComplexData e10e01,		/* ERF */
		                          ComplexData e30,		/* EXF */
		                          ComplexData e22,		/* ELF */
		                          ComplexData e10e32,		/* ETF */
		                          ComplexData ep33,		/* EDR */
		                          ComplexData ep22,		/* ESR */
		                          ComplexData ep23ep32,	/* ERR */
		                          ComplexData ep03,		/* EXR */
		                          ComplexData ep11,		/* ELR */
		                          ComplexData ep23ep01	/* ETR */);
		ErrCode importCalibration(TaskHandle t, const double* freqs, const unsigned int N,
		                          const ComplexData e00,		/* EDF */
		                          const ComplexData e11,		/* ESF */
		                          const ComplexData e10e01,	/* ERF */
		                          const ComplexData e30,		/* EXF */
		                          const ComplexData e22,		/* ELF */
		                          const ComplexData e10e32,	/* ETF */
		                          const ComplexData ep33,		/* EDR */
		                          const ComplexData ep22,		/* ESR */
		                          const ComplexData ep23ep32,	/* ERR */
		                          const ComplexData ep03,		/* EXR */
		                          const ComplexData ep11,		/* ELR */
		                          const ComplexData ep23ep01	/* ETR */);

		bool hasFactoryCalibration(TaskHandle t);
		ErrCode importFactoryCalibration(TaskHandle t);
//		ErrCode setOpenPhaseCorrection(TaskHandle t, const double* const phaseCorrections);


		bool callback(int percent, void* user);
};

#endif // VNALIBRARY_H


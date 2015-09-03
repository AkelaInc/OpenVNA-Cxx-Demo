#include <QDebug>
#include <QLibrary>
#include <QTime>
#include <cstdio>
#include "vnalibrary.h"

typedef int *intProto;

typedef const char* (*versionStringProto)();
typedef TaskHandle (*createTaskProto)();
typedef void (*deleteTaskProto)(TaskHandle t);
typedef ErrCode (*initializeProto)(TaskHandle t, progress_callback callback, void* user);
typedef ErrCode (*startProto)(TaskHandle t);
typedef ErrCode (*stopProto)(TaskHandle t);
typedef ErrCode (*setIPAddressProto)(TaskHandle t, const char* ipv4);
typedef ErrCode (*setIPPortProto)(TaskHandle t, const int port);
typedef ErrCode (*setTimeoutProto)(TaskHandle t, const unsigned int timeout);
typedef ErrCode (*setHopRateProto)(TaskHandle t, const HopRate rate);
typedef ErrCode (*setAttenuationProto)(TaskHandle t, const Attenuation atten);
typedef ErrCode (*setFrequenciesProto)(TaskHandle t, const double* freqs, const unsigned int N);
typedef TaskState (*getStateProto)(TaskHandle t);
typedef unsigned int (*getTimeoutProto)(TaskHandle t);
typedef const char* (*getIPAddressProto)(TaskHandle t);
typedef int (*getIPPortProto)(TaskHandle t);
typedef HopRate (*getHopRateProto)(TaskHandle t);
typedef Attenuation (*getAttenuationProto)(TaskHandle t);
typedef unsigned int (*getNumberOfFrequenciesProto)(TaskHandle t);
typedef const double* (*getFrequenciesProto)(TaskHandle t);
typedef HardwareDetails (*getHardwareDetailsProto)(TaskHandle t);
typedef ErrCode (*utilNearestLegalFreqProto)(TaskHandle t, double& freq);
typedef ErrCode (*utilFixLinearSweepLimitsProto)(TaskHandle t, double& startFreq, double& endFreq, const unsigned int N);
typedef ErrCode (*utilPingUnitProto)(TaskHandle t);
typedef ErrCode (*utilGenerateLinearSweepProto)(TaskHandle t, const double startFreq, const double endFreq, const unsigned int N);
typedef ErrCode (*measureUncalibratedProto)(TaskHandle t, RFPath paths, ComplexData T1R1, ComplexData T1R2,
        ComplexData T2R1, ComplexData T2R2,
        ComplexData Ref);
typedef ErrCode (*measure2PortCalibratedProto)(TaskHandle t, SParameter paths,
        ComplexData S11, ComplexData S21,
        ComplexData S12, ComplexData S22);
typedef ErrCode (*measureCalibrationStepProto)(TaskHandle t, CalibrationStep step);
typedef bool (*haveCalP1OpenProto)(TaskHandle t);
typedef bool (*haveCalP1ShortProto)(TaskHandle t);
typedef bool (*haveCalP1LoadProto)(TaskHandle t);
typedef bool (*haveCalP2OpenProto)(TaskHandle t);
typedef bool (*haveCalP2ShortProto)(TaskHandle t);
typedef bool (*haveCalP2LoadProto)(TaskHandle t);
typedef bool (*haveCalThruProto)(TaskHandle t);
typedef ErrCode (*interruptMeasurementProto)(TaskHandle t);
typedef ErrCode (*clearCalibrationProto)(TaskHandle t);
typedef bool (*isCalibrationCompleteProto)(TaskHandle t);
typedef unsigned int (*getCalibrationNumberOfFrequenciesProto)(TaskHandle t);
typedef const double* (*getCalibrationFrequenciesProto)(TaskHandle t);
typedef ErrCode (*exportCalibrationProto)(TaskHandle t,
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
typedef ErrCode (*importCalibrationProto)(TaskHandle t, const double* freqs, const unsigned int N,
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
typedef bool (*hasFactoryCalibrationProto)(TaskHandle t);
typedef ErrCode (*importFactoryCalibrationProto)(TaskHandle t);
typedef ErrCode (*setOpenPhaseCorrectionProto)(TaskHandle t, const double* const phaseCorrections);

class PrivateData
{
	public:
		bool loaded, ok;
		QLibrary* lib;

		intProto p_ERR_OK;
		intProto p_ERR_BAD_ATTEN;
		intProto p_ERR_BAD_CAL;
		intProto p_ERR_BAD_HANDLE;
		intProto p_ERR_BAD_HOP;
		intProto p_ERR_BAD_PATH;
		intProto p_ERR_BAD_PROM;
		intProto p_ERR_BYTES;
		intProto p_ERR_FREQ_OUT_OF_BOUNDS;
		intProto p_ERR_INTERRUPTED;
		intProto p_ERR_NO_RESPONSE;
		intProto p_ERR_MISSING_IP;
		intProto p_ERR_MISSING_PORT;
		intProto p_ERR_MISSING_HOP;
		intProto p_ERR_MISSING_ATTEN;
		intProto p_ERR_MISSING_FREQS;
		intProto p_ERR_PROG_OVERFLOW;
		intProto p_ERR_SOCKET;
		intProto p_ERR_TOO_MANY_POINTS;
		intProto p_ERR_WRONG_STATE;

		intProto p_HOP_UNDEFINED;
		intProto p_HOP_45K;
		intProto p_HOP_30K;
		intProto p_HOP_15K;
		intProto p_HOP_7K;
		intProto p_HOP_3K;
		intProto p_HOP_2K;
		intProto p_HOP_1K;
		intProto p_HOP_550;
		intProto p_HOP_312;
		intProto p_HOP_156;
		intProto p_HOP_78;
		intProto p_HOP_39;
		intProto p_HOP_20;

		intProto p_ATTEN_UNDEFINED;
		intProto p_ATTEN_0;
		intProto p_ATTEN_1;
		intProto p_ATTEN_2;
		intProto p_ATTEN_3;
		intProto p_ATTEN_4;
		intProto p_ATTEN_5;
		intProto p_ATTEN_6;
		intProto p_ATTEN_7;
		intProto p_ATTEN_8;
		intProto p_ATTEN_9;
		intProto p_ATTEN_10;
		intProto p_ATTEN_11;
		intProto p_ATTEN_12;
		intProto p_ATTEN_13;
		intProto p_ATTEN_14;
		intProto p_ATTEN_15;
		intProto p_ATTEN_16;
		intProto p_ATTEN_17;
		intProto p_ATTEN_18;
		intProto p_ATTEN_19;
		intProto p_ATTEN_20;
		intProto p_ATTEN_21;
		intProto p_ATTEN_22;
		intProto p_ATTEN_23;
		intProto p_ATTEN_24;
		intProto p_ATTEN_25;
		intProto p_ATTEN_26;
		intProto p_ATTEN_27;
		intProto p_ATTEN_28;
		intProto p_ATTEN_29;
		intProto p_ATTEN_30;
		intProto p_ATTEN_31;

		intProto p_TASK_UNINITIALIZED;
		intProto p_TASK_STOPPED;
		intProto p_TASK_STARTED;

		intProto p_PATH_T1R1;
		intProto p_PATH_T1R2;
		intProto p_PATH_T2R1;
		intProto p_PATH_T2R2;
		intProto p_PATH_REF;

		intProto p_PARAM_S11;
		intProto p_PARAM_S21;
		intProto p_PARAM_S12;
		intProto p_PARAM_S22;

		intProto p_STEP_P1_OPEN;
		intProto p_STEP_P1_SHORT;
		intProto p_STEP_P1_LOAD;
		intProto p_STEP_P2_OPEN;
		intProto p_STEP_P2_SHORT;
		intProto p_STEP_P2_LOAD;
		intProto p_STEP_THRU;


		versionStringProto p_versionString;
		createTaskProto p_createTask;
		deleteTaskProto p_deleteTask;
		initializeProto p_initialize;
		startProto p_start;
		stopProto p_stop;
		setIPAddressProto p_setIPAddress;
		setIPPortProto p_setIPPort;
		setTimeoutProto p_setTimeout;
		setHopRateProto p_setHopRate;
		setAttenuationProto p_setAttenuation;
		setFrequenciesProto p_setFrequencies;
		getStateProto p_getState;
		getTimeoutProto p_getTimeout;
		getIPAddressProto p_getIPAddress;
		getIPPortProto p_getIPPort;
		getHopRateProto p_getHopRate;
		getAttenuationProto p_getAttenuation;
		getNumberOfFrequenciesProto p_getNumberOfFrequencies;
		getFrequenciesProto p_getFrequencies;
		getHardwareDetailsProto p_getHardwareDetails;
		utilNearestLegalFreqProto p_utilNearestLegalFreq;
		utilFixLinearSweepLimitsProto p_utilFixLinearSweepLimits;
		utilPingUnitProto p_utilPingUnit;
		utilGenerateLinearSweepProto p_utilGenerateLinearSweep;
		measureUncalibratedProto p_measureUncalibrated;
		measure2PortCalibratedProto p_measure2PortCalibrated;
		measureCalibrationStepProto p_measureCalibrationStep;
		haveCalP1OpenProto p_haveCalP1Open;
		haveCalP1ShortProto p_haveCalP1Short;
		haveCalP1LoadProto p_haveCalP1Load;
		haveCalP2OpenProto p_haveCalP2Open;
		haveCalP2ShortProto p_haveCalP2Short;
		haveCalP2LoadProto p_haveCalP2Load;
		haveCalThruProto p_haveCalThru;
		interruptMeasurementProto p_interruptMeasurement;
		clearCalibrationProto p_clearCalibration;
		isCalibrationCompleteProto p_isCalibrationComplete;
		getCalibrationNumberOfFrequenciesProto p_getCalibrationNumberOfFrequencies;
		getCalibrationFrequenciesProto p_getCalibrationFrequencies;
		exportCalibrationProto p_exportCalibration;
		importCalibrationProto p_importCalibration;
		hasFactoryCalibrationProto p_hasFactoryCalibration;
		importFactoryCalibrationProto p_importFactoryCalibration;
		setOpenPhaseCorrectionProto p_setOpenPhaseCorrection;

		PrivateData() : loaded(false),ok(false), lib(0)
		{}
};

void VNALibrary::loadAsync(QString path)
{
	bool result = load(path);
	emit loadFinished(result);
}

typedef struct
{
	VNALibrary* lib;
	void* data;
} CallbackData;

static bool static_callback(int percent, void* user)
{
	if(user)
	{
		CallbackData* c = (CallbackData*)user;
		VNALibrary* v = (VNALibrary*)c->lib;
		return v->callback(percent, c->data);
	}
	return true;
}

bool VNALibrary::callback(int percent, void *user)
{
	emit initializeProgress(percent, Qtvoidptr(user));
	return true;
}

void VNALibrary::initializeAsync(QtTaskHandle t, Qtvoidptr user)
{
	printf("Initializing...\n");
	CallbackData c;
	c.lib = this;
	c.data = user.val;
	ErrCode result = initialize(t.val, static_callback, (void*)&c);
	printf("Done.\n");
	emit initializeFinished(QtErrCode(result));
}

void VNALibrary::startAsync(QtTaskHandle t)
{
	printf("Starting...\n");
	ErrCode result = start(t.val);
	printf("Done.\n");
	emit startFinished(QtErrCode(result));
}

void VNALibrary::stopAsync(QtTaskHandle t)
{
	ErrCode result = stop(t.val);
	emit stopFinished(QtErrCode(result));
}

void VNALibrary::utilPingUnitAsync(QtTaskHandle t)
{
	ErrCode result = utilPingUnit(t.val);
	emit utilPingUnitFinished(QtErrCode(result));
}

void VNALibrary::measureUncalibratedAsync(QtTaskHandle t, QtRFPath paths, QtComplexData T1R1, QtComplexData T1R2, QtComplexData T2R1, QtComplexData T2R2, QtComplexData Ref)
{
	QTime timer;
	timer.start();
	ErrCode result = measureUncalibrated(t.val, paths.val, T1R1.val, T1R2.val, T2R1.val, T2R2.val, Ref.val);

	QtErrCode out = QtErrCode(result);
	out.time = timer.elapsed();
	emit measureUncalibratedFinished(out);
}

void VNALibrary::measure2PortCalibratedAsync(QtTaskHandle t, QtSParameter paths, QtComplexData S11, QtComplexData S21, QtComplexData S12, QtComplexData S22)
{
	QTime timer;
	timer.start();
	ErrCode result = measure2PortCalibrated(t.val, paths.val, S11.val, S21.val, S12.val, S22.val);

	QtErrCode out = QtErrCode(result);
	out.time = timer.elapsed();
	emit measure2PortCalibratedFinished(out);
}

void VNALibrary::measureCalibrationStepAsync(QtTaskHandle t, QtCalibrationStep step)
{
	ErrCode result = measureCalibrationStep(t.val, step.val);
	emit measureCalibrationStepFinished(QtErrCode(result));
}

void VNALibrary::importCalibrationAsync(QtTaskHandle t, const double* freqs, const unsigned int N,
                                        const QtComplexData e00,		/* EDF */
                                        const QtComplexData e11,		/* ESF */
                                        const QtComplexData e10e01,	/* ERF */
                                        const QtComplexData e30,		/* EXF */
                                        const QtComplexData e22,		/* ELF */
                                        const QtComplexData e10e32,	/* ETF */
                                        const QtComplexData ep33,		/* EDR */
                                        const QtComplexData ep22,		/* ESR */
                                        const QtComplexData ep23ep32,	/* ERR */
                                        const QtComplexData ep03,		/* EXR */
                                        const QtComplexData ep11,		/* ELR */
                                        const QtComplexData ep23ep01	/* ETR */)
{
	ErrCode result = importCalibration(t.val, freqs, N, e00.val, e11.val, e10e01.val,
	                                   e30.val, e22.val, e10e32.val, ep33.val,
	                                   ep22.val, ep23ep32.val, ep03.val,
	                                   ep11.val, ep23ep01.val);
	emit importCalibrationFinished(QtErrCode(result));
}


VNALibrary::VNALibrary()
{
	d = new PrivateData();
}

VNALibrary::~VNALibrary()
{
	if(d->loaded) unload();
	delete d;
}

#define GET_INT(a) \
    d->p_##a = (intProto) d->lib->resolve(#a); \
    if(d->p_##a) \
    {\
        printf("%s: OK\n",#a); \
        VNALibrary::a = *(d->p_##a); \
    }\
    else         printf("%s: FAIL\n", #a); \

#define GET_FUNC(a) \
    d->p_##a = (a##Proto) d->lib->resolve(#a); \
    if(d->p_##a) printf("%s: OK\n",#a); \
    else         printf("%s: FAIL\n", #a);

bool VNALibrary::load(QString path)
{
	if(d->loaded)
	{
		unload();
	}

	d->lib = new QLibrary(path);
	bool loadstate = d->lib->load();
	// qDebug() << "DLL path:" << path;
	// qDebug() << "DLL :" << d->lib;
	// qDebug() << "DLL loadstate:" << loadstate;
	// qDebug() << "DLL loaded:" << d->lib->isLoaded();
	// qDebug() << "DLL load error:" << d->lib->errorString();


	GET_INT(ERR_OK);
	GET_INT(ERR_BAD_ATTEN);
	GET_INT(ERR_BAD_CAL);
	GET_INT(ERR_BAD_HANDLE);
	GET_INT(ERR_BAD_HOP);
	GET_INT(ERR_BAD_PATH);
	GET_INT(ERR_BAD_PROM);
	GET_INT(ERR_BYTES);
	GET_INT(ERR_FREQ_OUT_OF_BOUNDS);
	GET_INT(ERR_INTERRUPTED);
	GET_INT(ERR_NO_RESPONSE);
	GET_INT(ERR_MISSING_IP);
	GET_INT(ERR_MISSING_PORT);
	GET_INT(ERR_MISSING_HOP);
	GET_INT(ERR_MISSING_ATTEN);
	GET_INT(ERR_MISSING_FREQS);
	GET_INT(ERR_PROG_OVERFLOW);
	GET_INT(ERR_SOCKET);
	GET_INT(ERR_TOO_MANY_POINTS);
	GET_INT(ERR_WRONG_STATE);

	GET_INT(HOP_UNDEFINED);
	GET_INT(HOP_45K);
	GET_INT(HOP_30K);
	GET_INT(HOP_15K);
	GET_INT(HOP_7K);
	GET_INT(HOP_3K);
	GET_INT(HOP_2K);
	GET_INT(HOP_1K);
	GET_INT(HOP_550);
	GET_INT(HOP_312);
	GET_INT(HOP_156);
	GET_INT(HOP_78);
	GET_INT(HOP_39);
	GET_INT(HOP_20);

	GET_INT(ATTEN_UNDEFINED);
	GET_INT(ATTEN_0);
	GET_INT(ATTEN_1);
	GET_INT(ATTEN_2);
	GET_INT(ATTEN_3);
	GET_INT(ATTEN_4);
	GET_INT(ATTEN_5);
	GET_INT(ATTEN_6);
	GET_INT(ATTEN_7);
	GET_INT(ATTEN_8);
	GET_INT(ATTEN_9);
	GET_INT(ATTEN_10);
	GET_INT(ATTEN_11);
	GET_INT(ATTEN_12);
	GET_INT(ATTEN_13);
	GET_INT(ATTEN_14);
	GET_INT(ATTEN_15);
	GET_INT(ATTEN_16);
	GET_INT(ATTEN_17);
	GET_INT(ATTEN_18);
	GET_INT(ATTEN_19);
	GET_INT(ATTEN_20);
	GET_INT(ATTEN_21);
	GET_INT(ATTEN_22);
	GET_INT(ATTEN_23);
	GET_INT(ATTEN_24);
	GET_INT(ATTEN_25);
	GET_INT(ATTEN_26);
	GET_INT(ATTEN_27);
	GET_INT(ATTEN_28);
	GET_INT(ATTEN_29);
	GET_INT(ATTEN_30);
	GET_INT(ATTEN_31);

	GET_INT(TASK_UNINITIALIZED);
	GET_INT(TASK_STOPPED);
	GET_INT(TASK_STARTED);

	GET_INT(PATH_T1R1);
	GET_INT(PATH_T1R2);
	GET_INT(PATH_T2R1);
	GET_INT(PATH_T2R2);
	GET_INT(PATH_REF);

	GET_INT(PARAM_S11);
	GET_INT(PARAM_S21);
	GET_INT(PARAM_S12);
	GET_INT(PARAM_S22);

	GET_INT(STEP_P1_OPEN);
	GET_INT(STEP_P1_SHORT);
	GET_INT(STEP_P1_LOAD);
	GET_INT(STEP_P2_OPEN);
	GET_INT(STEP_P2_SHORT);
	GET_INT(STEP_P2_LOAD);
	GET_INT(STEP_THRU);

	GET_FUNC(versionString);
	GET_FUNC(createTask);
	GET_FUNC(deleteTask);
	GET_FUNC(initialize);
	GET_FUNC(start);
	GET_FUNC(stop);
	GET_FUNC(setIPAddress);
	GET_FUNC(setIPPort);
	GET_FUNC(setTimeout);
	GET_FUNC(setHopRate);
	GET_FUNC(setAttenuation);
	GET_FUNC(setFrequencies);
	GET_FUNC(getState);
	GET_FUNC(getTimeout);
	GET_FUNC(getIPAddress);
	GET_FUNC(getIPPort);
	GET_FUNC(getHopRate);
	GET_FUNC(getAttenuation);
	GET_FUNC(getNumberOfFrequencies);
	GET_FUNC(getFrequencies);
	GET_FUNC(getHardwareDetails);
	GET_FUNC(utilNearestLegalFreq);
	GET_FUNC(utilFixLinearSweepLimits);
	GET_FUNC(utilPingUnit);
	GET_FUNC(utilGenerateLinearSweep);
	GET_FUNC(measureUncalibrated);
	GET_FUNC(measure2PortCalibrated);
	GET_FUNC(measureCalibrationStep);
	GET_FUNC(haveCalP1Open);
	GET_FUNC(haveCalP1Short);
	GET_FUNC(haveCalP1Load);
	GET_FUNC(haveCalP2Open);
	GET_FUNC(haveCalP2Short);
	GET_FUNC(haveCalP2Load);
	GET_FUNC(haveCalThru);
	GET_FUNC(interruptMeasurement);
	GET_FUNC(clearCalibration);
	GET_FUNC(isCalibrationComplete);
	GET_FUNC(getCalibrationNumberOfFrequencies);
	GET_FUNC(getCalibrationFrequencies);
	GET_FUNC(exportCalibration);
	GET_FUNC(importCalibration);
	GET_FUNC(hasFactoryCalibration);
	GET_FUNC(importFactoryCalibration);
	GET_FUNC(setOpenPhaseCorrection);

	d->loaded = true;

	d->ok = d->p_versionString
	        && d->p_createTask
	        && d->p_deleteTask
	        && d->p_initialize
	        && d->p_start
	        && d->p_stop
	        && d->p_setIPAddress
	        && d->p_setIPPort
	        && d->p_setTimeout
	        && d->p_setHopRate
	        && d->p_setAttenuation
	        && d->p_setFrequencies
	        && d->p_getState
	        && d->p_getTimeout
	        && d->p_getIPAddress
	        && d->p_getIPPort
	        && d->p_getHopRate
	        && d->p_getAttenuation
	        && d->p_getNumberOfFrequencies
	        && d->p_getFrequencies
	        && d->p_getHardwareDetails
	        && d->p_utilNearestLegalFreq
	        && d->p_utilFixLinearSweepLimits
	        && d->p_utilPingUnit
	        && d->p_utilGenerateLinearSweep
	        && d->p_measureUncalibrated
	        && d->p_measure2PortCalibrated
	        && d->p_measureCalibrationStep
	        && d->p_haveCalP1Open
	        && d->p_haveCalP1Short
	        && d->p_haveCalP1Load
	        && d->p_haveCalP2Open
	        && d->p_haveCalP2Short
	        && d->p_haveCalP2Load
	        && d->p_haveCalThru
	        && d->p_interruptMeasurement
	        && d->p_clearCalibration
	        && d->p_isCalibrationComplete
	        && d->p_getCalibrationNumberOfFrequencies
	        && d->p_getCalibrationFrequencies
	        && d->p_exportCalibration
	        && d->p_importCalibration
	        && d->p_hasFactoryCalibration
	        && d->p_importFactoryCalibration
	        && d->p_setOpenPhaseCorrection;

	return d->ok;
}

bool VNALibrary::unload()
{
	d->loaded = false;
	d->ok = false;
	return d->lib->unload();
}

bool VNALibrary::isOK()
{
	return d->ok;
}

QString VNALibrary::ErrToString(int code)
{
	QString out = "UNKNOWN";
	if(code == VNALibrary::ERR_OK) out = "ERR_OK";
	if(code == VNALibrary::ERR_BAD_ATTEN) out = "ERR_BAD_ATTEN";
	if(code == VNALibrary::ERR_BAD_CAL) out = "ERR_BAD_CAL";
	if(code == VNALibrary::ERR_BAD_HANDLE) out = "ERR_BAD_HANDLE";
	if(code == VNALibrary::ERR_BAD_HOP) out = "ERR_BAD_HOP";
	if(code == VNALibrary::ERR_BAD_PATH) out = "ERR_BAD_PATH";
	if(code == VNALibrary::ERR_BAD_PROM) out = "ERR_BAD_PROM";
	if(code == VNALibrary::ERR_BYTES) out = "ERR_BYTES";
	if(code == VNALibrary::ERR_FREQ_OUT_OF_BOUNDS) out = "ERR_FREQ_OUT_OF_BOUNDS";
	if(code == VNALibrary::ERR_INTERRUPTED) out = "ERR_INTERRUPTED";
	if(code == VNALibrary::ERR_NO_RESPONSE) out = "ERR_NO_RESPONSE";
	if(code == VNALibrary::ERR_MISSING_IP) out = "ERR_MISSING_IP";
	if(code == VNALibrary::ERR_MISSING_PORT) out = "ERR_MISSING_PORT";
	if(code == VNALibrary::ERR_MISSING_HOP) out = "ERR_MISSING_HOP";
	if(code == VNALibrary::ERR_MISSING_ATTEN) out = "ERR_MISSING_ATTEN";
	if(code == VNALibrary::ERR_MISSING_FREQS) out = "ERR_MISSING_FREQS";
	if(code == VNALibrary::ERR_PROG_OVERFLOW) out = "ERR_PROG_OVERFLOW";
	if(code == VNALibrary::ERR_SOCKET) out = "ERR_SOCKET";
	if(code == VNALibrary::ERR_TOO_MANY_POINTS) out = "ERR_TOO_MANY_POINTS";
	if(code == VNALibrary::ERR_WRONG_STATE) out = "ERR_WRONG_STATE";
	return out;
}

const char *VNALibrary::versionString()
{
	if(d->p_versionString) return d->p_versionString();
	else return "";
}

TaskHandle VNALibrary::createTask()
{
	if(d->p_createTask) return d->p_createTask();
	else return 0;
}

void VNALibrary::deleteTask(TaskHandle t)
{
	if(d->p_deleteTask) d->p_deleteTask(t);
}

ErrCode VNALibrary::initialize(TaskHandle t, progress_callback callback, void *user)
{
	if(d->p_initialize) return d->p_initialize(t, callback, user);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::start(TaskHandle t)
{
	if(d->p_start) return d->p_start(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::stop(TaskHandle t)
{
	if(d->p_stop) return d->p_stop(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::setIPAddress(TaskHandle t, const char *ipv4)
{
	if(d->p_setIPAddress) return d->p_setIPAddress(t, ipv4);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::setIPPort(TaskHandle t, const int port)
{
	if(d->p_setIPPort) return d->p_setIPPort(t, port);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::setTimeout(TaskHandle t, const unsigned int timeout)
{
	if(d->p_setTimeout) return d->p_setTimeout(t, timeout);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::setHopRate(TaskHandle t, const HopRate rate)
{
	if(d->p_setHopRate) return d->p_setHopRate(t, rate);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::setAttenuation(TaskHandle t, const Attenuation atten)
{
	if(d->p_setAttenuation) return d->p_setAttenuation(t, atten);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::setFrequencies(TaskHandle t, const double *freqs, const unsigned int N)
{
	if(d->p_setFrequencies) return d->p_setFrequencies(t, freqs, N);
	else return VNALibrary::ERR_BAD_HANDLE;
}

TaskState VNALibrary::getState(TaskHandle t)
{
	if(d->p_getState) return d->p_getState(t);
	else return VNALibrary::TASK_UNINITIALIZED;
}

unsigned int VNALibrary::getTimeout(TaskHandle t)
{
	if(d->p_getTimeout) return d->p_getTimeout(t);
	else return 0;
}

const char *VNALibrary::getIPAddress(TaskHandle t)
{
	if(d->p_getIPAddress) return d->p_getIPAddress(t);
	else return "";
}

int VNALibrary::getIPPort(TaskHandle t)
{
	if(d->p_getIPPort) return d->p_getIPPort(t);
	else return 0;
}

HopRate VNALibrary::getHopRate(TaskHandle t)
{
	if(d->p_getHopRate) return d->p_getHopRate(t);
	else return VNALibrary::HOP_UNDEFINED;
}

Attenuation VNALibrary::getAttenuation(TaskHandle t)
{
	if(d->p_getAttenuation) return d->p_getAttenuation(t);
	else return VNALibrary::ATTEN_UNDEFINED;
}

unsigned int VNALibrary::getNumberOfFrequencies(TaskHandle t)
{
	if(d->p_getNumberOfFrequencies) return d->p_getNumberOfFrequencies(t);
	else return 0;
}

const double *VNALibrary::getFrequencies(TaskHandle t)
{
	if(d->p_getFrequencies) return d->p_getFrequencies(t);
	else return 0;
}

HardwareDetails VNALibrary::getHardwareDetails(TaskHandle t)
{
	HardwareDetails h;
	if(d->p_getHardwareDetails) return d->p_getHardwareDetails(t);
	else return h;
}

ErrCode VNALibrary::utilNearestLegalFreq(TaskHandle t, double &freq)
{
	if(d->p_utilNearestLegalFreq) return d->p_utilNearestLegalFreq(t, freq);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::utilFixLinearSweepLimits(TaskHandle t, double &startFreq, double &endFreq, const unsigned int N)
{
	if(d->p_utilFixLinearSweepLimits) return d->p_utilFixLinearSweepLimits(t, startFreq, endFreq, N);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::utilPingUnit(TaskHandle t)
{
	if(d->p_utilPingUnit) return d->p_utilPingUnit(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::utilGenerateLinearSweep(TaskHandle t, const double startFreq, const double endFreq, const unsigned int N)
{
	if(d->p_utilGenerateLinearSweep) return d->p_utilGenerateLinearSweep(t, startFreq, endFreq, N);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::measureUncalibrated(TaskHandle t, RFPath paths, ComplexData T1R1, ComplexData T1R2, ComplexData T2R1, ComplexData T2R2, ComplexData Ref)
{
	if(d->p_measureUncalibrated) return d->p_measureUncalibrated(t, paths, T1R1, T1R2, T2R1, T2R2, Ref);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::measure2PortCalibrated(TaskHandle t, SParameter paths, ComplexData S11, ComplexData S21, ComplexData S12, ComplexData S22)
{
	if(d->p_measure2PortCalibrated) return d->p_measure2PortCalibrated(t, paths, S11, S21, S12, S22);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::measureCalibrationStep(TaskHandle t, CalibrationStep step)
{
	if(d->p_measureCalibrationStep) return d->p_measureCalibrationStep(t, step);
	else return VNALibrary::ERR_BAD_HANDLE;
}
bool VNALibrary::haveCalP1Open(TaskHandle t)
{
	if(d->p_haveCalP1Open) return d->p_haveCalP1Open(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

bool VNALibrary::haveCalP1Short(TaskHandle t)
{
	if(d->p_haveCalP1Short) return d->p_haveCalP1Short(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

bool VNALibrary::haveCalP1Load(TaskHandle t)
{
	if(d->p_haveCalP1Load) return d->p_haveCalP1Load(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

bool VNALibrary::haveCalP2Open(TaskHandle t)
{
	if(d->p_haveCalP2Open) return d->p_haveCalP2Open(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

bool VNALibrary::haveCalP2Short(TaskHandle t)
{
	if(d->p_haveCalP2Short) return d->p_haveCalP2Short(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

bool VNALibrary::haveCalP2Load(TaskHandle t)
{
	if(d->p_haveCalP2Load) return d->p_haveCalP2Load(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

bool VNALibrary::haveCalThru(TaskHandle t)
{
	if(d->p_haveCalThru) return d->p_haveCalThru(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::interruptMeasurement(TaskHandle t)
{
	if(d->p_interruptMeasurement) return d->p_interruptMeasurement(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::clearCalibration(TaskHandle t)
{
	if(d->p_clearCalibration) return d->p_clearCalibration(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

bool VNALibrary::isCalibrationComplete(TaskHandle t)
{
	if(d->p_isCalibrationComplete) return d->p_isCalibrationComplete(t);
	else return false;
}

unsigned int VNALibrary::getCalibrationNumberOfFrequencies(TaskHandle t)
{
	if(d->p_getCalibrationNumberOfFrequencies) return d->p_getCalibrationNumberOfFrequencies(t);
	else return 0;
}

const double *VNALibrary::getCalibrationFrequencies(TaskHandle t)
{
	if(d->p_getCalibrationFrequencies) return d->p_getCalibrationFrequencies(t);
	else return 0;
}

ErrCode VNALibrary::exportCalibration(TaskHandle t, ComplexData e00, ComplexData e11, ComplexData e10e01, ComplexData e30, ComplexData e22, ComplexData e10e32, ComplexData ep33, ComplexData ep22, ComplexData ep23ep32, ComplexData ep03, ComplexData ep11, ComplexData ep23ep01)
{
	if(d->p_exportCalibration)
		return d->p_exportCalibration(t, e00,  e11,  e10e01,  e30,  e22,  e10e32,  ep33,  ep22,  ep23ep32,  ep03,  ep11,  ep23ep01);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::importCalibration(TaskHandle t, const double *freqs, const unsigned int N, const ComplexData e00, const ComplexData e11, const ComplexData e10e01, const ComplexData e30, const ComplexData e22, const ComplexData e10e32, const ComplexData ep33, const ComplexData ep22, const ComplexData ep23ep32, const ComplexData ep03, const ComplexData ep11, const ComplexData ep23ep01)
{
	if(d->p_importCalibration)
		return d->p_importCalibration(t, freqs, N, e00, e11, e10e01, e30, e22, e10e32, ep33, ep22, ep23ep32, ep03, ep11, ep23ep01);
	else return VNALibrary::ERR_BAD_HANDLE;
}

bool VNALibrary::hasFactoryCalibration(TaskHandle t)
{
	if(d->p_hasFactoryCalibration)
		return d->p_hasFactoryCalibration(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::importFactoryCalibration(TaskHandle t)
{
	if(d->p_importFactoryCalibration)
		return d->p_importFactoryCalibration(t);
	else return VNALibrary::ERR_BAD_HANDLE;
}

ErrCode VNALibrary::setOpenPhaseCorrection(TaskHandle t, const double* const phaseCorrections)
{
	if(d->p_setOpenPhaseCorrection)
		return d->p_setOpenPhaseCorrection(t, phaseCorrections);
	else return VNALibrary::ERR_BAD_HANDLE;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>
#include <QColor>
#include <QMessageBox>
#include <QFileDialog>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "vnalibrary.h"
#include "wrapperclasses.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	waitDialog = 0;

	buf1.I = buf1.Q = 0;
	buf2.I = buf2.Q = 0;
	buf3.I = buf3.Q = 0;
	buf4.I = buf4.Q = 0;
	buf5.I = buf5.Q = 0;
	freqAxis = 0;
	yAxis11 = 0;
	yAxis21 = 0;
	yAxis12 = 0;
	yAxis22 = 0;

	stopRequest = false;
	calStepRequest = false;

	updateDisabledState();

	registerTypes();
	configureWorkerThread();
	createPlots();
	setupSignalsAndSlots();
	loadVNADLL();
}

MainWindow::~MainWindow()
{
	worker.quit();
	worker.wait();

	delete waitDialog;

	delete ui;

	if(lib.isOK())
		lib.deleteTask(task);

	releaseMemory();
}
void MainWindow::registerTypes()
{
	// I can't pass custom types through the signals/slots
	// mechanism unless those types are registered with Qt
	qRegisterMetaType<QtErrCode>();
	qRegisterMetaType<QtRFPath>();
	qRegisterMetaType<QtSParameter>();
	qRegisterMetaType<QtCalibrationStep>();
	qRegisterMetaType<QtTaskHandle>();
	qRegisterMetaType<QtComplexData>();
	qRegisterMetaType<Qtprogress_callback>();
	qRegisterMetaType<Qtvoidptr>();
}

void MainWindow::configureWorkerThread()
{
	// Here I move the VNALibrary object to a different thread.
	// This has the effect of making its slots run on that
	// other thread, preventing the UI from blocking.
	lib.moveToThread(&worker);
	worker.start();
}

void MainWindow::createPlots()
{
	QGridLayout* L = ui->gridLayout;

	QwtPlotGrid *grid1 = new QwtPlotGrid();
	QwtPlotGrid *grid2 = new QwtPlotGrid();
	QwtPlotGrid *grid3 = new QwtPlotGrid();
	QwtPlotGrid *grid4 = new QwtPlotGrid();

	QPen lightGreyPen(Qt::lightGray, 0.0, Qt::SolidLine);

	grid1->setPen(lightGreyPen);
	grid2->setPen(lightGreyPen);
	grid3->setPen(lightGreyPen);
	grid4->setPen(lightGreyPen);

	s11 = new QwtPlot(QwtText("S11"));
	s11->setCanvasBackground(Qt::white);
	s11->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	grid1->attach( s11 );
	L->addWidget(s11, 0, 0);

	s21 = new QwtPlot(QwtText("S21"));
	s21->setCanvasBackground(Qt::white);
	s21->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	grid2->attach( s21 );
	L->addWidget(s21, 0, 1);

	s12 = new QwtPlot(QwtText("S12"));
	s12->setCanvasBackground(Qt::white);
	s12->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	grid3->attach( s12 );
	L->addWidget(s12, 1, 0);

	s22 = new QwtPlot(QwtText("S22"));
	s22->setCanvasBackground(Qt::white);
	s22->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	grid4->attach( s22 );
	L->addWidget(s22, 1, 1);


	c11 = new QwtPlotCurve("LogMag");
	c11->setRenderHint( QwtPlotItem::RenderAntialiased, true );
	c11->setPen(static_cast<QColor>(Qt::black));
	c11->attach(s11);

	c21 = new QwtPlotCurve("LogMag");
	c21->setRenderHint( QwtPlotItem::RenderAntialiased, true );
	c21->setPen(static_cast<QColor>(Qt::black));
	c21->attach(s21);

	c12 = new QwtPlotCurve("LogMag");
	c12->setRenderHint( QwtPlotItem::RenderAntialiased, true );
	c12->setPen(static_cast<QColor>(Qt::black));
	c12->attach(s12);

	c22 = new QwtPlotCurve("LogMag");
	c22->setRenderHint( QwtPlotItem::RenderAntialiased, true );
	c22->setPen(static_cast<QColor>(Qt::black));
	c22->attach(s22);




}

void MainWindow::setupSignalsAndSlots()
{
	connect(ui->doInitialize, SIGNAL(clicked(bool)), this, SLOT(onInitializeToggled(bool)));
	connect(ui->runToggle, SIGNAL(clicked(bool)), this, SLOT(onRunToggled(bool)));

	// MainWindow to VNALibrary
	connect(this, SIGNAL(requestLoadDLL(QString)), &lib, SLOT(loadAsync(QString)));
	connect(this, SIGNAL(requestInitialize(QtTaskHandle, Qtvoidptr)), &lib, SLOT(initializeAsync(QtTaskHandle, Qtvoidptr)));
	connect(this, SIGNAL(requestStart(QtTaskHandle)), &lib, SLOT(startAsync(QtTaskHandle)));
	connect(this, SIGNAL(requestStop(QtTaskHandle)), &lib, SLOT(stopAsync(QtTaskHandle)));
	connect(this, SIGNAL(requestUtilPingUnit(QtTaskHandle)), &lib, SLOT(utilPingUnitAsync(QtTaskHandle)));
	connect(this, SIGNAL(requestMeasureUncalibrated(QtTaskHandle,QtRFPath,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData)),
			&lib, SLOT(measureUncalibratedAsync(QtTaskHandle, QtRFPath, QtComplexData, QtComplexData, QtComplexData, QtComplexData, QtComplexData)));
	connect(this, SIGNAL(requestMeasure2PortCalibrated(QtTaskHandle,QtSParameter,QtComplexData,QtComplexData,QtComplexData,QtComplexData)),
			&lib, SLOT(measure2PortCalibratedAsync(QtTaskHandle, QtSParameter, QtComplexData, QtComplexData, QtComplexData, QtComplexData)));
	connect(this, SIGNAL(requestMeasureCalibrationStep(QtTaskHandle,QtCalibrationStep)),
			&lib, SLOT(measureCalibrationStepAsync(QtTaskHandle, QtCalibrationStep)));
	connect(this, SIGNAL(requestImportCalibrationAsync(QtTaskHandle,const double*,uint,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData)),
			&lib, SLOT(importCalibrationAsync(QtTaskHandle,const double*,uint,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData,QtComplexData)));

	// VNALibrary to MainWindow
	connect(&lib, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
	connect(&lib, SIGNAL(initializeProgress(int,Qtvoidptr)), this, SLOT(onInitializeProgress(int,Qtvoidptr)));
	connect(&lib, SIGNAL(initializeFinished(QtErrCode)), this, SLOT(onInitializeFinished(QtErrCode)));
	connect(&lib, SIGNAL(startFinished(QtErrCode)), this, SLOT(onStartFinished(QtErrCode)));
	connect(&lib, SIGNAL(stopFinished(QtErrCode)), this, SLOT(onStopFinished(QtErrCode)));
	connect(&lib, SIGNAL(utilPingUnitFinished(QtErrCode)), this, SLOT(onUtilPingUnitFinished(QtErrCode)));
	connect(&lib, SIGNAL(measureUncalibratedFinished(QtErrCode)), this, SLOT(onMeasureUncalibratedFinished(QtErrCode)));
	connect(&lib, SIGNAL(measure2PortCalibratedFinished(QtErrCode)), this, SLOT(onMeasure2PortCalibratedFinished(QtErrCode)));
	connect(&lib, SIGNAL(measureCalibrationStepFinished(QtErrCode)), this, SLOT(onMeasureCalibrationStepFinished(QtErrCode)));
	connect(&lib, SIGNAL(importCalibrationFinished(QtErrCode)), this, SLOT(onImportCalibrationFinished(QtErrCode)));

	// Cal buttons
	connect(ui->doP1Open,  SIGNAL(clicked(bool)), this, SLOT(onP1Open(bool)));
	connect(ui->doP1Short, SIGNAL(clicked(bool)), this, SLOT(onP1Short(bool)));
	connect(ui->doP1Load,  SIGNAL(clicked(bool)), this, SLOT(onP1Load(bool)));
	connect(ui->doP2Open,  SIGNAL(clicked(bool)), this, SLOT(onP2Open(bool)));
	connect(ui->doP2Short, SIGNAL(clicked(bool)), this, SLOT(onP2Short(bool)));
	connect(ui->doP2Load,  SIGNAL(clicked(bool)), this, SLOT(onP2Load(bool)));
	connect(ui->doThru,    SIGNAL(clicked(bool)), this, SLOT(onThru(bool)));
	connect(ui->applyOpenLength, SIGNAL(clicked(bool)), this, SLOT(onApplyOffsetLength(bool)));

	connect(ui->calibrationSetting, SIGNAL(currentIndexChanged(int)), this, SLOT(onCalTypeChanged(int)));
	connect(ui->clearCal, SIGNAL(clicked(bool)), this, SLOT(onClearCalibration(bool)));
	connect(ui->saveCal, SIGNAL(clicked(bool)), this, SLOT(onSaveCalibration(bool)));
	connect(ui->loadCal, SIGNAL(clicked(bool)), this, SLOT(onLoadCalibration(bool)));
}


void MainWindow::loadVNADLL()
{
	#ifdef WIN32
		emit requestLoadDLL(QString("vnadll.dll"));
	#else
		emit requestLoadDLL(QString("libvna.so"));
	#endif
}

void MainWindow::onInitializeProgress(int percent, Qtvoidptr user)
{
	if(waitDialog)
	{
		waitDialog->setValue(percent);
		if(percent == 100)
		{
			delete waitDialog;
			waitDialog = 0;
		}
	}
}

void MainWindow::onInitializeToggled(bool state)
{
	if(state)
	{
		// From off to on
		QString ip = QString("192.168.1.") + QString::number(ui->ip->value());
		lib.setIPAddress(task, ip.toStdString().c_str());
		lib.setIPPort(task, ui->port->value());
		lib.setTimeout(task, 150);

		waitDialog = new QProgressDialog("Retreiving hardware information...", "Cancel", 0, 100, this);
		waitDialog->setWindowModality(Qt::WindowModal);
		waitDialog->setMinimumDuration(0);
		waitDialog->setCancelButton(0); // disable

		emit requestInitialize(QtTaskHandle(task), Qtvoidptr((void*)this));
	}
	else
	{
		// From on to off
		if(ui->runToggle->isChecked())
		{
			ui->runToggle->setChecked(false);
			onRunToggled(false); // not automatically invoked by setChecked I guess
		}
	}
	updateDisabledState();
}

void MainWindow::onRunToggled(bool state)
{
	if(state)
	{
		// From off to on

		stopRequest = false;

		double fmin = ui->startFreq->value();
		double fmax = ui->stopFreq->value();
		double requestedN = ui->points->value();

		lib.utilGenerateLinearSweep(task, fmin, fmax, requestedN);

		lib.setAttenuation(task, lib.ATTEN_0);

		int hop = ui->sweepRate->currentIndex();
		HopRate rate = lib.HOP_45K;
		if(hop == 0) rate = lib.HOP_45K;
		if(hop == 1) rate = lib.HOP_30K;
		if(hop == 2) rate = lib.HOP_15K;
		if(hop == 3) rate = lib.HOP_7K;
		if(hop == 4) rate = lib.HOP_3K;
		if(hop == 5) rate = lib.HOP_2K;
		lib.setHopRate(task, rate);

		const double* freqs = lib.getFrequencies(task);
		nPts = lib.getNumberOfFrequencies(task);

		releaseMemory();
		allocateMemory(nPts);

		memcpy(freqAxis, freqs, nPts*sizeof(double));

		emit requestStart(QtTaskHandle(task));

	}
	else
	{
		// From on to off
		stopRequest = true;

		emit requestStop(QtTaskHandle(task));
	}

	updateDisabledState();
}

void MainWindow::onClearCalibration(bool)
{
	lib.clearCalibration(task);
	ui->p1OpenStatus->setChecked(false);
	ui->p1ShortStatus->setChecked(false);
	ui->p1LoadStatus->setChecked(false);
	ui->p2OpenStatus->setChecked(false);
	ui->p2ShortStatus->setChecked(false);
	ui->p2LoadStatus->setChecked(false);
	ui->thruStatus->setChecked(false);
	ui->calibrationSetting->setCurrentIndex(0);
}

class ComplexArray
{
	public:
		double* Idata, *Qdata;
		unsigned int N;
		ComplexArray(unsigned int n)
		{
			Idata = new double[n];
			Qdata = new double[n];
			N = n;
		}
		~ComplexArray()
		{
			delete [] Idata;
			delete [] Qdata;
		}
};

ComplexData wrapArray(ComplexArray a)
{
	ComplexData out;
	out.I = a.Idata;
	out.Q = a.Qdata;
	return out;
}
#define WRAP(a)        \
	ComplexData cd##a; \
	cd##a.I = a.Idata; \
	cd##a.Q = a.Qdata;

#define UNWRAP(a) cd##a.I = 0; cd##a.Q = 0;

void MainWindow::onSaveCalibration(bool)
{
	unsigned int N = lib.getCalibrationNumberOfFrequencies(task);
	ComplexArray EDF(N);
	ComplexArray ESF(N);
	ComplexArray ERF(N);
	ComplexArray EXF(N);
	ComplexArray ELF(N);
	ComplexArray ETF(N);
	ComplexArray EDR(N);
	ComplexArray ESR(N);
	ComplexArray ERR(N);
	ComplexArray EXR(N);
	ComplexArray ELR(N);
	ComplexArray ETR(N);

	WRAP(EDF);
	WRAP(ESF);
	WRAP(ERF);
	WRAP(EXF);
	WRAP(ELF);
	WRAP(ETF);
	WRAP(EDR);
	WRAP(ESR);
	WRAP(ERR);
	WRAP(EXR);
	WRAP(ELR);
	WRAP(ETR);

	const double* freqs = lib.getCalibrationFrequencies(task);

	ErrCode result = lib.exportCalibration(task,
										   cdEDF, cdESF, cdERF,
										   cdEXF, cdELF, cdETF,
										   cdEDR, cdESR, cdERR,
										   cdEXR, cdELR, cdETR);

	// I need to zero these out, otherwise when the ComplexData's get
	// deconstructed they try to delete the pointers too
	UNWRAP(EDF);
	UNWRAP(ESF);
	UNWRAP(ERF);
	UNWRAP(EXF);
	UNWRAP(ELF);
	UNWRAP(ETF);
	UNWRAP(EDR);
	UNWRAP(ESR);
	UNWRAP(ERR);
	UNWRAP(EXR);
	UNWRAP(ELR);
	UNWRAP(ETR);

	if(result != lib.ERR_OK)
	{
		QString msg = QString("Unable to export calibration. Error code: "+lib.ErrToString(result));
		statusBar()->showMessage(msg, 1000);
	}
	else
	{
		QString filename = QFileDialog::getSaveFileName(this,QString("Save Calibration File"),QString(""),QString("CSV Files (*.csv)"));
		FILE* file = fopen(filename.toStdString().c_str(), "wt");
		if(file)
		{
			fprintf(file, "Freq,EDFi,EDFq,ESFi,ESFq,ERFi,ERFq,EXFi,EXFq,ELFi,ELFq,ETFi,ETFq,EDRi,EDRq,ESRi,ESRq,ERRi,ERRq,EXRi,EXRq,ELRi,ELRq,ETRi,ETRq\n");
			for(unsigned int i=0; i<N; ++i)
				fprintf(file,"%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f,%.16f\n",
						freqs[i],
						EDF.Idata[i], EDF.Qdata[i],
						ESF.Idata[i], ESF.Qdata[i],
						ERF.Idata[i], ERF.Qdata[i],
						EXF.Idata[i], EXF.Qdata[i],
						ELF.Idata[i], ELF.Qdata[i],
						ETF.Idata[i], ETF.Qdata[i],
						EDR.Idata[i], EDR.Qdata[i],
						ESR.Idata[i], ESR.Qdata[i],
						ERR.Idata[i], ERR.Qdata[i],
						EXR.Idata[i], EXR.Qdata[i],
						ELR.Idata[i], ELR.Qdata[i],
						ETR.Idata[i], ETR.Qdata[i]
					   );
			fclose(file);
			statusBar()->showMessage(QString("Wrote ")+filename, 1000);
		}
	}

}
#define MAKE(name,L)               \
	ComplexData name;              \
	name.I = new double[L];        \
	name.Q = new double[L];

#define CPY(name, i)               \
name.I[i] = importData[i].name##i; \
name.Q[i] = importData[i].name##q;

typedef struct _Row
{
	double freq;
	double EDFi;
	double EDFq;
	double ESFi;
	double ESFq;
	double ERFi;
	double ERFq;
	double EXFi;
	double EXFq;
	double ELFi;
	double ELFq;
	double ETFi;
	double ETFq;
	double EDRi;
	double EDRq;
	double ESRi;
	double ESRq;
	double ERRi;
	double ERRq;
	double EXRi;
	double EXRq;
	double ELRi;
	double ELRq;
	double ETRi;
	double ETRq;
} Row;

void MainWindow::onLoadCalibration(bool)
{
	QString filename = QFileDialog::getOpenFileName(this, QString("Open Calibration File"),QString(),QString("CSV Files (*.csv)"));
	FILE* file = fopen(filename.toStdString().c_str(),"rt");
	if(file)
	{
		const int MAX_LINE_WIDTH = 65535;
		char line[MAX_LINE_WIDTH];
		std::vector<Row> importData;

		int i=0;
		bool ok = true;
		while(fgets(line, MAX_LINE_WIDTH, file) != 0)
		{
			if(i==0)
			{
				++i;    //first line is header
				continue;
			}
			Row row;
			int count = sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
							   &(row.freq),
							   &(row.EDFi),&(row.EDFq), &(row.ESFi),&(row.ESFq), &(row.ERFi),&(row.ERFq), &(row.EXFi),&(row.EXFq), &(row.ELFi),&(row.ELFq), &(row.ETFi),&(row.ETFq),
							   &(row.EDRi),&(row.EDRq), &(row.ESRi),&(row.ESRq), &(row.ERRi),&(row.ERRq), &(row.EXRi),&(row.EXRq), &(row.ELRi),&(row.ELRq), &(row.ETRi),&(row.ETRq));
			if(count != 25)
			{
				QMessageBox box;
				box.setText(QString("Error during import: line ")+QString::number(count+1)+QString(" had wrong number of columns (expected 13)"));
				box.exec();
				ok = false;
				break;
			}

			importData.push_back(row);
		}

		if(ok)
		{
			const int nF = importData.size();
			double* freqs = new double[nF];
			MAKE(EDF,nF);
			MAKE(ESF,nF);
			MAKE(ERF,nF);
			MAKE(EXF,nF);
			MAKE(ELF,nF);
			MAKE(ETF,nF);
			MAKE(EDR,nF);
			MAKE(ESR,nF);
			MAKE(ERR,nF);
			MAKE(EXR,nF);
			MAKE(ELR,nF);
			MAKE(ETR,nF);
			for(int i=0; i<nF; ++i)
			{
				freqs[i] = importData[i].freq;
				CPY(EDF,i);
				CPY(ESF,i);
				CPY(ERF,i);
				CPY(EXF,i);
				CPY(ELF,i);
				CPY(ETF,i);
				CPY(EDR,i);
				CPY(ESR,i);
				CPY(ERR,i);
				CPY(EXR,i);
				CPY(ELR,i);
				CPY(ETR,i);
			}

			// I'm making this call through the signals/slots mechanism
			// to guarantee that this call happens in the same event
			// handler loop as the data measurements. This guarantees
			// that the cal parameters won't be altered at the same time
			// the parameters are being used.
			emit requestImportCalibrationAsync(task, freqs, nF,
											   EDF, ESF, ERF, EXF, ELF, ETF,
											   EDR, ESR, ERR, EXR, ELR, ETR);

		}
	}
}
void MainWindow::onImportCalibrationFinished(QtErrCode result)
{
	ErrCode code = result.val;
	if(code != lib.ERR_OK)
	{
		QMessageBox box;
		QString msg = QString("Unable to load calibration, code: "+lib.ErrToString(result.val));
		box.setText(msg);
		box.exec();
	}
	else
	{
		// The calibration file does not contain the raw data used to compute
		// the parameters. The dll cleared any existing raw data when we loaded
		// the file, so to reflect that we should uncheck all the status boxes.
		ui->p1OpenStatus->setChecked(false);
		ui->p1ShortStatus->setChecked(false);
		ui->p1LoadStatus->setChecked(false);
		ui->p2OpenStatus->setChecked(false);
		ui->p2ShortStatus->setChecked(false);
		ui->p2LoadStatus->setChecked(false);
		ui->thruStatus->setChecked(false);

		// automatically select the loaded calibration
		ui->calibrationSetting->setCurrentIndex(2);
	}
}

void MainWindow::onLoadFinished(bool result)
{
	if(result)
	{
		this->statusBar()->showMessage(QString(lib.versionString()), 10000);
		task = lib.createTask();
	}
	else
	{
		QMessageBox box;
		box.setText("The VNA DLL (vnadll.dll) failed to load. All functions are disabled.");
		box.exec();
		ui->centralWidget->setDisabled(true);
	}
}
void MainWindow::releaseMemory()
{
	delete [] buf1.I;
	delete [] buf1.Q;
	delete [] buf2.I;
	delete [] buf2.Q;
	delete [] buf3.I;
	delete [] buf3.Q;
	delete [] buf4.I;
	delete [] buf4.Q;
	delete [] buf5.I;
	delete [] buf5.Q;
	delete [] freqAxis;
	delete [] yAxis11;
	delete [] yAxis21;
	delete [] yAxis12;
	delete [] yAxis22;
}
void MainWindow::allocateMemory(unsigned int N)
{
	buf1.I = new double[N];
	buf1.Q = new double[N];
	buf2.I = new double[N];
	buf2.Q = new double[N];
	buf3.I = new double[N];
	buf3.Q = new double[N];
	buf4.I = new double[N];
	buf4.Q = new double[N];
	buf5.I = new double[N];
	buf5.Q = new double[N];
	freqAxis = new double[N];
	yAxis11 = new double[N];
	yAxis21 = new double[N];
	yAxis12 = new double[N];
	yAxis22 = new double[N];

	// QwtPlotCurve::setRawSamples tells the plot to simply
	// read from these pointers, rather than making a copy
	// internally
	c11->setRawSamples(freqAxis, yAxis11, N);
	c21->setRawSamples(freqAxis, yAxis21, N);
	c12->setRawSamples(freqAxis, yAxis12, N);
	c22->setRawSamples(freqAxis, yAxis22, N);
}

void MainWindow::onInitializeFinished(QtErrCode result)
{
	if(result.val != lib.ERR_OK)
	{
		QMessageBox box;
		box.setText("Unable to initialize VNA task.\nError code: "+lib.ErrToString(result.val));
		box.exec();
		ui->doInitialize->setChecked(false); // reject button press
		onInitializeToggled(false); // not automatically called by setChecked
	}
	else
	{
		HardwareDetails details = lib.getHardwareDetails(task);
		ui->startFreq->setMinimum(details.minimum_frequency);
		ui->startFreq->setMaximum(details.maximum_frequency);
		ui->stopFreq->setMinimum(details.minimum_frequency);
		ui->stopFreq->setMaximum(details.maximum_frequency);
		ui->points->setMinimum(2);
		ui->points->setMaximum(details.maximum_points);
		// Note that setting the limits invokes the validator, so at this
		// moment the values are legal

		if(ui->startFreq->value() == ui->stopFreq->value())
		{
			ui->startFreq->setValue(details.minimum_frequency);
			ui->stopFreq->setValue(details.maximum_frequency);
		}

		if(ui->startFreq->value() > ui->stopFreq->value())
		{
			double tmp = ui->stopFreq->value();
			ui->stopFreq->setValue(ui->startFreq->value());
			ui->startFreq->setValue(tmp);
		}

	}
}
void MainWindow::updateDisabledState()
{
	bool initialized = ui->doInitialize->isChecked();
	bool running = ui->runToggle->isChecked();

	if(initialized)
	{
		ui->runToggle->setDisabled(false);
		ui->ip->setDisabled(true);
		ui->port->setDisabled(true);
	}
	else
	{
		ui->runToggle->setDisabled(true);
		ui->ip->setDisabled(false);
		ui->port->setDisabled(false);
	}

	if(running)
	{
		ui->runToggle->setText("Click to stop");
		ui->calGroup->setDisabled(false);
		ui->stimGroup->setDisabled(true);
	}
	else
	{
		ui->runToggle->setText("Run");
		ui->calGroup->setDisabled(true);
		ui->stimGroup->setDisabled(false);
	}
}

void MainWindow::onStartFinished(QtErrCode result)
{
	if(result.val != lib.ERR_OK)
	{
		QMessageBox box;
		box.setText("Unable to start VNA task.\nError code: "+lib.ErrToString(result.val));
		box.exec();
		ui->runToggle->setChecked(false); // reject button press
	}
	else
	{
		if(lib.getState(task) != lib.TASK_STARTED)
		{
			QMessageBox box;
			box.setText("This should not happen by design");
			box.exec();
			ui->runToggle->setChecked(false); // reject button press
		}
		else
		{
			setAxes();
			measureAgain();
		}
	}
}

void MainWindow::measureAgain()
{
	if(stopRequest)
	{
		stopRequest = false;
		return;
	}

	if(calStepRequest)
	{
		calStepRequest = false;
		emit requestMeasureCalibrationStep(QtTaskHandle(task), QtCalibrationStep(step));

	}
	else
	{
		int setting = ui->calibrationSetting->currentIndex();
		if(setting == 0)
		{
			// calibration off: measure raw data
			QtRFPath path = QtRFPath(lib.PATH_T1R1 | lib.PATH_T1R2 | lib.PATH_T2R1 | lib.PATH_T2R2 | lib.PATH_REF);
			emit requestMeasureUncalibrated(QtTaskHandle(task), path,
											QtComplexData(buf1), QtComplexData(buf2),
											QtComplexData(buf3), QtComplexData(buf4),
											QtComplexData(buf5));
		}
		else
		{
			// calibrated data
			QtSParameter paths = QtSParameter(lib.PARAM_S11 | lib.PARAM_S21 | lib.PARAM_S12 | lib.PARAM_S22);
			emit requestMeasure2PortCalibrated(QtTaskHandle(task), paths,
											   QtComplexData(buf1), QtComplexData(buf2),
											   QtComplexData(buf3), QtComplexData(buf4));
		}
	}
}

void MainWindow::setAxes()
{
	int setting = ui->calibrationSetting->currentIndex();
	if(setting == 0)
	{
		// raw data goes from 0 to 96.3 (max I or Q is 32767)
		s11->setAxisScale(QwtPlot::yLeft, 0, 100);
		s21->setAxisScale(QwtPlot::yLeft, 0, 100);
		s12->setAxisScale(QwtPlot::yLeft, 0, 100);
		s22->setAxisScale(QwtPlot::yLeft, 0, 100);
	}
	else
	{
		// calibrated data goes from -100 to 0
		s11->setAxisScale(QwtPlot::yLeft, -100, 0);
		s21->setAxisScale(QwtPlot::yLeft, -100, 0);
		s12->setAxisScale(QwtPlot::yLeft, -100, 0);
		s22->setAxisScale(QwtPlot::yLeft, -100, 0);
	}
	s11->setAxisScale(QwtPlot::xBottom, freqAxis[0], freqAxis[nPts-1]);
	s21->setAxisScale(QwtPlot::xBottom, freqAxis[0], freqAxis[nPts-1]);
	s12->setAxisScale(QwtPlot::xBottom, freqAxis[0], freqAxis[nPts-1]);
	s22->setAxisScale(QwtPlot::xBottom, freqAxis[0], freqAxis[nPts-1]);
}

void MainWindow::onStopFinished(QtErrCode result)
{
	if(result.val != lib.ERR_OK)
	{
		QMessageBox box;
		box.setText("Unable to stop VNA task.\nError code: "+lib.ErrToString(result.val));
		box.exec();
	}
}

void MainWindow::onUtilPingUnitFinished(QtErrCode result)
{
	if(result.val != lib.ERR_OK)
	{
		QMessageBox box;
		box.setText(lib.ErrToString(result.val));
		box.exec();
	}
}

void MainWindow::onMeasureUncalibratedFinished(QtErrCode result)
{
	if(result.val != lib.ERR_OK)
	{
		QString msg = QString("Measurement error, code: "+lib.ErrToString(result.val));
		statusBar()->showMessage(msg, 1000);
	}
	else
	{
		/*printf("%.0f %.0f    %.0f %.0f    %.0f %.0f    %.0f %.0f    %.0f %.0f\n",
			   buf1.I[0], buf1.Q[0],
			   buf2.I[0], buf2.Q[0],
			   buf3.I[0], buf3.Q[0],
			   buf4.I[0], buf4.Q[0],
			   buf5.I[0], buf5.Q[0]);*/
		//statusBar()->showMessage(QString("Sweep time: ")+QString::number(result.time)+QString(" ms"), 1000);
		updatePlotData();
	}
	measureAgain();
}

void MainWindow::onMeasure2PortCalibratedFinished(QtErrCode result)
{
	if(result.val != lib.ERR_OK)
	{
		QString msg;
		if(lib.isCalibrationComplete(task) == false)
			msg = QString("No valid calibration found");
		else
			msg = QString("Measurement error, code: "+lib.ErrToString(result.val));
		statusBar()->showMessage(msg, 1000);
	}
	else
	{
		/*printf("%.1f %.1f    %.1f %.1f    %.1f %.1f    %.1f %.1f\n",
			   buf1.I[0], buf1.Q[0],
			   buf2.I[0], buf2.Q[0],
			   buf3.I[0], buf3.Q[0],
			   buf4.I[0], buf4.Q[0]);*/
		//statusBar()->showMessage(QString("Sweep time: ")+QString::number(result.time)+QString(" ms"), 1000);
		updatePlotData();
	}
	measureAgain();
}

void MainWindow::onMeasureCalibrationStepFinished(QtErrCode result)
{
	printf("Cal step finished\n");
	if(result.val != lib.ERR_OK)
	{
		QString msg = QString("Measurement error, code: "+lib.ErrToString(result.val));
		statusBar()->showMessage(msg, 1000);
	}
	else
	{
		// update checkboxes
		ui->p1OpenStatus->setChecked(lib.haveCalP1Open(task));
		ui->p1ShortStatus->setChecked(lib.haveCalP1Short(task));
		ui->p1LoadStatus->setChecked(lib.haveCalP1Load(task));
		ui->p2OpenStatus->setChecked(lib.haveCalP2Open(task));
		ui->p2ShortStatus->setChecked(lib.haveCalP2Short(task));
		ui->p2LoadStatus->setChecked(lib.haveCalP2Load(task));
		ui->thruStatus->setChecked(lib.haveCalThru(task));

		if(lib.isCalibrationComplete(task))
			ui->calibrationSetting->setCurrentIndex(2);
	}
	measureAgain();
}

void MainWindow::onP1Open(bool)
{
	calStepRequest = true;
	step = lib.STEP_P1_OPEN;
}

void MainWindow::onP1Short(bool)
{
	calStepRequest = true;
	step = lib.STEP_P1_SHORT;
}

void MainWindow::onP1Load(bool)
{
	calStepRequest = true;
	step = lib.STEP_P1_LOAD;
}

void MainWindow::onP2Open(bool)
{
	calStepRequest = true;
	step = lib.STEP_P2_OPEN;
}

void MainWindow::onP2Short(bool)
{
	calStepRequest = true;
	step = lib.STEP_P2_SHORT;
}

void MainWindow::onP2Load(bool)
{
	calStepRequest = true;
	step = lib.STEP_P2_LOAD;
}

void MainWindow::onThru(bool)
{
	calStepRequest = true;
	step = lib.STEP_THRU;
}

void MainWindow::onApplyOffsetLength(bool)
{
	// phase rotation vs time is
	// 2*pi*f*t
	// For propagation through distance L, t = L/c.
	// phase = 2*pi*f*L/c

	const unsigned int N = lib.getCalibrationNumberOfFrequencies(task);
	double* phases = new double[N];
	const double* const f = lib.getCalibrationFrequencies(task);
	const double L = ui->openLength->value() / 1000.0; // the control is in mm, so convert to m
	const double c = 299792458.0 / 1e6; // divide by 1e6 since f is in MHz
	for(unsigned int i=0; i<N; ++i)
	{
		phases[i] = 2*M_PI*f[i]*L/c;
	}
	ErrCode code = lib.setOpenPhaseCorrection(task, phases);
	delete [] phases;

	if(code != lib.ERR_OK)
	{
		QMessageBox box;
		box.setText("Problem setting phase corrections.\nError code: "+lib.ErrToString(code));
		box.exec();
	}

}


void MainWindow::onCalTypeChanged(int index)
{
	setAxes();

	// When going from calibrated to uncalibrated, nothing special needs to happen
	if(index == 0)
	{

	}
	// When switching to factory cal, I need to load it
	else if(index == 1)
	{
		if(lib.hasFactoryCalibration(task))
			lib.importFactoryCalibration(task);
		else
		{
			QMessageBox box;
			box.setText("Unit does not have a factory calibration");
			box.exec();

			ui->calibrationSetting->setCurrentIndex(0);
		}
	}
	else if(index == 2)
	{
		// Nothing to do. Note that this means if the user selects factory cal,
		// and then user cal, the cal parameters are unchanged, but now there
		// is no intermediate raw data available since it was cleared by the
		// dll when the factory cal was loaded.
	}

}

void computeLogMag(double& dest, const double I, const double Q)
{
	double mag = sqrt( I*I + Q*Q );
	dest = mag > 0.0f ? 20 * log10(mag) : -100;
}

void MainWindow::updatePlotData()
{
	for(int i=0; i<nPts; ++i)
	{
		computeLogMag(yAxis11[i], buf1.I[i], buf1.Q[i]);
		computeLogMag(yAxis21[i], buf2.I[i], buf2.Q[i]);
		computeLogMag(yAxis12[i], buf3.I[i], buf3.Q[i]);
		computeLogMag(yAxis22[i], buf4.I[i], buf4.Q[i]);
	}
	s11->replot();
	s21->replot();
	s12->replot();
	s22->replot();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QProgressDialog>
#include "vnalibrary.h"
#include "dataacquisitionthread.h"
#include "wrapperclasses.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

		bool onProgress(int percentComplete);

	private:
		Ui::MainWindow *ui;
		// Designer doesn't have a QwtPlot plugin so I manually
		// create and add the plots to the UI
		QwtPlot *s11, *s21, *s12, *s22;
		QwtPlotCurve *c11, *c21, *c12, *c22;

		VNALibrary lib;
		TaskHandle task;
		QThread worker;

		void registerTypes();
		void configureWorkerThread();
		void createPlots();
		void setupSignalsAndSlots();
		void loadVNADLL();

		ComplexData buf1, buf2, buf3, buf4, buf5;
		double* yAxis11, *yAxis21, *yAxis12, *yAxis22;
		double* freqAxis;
		int nPts;
		void releaseMemory();
		void allocateMemory(unsigned int N);

		QProgressDialog* waitDialog;


		bool stopRequest;
		bool calStepRequest;
		CalibrationStep step;
		void measureAgain();

		void setAxes();
		void updatePlotData();

		void updateDisabledState();

	signals:
		void requestLoadDLL(QString path);
		void requestInitialize(QtTaskHandle t, Qtvoidptr user);
		void requestStart(QtTaskHandle t);
		void requestStop(QtTaskHandle t);
		void requestUtilPingUnit(QtTaskHandle t);
        void requestMeasureUncalibrated(QtTaskHandle t, QtComplexData T1R1, QtComplexData T1R2, QtComplexData T2R1, QtComplexData T2R2, QtComplexData Ref);
		void requestMeasure2PortCalibrated(QtTaskHandle t, QtComplexData S11, QtComplexData S21, QtComplexData S12, QtComplexData S22);
		void requestMeasureCalibrationStep(QtTaskHandle t, QtCalibrationStep step);
		void requestImportCalibrationAsync(QtTaskHandle t,const double* freqs, const unsigned int N,
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
		void requestClearCalibration(QtTaskHandle t);

	private slots:
		void onLoadFinished(bool result);
		void onInitializeProgress(int percent, Qtvoidptr user);
		void onInitializeFinished(QtErrCode result);
		void onStartFinished(QtErrCode result);
		void onStopFinished(QtErrCode result);
		void onUtilPingUnitFinished(QtErrCode result);
		void onMeasureUncalibratedFinished(QtErrCode result);
		void onMeasure2PortCalibratedFinished(QtErrCode result);
		void onMeasureCalibrationStepFinished(QtErrCode result);
		void onImportCalibrationFinished(QtErrCode result);
		void onClearCalibrationFinished(QtErrCode result);

		void onInitializeToggled(bool state);
		void onRunToggled(bool state);
		void onClearCalibration(bool);
		void onSaveCalibration(bool);
		void onLoadCalibration(bool);

		void onP1Open(bool);
		void onP1Short(bool);
		void onP1Load(bool);
		void onP2Open(bool);
		void onP2Short(bool);
		void onP2Load(bool);
		void onThru(bool);

		void onApplyOffsetLength(bool);

		void onCalTypeChanged(int index);

};

#endif // MAINWINDOW_H

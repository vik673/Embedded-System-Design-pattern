#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TestBuilder.h"

int main() {
    TestBuilder* p_TestBuilder;
    
    // Initialize random seed
    srand((unsigned int)time(NULL));
    
    printf("ECG Monitor System - Client-Server Architecture Demo\n");
    printf("=====================================================\n\n");
    
    p_TestBuilder = TestBuilder_Create();
    
    // Acquire some ECG data values
    printf("Acquiring ECG data...\n");
    ECG_Module_acquireValue(&(p_TestBuilder->itsECG_Module));
    ECG_Module_acquireValue(&(p_TestBuilder->itsECG_Module));
    ECG_Module_acquireValue(&(p_TestBuilder->itsECG_Module));
    ECG_Module_acquireValue(&(p_TestBuilder->itsECG_Module));
    ECG_Module_acquireValue(&(p_TestBuilder->itsECG_Module));
    
    printf("\nHistogram Display processing data:\n");
    HistogramDisplay_getValue(&(p_TestBuilder->itsHistogramDisplay));
    HistogramDisplay_getValue(&(p_TestBuilder->itsHistogramDisplay));
    HistogramDisplay_getValue(&(p_TestBuilder->itsHistogramDisplay));
    HistogramDisplay_getValue(&(p_TestBuilder->itsHistogramDisplay));
    HistogramDisplay_getValue(&(p_TestBuilder->itsHistogramDisplay));
    
    printf("\nQRS Detector processing data:\n");
    QRSDetector_getDataSample(&(p_TestBuilder->itsQRSDetector));
    QRSDetector_getDataSample(&(p_TestBuilder->itsQRSDetector));
    QRSDetector_getDataSample(&(p_TestBuilder->itsQRSDetector));
    
    printf("\nWaveform Display processing data:\n");
    WaveformDisplay_getScalarValue(&(p_TestBuilder->itsWaveformDisplay));
    WaveformDisplay_getScalarValue(&(p_TestBuilder->itsWaveformDisplay));
    WaveformDisplay_getScalarValue(&(p_TestBuilder->itsWaveformDisplay));
    WaveformDisplay_getScalarValue(&(p_TestBuilder->itsWaveformDisplay));
    WaveformDisplay_getScalarValue(&(p_TestBuilder->itsWaveformDisplay));
    
    printf("\nArrythmia Detector processing data:\n");
    ArrythmiaDetector_getDataSample(&(p_TestBuilder->itsArrythmiaDetector));
    ArrythmiaDetector_getDataSample(&(p_TestBuilder->itsArrythmiaDetector));
    ArrythmiaDetector_getDataSample(&(p_TestBuilder->itsArrythmiaDetector));
    ArrythmiaDetector_getDataSample(&(p_TestBuilder->itsArrythmiaDetector));
    ArrythmiaDetector_getDataSample(&(p_TestBuilder->itsArrythmiaDetector));
    
    printf("\nDone\n");
    
    TestBuilder_Destroy(p_TestBuilder);
    
    return 0;
}

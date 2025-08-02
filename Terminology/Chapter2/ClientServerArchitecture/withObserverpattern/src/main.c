#include <stdio.h>
#include "TestBuilder.h"
#include "ECG_Module.h"

int main(void) {
    printf("==================================================\n");
    printf("         Observer Pattern Implementation\n");
    printf("==================================================\n\n");
    
    TestBuilder* p_TestBuilder = TestBuilder_Create();
    
    printf("Creating ECG system with Observer pattern...\n");
    printf("Subscribers: HistogramDisplay, WaveformDisplay, QRSDetector, ArrythmiaDetector\n\n");
    
    printf("Starting ECG data acquisition and automatic notification:\n");
    printf("=========================================================\n");
    
    /* When ECG Module generates data, all observers are automatically notified */
    ECG_Module_getDataSample(&(p_TestBuilder->itsECG_Module));
    printf("\n");
    
    ECG_Module_getDataSample(&(p_TestBuilder->itsECG_Module));
    printf("\n");
    
    ECG_Module_getDataSample(&(p_TestBuilder->itsECG_Module));
    printf("\n");
    
    ECG_Module_getDataSample(&(p_TestBuilder->itsECG_Module));
    printf("\n");
    
    printf("==================================================\n");
    printf("Observer Pattern Benefits Demonstrated:\n");
    printf("- Automatic push-based data distribution\n");
    printf("- Dynamic subscription/unsubscription\n");
    printf("- Loose coupling between data producer and consumers\n");
    printf("- Efficient - only notified when data changes\n");
    printf("==================================================\n");
    
    TestBuilder_Destroy(p_TestBuilder);
    
    return 0;
}

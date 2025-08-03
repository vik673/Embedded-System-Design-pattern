#include "LightControllerClient.h"
#include <stdio.h>

int main(void) {
    printf("Decomposed AND-State Pattern Implementation\n");
    printf("===========================================\n\n");
    
    LightControllerClient* client = LightControllerClient_Create();
    
    if (client != NULL) {
        LightControllerClient_runDemo(client);
        LightControllerClient_Destroy(client);
    } else {
        printf("Error: Failed to create LightControllerClient\n");
        return 1;
    }
    
    return 0;
}

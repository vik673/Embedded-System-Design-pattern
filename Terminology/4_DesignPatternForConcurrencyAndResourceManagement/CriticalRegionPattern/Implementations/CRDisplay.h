#ifndef CRDisplay_H
#define CRDisplay_H

typedef struct CRDisplay CRDisplay;

struct CRDisplay {
    // Display-specific data members would go here
    int displayId;
};

/* Constructor and destructor */
void CRDisplay_Init(CRDisplay* const me);
void CRDisplay_Cleanup(CRDisplay* const me);
CRDisplay* CRDisplay_Create(void);
void CRDisplay_Destroy(CRDisplay* const me);

/* Operations */
void CRDisplay_printMsg(CRDisplay* const me, const char* message);
void CRDisplay_printInt(CRDisplay* const me, const char* prefix, int value);

#endif

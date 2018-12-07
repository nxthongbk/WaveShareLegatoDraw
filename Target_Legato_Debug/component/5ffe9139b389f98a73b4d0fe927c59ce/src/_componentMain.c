/*
 * AUTO-GENERATED _componentMain.c for the FBTestComponent component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component log session variables.
le_log_SessionRef_t FBTestComponent_LogSession;
le_log_Level_t* FBTestComponent_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _FBTestComponent_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _FBTestComponent_Init(void)
{
    LE_DEBUG("Initializing FBTestComponent component library.");

    // Register the component with the Log Daemon.
    FBTestComponent_LogSession = log_RegComponent("FBTestComponent", &FBTestComponent_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_FBTestComponent_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif

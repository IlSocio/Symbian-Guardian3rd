// ET_CLSVR.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//
/**
 @file 
 @publishedAll
 @released 

 This version of the file contains the reordered version of the IPC table for the purpose
 of having a more efficient policy table as part of the platform security framework.
 Previously IPCs were ordered by functional area and now they are ordered by the capability
 associated with them.
*/

#if !defined (__ET_CLISVR_H__)
#define __ET_CLISVR_H__

#define IPC_ETEL_CORE   (0)

/**
Used by extension APIs to offset their cancel IPC values
*/
#define EMobileCancelOffset					500

//
// None
//
enum
	{
	EEtelOpenFromSession = 0,                                    // 0
	EEtelOpenFromSubSession,                                     // 1
	EEtelOpenByNameFromSession,                                  // 2
	EEtelOpenByNameFromSubSession,                               // 3
	EEtelClose,                                                  // 4
	EEtelCancelSubSession,                                       // 5
	EETelLineCapsChangeNotification,                             // 6
	EETelLineCapsChangeNotificationCancel,                       // 7
	EETelPhoneCapsChangeNotification,                            // 8
	EETelPhoneCapsChangeNotificationCancel,                      // 9
	EEtelCallCapsChangeNotification,                             // 10
	EEtelCallCapsChangeNotificationCancel,                       // 11
	EEtelCallGetBearerServiceInfo,                               // 12
	EEtelCallGetCallDuration,                                    // 13
	EEtelCallGetCallParams,                                      // 14
	EEtelCallGetCaps,                                            // 15
	EEtelCallGetFaxSettings,                                     // 16
	EEtelCallGetInfo,                                            // 17
	EEtelCallGetOwnershipStatus,                                 // 18
	EEtelCallGetStatus,                                          // 19
	EEtelCallNotifyDurationChange,                               // 20
	EEtelCallNotifyDurationChangeCancel,                         // 21
	EEtelCallNotifyHookChange,                                   // 22
	EEtelCallNotifyHookChangeCancel,                             // 23
	EEtelCallNotifyStatusChange,                                 // 24
	EEtelCallNotifyStatusChangeCancel,                           // 25
	EEtelCallReferenceCount,                                     // 26
	EEtelDbgCheckHeap,                                           // 27
	EEtelDbgDoDumpDebugInfo,                                     // 28
	EEtelDbgFailNext,                                            // 29
	EEtelDbgMarkEnd,                                             // 30
	EEtelDbgMarkHeap,                                            // 31
	EEtelDbgSetDebugPrintMask,                                   // 32
	EEtelFaxWaitForEndOfPage,                                    // 33
	EEtelLineEnumerateCall,                                      // 34
	EEtelLineGetCallInfo,                                        // 35
	EEtelLineGetCaps,                                            // 36
	EEtelLineGetHookStatus,                                      // 37
	EEtelLineGetInfo,                                            // 38
	EEtelLineGetStatus,                                          // 39
	EEtelLineNotifyCallAdded,                                    // 40
	EEtelLineNotifyCallAddedCancel,                              // 41
	EEtelLineNotifyHookChange,                                   // 42
	EEtelLineNotifyHookChangeCancel,                             // 43
	EEtelLineNotifyStatusChange,                                 // 44
	EEtelLineNotifyStatusChangeCancel,                           // 45
	EEtelPhoneEnumerateLines,                                    // 46
	EEtelPhoneGetCaps,                                           // 47
	EEtelPhoneGetInfo,                                           // 48
	EEtelPhoneGetLineInfo,                                       // 49
	EEtelPhoneGetStatus,                                         // 50
	EEtelPhoneNotifyModemDetected,                               // 51
	EEtelPhoneNotifyModemDetectedCancel,                         // 52
	EEtelServerClosePhoneModule,                                 // 53
	EEtelServerEnumeratePhones,                                  // 54
	EEtelServerGetTsyName,                                       // 55
	EEtelServerGetTsyVersionNo,                                  // 56
	EEtelServerLoadPhoneModule,                                  // 57
	EEtelServerOpen,                                             // 58
	EEtelServerPhoneInfoByIndex,                                 // 59
	EEtelServerQueryTsyFunctionality,                            // 60
	EEtelServerSetExtendedErrorGranularity                       // 61
	};

//
// NetworkServices
//
enum
	{
	EEtelAdoptFaxSharedHeaderFile = 62,                          // 62
	EEtelCallAcquireOwnership,                                   // 63
	EEtelCallAcquireOwnershipCancel,                             // 64
	EEtelCallConnect,                                            // 65
	EEtelCallConnectCancel,                                      // 66
	EEtelCallHangUp,                                             // 67
	EEtelCallHangUpCancel,                                       // 68
	EEtelCallTransferOwnership,                                  // 69
	EEtelFaxTerminateFaxSession,                                 // 70
	EEtelLineNotifyIncomingCall,                                 // 71
	EEtelLineNotifyIncomingCallCancel                            // 72
	};

//
// WriteDeviceData
//
enum
	{
	EEtelCallSetFaxSettings = 73,                                // 73
	};

//
// NetworkControl
//
enum
	{
	EEtelGlobalKernelObjectHandle = 74,                          // 74
	};

//
// None
//
enum
	{
	EEtelPhoneInitialise = 75,                                   // 75
	EEtelPhoneInitialiseCancel,                                  // 76
	};

//
// NetworkControl
//
enum
	{
	EEtelServerSetPriorityClient = 77,                           // 77
	};

//
// NetworkControl NetworkServices
//
enum
	{
	EEtelCallAnswer = 78,                                        // 78
	EEtelCallAnswerCancel,                                       // 79
	EEtelCallDial,                                               // 80
	EEtelCallDialCancel,                                         // 81
	EEtelCallLoanDataPort,                                       // 82
	EEtelCallLoanDataPortCancel,                                 // 83
	EEtelCallRecoverDataPort                                     // 84
	};

//
// NetworkServices ReadUserData
//
enum
	{
	EEtelFaxRead = 85,                                           // 85
	};

//
// NetworkServices WriteUserData
//
enum
	{
	EEtelFaxWrite = 86,                                          // 86
	};

#endif


#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/sdk.h>
#include "djni.h"

//initialize native extension.Register methods and etc
void SpeechRecognition_Initialize();
void SpeechRecognition_Finalize();
void SpeechRecognition_RegisterNatives(JNIEnv* env) ;

//create speech recognition
void SpeechRecognition_Init();
void SpeechRecognition_Start();
void SpeechRecognition_Stop();
void SpeechRecognition_SetContinuous(bool continuous);
void SpeechRecognition_TTS(const char* text);
void SpeechRecognition_OnActivityResult(void *env, void* activity, int32_t request_code, int32_t result_code, void* result);

#endif
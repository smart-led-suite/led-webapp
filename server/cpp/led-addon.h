#ifndef led_addon_h
#define led_addon_h

// ####### includes #######
#include <node.h>
#include <v8.h>

// ####### usings #######
using namespace v8; // we need this a lot

// ###### functions #######
// accessible from node
void Init(Handle<Object> exports, Handle<Object> module);
void FadeBrightness(const v8::FunctionCallbackInfo<v8::Value>& args);
void SetBrightness(const v8::FunctionCallbackInfo<v8::Value>& args);
void SetFadeTime(const v8::FunctionCallbackInfo<v8::Value>& args);
void CancelFade(const v8::FunctionCallbackInfo<v8::Value>& args);
void StartRandom(const v8::FunctionCallbackInfo<v8::Value>& args);
void StopRandom(const v8::FunctionCallbackInfo<v8::Value>& args);

// internal
bool checkNumArgs(int numberOfArgs, const v8::FunctionCallbackInfo<v8::Value>& args);


#endif

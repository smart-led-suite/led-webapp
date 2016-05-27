#include "led-addon.h"

/*
* Checks if there are at least numArgs arguments that are all numerical
* values. Returns false if not.
*/
bool checkNumArgs(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  Isolate* isolate = args.GetIsolate();

  // check for number of arguments
  if(args.Length() < numberOfArgs) // two arguments: pin, targetBrightness
  {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return false;
  }

  // check each argument for type
  for(int i = 0; i < numberOfArgs) {
    if(!args[i]->IsNumber)  // both pin and targetBrightness
    {                                             // need to be integer values
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong type(s) of arguments")));
      return false;
    }
  }


}

// TODO implement FadeBrightness
void FadeBrightness(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  Isolate* isolate = args.GetIsolate();

  // do all required argument checks, return if failed
  if(!checkNumArgs(2, args) // we need 2 arguments (pin, targetBrightness), both numerical
  {
    return;
  }

  // extract parameter values
  int pin = args[0]->NumberValue();
  int targetBrightness = args[1]->NumberValue();

  // finally call fade Function
  LEDBlaster::fadeBrightness(pin, value);
}

// TODO implement SetBrightness
void SetBrightness(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  Isolate* isolate = args.GetIsolate();

  // do all required argument checks, return if failed
  if(!checkNumArgs(2, args) // we need 2 arguments (pin, targetBrightness), both numerical
  {
    return;
  }

  // extract parameter values
  int pin = args[0]->NumberValue();
  int targetBrightness = args[1]->NumberValue();

  // finally call set Function
  LEDBlaster::setBrightness(pin, value);
}

// TODO implement SetFadeTime
void SetFadeTime(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  Isolate* isolate = args.GetIsolate();

  // do all required argument checks, return if failed
  if(!checkNumArgs(1, args) // we need one number (the desired fadetime)
  {
    return;
  }

  // extract values
  int fadetime = args[0]->NumberValue();

  // call LED-Blaster Function
  LEDBlaster::setFadetime(fadetime);
}

// TODO implement CancelFade
void CancelFade(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  Isolate* isolate = args.GetIsolate();

  // do all required argument checks, return if failed
  if(!checkNumArgs(1, args) // we need one number (the pin)
  {
    return;
  }

  // extract values
  int pin = args[0]->NumberValue();

  // call LED-Blaster Function
  LEDBlaster::cancelFade(pin);
}

// TODO implement StartRandom
void StartRandom(const v8::FunctionCallbackInfo<v8::Value>& args);
{
  Isolate* isolate = args.GetIsolate();

  // do all required argument checks, return if failed
  if(!checkNumArgs(1, args) // we need one number (the pin)
  {
    return;
  }

  // extract values
  int pin = args[0]->NumberValue();

  // call LED-Blaster Function
  LEDBlaster::startRandom(pin);
}

// TODO implement StopRandom
void StopRandom(const v8::FunctionCallbackInfo<v8::Value>& args);
{
  Isolate* isolate = args.GetIsolate();

  // do all required argument checks, return if failed
  if(!checkNumArgs(1, args) // we need one number (the pin)
  {
    return;
  }

  // extract values
  int pin = args[0]->NumberValue();

  // call LED-Blaster Function
  LEDBlaster::stopRandom(pin);
}

void Init(Handle<Object> exports, Handle<Object> module)
{
  NODE_SET_METHOD(exports, "fade_brightness", FadeBrightness);
  NODE_SET_METHOD(exports, "set_brightness", SetBrightness);
  NODE_SET_METHOD(exports, "set_fadetime", SetFadeTime);
  NODE_SET_METHOD(exports, "cancel_fade", CancelFade);
  NODE_SET_METHOD(exports, "start_random", StartRandom);
  NODE_SET_METHOD(exports, "stop_random", StopRandom);
}

// register node module with node-gyp
NODE_MODULE(led-addon, Init)

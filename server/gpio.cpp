// addon.cc
#include <node.h>
#include <string>
#include <sstream>

// led-blaster includes
#include <iostream>
#include <cstdlib>
#include <pigpio.h> // TODO enable again!
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
#include <vector>

#include <string>
#include <pthread.h>
#include <stdint.h> //libary which includes uint8_t etc.
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>

#include "./led-blaster/led.hpp"
#include "./led-blaster/modes.hpp"
#include "./led-blaster/fade.hpp"
#include "./led-blaster/config.h"
#include "./led-blaster/file.hpp"
#include "./led-blaster/init.hpp"
#include "./led-blaster/led-blaster-pre.hpp"
#include "./led-blaster/fifo.hpp"
// led-blaster includes end


//#include <pigpio.h>

namespace demo {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

// This is the implementation of the "add" method
// Input arguments are passed using the
// const FunctionCallbackInfo<Value>& args struct
void Add(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 2) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
    }

    // Check the argument types
    if (!args[0]->IsString() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
    }

    // Perform the operation
    v8::String::Utf8Value s(args[0]);
    std::string pin = std::string(*s);
    int val = args[1]->NumberValue();

    std::stringstream str(std::string(""));
    str << "Setting pin " << pin << " to value of " << std::to_string(val);

    Local<String> returnVal = String::NewFromUtf8(isolate, str.str().c_str()); // isolate, "Setting Pin " << std::string(pin) << " to " << val);

    //gpioPWM(pin, val);

    // Set the return value (using the passed in
    // FunctionCallbackInfo<Value>&)
  args.GetReturnValue().Set(returnVal);
}

void Init(Local<Object> exports) {

    initialize();

    NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(addon, Init)

}  // namespace demo

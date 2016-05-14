// addon.cc
#include <node.h>
#include <string>
#include <sstream>
#include <pigpio.h>

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
    if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
    }

    // Perform the operation
    int pin = args[0]->NumberValue();
    int val = args[1]->NumberValue();

    std::stringstream str(std::string(""));
    str << "Setting pin " << std::to_string(pin) << " to value of " << std::to_string(val);

    Local<String> returnVal = String::NewFromUtf8(isolate, str.str().c_str()); // isolate, "Setting Pin " << std::string(pin) << " to " << val);

    gpioPWM(pin, val);

    // Set the return value (using the passed in
    // FunctionCallbackInfo<Value>&)
  args.GetReturnValue().Set(returnVal);
}

void Init(Local<Object> exports) {
    
    gpioTerminate();
    gpioInitialise();
    
    gpioSetMode(17, 1);
    
    gpioSetPWMfrequency(17, 200);
    gpioSetPWMrange(17, 1000);
    gpioPWM(17, 0);
    
    NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(addon, Init)

}  // namespace demo

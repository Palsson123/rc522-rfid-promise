#include <node.h>
#include <v8.h>
#include <unistd.h>
#include "rfid.h"
#include "spi.h"
#include "rc522.h"

#define DEFAULT_SPI_SPEED 5000L

uint8_t initRfidReader(void);

char statusRfidReader;
uint16_t CType=0;
uint8_t serialNumber[10];
uint8_t serialNumberLength=0;
uint8_t noTagFoundCount=0;
char rfidChipSerialNumber[23];
char rfidChipSerialNumberRecentlyDetected[23];
char *p;
int loopCounter;

using namespace v8;

void RunCallback(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate=Isolate::GetCurrent();
        HandleScope scope(isolate);

        Local<Function> callback = Local<Function>::Cast(args[0]);
        const unsigned argc = 1;
Local<Value> argv[argc] = {
                                Local<Value>::New(isolate,String::NewFromUtf8(isolate,&rfidChipSerialNumber[0]))
                        };
                        callback->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}

void Init(Handle<Object> exports, Handle<Object> module) {
        initRfidReader();
        NODE_SET_METHOD(module,"exports",RunCallback);
}

uint8_t initRfidReader(void) {

        //initGPIO();
        return 0;
}

NODE_MODULE(rc522, Init)

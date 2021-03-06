#include <node.h>
#include <v8.h>
#include <unistd.h>
#include <uv.h>
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
	const unsigned argc = 2;

	InitRc522();

	for (;; ) {
		statusRfidReader = find_tag(&CType);
		if (statusRfidReader == TAG_NOTAG) {

			// The status that no tag is found is sometimes set even when a tag is within reach of the tag reader
			// to prevent that the reset is performed the no tag event has to take place multiple times (ger: entrprellen)
			if (noTagFoundCount > 2) {
				// Sets the content of the array 'rfidChipSerialNumberRecentlyDetected' back to zero
				memset(&rfidChipSerialNumberRecentlyDetected[0], 0, sizeof(rfidChipSerialNumberRecentlyDetected));
				noTagFoundCount = 0;
			}
			else {
				noTagFoundCount++;
			}
			Local<Value> argv[argc] = {
				Local<Value>::New(isolate,Integer::New(isolate,1)),
				Local<Value>::New(isolate,String::NewFromUtf8(isolate,"undefined"))
			};
			callback->Call(isolate->GetCurrentContext()->Global(), argc, argv);
			break;

		} else if (statusRfidReader != TAG_OK && statusRfidReader != TAG_COLLISION) {
			continue;
		}

		if (select_tag_sn(serialNumber,&serialNumberLength) != TAG_OK) {
			continue;
		}
		// Is a successful detected, the counter will be set to zero
		noTagFoundCount = 0;

		p=rfidChipSerialNumber;
		for (loopCounter = 0; loopCounter < serialNumberLength; loopCounter++) {
			sprintf(p,"%02x", serialNumber[loopCounter]);
			p+=2;
		}

		// Only when the serial number of the currently detected tag differs from the
		// recently detected tag the callback will be executed with the serial number
		if(strcmp(rfidChipSerialNumberRecentlyDetected, rfidChipSerialNumber) != 0)
		{
			Local<Value> argv[argc] = {
				Local<Value>::New(isolate,Integer::New(isolate,0)),
				Local<Value>::New(isolate,String::NewFromUtf8(isolate,&rfidChipSerialNumber[0]))
			};
			callback->Call(isolate->GetCurrentContext()->Global(), argc, argv);
			break;
		}

		// Preserves the current detected serial number, so that it can be used
		// for future evaluations
		strcpy(rfidChipSerialNumberRecentlyDetected, rfidChipSerialNumber);

		*(p++)=0;
	}

}

void Init(Handle<Object> exports, Handle<Object> module) {
	initRfidReader();
	NODE_SET_METHOD(module,"exports",RunCallback);
}

uint8_t initRfidReader(void) {

	initGPIO();
	return 0;
}

NODE_MODULE(rc522, Init)

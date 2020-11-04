#include <Arduino.h>
#include "src-gen/ZowiSCT.h"
#include "src/ZowiCallbacks.h"
#include "src-gen/ZowiSCT.h"
#include "src-gen/sc_timer_service.h"
using namespace sc::timer;

#define MAX_TIMERS 4
TimerTask tasks[MAX_TIMERS];

ZowiSCT* zowi_sct = new ZowiSCT();
ZowiCallbacks* zowi_callbacks = new ZowiCallbacks();
TimerService* timer_sct = new TimerService(tasks, MAX_TIMERS);

void setup() {
	zowi_sct->zowi()->setOperationCallback(zowi_callbacks);
	zowi_sct->setTimerService(timer_sct);
	zowi_sct->enter();
}

long current_time = 0;
long last_cycle_time = 0;
void loop() {
	last_cycle_time = current_time;
	current_time = millis();
	timer_sct->proceed(current_time - last_cycle_time);
	zowi_sct->runCycle();
}

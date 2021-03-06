/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * This file is designed to be parsed during the build process
 *
 * JavaScript Pin Object Functions
 * ----------------------------------------------------------------------------
 */
#include "jswrap_pin.h"
#include "jswrap_io.h"
#include "jstimer.h"

/*JSON{
  "type" : "class",
  "class" : "Pin",
  "check" : "jsvIsPin(var)"
}
This is the built-in class for Pins, such as D0,D1,LED1, or BTN

You can call the methods on Pin, or you can use Wiring-style functions such as digitalWrite
 */

/*JSON{
  "type" : "constructor",
  "class" : "Pin",
  "name" : "Pin",
  "generate" : "jswrap_pin_constructor",
  "params" : [
    ["value","JsVar","A value to be converted to a pin. Can be a number, pin, or String."]
  ],
  "return" : ["JsVar","A Pin object"]
}
Creates a pin from the given argument (or returns undefined if no argument)
 */
JsVar *jswrap_pin_constructor(JsVar *val) {
  Pin pin = jshGetPinFromVar(val);
  if (!jshIsPinValid(pin)) return 0;
  return jsvNewFromPin(pin);
}

/*JSON{
  "type" : "method",
  "class" : "Pin",
  "name" : "read",
  "generate" : "jswrap_pin_read",
  "return" : ["bool","Whether pin is a logical 1 or 0"]
}
Returns the input state of the pin as a boolean.

 **Note:** if you didn't call `pinMode` beforehand then this function will also reset pin's state to `"input"`
 */
bool jswrap_pin_read(JsVar *parent) {
  Pin pin = jshGetPinFromVar(parent);
  return jshPinInput(pin);
}

/*JSON{
  "type" : "method",
  "class" : "Pin",
  "name" : "set",
  "generate" : "jswrap_pin_set"
}
Sets the output state of the pin to a 1

 **Note:** if you didn't call `pinMode` beforehand then this function will also reset pin's state to `"output"`
 */
void jswrap_pin_set(JsVar *parent) {
  Pin pin = jshGetPinFromVar(parent);
  jshPinOutput(pin, 1);
}

/*JSON{
  "type" : "method",
  "class" : "Pin",
  "name" : "reset",
  "generate" : "jswrap_pin_reset"
}
Sets the output state of the pin to a 0

 **Note:** if you didn't call `pinMode` beforehand then this function will also reset pin's state to `"output"`
 */
void jswrap_pin_reset(JsVar *parent) {
  Pin pin = jshGetPinFromVar(parent);
  jshPinOutput(pin, 0);
}

/*JSON{
  "type" : "method",
  "class" : "Pin",
  "name" : "write",
  "generate" : "jswrap_pin_write",
  "params" : [
    ["value","bool","Whether to set output high (true/1) or low (false/0)"]
  ]
}
Sets the output state of the pin to the parameter given

 **Note:** if you didn't call `pinMode` beforehand then this function will also reset pin's state to `"output"`
 */
void jswrap_pin_write(JsVar *parent, bool value) {
  Pin pin = jshGetPinFromVar(parent);
  jshPinOutput(pin, value);
}

/*JSON{
  "type" : "method",
  "class" : "Pin",
  "name" : "writeAtTime",
  "ifndef" : "SAVE_ON_FLASH",
  "generate" : "jswrap_pin_writeAtTime",
  "params" : [
    ["value","bool","Whether to set output high (true/1) or low (false/0)"],
    ["time","float","Time at which to write"]
  ]
}
Sets the output state of the pin to the parameter given at the specified time.

 **Note:** this **doesn't** change the mode of the pin to an output. To do that, you need to use `pin.write(0)` or `pinMode(pin, 'output')` first.
 */
void jswrap_pin_writeAtTime(JsVar *parent, bool value, JsVarFloat time) {
  Pin pin = jshGetPinFromVar(parent);
  JsSysTime sTime = jshGetTimeFromMilliseconds(time*1000);
  jstPinOutputAtTime(sTime, &pin, 1, value);
}


/*JSON{
  "type" : "method",
  "class" : "Pin",
  "name" : "getMode",
  "generate" : "jswrap_pin_getMode",
  "return" : ["JsVar","The pin mode, as a string"]
}
Return the current mode of the given pin. See `pinMode` for more information.
 */
JsVar *jswrap_pin_getMode(JsVar *parent) {
  return jswrap_io_getPinMode(jshGetPinFromVar(parent));  
}

/*JSON{
  "type" : "method",
  "class" : "Pin",
  "name" : "mode",
  "generate" : "jswrap_pin_mode",
  "params" : [
    ["mode","JsVar","The mode - a string that is either 'analog', 'input', 'input_pullup', 'input_pulldown', 'output', 'opendrain', 'af_output' or 'af_opendrain'. Do not include this argument if you want to revert to automatic pin mode setting."]
  ]
}
Set the mode of the given pin. See [`pinMode`](#l__global_pinMode) for more information on pin modes.
 */
void jswrap_pin_mode(JsVar *parent, JsVar *mode) {
  jswrap_io_pinMode(jshGetPinFromVar(parent), mode);  
}


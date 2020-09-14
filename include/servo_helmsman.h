// Copyright (c) 2020 Sarun Rattanasiri
// under the 3-Clause BSD License
// https://opensource.org/licenses/BSD-3-Clause

#ifndef __SERVO_HELMSMAN_H
#define __SERVO_HELMSMAN_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _servo_helmsman__config {
  uint8_t offset;
  void (*output)(bool state);
} ServoHelmsman_Config;

typedef struct _servo_helmsman__state {
  uint8_t desired_position;
  uint8_t procedure;
  uint8_t step;
} ServoHelmsman_State;

#define servo_helmsman__init(state)                                            \
  do {                                                                         \
    (state)->procedure = 0;                                                    \
    (state)->step = 0;                                                         \
  } while (0)

void servo_helmsman__cycle_sync(const ServoHelmsman_Config *config,
                                ServoHelmsman_State *state);

void servo_helmsman__step_poll(const ServoHelmsman_Config *config,
                               ServoHelmsman_State *state);

void servo_helmsman__set_position(const ServoHelmsman_Config *config,
                                  ServoHelmsman_State *state, uint8_t position);

#endif

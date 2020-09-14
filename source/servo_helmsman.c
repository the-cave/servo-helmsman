// Copyright (c) 2020 Sarun Rattanasiri
// under the 3-Clause BSD License
// https://opensource.org/licenses/BSD-3-Clause

#include "servo_helmsman.h"

#define PROCEDURE_UNINITIALIZE 0
#define PROCEDURE_SYNC_WAIT 1
#define PROCEDURE_OFFSETTING 2
#define PROCEDURE_POSITIONING 3
#define PROCEDURE_WAIT_FOR_CYCLE 4

void servo_helmsman__cycle_sync(const ServoHelmsman_Config *config,
                                ServoHelmsman_State *state) {
  if (state->procedure == PROCEDURE_UNINITIALIZE)
    return;
  state->procedure = PROCEDURE_SYNC_WAIT;
  config->output(false);
}

void servo_helmsman__step_poll(const ServoHelmsman_Config *config,
                               ServoHelmsman_State *state) {
  if (state->procedure == PROCEDURE_SYNC_WAIT) {
    state->procedure = PROCEDURE_OFFSETTING;
    state->step = 0;
    config->output(true);
  }
  if (state->procedure == PROCEDURE_OFFSETTING) {
    if (state->step < config->offset) {
      state->step++;
      return;
    }
    state->procedure = PROCEDURE_POSITIONING;
    state->step = 0;
  }
  if (state->procedure == PROCEDURE_POSITIONING) {
    if (state->step < state->desired_position) {
      state->step++;
      return;
    }
    state->procedure = PROCEDURE_WAIT_FOR_CYCLE;
    config->output(false);
  }
}

void servo_helmsman__set_position(const ServoHelmsman_Config *config,
                                  ServoHelmsman_State *state,
                                  uint8_t position) {
  if (state->procedure == PROCEDURE_UNINITIALIZE)
    state->procedure = PROCEDURE_WAIT_FOR_CYCLE;
  state->desired_position = position;
}

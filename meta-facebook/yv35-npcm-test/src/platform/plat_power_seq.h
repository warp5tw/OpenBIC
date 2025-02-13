/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PLAT_PWRSEQ_H
#define PLAT_PWRSEQ_H

#include "hal_gpio.h"
#include "plat_gpio.h"

#define DEFAULT_POWER_ON_SEQ 0x00
#define DEFAULT_POWER_OFF_SEQ 0x0B
#define NUMBER_OF_POWER_ON_SEQ 0x0A
#define NUMBER_OF_POWER_OFF_SEQ 0x00
#define CHKPWR_DELAY_MSEC 100
#define DEV_RESET_DELAY_USEC 100

#define CXL_POWER_OFF 0
#define CXL_POWER_ON 1

enum CONTROL_POWER_MODE {
	ENABLE_POWER_MODE = 0x00,
	DISABLE_POWER_MODE,
};

enum POWER_ON_STAGE {
	ASIC_POWER_ON_STAGE = 0x00,
	DIMM_POWER_ON_STAGE1,
	DIMM_POWER_ON_STAGE2,
	DIMM_POWER_ON_STAGE3,
	BOARD_POWER_ON_STAGE,
};

enum POWER_OFF_STAGE {
	DIMM_POWER_OFF_STAGE1 = 0x00,
	DIMM_POWER_OFF_STAGE2,
	DIMM_POWER_OFF_STAGE3,
	ASIC_POWER_OFF_STAGE1,
	ASIC_POWER_OFF_STAGE2,
	BOARD_POWER_OFF_STAGE,
};

enum CONTROL_POWER_SEQ_NUM_MAPPING {
	CONTROL_POWER_SEQ_01 = Reserve_GPIO00,
	CONTROL_POWER_SEQ_02 = Reserve_GPIO01,
	CONTROL_POWER_SEQ_03 = Reserve_GPIO02,
	CONTROL_POWER_SEQ_04 = Reserve_GPIO03,
	CONTROL_POWER_SEQ_05 = Reserve_GPIO04,
	CONTROL_POWER_SEQ_06 = Reserve_GPIO05,
	CONTROL_POWER_SEQ_07 = Reserve_GPIO06,
	CONTROL_POWER_SEQ_08 = Reserve_GPIO07,
	CONTROL_POWER_SEQ_09 = Reserve_GPIO10,
	CONTROL_POWER_SEQ_10 = Reserve_GPIO11,
};

enum CHECK_POWER_SEQ_NUM_MAPPING {
	CHECK_POWER_SEQ_01 = Reserve_GPIO12,
	CHECK_POWER_SEQ_02 = Reserve_GPIO13,
	CHECK_POWER_SEQ_03 = Reserve_GPIO14,
	CHECK_POWER_SEQ_04 = Reserve_GPIO15,
	CHECK_POWER_SEQ_05 = Reserve_GPIO16,
	CHECK_POWER_SEQ_06 = Reserve_GPIO17,
	CHECK_POWER_SEQ_07 = Reserve_GPIO20,
	CHECK_POWER_SEQ_08 = Reserve_GPIO21,
	CHECK_POWER_SEQ_09 = Reserve_GPIO22,
	CHECK_POWER_SEQ_10 = Reserve_GPIO23,
};

void set_MB_DC_status(uint8_t gpio_num);
void control_power_on_sequence();
void control_power_off_sequence();
void control_power_stage(uint8_t control_mode, uint8_t control_seq);
int check_power_stage(uint8_t check_mode, uint8_t check_seq, uint8_t stage);

#endif

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

#ifndef PLAT_HOOK_H
#define PLAT_HOOK_H
extern struct k_mutex wait_pm8702_mutex;

typedef struct _isl69254iraz_t_pre_arg_ {
	uint8_t vr_page;
} isl69254iraz_t_pre_arg;

typedef struct _vr_pre_proc_arg {
	/* vr page to set */
	uint8_t vr_page;
} vr_pre_proc_arg;

/**************************************************************************************************
 * INIT ARGS
**************************************************************************************************/
extern pm8702_dimm_init_arg pm8702_dimm_init_args[];
extern adc_npcm4xx_init_arg adc_npcm4xx_init_args[];
extern ina230_init_arg SQ5220x_init_args[];
extern ina233_init_arg ina233_init_args[];
extern vr_pre_proc_arg vr_page_select[];
/**************************************************************************************************
 *  PRE-HOOK/POST-HOOK ARGS
 **************************************************************************************************/
extern isl69254iraz_t_pre_arg isl69254iraz_t_pre_read_args[];

/**************************************************************************************************
 *  PRE-HOOK/POST-HOOK FUNC
 **************************************************************************************************/
bool pre_isl69254iraz_t_read(sensor_cfg *cfg, void *args);
bool pre_vr_read(sensor_cfg *cfg, void *args);
bool pre_pm8702_read(sensor_cfg *cfg, void *args);
bool post_pm8702_read(sensor_cfg *cfg, void *args, int *reading);
bool post_isl69254iraz_t_read(sensor_cfg *cfg, void *args, int *reading);

#endif

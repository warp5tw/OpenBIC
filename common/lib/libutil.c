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

#include "libutil.h"
#include <stdlib.h>
#include <string.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(libutil);

/*
 * @brief Construct an IPMI message buffer.
 *
 * @param seq_source The I2C bus ID.
 * @param netFn The net function.
 * @param cmd The command code.
 * @param source_inft the source bridge interface.
 * @param target_inft the target bridge interface.
 * @param data_len the amount of valid bytes in #data buffer.
 * @param data the data buffer.
 *
 * @retval The IPMI message buffer.
 */
ipmi_msg construct_ipmi_message(uint8_t seq_source, uint8_t netFn, uint8_t command,
				uint8_t source_inft, uint8_t target_inft, uint16_t data_len,
				uint8_t *data)
{
	ipmi_msg ipmi_message;
	ipmi_message.seq_source = seq_source;
	ipmi_message.netfn = netFn;
	ipmi_message.cmd = command;
	ipmi_message.InF_source = source_inft;
	ipmi_message.InF_target = target_inft;
	ipmi_message.data_len = data_len;
	if ((data_len != 0) && (data != NULL)) {
		memcpy(ipmi_message.data, data, data_len);
	}
	return ipmi_message;
}

/*
 * @brief Construct an I2C message buffer.
 *
 * @param bus_id The I2C bus ID.
 * @param address Target device address(7-bit address).
 * @param tx_len the data length that transmits to target device.
 * @param data the data buffer that ready to transmit to target.
 * @param rx_len the data length that receive the response from target device.
 *
 * @retval The I2C message buffer.
 */
I2C_MSG construct_i2c_message(uint8_t bus_id, uint8_t address, uint8_t tx_len, uint8_t *data,
			      uint8_t rx_len)
{
	I2C_MSG i2c_msg;
	i2c_msg.bus = bus_id;
	i2c_msg.target_addr = address;
	i2c_msg.tx_len = tx_len;
	memcpy(i2c_msg.data, data, tx_len);
	i2c_msg.rx_len = rx_len;
	return i2c_msg;
}

void reverse_array(uint8_t arr[], uint8_t size)
{
	uint8_t i;
	for (i = 0; i < size / 2; i++) {
		uint8_t temp = arr[i];
		arr[i] = arr[size - 1 - i];
		arr[size - 1 - i] = temp;
	}
}

int ascii_to_val(uint8_t ascii_byte)
{
	if (ascii_byte >= 0x30 && ascii_byte < 0x3A)
		return ascii_byte - 0x30;
	else if (ascii_byte >= 0x41 && ascii_byte < 0x47)
		return ascii_byte - 0x41 + 10;
	else
		return -1;
}

uint32_t uint32_t_byte_reverse(uint32_t data)
{
	uint32_t re_data;

	re_data = (((data & 0xaaaaaaaa) >> 1) | ((data & 0x55555555) << 1));
	re_data = (((re_data & 0xcccccccc) >> 2) | ((re_data & 0x33333333) << 2));
	re_data = (((re_data & 0xf0f0f0f0) >> 4) | ((re_data & 0x0f0f0f0f) << 4));
	re_data = (((re_data & 0xff00ff00) >> 8) | ((re_data & 0x00ff00ff) << 8));

	return ((re_data >> 16) | ((re_data << 16) & 0xffffffff));
}

void convert_uint32_t_to_uint8_t_pointer(uint32_t data_32, uint8_t *data_8, uint8_t len,
					 uint8_t endian)
{
	CHECK_NULL_ARG(data_8);
	int i;

	if (len != 4) {
		LOG_ERR("Unexpected length %d", len);
		return;
	}

	for (i = 0; i < len; ++i) {
		if (endian == SMALL_ENDIAN) {
			data_8[i] = (data_32 >> (8 * i)) & 0xFF;
		} else {
			data_8[i] = (data_32 >> (24 - 8 * i)) & 0xFF;
		}
	}
}

void convert_uint8_t_pointer_to_uint32_t(uint32_t *data_32, uint8_t *data_8, uint8_t len,
					 uint8_t endian)
{
	CHECK_NULL_ARG(data_32);
	CHECK_NULL_ARG(data_8);

	if (len != 4) {
		LOG_ERR("Unexpected length %d", len);
		return;
	}

	if (endian == SMALL_ENDIAN) {
		*data_32 = (data_8[3] << 24) + (data_8[2] << 16) + (data_8[1] << 8) + data_8[0];
	} else {
		*data_32 = (data_8[0] << 24) + (data_8[1] << 16) + (data_8[2] << 8) + data_8[3];
	}
}

double power(double x, int y)
{
	double result = 1;

	if (y < 0) {
		y = -y;
		while (y--)
			result /= x;
	} else {
		while (y--)
			result *= x;
	}

	return result;
}

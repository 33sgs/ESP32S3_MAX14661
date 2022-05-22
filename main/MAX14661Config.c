#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/spi_common.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_log.h"

#define PIN_NUM_MOSI 18
#define PIN_NUM_MISO 2
#define PIN_NUM_CLK 12
#define CS_GPIO_1 10

#define SPI_HOST SPI2_HOST

static const char *TAG = "ESP32S3";

void app_main(void)
{
	esp_err_t ret;
	spi_host_device_t host = SPI2_HOST;
	spi_device_handle_t handle = NULL;

	gpio_set_direction(CS_GPIO_1, GPIO_MODE_OUTPUT);
	gpio_set_level(CS_GPIO_1, 1);

	uint32_t data = SPI_SWAP_DATA_TX(0x00, 32);

	spi_bus_config_t buscfg = {
		.miso_io_num = PIN_NUM_MISO,
		.mosi_io_num = PIN_NUM_MOSI,
		.sclk_io_num = PIN_NUM_CLK,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1,
		.max_transfer_sz = 32,
		.flags = 0,

	};

	spi_device_interface_config_t devcfg = {
		.command_bits = 0,
		.address_bits = 0,
		.dummy_bits = 0,
		.spics_io_num = -1,
		.clock_speed_hz = SPI_MASTER_FREQ_8M/10,
		.mode = 3,
		.duty_cycle_pos = 128,
		.cs_ena_pretrans = 0,
		.cs_ena_posttrans = 0,
		.input_delay_ns = 0,
		.flags = 0,
		.queue_size = 10,
	};

	vTaskDelay(1000 / portTICK_PERIOD_MS);

	spi_transaction_t t;
	memset(&t, 0, sizeof(t));
	t.length = 32;
	t.tx_buffer = &data;
	t.rxlength = 0;
	t.rx_buffer = NULL;
	t.flags = 0;

	ret = spi_bus_initialize(SPI_HOST, &buscfg, SPI_DMA_CH_AUTO);
	ESP_ERROR_CHECK(ret);

	ESP_LOGI(TAG, "Added SPI device...");
	ESP_ERROR_CHECK(ret);

	data = SPI_SWAP_DATA_TX(0xFFFFFFFF, 32);
	gpio_set_level(CS_GPIO_1, 0);
	ret = spi_device_polling_transmit(handle, &t);
	ESP_ERROR_CHECK(ret);
	ESP_LOGI(TAG, "Transmitted...");
	gpio_set_level(CS_GPIO_1, 1);

	while(1){
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		ESP_LOGI(TAG, "waiting...");
	}
}


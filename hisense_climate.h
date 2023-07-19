#include "esphome.h"
#include "esphome/components/sensor/sensor.h"
#include "hisense_packet.h"

static const char *const TAG = "hisense_ac.climate";

class HisenseAC : public PollingComponent, public Climate, public UARTDevice
{
public:
    HisenseAC(UARTComponent *parent) : PollingComponent(2000),
                                       UARTDevice(parent),
                                       compressor_frequency(),
                                       compressor_frequency_setting(),
                                       compressor_frequency_send(),
                                       outdoor_temperature(),
                                       outdoor_condenser_temperature(),
                                       compressor_exhaust_temperature(),
                                       target_exhaust_temperature(),
                                       indoor_pipe_temperature(),
                                       indoor_humidity_setting(),
                                       indoor_humidity_status(),
                                       UART_crc_errors() {}

    void send_custom_command()
    {
        ESP_LOGD(TAG, "Custom command received from outside.");
    }
    
    void setup() override
    {
        compressor_frequency.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        compressor_frequency_setting.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        compressor_frequency_send.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        outdoor_temperature.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        outdoor_condenser_temperature.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        compressor_exhaust_temperature.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        target_exhaust_temperature.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        indoor_pipe_temperature.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        indoor_humidity_setting.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        indoor_humidity_status.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        UART_crc_errors.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
    }

    void update() override
    {
        uint8_t req_stat[] = {
            0xF4, 0xF5, 0x00, 0x40,
            0x0C, 0x00, 0x00, 0x01,
            0x01, 0xFE, 0x01, 0x00,
            0x00, 0x66, 0x00, 0x00,
            0x00, 0x01, 0xB3, 0xF4,
            0xFB};

        write_array(req_stat, 21);
        flush();

        if (read_response())
        {

            ESP_LOGD(
                TAG,
                "compf: %d compf_set: %d compf_snd: %d\n",
                ((Device_Status*)int_buf)compressor_frequency,
                ((Device_Status*)int_buf)compressor_frequency_setting,
                ((Device_Status*)int_buf)compressor_frequency_send);

            ESP_LOGD(
                TAG,
                "out_temp: %d out_cond_temp: %d comp_exh_temp: %d comp_exh_temp_tgt: %d\n",
                ((Device_Status*)int_buf)outdoor_temperature,
                ((Device_Status*)int_buf)outdoor_condenser_temperature,
                ((Device_Status*)int_buf)compressor_exhaust_temperature,
                ((Device_Status*)int_buf)target_exhaust_temperature);

            ESP_LOGD(
                TAG,
                "indoor_pipe_temp %d\n",
                ((Device_Status*)int_buf)indoor_pipe_temperature);

            ESP_LOGD(
                TAG,
                "indor_humid_set: %d indoor_humid: %d\n",
                ((Device_Status*)int_buf)indoor_humidity_setting,
                ((Device_Status*)int_buf)indoor_humidity_status);

            target_temperature = ((Device_Status*)int_buf)->indoor_temperature_setting;
            current_temperature = ((Device_Status*)int_buf)->indoor_temperature_status;

            // See if the system is actively running
            bool comp_running = false;
            if (((Device_Status*)int_buf)->compressor_frequency > 0)
            {
                comp_running = true;
            }

            if (((Device_Status*)int_buf)->left_right && ((Device_Status*)int_buf)->up_down)
                swing_mode = climate::CLIMATE_SWING_BOTH;
            else if (((Device_Status*)int_buf)->left_right)
                swing_mode = climate::CLIMATE_SWING_HORIZONTAL;
            else if (((Device_Status*)int_buf)->up_down)
                swing_mode = climate::CLIMATE_SWING_VERTICAL;
            else
                swing_mode = climate::CLIMATE_SWING_OFF;

            if (((Device_Status*)int_buf)->run_status == 0)
            {
                mode = CLIMATE_MODE_OFF;
                action = CLIMATE_ACTION_OFF;
            }
            else if (((Device_Status*)int_buf)->mode_status == 0)
            {
                mode = CLIMATE_MODE_FAN_ONLY;
                action = CLIMATE_ACTION_FAN;
            }
            else if (((Device_Status*)int_buf)->mode_status == 1)
            {
                mode = climate::CLIMATE_MODE_HEAT;
                if (comp_running)
                {
                    action = CLIMATE_ACTION_HEATING;
                }
                else
                {
                    action = CLIMATE_ACTION_IDLE;
                }
            }
            else if (((Device_Status*)int_buf)->mode_status == 2)
            {
                mode = climate::CLIMATE_MODE_COOL;
                if (comp_running)
                {
                    action = CLIMATE_ACTION_COOLING;
                }
                else
                {
                    action = CLIMATE_ACTION_IDLE;
                }
            }
            else if (((Device_Status*)int_buf)->mode_status == 3)
            {
                mode = climate::CLIMATE_MODE_DRY;
                if (comp_running)
                {
                    action = CLIMATE_ACTION_DRYING;
                }
                else
                {
                    action = CLIMATE_ACTION_IDLE;
                }
            }

            if (((Device_Status*)int_buf)->wind_status == 18 || ((Device_Status*)int_buf)->wind_status == 16)
            {
                fan_mode = climate::CLIMATE_FAN_HIGH;
            }
/* 			else if (((Device_Status*)int_buf)->wind_status == 16)
            {
                fan_mode = climate::CLIMATE_FAN_HIGH;
            } */
            else if (((Device_Status*)int_buf)->wind_status == 14 || ((Device_Status*)int_buf)->wind_status == 12)
            {
                fan_mode = climate::CLIMATE_FAN_MEDIUM;
            }
/* 			else if (((Device_Status*)int_buf)->wind_status == 12)
            {
                fan_mode = climate::CLIMATE_FAN_LOW;
            } */
            else if (((Device_Status*)int_buf)->wind_status == 10)
            {
                fan_mode = climate::CLIMATE_FAN_LOW;
            }
            else if (((Device_Status*)int_buf)->wind_status == 2)
            {
                fan_mode = climate::CLIMATE_FAN_QUIET;
            }
            else if (((Device_Status*)int_buf)->wind_status == 1)
            {
                fan_mode = climate::CLIMATE_FAN_AUTO;
            }

            this->publish_state();

            // Update sensors
            set_sensor(compressor_frequency, ((Device_Status*)int_buf)->compressor_frequency);
            set_sensor(compressor_frequency_setting, ((Device_Status*)int_buf)->compressor_frequency_setting);
            set_sensor(compressor_frequency_send, ((Device_Status*)int_buf)->compressor_frequency_send);
            set_sensor(outdoor_temperature, ((Device_Status*)int_buf)->outdoor_temperature);
            set_sensor(outdoor_condenser_temperature, ((Device_Status*)int_buf)->outdoor_condenser_temperature);
            set_sensor(compressor_exhaust_temperature, ((Device_Status*)int_buf)->compressor_exhaust_temperature);
            set_sensor(target_exhaust_temperature, ((Device_Status*)int_buf)->target_exhaust_temperature);
            set_sensor(indoor_pipe_temperature, ((Device_Status*)int_buf)->indoor_pipe_temperature);
            set_sensor(indoor_humidity_setting, ((Device_Status*)int_buf)->indoor_humidity_setting);
            set_sensor(indoor_humidity_status, ((Device_Status*)int_buf)->indoor_humidity_status);
            set_sensor(UART_crc_errors, get_uart_crc_errors());

            // Save target temperature since it gets messed up by the mode switch command
            if ((this->mode == CLIMATE_MODE_COOL || this->mode == CLIMATE_MODE_HEAT) && target_temperature > 0)
            {
                tgt_temp = target_temperature;
            }
        }
    }

    void control(const ClimateCall &call) override
    {
        const uint8_t resp_size = 83;
        uint8_t response_buf[resp_size];
        if (call.get_mode().has_value())
        {
            // Save target temperature since it gets messed up by the mode switch command
            if ((this->mode == CLIMATE_MODE_COOL || this->mode == CLIMATE_MODE_HEAT) && target_temperature > 0)
            {
                tgt_temp = target_temperature;
            }

            // User requested mode change
            ClimateMode md = *call.get_mode();

            if (md != climate::CLIMATE_MODE_OFF && this->mode == climate::CLIMATE_MODE_OFF)
            {
                send_command(on, sizeof(on));
            }

            switch (md)
            {
            case climate::CLIMATE_MODE_OFF:
                send_command(off, sizeof(off));
                break;
            case climate::CLIMATE_MODE_COOL:
                send_command(mode_cool, sizeof(mode_cool));
                set_temp(tgt_temp);
                break;
            case climate::CLIMATE_MODE_HEAT:
                send_command(mode_heat, sizeof(mode_heat));
                set_temp(tgt_temp);
                break;
            case climate::CLIMATE_MODE_FAN_ONLY:
                send_command(mode_fan, sizeof(mode_fan));
                break;
            case climate::CLIMATE_MODE_DRY:
                send_command(mode_dry, sizeof(mode_dry));
                break;
            default:
                break;
            }

            // Publish updated state
            this->mode = md;
            this->publish_state();
        }

        if (call.get_target_temperature().has_value())
        {
            // User requested target temperature change
            float temp = *call.get_target_temperature();

            set_temp(temp);

            // Send target temp to climate
            target_temperature = temp;
            this->publish_state();
        }

        if (call.get_fan_mode().has_value())
        {
            ClimateFanMode fm = *call.get_fan_mode();
            switch (fm)
            {
            case climate::CLIMATE_FAN_AUTO:
                send_command(speed_auto, sizeof(speed_auto));
                break;
            case climate::CLIMATE_FAN_LOW:
                send_command(speed_low, sizeof(speed_low));
                break;
            case climate::CLIMATE_FAN_MEDIUM:
                send_command(speed_med, sizeof(speed_med));
                break;
            case climate::CLIMATE_FAN_HIGH:
                send_command(speed_max, sizeof(speed_max));
                break;
            case climate::CLIMATE_FAN_QUIET:
                send_command(speed_mute, sizeof(speed_mute));
                break;
            default:
                break;
            }
            fan_mode = fm;
            this->publish_state();
        }

        if (call.get_swing_mode().has_value())
        {
            uint32_t start_time = millis();
            ClimateSwingMode sm = *call.get_swing_mode();

            if (sm == climate::CLIMATE_SWING_OFF)
            {
                if (climate::CLIMATE_SWING_BOTH == swing_mode)
                {
                    send_command(vert_dir, sizeof(vert_dir));
                    bzzz(500);
                    send_command(hor_dir, sizeof(hor_dir));
                }
                else if (climate::CLIMATE_SWING_VERTICAL == swing_mode)
                {
                    send_command(vert_dir, sizeof(vert_dir));
                }
                else if (climate::CLIMATE_SWING_HORIZONTAL == swing_mode)
                {
                    send_command(hor_dir, sizeof(hor_dir));
                }
            }
            else if (sm == climate::CLIMATE_SWING_BOTH)
            {
                if (climate::CLIMATE_SWING_OFF == swing_mode)
                {
                    send_command(vert_swing, sizeof(vert_swing));
                    bzzz(500);
                    send_command(hor_swing, sizeof(hor_swing));
                }
                else if (climate::CLIMATE_SWING_VERTICAL == swing_mode)
                {
                    send_command(hor_swing, sizeof(hor_swing));
                }
                else if (climate::CLIMATE_SWING_HORIZONTAL == swing_mode)
                {
                    send_command(vert_swing, sizeof(vert_swing));
                }
            }
            else if (sm == climate::CLIMATE_SWING_VERTICAL)
            {
                if (climate::CLIMATE_SWING_OFF == swing_mode)
                {
                    send_command(vert_swing, sizeof(vert_swing));
                }
                else if (climate::CLIMATE_SWING_BOTH == swing_mode)
                {
                    send_command(hor_dir, sizeof(hor_dir));
                }
                else if (climate::CLIMATE_SWING_HORIZONTAL == swing_mode)
                {
                    send_command(hor_dir, sizeof(hor_dir));
                    bzzz(500);
                    send_command(vert_swing, sizeof(vert_swing));
                }
            }
            else if (sm == climate::CLIMATE_SWING_HORIZONTAL)
            {
                if (climate::CLIMATE_SWING_OFF == swing_mode)
                {
                    send_command(hor_swing, sizeof(hor_swing));
                }
                else if (climate::CLIMATE_SWING_BOTH == swing_mode)
                {
                    send_command(vert_dir, sizeof(vert_dir));
                }
                else if (climate::CLIMATE_SWING_VERTICAL == swing_mode)
                {
                    send_command(vert_dir, sizeof(vert_dir));
                    bzzz(500);
                    send_command(hor_swing, sizeof(hor_swing));
                }
            }

            swing_mode = sm;
            this->publish_state();
        }

        if (call.get_preset().has_value())
        {
            ClimatePreset pre = *call.get_preset();
            switch (pre)
            {
            case climate::CLIMATE_PRESET_NONE:
                send_command(turbo_off, sizeof(turbo_off));
                send_command(energysave_off, sizeof(energysave_off));
                break;
            case climate::CLIMATE_PRESET_BOOST:
                send_command(turbo_on, sizeof(turbo_on));
                break;
            case climate::CLIMATE_PRESET_ECO:
                send_command(energysave_on, sizeof(energysave_on));
                break;
            default:
                break;
            }

            preset = pre;
            this->publish_state();
        }
    }

    ClimateTraits traits() override
    {
        // The capabilities of the climate device
        auto traits = climate::ClimateTraits();
        traits.set_supports_current_temperature(true);
        traits.set_visual_min_temperature(16);
        traits.set_visual_max_temperature(30);
        traits.set_visual_temperature_step(1);
        traits.set_supported_modes({
            climate::CLIMATE_MODE_OFF,
            climate::CLIMATE_MODE_COOL,
            climate::CLIMATE_MODE_HEAT,
            climate::CLIMATE_MODE_FAN_ONLY,
            climate::CLIMATE_MODE_DRY,
        });
        traits.set_supported_swing_modes({climate::CLIMATE_SWING_OFF,
                                          climate::CLIMATE_SWING_BOTH,
                                          climate::CLIMATE_SWING_VERTICAL,
                                          climate::CLIMATE_SWING_HORIZONTAL});
        traits.set_supported_fan_modes({
            climate::CLIMATE_FAN_AUTO,
            climate::CLIMATE_FAN_LOW,
            climate::CLIMATE_FAN_MEDIUM,
            climate::CLIMATE_FAN_HIGH,
            climate::CLIMATE_FAN_QUIET,
        });
        traits.set_supported_presets({climate::CLIMATE_PRESET_NONE,
                                      climate::CLIMATE_PRESET_BOOST,
                                      climate::CLIMATE_PRESET_ECO});
        traits.set_supports_action(true);
        return traits;
    }

    sensor::Sensor compressor_frequency;
    sensor::Sensor compressor_frequency_setting;
    sensor::Sensor compressor_frequency_send;
    sensor::Sensor outdoor_temperature;
    sensor::Sensor outdoor_condenser_temperature;
    sensor::Sensor compressor_exhaust_temperature;
    sensor::Sensor target_exhaust_temperature;
    sensor::Sensor indoor_pipe_temperature;
    sensor::Sensor indoor_humidity_setting;
    sensor::Sensor indoor_humidity_status;
    sensor::Sensor UART_crc_errors;

private:
    float heat_tgt_temp = 16;
    float cool_tgt_temp = 26;
    float tgt_temp = 25;

    bool read_response()
    {
        int size = 0;
        uint32_t start_time = millis();
        while (millis() - start_time < 250)
            ;

        size = available();
        bool read_success = read_array(int_buf, size);

        // Exit if we timed out
        if (!read_success)
        {
            return false;
        }

        ESP_LOGD(
            TAG,
            "Received %d bytes.",
            size);

        uint16_t checksum = 0;
        for (int i = 2; i < size - 4; i++)
        {
            checksum += int_buf[i];
        }
        uint16_t rxd_checksum = int_buf[size - 4];
        rxd_checksum = rxd_checksum << 8;
        rxd_checksum |= int_buf[size - 3];
        if (rxd_checksum != checksum)
        {
            ESP_LOGD(
                TAG,
                "CRC check failed. Computed: %d Received: %d Bytes Not Read: %d\n",
                checksum,
                rxd_checksum,
                available());
            set_uart_crc_errors();
            read_success = false;
        }

        return read_success;
    }

    void send_command(uint8_t cmd[], size_t sz)
    {
        write_array(cmd, sz);
        flush();
        read_response();
    }

    void set_sensor(Sensor &sensor, float value)
    {
        if (!sensor.has_state() || sensor.get_raw_state() != value)
            sensor.publish_state(value);
    }
    
    uint8_t get_uart_crc_errors() const
    {
        return uart_crc_errors;
    }
    
    void set_uart_crc_errors()
    {
        if (uart_crc_errors < 100)
            ++uart_crc_errors;
    }
    
    void bzzz(uint32_t how_long)
    {
        uint32_t start_time = millis();
        while (millis() - start_time < how_long)
                        ;
    }

    void set_temp(float temp)
    {
		uint8_t temp_c = roundf(temp);
        switch (temp_c)
        {
        case 16:
            send_command(temp_16_C, sizeof(temp_16_C));
            break;
        case 17:
            send_command(temp_17_C, sizeof(temp_17_C));
            break;
        case 18:
            send_command(temp_18_C, sizeof(temp_18_C));
            break;
        case 19:
            send_command(temp_19_C, sizeof(temp_19_C));
            break;
        case 20:
            send_command(temp_20_C, sizeof(temp_20_C));
            break;
        case 21:
            send_command(temp_21_C, sizeof(temp_21_C));
            break;
        case 22:
            send_command(temp_22_C, sizeof(temp_22_C));
            break;
        case 23:
            send_command(temp_23_C, sizeof(temp_23_C));
            break;
        case 24:
            send_command(temp_24_C, sizeof(temp_24_C));
            break;
        case 25:
            send_command(temp_25_C, sizeof(temp_25_C));
            break;
        case 26:
            send_command(temp_26_C, sizeof(temp_26_C));
            break;
        case 27:
            send_command(temp_27_C, sizeof(temp_27_C));
            break;
        case 28:
            send_command(temp_28_C, sizeof(temp_28_C));
            break;
        case 29:
            send_command(temp_29_C, sizeof(temp_29_C));
            break;
        case 30:
            send_command(temp_30_C, sizeof(temp_30_C));
            break;
        case 31:
            send_command(temp_31_C, sizeof(temp_31_C));
            break;
        case 32:
            send_command(temp_32_C, sizeof(temp_32_C));
            break;
        default:
            break;
        }
    }

    uint8_t int_buf[256];
    uint8_t uart_crc_errors = 0;
};

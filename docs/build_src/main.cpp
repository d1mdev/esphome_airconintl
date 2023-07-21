// Auto generated code by esphome
// ========== AUTO GENERATED INCLUDE BLOCK BEGIN ===========
#include "esphome.h"
using namespace esphome;
using std::isnan;
using std::min;
using std::max;
using namespace time;
using namespace climate;
using namespace button;
logger::Logger *logger_logger;
web_server_base::WebServerBase *web_server_base_webserverbase;
captive_portal::CaptivePortal *captive_portal_captiveportal;
wifi::WiFiComponent *wifi_wificomponent;
mdns::MDNSComponent *mdns_mdnscomponent;
ota::OTAComponent *ota_otacomponent;
web_server::WebServer *web_server_webserver;
const uint8_t ESPHOME_WEBSERVER_INDEX_HTML[174] PROGMEM = {60, 33, 68, 79, 67, 84, 89, 80, 69, 32, 104, 116, 109, 108, 62, 60, 104, 116, 109, 108, 62, 60, 104, 101, 97, 100, 62, 60, 109, 101, 116, 97, 32, 99, 104, 97, 114, 115, 101, 116, 61, 85, 84, 70, 45, 56, 62, 60, 108, 105, 110, 107, 32, 114, 101, 108, 61, 105, 99, 111, 110, 32, 104, 114, 101, 102, 61, 100, 97, 116, 97, 58, 62, 60, 47, 104, 101, 97, 100, 62, 60, 98, 111, 100, 121, 62, 60, 101, 115, 112, 45, 97, 112, 112, 62, 60, 47, 101, 115, 112, 45, 97, 112, 112, 62, 60, 115, 99, 114, 105, 112, 116, 32, 115, 114, 99, 61, 34, 104, 116, 116, 112, 115, 58, 47, 47, 111, 105, 46, 101, 115, 112, 104, 111, 109, 101, 46, 105, 111, 47, 118, 50, 47, 119, 119, 119, 46, 106, 115, 34, 62, 60, 47, 115, 99, 114, 105, 112, 116, 62, 60, 47, 98, 111, 100, 121, 62, 60, 47, 104, 116, 109, 108, 62};
const size_t ESPHOME_WEBSERVER_INDEX_HTML_SIZE = 174;
api::APIServer *api_apiserver;
using namespace api;
using namespace sensor;
using namespace json;
preferences::IntervalSyncer *preferences_intervalsyncer;
sntp::SNTPComponent *time_now;
using namespace uart;
uart::ESP32ArduinoUARTComponent *uart_bus_1;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_2;
restart::RestartButton *restart_restartbutton;
shutdown::ShutdownButton *shutdown_shutdownbutton;
safe_mode::SafeModeButton *safe_mode_safemodebutton;
template_::TemplateButton *template__templatebutton;
button::ButtonPressTrigger *button_buttonpresstrigger;
Automation<> *automation;
LambdaAction<> *lambdaaction;
LambdaAction<> *lambdaaction_2;
globals::GlobalsComponent<Sensor*> *compressor_frequency;
globals::GlobalsComponent<Sensor*> *compressor_frequency_setting;
globals::GlobalsComponent<Sensor*> *compressor_frequency_send;
globals::GlobalsComponent<Sensor*> *outdoor_temperature;
globals::GlobalsComponent<Sensor*> *outdoor_condenser_temperature;
globals::GlobalsComponent<Sensor*> *compressor_exhaust_temperature;
globals::GlobalsComponent<Sensor*> *target_exhaust_temperature;
globals::GlobalsComponent<Sensor*> *indoor_pipe_temperature;
globals::GlobalsComponent<Sensor*> *indoor_humidity_setting;
globals::GlobalsComponent<Sensor*> *indoor_humidity_status;
globals::GlobalsComponent<Sensor*> *UART_crc_errors;
climate::Climate *climate_climate;
#define yield() esphome::yield()
#define millis() esphome::millis()
#define micros() esphome::micros()
#define delay(x) esphome::delay(x)
#define delayMicroseconds(x) esphome::delayMicroseconds(x)
#include "hisense_climate.h"
// ========== AUTO GENERATED INCLUDE BLOCK END ==========="

void setup() {
  // ========== AUTO GENERATED CODE BEGIN ===========
  // async_tcp:
  //   {}
  // esphome:
  //   name: test-devkit-v1
  //   friendly_name: test-devkit-v1
  //   comment: TEST - HVAC
  //   includes:
  //   - hisense_climate.h
  //   build_path: .esphome/build/test-devkit-v1
  //   platformio_options: {}
  //   libraries: []
  //   name_add_mac_suffix: false
  //   min_version: 2023.6.5
  App.pre_setup("test-devkit-v1", "test-devkit-v1", "TEST - HVAC", __DATE__ ", " __TIME__, false);
  // time:
  // climate:
  // button:
  // logger:
  //   hardware_uart: UART0
  //   baud_rate: 0
  //   level: DEBUG
  //   id: logger_logger
  //   tx_buffer_size: 512
  //   deassert_rts_dtr: false
  //   logs: {}
  logger_logger = new logger::Logger(0, 512);
  logger_logger->set_uart_selection(logger::UART_SELECTION_UART0);
  logger_logger->pre_setup();
  logger_logger->set_component_source("logger");
  App.register_component(logger_logger);
  // web_server_base:
  //   id: web_server_base_webserverbase
  web_server_base_webserverbase = new web_server_base::WebServerBase();
  web_server_base_webserverbase->set_component_source("web_server_base");
  App.register_component(web_server_base_webserverbase);
  // captive_portal:
  //   id: captive_portal_captiveportal
  //   web_server_base_id: web_server_base_webserverbase
  captive_portal_captiveportal = new captive_portal::CaptivePortal(web_server_base_webserverbase);
  captive_portal_captiveportal->set_component_source("captive_portal");
  App.register_component(captive_portal_captiveportal);
  // wifi:
  //   ap:
  //     ssid: Test-Devkit-V1 Fallback Hotspot
  //     password: uzBKkDuQ8mTe
  //     id: wifi_wifiap
  //     ap_timeout: 1min
  //   id: wifi_wificomponent
  //   domain: .local
  //   reboot_timeout: 15min
  //   power_save_mode: LIGHT
  //   fast_connect: false
  //   passive_scan: false
  //   enable_on_boot: true
  //   networks:
  //   - ssid: !secret 'wifi_ssid'
  //     password: !secret 'wifi_password'
  //     id: wifi_wifiap_2
  //     priority: 0.0
  //   use_address: test-devkit-v1.local
  wifi_wificomponent = new wifi::WiFiComponent();
  wifi_wificomponent->set_use_address("test-devkit-v1.local");
  {
  wifi::WiFiAP wifi_wifiap_2 = wifi::WiFiAP();
  wifi_wifiap_2.set_ssid("cell");
  wifi_wifiap_2.set_password("0503050305030");
  wifi_wifiap_2.set_priority(0.0f);
  wifi_wificomponent->add_sta(wifi_wifiap_2);
  }
  {
  wifi::WiFiAP wifi_wifiap = wifi::WiFiAP();
  wifi_wifiap.set_ssid("Test-Devkit-V1 Fallback Hotspot");
  wifi_wifiap.set_password("uzBKkDuQ8mTe");
  wifi_wificomponent->set_ap(wifi_wifiap);
  }
  wifi_wificomponent->set_ap_timeout(60000);
  wifi_wificomponent->set_reboot_timeout(900000);
  wifi_wificomponent->set_power_save_mode(wifi::WIFI_POWER_SAVE_LIGHT);
  wifi_wificomponent->set_fast_connect(false);
  wifi_wificomponent->set_passive_scan(false);
  wifi_wificomponent->set_enable_on_boot(true);
  wifi_wificomponent->set_component_source("wifi");
  App.register_component(wifi_wificomponent);
  // mdns:
  //   id: mdns_mdnscomponent
  //   disabled: false
  //   services: []
  mdns_mdnscomponent = new mdns::MDNSComponent();
  mdns_mdnscomponent->set_component_source("mdns");
  App.register_component(mdns_mdnscomponent);
  // ota:
  //   password: 13f18b24a3dfbad6ff78112f9a767f1b
  //   id: ota_otacomponent
  //   safe_mode: true
  //   port: 3232
  //   reboot_timeout: 5min
  //   num_attempts: 10
  ota_otacomponent = new ota::OTAComponent();
  ota_otacomponent->set_port(3232);
  ota_otacomponent->set_auth_password("13f18b24a3dfbad6ff78112f9a767f1b");
  ota_otacomponent->set_component_source("ota");
  App.register_component(ota_otacomponent);
  if (ota_otacomponent->should_enter_safe_mode(10, 300000)) return;
  // web_server:
  //   port: 80
  //   version: 2
  //   include_internal: true
  //   ota: false
  //   id: web_server_webserver
  //   web_server_base_id: web_server_base_webserverbase
  //   log: true
  //   css_url: ''
  //   js_url: https:oi.esphome.io/v2/www.js
  web_server_webserver = new web_server::WebServer(web_server_base_webserverbase);
  web_server_webserver->set_component_source("web_server");
  App.register_component(web_server_webserver);
  web_server_base_webserverbase->set_port(80);
  web_server_webserver->set_allow_ota(false);
  web_server_webserver->set_expose_log(true);
  web_server_webserver->set_include_internal(true);
  // api:
  //   encryption:
  //     key: CpkNTZ3Wj3heCfBlS44kUFy8r+W13ukExEbIQNfZxoA=
  //   id: api_apiserver
  //   port: 6053
  //   password: ''
  //   reboot_timeout: 15min
  api_apiserver = new api::APIServer();
  api_apiserver->set_component_source("api");
  App.register_component(api_apiserver);
  api_apiserver->set_port(6053);
  api_apiserver->set_password("");
  api_apiserver->set_reboot_timeout(900000);
  api_apiserver->set_noise_psk({10, 153, 13, 77, 157, 214, 143, 120, 94, 9, 240, 101, 75, 142, 36, 80, 92, 188, 175, 229, 181, 222, 233, 4, 196, 70, 200, 64, 215, 217, 198, 128});
  // sensor:
  // json:
  //   {}
  // esp32:
  //   board: nodemcu-32s
  //   framework:
  //     version: 2.0.5
  //     source: ~3.20005.0
  //     platform_version: platformio/espressif32@5.3.0
  //     type: arduino
  //   variant: ESP32
  // preferences:
  //   id: preferences_intervalsyncer
  //   flash_write_interval: 60s
  preferences_intervalsyncer = new preferences::IntervalSyncer();
  preferences_intervalsyncer->set_write_interval(60000);
  preferences_intervalsyncer->set_component_source("preferences");
  App.register_component(preferences_intervalsyncer);
  // time.sntp:
  //   platform: sntp
  //   timezone: MSK-3
  //   id: time_now
  //   servers:
  //   - pool.ntp.org
  //   - 0.pool.ntp.org
  //   - 1.pool.ntp.org
  //   update_interval: 15min
  time_now = new sntp::SNTPComponent();
  time_now->set_servers("pool.ntp.org", "0.pool.ntp.org", "1.pool.ntp.org");
  time_now->set_update_interval(900000);
  time_now->set_component_source("sntp.time");
  App.register_component(time_now);
  time_now->set_timezone("MSK-3");
  // uart:
  //   id: uart_bus_1
  //   tx_pin:
  //     number: 17
  //     mode:
  //       output: true
  //       input: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin
  //     inverted: false
  //     drive_strength: 20.0
  //   rx_pin:
  //     number: 16
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_2
  //     inverted: false
  //     drive_strength: 20.0
  //   baud_rate: 9600
  //   parity: NONE
  //   stop_bits: 1
  //   rx_buffer_size: 256
  //   data_bits: 8
  uart_bus_1 = new uart::ESP32ArduinoUARTComponent();
  uart_bus_1->set_component_source("uart");
  App.register_component(uart_bus_1);
  uart_bus_1->set_baud_rate(9600);
  esp32_esp32internalgpiopin = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin->set_pin(::GPIO_NUM_17);
  esp32_esp32internalgpiopin->set_inverted(false);
  esp32_esp32internalgpiopin->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin->set_flags(gpio::Flags::FLAG_OUTPUT);
  uart_bus_1->set_tx_pin(esp32_esp32internalgpiopin);
  esp32_esp32internalgpiopin_2 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_2->set_pin(::GPIO_NUM_16);
  esp32_esp32internalgpiopin_2->set_inverted(false);
  esp32_esp32internalgpiopin_2->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_2->set_flags(gpio::Flags::FLAG_INPUT);
  uart_bus_1->set_rx_pin(esp32_esp32internalgpiopin_2);
  uart_bus_1->set_rx_buffer_size(256);
  uart_bus_1->set_stop_bits(1);
  uart_bus_1->set_data_bits(8);
  uart_bus_1->set_parity(uart::UART_CONFIG_PARITY_NONE);
  // climate.custom:
  //   platform: custom
  //   id: hisense_climate_1
  //   lambda: !lambda |-
  //     auto hisense_climate = new HisenseAC(id(uart_bus_1));
  //     App.register_component(hisense_climate);
  //     id(compressor_frequency) = &hisense_climate->compressor_frequency;
  //     id(compressor_frequency_setting) = &hisense_climate->compressor_frequency_setting;
  //     id(compressor_frequency_send) = &hisense_climate->compressor_frequency_send;
  //     id(outdoor_temperature) = &hisense_climate->outdoor_temperature;
  //     id(outdoor_condenser_temperature) = &hisense_climate->outdoor_condenser_temperature;
  //     id(compressor_exhaust_temperature) = &hisense_climate->compressor_exhaust_temperature;
  //     id(target_exhaust_temperature) = &hisense_climate->target_exhaust_temperature;
  //     id(indoor_pipe_temperature) = &hisense_climate->indoor_pipe_temperature;
  //     id(indoor_humidity_setting) = &hisense_climate->indoor_humidity_setting;
  //     id(indoor_humidity_status) = &hisense_climate->indoor_humidity_status;
  //     id(UART_crc_errors) = &hisense_climate->UART_crc_errors;
  //     return {hisense_climate};
  //   climates:
  //   - name: HVAC-test
  //     disabled_by_default: false
  //     id: climate_climate
  //     visual: {}
  // button.restart:
  //   platform: restart
  //   name: Restart
  //   internal: true
  //   disabled_by_default: false
  //   id: restart_restartbutton
  //   entity_category: config
  //   device_class: restart
  restart_restartbutton = new restart::RestartButton();
  restart_restartbutton->set_component_source("restart.button");
  App.register_component(restart_restartbutton);
  App.register_button(restart_restartbutton);
  restart_restartbutton->set_name("Restart");
  restart_restartbutton->set_object_id("restart");
  restart_restartbutton->set_disabled_by_default(false);
  restart_restartbutton->set_internal(true);
  restart_restartbutton->set_entity_category(::ENTITY_CATEGORY_CONFIG);
  restart_restartbutton->set_device_class("restart");
  // button.shutdown:
  //   platform: shutdown
  //   name: Shutdown
  //   internal: true
  //   disabled_by_default: false
  //   id: shutdown_shutdownbutton
  //   icon: mdi:power
  //   entity_category: config
  shutdown_shutdownbutton = new shutdown::ShutdownButton();
  shutdown_shutdownbutton->set_component_source("shutdown.button");
  App.register_component(shutdown_shutdownbutton);
  App.register_button(shutdown_shutdownbutton);
  shutdown_shutdownbutton->set_name("Shutdown");
  shutdown_shutdownbutton->set_object_id("shutdown");
  shutdown_shutdownbutton->set_disabled_by_default(false);
  shutdown_shutdownbutton->set_internal(true);
  shutdown_shutdownbutton->set_icon("mdi:power");
  shutdown_shutdownbutton->set_entity_category(::ENTITY_CATEGORY_CONFIG);
  // button.safe_mode:
  //   platform: safe_mode
  //   name: Restart (Safe Mode)
  //   internal: true
  //   disabled_by_default: false
  //   id: safe_mode_safemodebutton
  //   icon: mdi:restart-alert
  //   entity_category: config
  //   device_class: restart
  //   ota: ota_otacomponent
  safe_mode_safemodebutton = new safe_mode::SafeModeButton();
  safe_mode_safemodebutton->set_component_source("safe_mode.button");
  App.register_component(safe_mode_safemodebutton);
  App.register_button(safe_mode_safemodebutton);
  safe_mode_safemodebutton->set_name("Restart (Safe Mode)");
  safe_mode_safemodebutton->set_object_id("restart_safe_mode");
  safe_mode_safemodebutton->set_disabled_by_default(false);
  safe_mode_safemodebutton->set_internal(true);
  safe_mode_safemodebutton->set_icon("mdi:restart-alert");
  safe_mode_safemodebutton->set_entity_category(::ENTITY_CATEGORY_CONFIG);
  safe_mode_safemodebutton->set_device_class("restart");
  safe_mode_safemodebutton->set_ota(ota_otacomponent);
  // button.template:
  //   platform: template
  //   name: Test
  //   on_press:
  //   - then:
  //     - logger.log:
  //         format: Button press
  //         tag: main
  //         level: DEBUG
  //         args: []
  //       type_id: lambdaaction
  //     - lambda: !lambda |
  //          id(hisense_climate_1).send_custom_command();
  //         static_cast<HisenseAC*> (id(hisense_climate_1).get_component(0))->send_custom_command();
  //       type_id: lambdaaction_2
  //     automation_id: automation
  //     trigger_id: button_buttonpresstrigger
  //   disabled_by_default: false
  //   id: template__templatebutton
  template__templatebutton = new template_::TemplateButton();
  App.register_button(template__templatebutton);
  template__templatebutton->set_name("Test");
  template__templatebutton->set_object_id("test");
  template__templatebutton->set_disabled_by_default(false);
  button_buttonpresstrigger = new button::ButtonPressTrigger(template__templatebutton);
  automation = new Automation<>(button_buttonpresstrigger);
  lambdaaction = new LambdaAction<>([=]() -> void {
      ESP_LOGD("main", "Button press");
  });
  lambdaaction_2 = new LambdaAction<>([=]() -> void {
      #line 129 "/config/esphome/test-devkit-v1.yaml"
       
       
      
  });
  automation->add_actions({lambdaaction, lambdaaction_2});
  // socket:
  //   implementation: bsd_sockets
  // network:
  //   {}
  // globals:
  //   id: compressor_frequency
  //   type: Sensor*
  //   restore_value: false
  compressor_frequency = new globals::GlobalsComponent<Sensor*>();
  compressor_frequency->set_component_source("globals");
  App.register_component(compressor_frequency);
  // globals:
  //   id: compressor_frequency_setting
  //   type: Sensor*
  //   restore_value: false
  compressor_frequency_setting = new globals::GlobalsComponent<Sensor*>();
  compressor_frequency_setting->set_component_source("globals");
  App.register_component(compressor_frequency_setting);
  // globals:
  //   id: compressor_frequency_send
  //   type: Sensor*
  //   restore_value: false
  compressor_frequency_send = new globals::GlobalsComponent<Sensor*>();
  compressor_frequency_send->set_component_source("globals");
  App.register_component(compressor_frequency_send);
  // globals:
  //   id: outdoor_temperature
  //   type: Sensor*
  //   restore_value: false
  outdoor_temperature = new globals::GlobalsComponent<Sensor*>();
  outdoor_temperature->set_component_source("globals");
  App.register_component(outdoor_temperature);
  // globals:
  //   id: outdoor_condenser_temperature
  //   type: Sensor*
  //   restore_value: false
  outdoor_condenser_temperature = new globals::GlobalsComponent<Sensor*>();
  outdoor_condenser_temperature->set_component_source("globals");
  App.register_component(outdoor_condenser_temperature);
  // globals:
  //   id: compressor_exhaust_temperature
  //   type: Sensor*
  //   restore_value: false
  compressor_exhaust_temperature = new globals::GlobalsComponent<Sensor*>();
  compressor_exhaust_temperature->set_component_source("globals");
  App.register_component(compressor_exhaust_temperature);
  // globals:
  //   id: target_exhaust_temperature
  //   type: Sensor*
  //   restore_value: false
  target_exhaust_temperature = new globals::GlobalsComponent<Sensor*>();
  target_exhaust_temperature->set_component_source("globals");
  App.register_component(target_exhaust_temperature);
  // globals:
  //   id: indoor_pipe_temperature
  //   type: Sensor*
  //   restore_value: false
  indoor_pipe_temperature = new globals::GlobalsComponent<Sensor*>();
  indoor_pipe_temperature->set_component_source("globals");
  App.register_component(indoor_pipe_temperature);
  // globals:
  //   id: indoor_humidity_setting
  //   type: Sensor*
  //   restore_value: false
  indoor_humidity_setting = new globals::GlobalsComponent<Sensor*>();
  indoor_humidity_setting->set_component_source("globals");
  App.register_component(indoor_humidity_setting);
  // globals:
  //   id: indoor_humidity_status
  //   type: Sensor*
  //   restore_value: false
  indoor_humidity_status = new globals::GlobalsComponent<Sensor*>();
  indoor_humidity_status->set_component_source("globals");
  App.register_component(indoor_humidity_status);
  // globals:
  //   id: UART_crc_errors
  //   type: Sensor*
  //   restore_value: false
  UART_crc_errors = new globals::GlobalsComponent<Sensor*>();
  UART_crc_errors->set_component_source("globals");
  App.register_component(UART_crc_errors);
  custom::CustomClimateConstructor hisense_climate_1 = custom::CustomClimateConstructor([=]() -> std::vector<climate::Climate *> {
      #line 94 "/config/esphome/test-devkit-v1.yaml"
      auto hisense_climate = new HisenseAC(uart_bus_1);
      App.register_component(hisense_climate);
      compressor_frequency->value() = &hisense_climate->compressor_frequency;
      compressor_frequency_setting->value() = &hisense_climate->compressor_frequency_setting;
      compressor_frequency_send->value() = &hisense_climate->compressor_frequency_send;
      outdoor_temperature->value() = &hisense_climate->outdoor_temperature;
      outdoor_condenser_temperature->value() = &hisense_climate->outdoor_condenser_temperature;
      compressor_exhaust_temperature->value() = &hisense_climate->compressor_exhaust_temperature;
      target_exhaust_temperature->value() = &hisense_climate->target_exhaust_temperature;
      indoor_pipe_temperature->value() = &hisense_climate->indoor_pipe_temperature;
      indoor_humidity_setting->value() = &hisense_climate->indoor_humidity_setting;
      indoor_humidity_status->value() = &hisense_climate->indoor_humidity_status;
      UART_crc_errors->value() = &hisense_climate->UART_crc_errors;
      return {hisense_climate};
  });
  climate_climate = hisense_climate_1.get_climate(0);
  App.register_climate(climate_climate);
  climate_climate->set_name("HVAC-test");
  climate_climate->set_object_id("hvac-test");
  climate_climate->set_disabled_by_default(false);
  // =========== AUTO GENERATED CODE END ============
  App.setup();
}

void loop() {
  App.loop();
}

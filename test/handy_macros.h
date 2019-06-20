#ifndef BGEIGIECAST_HANDY_MACROS_HPP
#define BGEIGIECAST_HANDY_MACROS_HPP

#include <Arduino.h>
#include <controller.h>
#include "test_api.h"
#include "test_config.h"
#include "test_bluetooth.h"

#define INCLUDE_TEST_CONTROLLER \
    TestEspConfig config; \
    StreamString bgeigie_connection; \
    StreamString api_output; \
    StreamString bt_output; \
    TestApiConnector api_conn(config, api_output); \
    TestBluetoohConnector bt_conn(bt_output); \
    Controller controller(config, bgeigie_connection, api_conn, bt_conn); \

#endif //BGEIGIECAST_HANDY_MACROS_HPP

#include "Adafruit_TinyUSB.h"
#include <Arduino.h>
#include <bb_captouch.h>

#define TOUCH_SDA 4
#define TOUCH_SCL 5
#define TOUCH_IRQ 3
#define TOUCH_RST 2

#define TOUCH_HEIGHT 600
#define TOUCH_WIDTH 1024
#define TOUCH_MAX_FINGERS 5

#define POWER_EN 1

const uint8_t desc_hid_report[] = {
    0x05, 0x0D, // USAGE_PAGE(Digitizers)
    0x09, 0x04, // USAGE     (Touch Screen)
    0xA1, 0x01, // COLLECTION(Application)
    0x85, 0x01, // REPORT_ID (1)

    // declare a finger collection
    0x05, 0x0D, //   USAGE_PAGE(Digitizers)
    0x09, 0x22, //   USAGE (Finger)
    0xA1, 0x02, //   COLLECTION (Logical)

    // declare Tip Switch & In range
    0x09, 0x42, //     USAGE (Tip Switch)
    0x09, 0x32, //     USAGE (In Range)
    0x15, 0x00, //     LOGICAL_MINIMUM (0)
    0x25, 0x01, //     LOGICAL_MAXIMUM (1)
    0x75, 0x01, //     REPORT_SIZE (1)
    0x95, 0x02, //     REPORT_COUNT(2)
    0x81, 0x02, //     INPUT (Data,Var,Abs)
    // declare the 6 padding bits as constant so the driver will ignore them
    0x95, 0x06, //     REPORT_COUNT (6)
    0x81, 0x03, //     INPUT (Cnst,Ary,Abs)

    // declare an identifier for the finger
    0x09, 0x51, //     USAGE (Contact Identifier)
    0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
    0x75, 0x08, //     REPORT_SIZE (8)
    0x95, 0x01, //     REPORT_COUNT (1)
    0x81, 0x02, //     INPUT (Data,Var,Abs)

    // define absolute X and Y coordinates of 16 bit each (percent values multiplied with 100)
    0x05, 0x01,       //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,       //     Usage (X)
    0x09, 0x31,       //     Usage (Y)
    0x16, 0x00, 0x00, //     Logical Minimum (0)
    0x26, 0xff, 0x0f, // LOGICAL_MAXIMUM (4095)
    0x36, 0x00, 0x00, //     Physical Minimum (0)
    0x46, 0xff, 0x0f, //     Physical Maximum (10000)
    // 0x66, 0x00, 0x00, //     UNIT (None)
    0x65, 0x00, //     UNIT (None)
    0x75, 0x10, //     Report Size (16),
    0x95, 0x02, //     Report Count (2),
    0x81, 0x02, //     Input (Data,Var,Abs)

    0xC0, //   END_COLLECTION

    // declare a finger collection
    0x05, 0x0D, //   USAGE_PAGE(Digitizers)
    0x09, 0x22, //   USAGE (Finger)
    0xA1, 0x02, //   COLLECTION (Logical)

    // declare Tip Switch & In range
    0x09, 0x42, //     USAGE (Tip Switch)
    0x09, 0x32, //     USAGE (In Range)
    0x15, 0x00, //     LOGICAL_MINIMUM (0)
    0x25, 0x01, //     LOGICAL_MAXIMUM (1)
    0x75, 0x01, //     REPORT_SIZE (1)
    0x95, 0x02, //     REPORT_COUNT(2)
    0x81, 0x02, //     INPUT (Data,Var,Abs)
    // declare the 6 padding bits as constant so the driver will ignore them
    0x95, 0x06, //     REPORT_COUNT (6)
    0x81, 0x03, //     INPUT (Cnst,Ary,Abs)

    // declare an identifier for the finger
    0x09, 0x51, //     USAGE (Contact Identifier)
    0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
    0x75, 0x08, //     REPORT_SIZE (8)
    0x95, 0x01, //     REPORT_COUNT (1)
    0x81, 0x02, //     INPUT (Data,Var,Abs)

    // define absolute X and Y coordinates of 16 bit each (percent values multiplied with 100)
    0x05, 0x01,       //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,       //     Usage (X)
    0x09, 0x31,       //     Usage (Y)
    0x16, 0x00, 0x00, //     Logical Minimum (0)
    0x26, 0xff, 0x0f, // LOGICAL_MAXIMUM (4095)
    0x36, 0x00, 0x00, //     Physical Minimum (0)
    0x46, 0xff, 0x0f, //     Physical Maximum (10000)
    // 0x66, 0x00, 0x00, //     UNIT (None)
    0x65, 0x00, //     UNIT (None)
    0x75, 0x10, //     Report Size (16),
    0x95, 0x02, //     Report Count (2),
    0x81, 0x02, //     Input (Data,Var,Abs)

    0xC0, //   END_COLLECTION

    // declare a finger collection
    0x05, 0x0D, //   USAGE_PAGE(Digitizers)
    0x09, 0x22, //   USAGE (Finger)
    0xA1, 0x02, //   COLLECTION (Logical)

    // declare Tip Switch & In range
    0x09, 0x42, //     USAGE (Tip Switch)
    0x09, 0x32, //     USAGE (In Range)
    0x15, 0x00, //     LOGICAL_MINIMUM (0)
    0x25, 0x01, //     LOGICAL_MAXIMUM (1)
    0x75, 0x01, //     REPORT_SIZE (1)
    0x95, 0x02, //     REPORT_COUNT(2)
    0x81, 0x02, //     INPUT (Data,Var,Abs)
    // declare the 6 padding bits as constant so the driver will ignore them
    0x95, 0x06, //     REPORT_COUNT (6)
    0x81, 0x03, //     INPUT (Cnst,Ary,Abs)

    // declare an identifier for the finger
    0x09, 0x51, //     USAGE (Contact Identifier)
    0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
    0x75, 0x08, //     REPORT_SIZE (8)
    0x95, 0x01, //     REPORT_COUNT (1)
    0x81, 0x02, //     INPUT (Data,Var,Abs)

    // define absolute X and Y coordinates of 16 bit each (percent values multiplied with 100)
    0x05, 0x01,       //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,       //     Usage (X)
    0x09, 0x31,       //     Usage (Y)
    0x16, 0x00, 0x00, //     Logical Minimum (0)
    0x26, 0xff, 0x0f, // LOGICAL_MAXIMUM (4095)
    0x36, 0x00, 0x00, //     Physical Minimum (0)
    0x46, 0xff, 0x0f, //     Physical Maximum (10000)
    // 0x66, 0x00, 0x00, //     UNIT (None)
    0x65, 0x00, //     UNIT (None)
    0x75, 0x10, //     Report Size (16),
    0x95, 0x02, //     Report Count (2),
    0x81, 0x02, //     Input (Data,Var,Abs)

    0xC0, //   END_COLLECTION

    // declare a finger collection
    0x05, 0x0D, //   USAGE_PAGE(Digitizers)
    0x09, 0x22, //   USAGE (Finger)
    0xA1, 0x02, //   COLLECTION (Logical)

    // declare Tip Switch & In range
    0x09, 0x42, //     USAGE (Tip Switch)
    0x09, 0x32, //     USAGE (In Range)
    0x15, 0x00, //     LOGICAL_MINIMUM (0)
    0x25, 0x01, //     LOGICAL_MAXIMUM (1)
    0x75, 0x01, //     REPORT_SIZE (1)
    0x95, 0x02, //     REPORT_COUNT(2)
    0x81, 0x02, //     INPUT (Data,Var,Abs)
    // declare the 6 padding bits as constant so the driver will ignore them
    0x95, 0x06, //     REPORT_COUNT (6)
    0x81, 0x03, //     INPUT (Cnst,Ary,Abs)

    // declare an identifier for the finger
    0x09, 0x51, //     USAGE (Contact Identifier)
    0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
    0x75, 0x08, //     REPORT_SIZE (8)
    0x95, 0x01, //     REPORT_COUNT (1)
    0x81, 0x02, //     INPUT (Data,Var,Abs)

    // define absolute X and Y coordinates of 16 bit each (percent values multiplied with 100)
    0x05, 0x01,       //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,       //     Usage (X)
    0x09, 0x31,       //     Usage (Y)
    0x16, 0x00, 0x00, //     Logical Minimum (0)
    0x26, 0xff, 0x0f, // LOGICAL_MAXIMUM (4095)
    0x36, 0x00, 0x00, //     Physical Minimum (0)
    0x46, 0xff, 0x0f, //     Physical Maximum (10000)
    // 0x66, 0x00, 0x00, //     UNIT (None)
    0x65, 0x00, //     UNIT (None)
    0x75, 0x10, //     Report Size (16),
    0x95, 0x02, //     Report Count (2),
    0x81, 0x02, //     Input (Data,Var,Abs)

    0xC0, //   END_COLLECTION

    // declare a finger collection
    0x05, 0x0D, //   USAGE_PAGE(Digitizers)
    0x09, 0x22, //   USAGE (Finger)
    0xA1, 0x02, //   COLLECTION (Logical)

    // declare Tip Switch & In range
    0x09, 0x42, //     USAGE (Tip Switch)
    0x09, 0x32, //     USAGE (In Range)
    0x15, 0x00, //     LOGICAL_MINIMUM (0)
    0x25, 0x01, //     LOGICAL_MAXIMUM (1)
    0x75, 0x01, //     REPORT_SIZE (1)
    0x95, 0x02, //     REPORT_COUNT(2)
    0x81, 0x02, //     INPUT (Data,Var,Abs)
    // declare the 6 padding bits as constant so the driver will ignore them
    0x95, 0x06, //     REPORT_COUNT (6)
    0x81, 0x03, //     INPUT (Cnst,Ary,Abs)

    // declare an identifier for the finger
    0x09, 0x51, //     USAGE (Contact Identifier)
    0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
    0x75, 0x08, //     REPORT_SIZE (8)
    0x95, 0x01, //     REPORT_COUNT (1)
    0x81, 0x02, //     INPUT (Data,Var,Abs)

    // define absolute X and Y coordinates of 16 bit each (percent values multiplied with 100)
    0x05, 0x01,       //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,       //     Usage (X)
    0x09, 0x31,       //     Usage (Y)
    0x16, 0x00, 0x00, //     Logical Minimum (0)
    0x26, 0xff, 0x0f, // LOGICAL_MAXIMUM (4095)
    0x36, 0x00, 0x00, //     Physical Minimum (0)
    0x46, 0xff, 0x0f, //     Physical Maximum (10000)
    // 0x66, 0x00, 0x00, //     UNIT (None)
    0x65, 0x00, //     UNIT (None)
    0x75, 0x10, //     Report Size (16),
    0x95, 0x02, //     Report Count (2),
    0x81, 0x02, //     Input (Data,Var,Abs)

    0xC0, //   END_COLLECTION

    0x05, 0x0D, //   USAGE_PAGE(Digitizers)
    0x27, 0xff, 0xff, 0x00, 0x00,

    0x09, 0x54,             //   USAGE (Contact count)
    0x15, 0x00, 0x25, 0x7f, //   LOGICAL_MAXIMUM (128)
    0x75, 0x08,             //   REPORT_SIZE (8)
    0x95, 0x01,             //   REPORT_COUNT(1)
    0x81, 0x02,             //   INPUT (Data,Var,Abs)

    0x85, 0x02, 0x09, 0x55, //   USAGE (Contact Count Maximum)
    0x25, 0x0A,             //   LOGICAL_MAXIMUM (127)
    0x75, 0x08,             //   REPORT_SIZE (8)
    0x95, 0x01,             //   REPORT_COUNT(1)
    0xB1, 0x02,             //   FEATURE (Data,Var,Abs)

    0xC0 // END_COLLECTION
};

typedef struct __attribute__((packed)) {
    struct {
        uint8_t status;
        uint8_t identifier;
        uint16_t x;
        uint16_t y;
    } point[5];
    uint8_t count;
} HID_Touchscreen_Report_Data_t;

BBCapTouch touch;
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 20,
                          false);

uint16_t get_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer,
                             uint16_t reqlen)
{
    if (report_type == HID_REPORT_TYPE_FEATURE) {
        buffer[0] = TOUCH_MAX_FINGERS;
    }
    return 1;
}

void setup()
{
    Serial.begin(115200);

    // power on screen
    pinMode(POWER_EN, OUTPUT);
    digitalWrite(POWER_EN, HIGH);

    // init touch screen
    touch.init(TOUCH_SDA, TOUCH_SCL, TOUCH_RST, TOUCH_IRQ);

    usb_hid.setReportCallback(get_report_callback, NULL);
    usb_hid.begin();
    while (!TinyUSBDevice.mounted())
        delay(1);

    Serial.println("Init GT911 touchscreen success!");
}

void loop()
{
    static bool is_pressed;
    TOUCHINFO points;
    int i;
    HID_Touchscreen_Report_Data_t report;

    if (touch.getSamples(&points)) {
        for (i = 0; i < points.count; i++) {
            Serial.print("X[");
            Serial.print(i);
            Serial.print("]:");
            Serial.print(points.x[i]);
            Serial.print(" ");
            Serial.print(" Y[");
            Serial.print(i);
            Serial.print("]:");
            Serial.print(points.y[i]);
            Serial.print(" ");
            is_pressed = true;
            report.point[i].identifier = i;
            report.point[i].status = 0x01;
            report.point[i].x = points.x[i] * 4095 / TOUCH_WIDTH;
            report.point[i].y = points.y[i] * 4095 / TOUCH_HEIGHT;
            report.count = points.count;
        }
        if (TinyUSBDevice.suspended()) {
            TinyUSBDevice.remoteWakeup();
        }
        if (usb_hid.ready()) {
            usb_hid.sendReport(1, &report, sizeof(report));
        }
        Serial.println();
    } else {
        if (is_pressed) {
            Serial.println("Released");
            is_pressed = false;
            memset(&report, 0, sizeof(report));
            usb_hid.sendReport(1, &report, sizeof(report));
        }
    }

    // short delay is required for prevent expected release
    delay(20);
}
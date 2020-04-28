#include "mbed.h"

#include <nrfx_gpiote.h>
#include <nrfx_ppi.h>
#include <nrf52832_peripherals.h>
#include <nrfx_timer.h>

void led_setup()
{
    nrfx_gpiote_out_config_t ledconfig;
    ledconfig.action = NRF_GPIOTE_POLARITY_TOGGLE;
    ledconfig.init_state = NRF_GPIOTE_INITIAL_VALUE_LOW;
    ledconfig.task_pin = true;
    nrfx_gpiote_out_init(LED1, &ledconfig);
    nrfx_gpiote_out_task_enable(LED1);
}

void button_setup()
{
    nrfx_gpiote_in_config_t buttonconfig;
    buttonconfig.sense = NRF_GPIOTE_POLARITY_TOGGLE; // push button event
    buttonconfig.pull = NRF_GPIO_PIN_PULLUP;
    buttonconfig.is_watcher = false;
    buttonconfig.hi_accuracy = false;
    buttonconfig.skip_gpio_setup = false;
    nrfx_gpiote_in_init(BUTTON1, &buttonconfig, nullptr);
    nrfx_gpiote_in_event_enable(BUTTON1, false); // event for PPI, not for interrupts
}

nrfx_timer_t instance4 = NRFX_TIMER_INSTANCE(4);

nrf_ppi_channel_t mychannel;

void ppi_setup()
{
    nrfx_ppi_channel_alloc(&mychannel);
    nrfx_ppi_channel_assign(mychannel,
                            //nrfx_gpiote_in_event_addr_get(BUTTON1),
                            nrfx_timer_event_address_get(&instance4, NRF_TIMER_EVENT_COMPARE1),
                            nrfx_gpiote_out_task_addr_get(LED1));
    nrfx_ppi_channel_enable(mychannel);
}

void f1()
{
    while (true)
    {
        //  ThisThread::sleep_for(100);
        nrfx_gpiote_out_clear(LED1);
        // nrfx_gpiote_out_task_trigger(LED1);
    }
}

    void timerSetUp()
{
    //Software Development Kit > Previous versions of nRF5 SDK > nRF5 SDK v15.0.0 > Data Structures > Data Structures
    nrfx_timer_config_t confiG;
    confiG.frequency = NRF_TIMER_FREQ_1MHz;
    confiG.mode = NRF_TIMER_MODE_TIMER;
    confiG.bit_width = NRF_TIMER_BIT_WIDTH_32;

    nrfx_timer_init (&instance4, &confiG, nullptr);
    nrfx_timer_enable(&instance4);
    nrfx_timer_extended_compare(&instance4, NRF_TIMER_CC_CHANNEL1, 100000, NRF_TIMER_SHORT_COMPARE1_CLEAR_MASK, false);
    
}

int main()
{
    nrfx_gpiote_init();

    led_setup();
    button_setup();
    timerSetUp();
    ppi_setup();

    // f1();
}
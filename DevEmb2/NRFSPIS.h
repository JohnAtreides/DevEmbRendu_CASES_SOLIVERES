#ifndef NRFSPIS_H
#define NRFSPIS_H



#include "mbed.h"


#include "nrfx_spis.h"



class NRFSPIS
{

public:
    static const int buffersize = 100;

public:

    void transfer(const uint8_t *tx_buffer, uint8_t tx_length, uint8_t *rx_buffer, int rx_length,  void (*fun)(void), int event = SPI_EVENT_COMPLETE){
        cf = fun;

        nrfx_spis_init(&spis_driver, &spis_config, spis_event_handler, this);
        nrfx_spis_buffers_set(&spis_driver,tx_buffer,tx_length,rx_buffer,rx_length);


    }   
 /*   void write_txbuffer(uint8_t * buf, int len)
    {
        memcpy((void *)txbuffer, buf, len);
        nrfx_spis_buffers_set(&spis_driver,txbuffer,len,rxbuffer,len);
    }
    void read_buffer(uint8_t * buf, int len)
    {
        memcpy(buf, rxbuffer, len);
    }
*/
    NRFSPIS(PinName mosi, PinName miso, PinName sclk, PinName ss, nrf_spis_mode_t mode, int instance)
    {

        spis_config.miso_pin = miso;
        spis_config.mosi_pin = mosi;
        spis_config.sck_pin = sclk;
        spis_config.csn_pin = ss;
        spis_config.mode = mode;
        spis_config.bit_order = NRF_SPIS_BIT_ORDER_MSB_FIRST;
        spis_config.csn_pullup = NRFX_SPIS_DEFAULT_CSN_PULLUP;
        spis_config.miso_drive = NRFX_SPIS_DEFAULT_MISO_DRIVE;
        spis_config.def = NRFX_SPIS_DEFAULT_DEF;
        spis_config.orc = NRFX_SPIS_DEFAULT_ORC;
        spis_config.irq_priority = NRFX_SPIS_DEFAULT_CONFIG_IRQ_PRIORITY;

        switch (instance)
        {
       /* case 0:
            spis_driver = NRFX_SPIS_INSTANCE(0);
            NVIC_SetVector(SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn, (uint32_t)nrfx_spis_0_irq_handler);
            NVIC_EnableIRQ(SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn);
            break;
            */
        case 1:
            spis_driver = NRFX_SPIS_INSTANCE(1);
            NVIC_SetVector(SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQn, (uint32_t)nrfx_spis_1_irq_handler);
            NVIC_EnableIRQ(SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQn);

            break;
            /*
        case 2:
            spis_driver = NRFX_SPIS_INSTANCE(2);
            NVIC_SetVector(SPIM2_SPIS2_SPI2_IRQn, (uint32_t)nrfx_spis_2_irq_handler);
            NVIC_EnableIRQ(SPIM2_SPIS2_SPI2_IRQn);
            break;
            */
        }
        nrfx_spis_init(&spis_driver, &spis_config, spis_event_handler, this);
    }

private:
    static void spis_event_handler(nrfx_spis_evt_t const *p_event, void *p_context)
    {
        NRFSPIS * spis = reinterpret_cast<NRFSPIS *>(p_context);
        switch (p_event->evt_type)
        {
        case NRFX_SPIS_BUFFERS_SET_DONE:
            break;
        case NRFX_SPIS_XFER_DONE:
            spis->cf();            
            break;
        case NRFX_SPIS_EVT_TYPE_MAX:
            break;
        }
    }

    nrfx_spis_config_t spis_config;
    nrfx_spis_t spis_driver;
    //uint8_t *mRxBuffer;
    //uint8_t *mTxBuffer;

    void (* cf)(void);
};

#endif
// Stubbed functions  for use on other systems than raspberry
#include "bcm2835.h"


int bcm2835_init(void){}
   int bcm2835_close(void){}
   void  bcm2835_set_debug(uint8_t debug){}
   unsigned int bcm2835_version(void){}
   uint32_t* bcm2835_regbase(uint8_t regbase){}
   uint32_t bcm2835_peri_read(volatile uint32_t* paddr){}
   uint32_t bcm2835_peri_read_nb(volatile uint32_t* paddr){}
   void bcm2835_peri_write(volatile uint32_t* paddr, uint32_t value){}
   void bcm2835_peri_write_nb(volatile uint32_t* paddr, uint32_t value){}
   void bcm2835_peri_set_bits(volatile uint32_t* paddr, uint32_t value, uint32_t mask){}
   void bcm2835_gpio_fsel(uint8_t pin, uint8_t mode){}
   void bcm2835_gpio_set(uint8_t pin){}
   void bcm2835_gpio_clr(uint8_t pin){}
   void bcm2835_gpio_set_multi(uint32_t mask){}
   void bcm2835_gpio_clr_multi(uint32_t mask){}
   uint8_t bcm2835_gpio_lev(uint8_t pin){}
   uint8_t bcm2835_gpio_eds(uint8_t pin){}
   uint32_t bcm2835_gpio_eds_multi(uint32_t mask){}
   void bcm2835_gpio_set_eds(uint8_t pin){}
   void bcm2835_gpio_set_eds_multi(uint32_t mask){}
   void bcm2835_gpio_ren(uint8_t pin){}
   void bcm2835_gpio_clr_ren(uint8_t pin){}
   void bcm2835_gpio_fen(uint8_t pin){}
   void bcm2835_gpio_clr_fen(uint8_t pin){}
   void bcm2835_gpio_hen(uint8_t pin){}
   void bcm2835_gpio_clr_hen(uint8_t pin){}
   void bcm2835_gpio_len(uint8_t pin){}
   void bcm2835_gpio_clr_len(uint8_t pin){}
   void bcm2835_gpio_aren(uint8_t pin){}
   void bcm2835_gpio_clr_aren(uint8_t pin){}
   void bcm2835_gpio_afen(uint8_t pin){}
   void bcm2835_gpio_clr_afen(uint8_t pin){}
   void bcm2835_gpio_pud(uint8_t pud){}
   void bcm2835_gpio_pudclk(uint8_t pin, uint8_t on){}
   uint32_t bcm2835_gpio_pad(uint8_t group){}
   void bcm2835_gpio_set_pad(uint8_t group, uint32_t control){}
   void bcm2835_delay (unsigned int millis){}
   void bcm2835_delayMicroseconds (uint64_t micros){}
   void bcm2835_gpio_write(uint8_t pin, uint8_t on){}
   void bcm2835_gpio_write_multi(uint32_t mask, uint8_t on){}
   void bcm2835_gpio_write_mask(uint32_t value, uint32_t mask){}
   void bcm2835_gpio_set_pud(uint8_t pin, uint8_t pud){}
   int bcm2835_spi_begin(void){}
   void bcm2835_spi_end(void){}
   void bcm2835_spi_setBitOrder(uint8_t order){}
   void bcm2835_spi_setClockDivider(uint16_t divider){}
   void bcm2835_spi_setDataMode(uint8_t mode){}
   void bcm2835_spi_chipSelect(uint8_t cs){}
   void bcm2835_spi_setChipSelectPolarity(uint8_t cs, uint8_t active){}
   uint8_t bcm2835_spi_transfer(uint8_t value){}
   void bcm2835_spi_transfernb(char* tbuf, char* rbuf, uint32_t len){}
   void bcm2835_spi_transfern(char* buf, uint32_t len){}
   void bcm2835_spi_writenb(char* buf, uint32_t len){}
   int bcm2835_i2c_begin(void){}
   void bcm2835_i2c_end(void){}
   void bcm2835_i2c_setSlaveAddress(uint8_t addr){}
   void bcm2835_i2c_setClockDivider(uint16_t divider){}
   void bcm2835_i2c_set_baudrate(uint32_t baudrate){}
   uint8_t bcm2835_i2c_write(const char * buf, uint32_t len){}
   uint8_t bcm2835_i2c_read(char* buf, uint32_t len){}
   uint8_t bcm2835_i2c_read_register_rs(char* regaddr, char* buf, uint32_t len){}
   uint8_t bcm2835_i2c_write_read_rs(char* cmds, uint32_t cmds_len, char* buf, uint32_t buf_len){}
   uint64_t bcm2835_st_read(void){}
   void bcm2835_st_delay(uint64_t offset_micros, uint64_t micros){}
   void bcm2835_pwm_set_clock(uint32_t divisor){}
   void bcm2835_pwm_set_mode(uint8_t channel, uint8_t markspace, uint8_t enabled){}
   void bcm2835_pwm_set_range(uint8_t channel, uint32_t range){}
   void bcm2835_pwm_set_data(uint8_t channel, uint32_t data){}

#include <pwm_driver.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <chrono>
#include <thread>
#include <cmath>

namespace lupus::pwm
{

PwmDriver::PwmDriver (int address)
{
  fd = open("/dev/i2c-1", O_RDWR);
  if(fd == 0)
  {
    fprintf(stderr, "could not open /dev/i2c-1: %m\n");
  }
  if( ioctl(fd, I2C_SLAVE, address ) < 0)
  {
    fprintf(stderr, "Failed to set slave address: %m\n");
  }
  setAllPwm(0, 0);
  i2c_smbus_write_byte_data(fd, this->mode2, this->outDrv);
  i2c_smbus_write_byte_data(fd, this->mode1, this->allCall);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  int mode= i2c_smbus_read_word_data(fd, this->mode1);
  mode = mode& ~sleep;
  i2c_smbus_write_byte_data(fd, this->mode1, mode);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

PwmDriver::~PwmDriver ()
{
  close(fd);
}

void PwmDriver::setPwmFrequency(float frequency)
{
  float prescaleval = 25000000.0;
  prescaleval /= 4096.0;
  prescaleval /= frequency;
  prescaleval -= 1.0;
  int prescale = std::floor(prescaleval + 0.5);
  int oldmode= i2c_smbus_read_byte_data(fd, this->mode1);
  int newmode= (oldmode& 0x7F) | 0x10;
  i2c_smbus_write_byte_data(fd, this->mode1, newmode);
  i2c_smbus_write_byte_data(fd, this->prescale, prescale);
  i2c_smbus_write_byte_data(fd, this->mode1, oldmode);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  i2c_smbus_write_byte_data(fd, this->mode1, oldmode| 0x80);
}

void PwmDriver::setPwm(int channel, int on, int off)
{
  i2c_smbus_write_byte_data(fd, this->led0_on_l+4*channel, on & 0xFF);
  i2c_smbus_write_byte_data(fd, this->led0_on_h+4*channel, on >> 8);
  i2c_smbus_write_byte_data(fd, this->led0_off_l+4*channel, off & 0xFF);
  i2c_smbus_write_byte_data(fd, this->led0_off_h+4*channel, off >> 8);
}

void PwmDriver::setAllPwm(int on, int off)
{
  i2c_smbus_write_byte_data(fd, this->all_led_on_l, on & 0xFF);
  i2c_smbus_write_byte_data(fd, this->all_led_on_h, on >> 8);
  i2c_smbus_write_byte_data(fd, this->all_led_off_l, off & 0xFF);
  i2c_smbus_write_byte_data(fd, this->all_led_off_h, off >> 8);
}

} // namespace lupus::pwm

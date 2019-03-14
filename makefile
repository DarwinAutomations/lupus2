CC = gcc
CXX = g++
RM = rm -f
CPPFLAGS = $(IS) -Wall -g
LDFLAGS = -g
LDLIBS = -lpthread -lpigpiod_if2 -lconfig++

IS=\
-Isrc\
-Isrc/construction\
-Isrc/construction/steering_unit\
-Isrc/construction/motor\
-Isrc/construction/rps_sensor\
-Isrc/construction/distance_sensor\
-Isrc/drivers/pwm\
-Isrc/drivers/gpio\
-Isrc/application/profiles\

CORE=\
src/main.cpp\
src/construction/lupus.cpp\
src/construction/lupus_controller.cpp\
src/construction/motor/propulsion_service.cpp\
src/application/profiles/granny_profile.cpp\

SRCS=$(CORE)\
src/drivers/pwm/pwm_driver.cpp\
src/drivers/pwm/pwm_control_unit.cpp\
src/drivers/gpio/gpio_driver.cpp\
src/construction/steering_unit/servo.cpp\
src/construction/steering_unit/rc_steering.cpp\
src/construction/motor/propulsion_unit.cpp\
src/construction/motor/rc_motor.cpp\
src/construction/rps_sensor/hall_rps_sensor.cpp\
src/construction/distance_sensor/distance_sensor_config.cpp\
src/construction/distance_sensor/ultrasonic_sensor.cpp\
src/construction/distance_sensor/ultrasonic_service.cpp\
src/construction/lupus_factory.cpp\
src/construction/lupus_configuration.cpp\

OBJS=$(subst .cpp,.o, $(SRCS))

make: $(OBJS)
	$(CXX) $(LDFLAGS) -o bin/lupus.bin $(OBJS) $(LDLIBS)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) bin/lupus.bin

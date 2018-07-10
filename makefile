CC = gcc
CXX = g++
RM = rm -f
CPPFLAGS = $(IS) -Wall -g
LDFLAGS = -g
LDLIBS = -lpthread -lpigpio

IS=\
-Isrc\
-Isrc/constructions\
-Isrc/controllers\
-Isrc/navigation\
-Isrc/propulsion\
-Isrc/pwm\
-Isrc/simulations\
-Isrc/profiles\
-Isrc/sensors\
-Isrc/gpio\

CORE=\
src/main.cpp\
src/constructions/local_construction.cpp\
src/controllers/intelligent_controller.cpp\
src/propulsion/propulsion_service.cpp\
src/profiles/granny_profile.cpp\

SRCS=$(CORE)\
src/pwm/pwm_driver.cpp\
src/pwm/pwm_control_unit.cpp\
src/gpio/gpio_driver.cpp\
src/navigation/servo.cpp\
src/navigation/rc_steering.cpp\
src/propulsion/propulsion_unit.cpp\
src/propulsion/rc_motor.cpp\
src/sensors/hall_rps_sensor.cpp\
src/sensors/hall_sensor.cpp\
src/sensors/ultrasonic_sensor.cpp\
src/sensors/ultrasonic_service.cpp\
src/constructions/local_construction_factory.cpp\

SRCSSIM=$(CORE)\
src/simulations/simulated_control_unit.cpp\
src/constructions/simulated_consturction_factory.cpp\

OBJS=$(subst .cpp,.o, $(SRCS))
OBJSSIM=$(subst .cpp,.o, $(SRCSSIM))

make: $(OBJS)
	$(CXX) $(LDFLAGS) -o bin/lupus.bin $(OBJS) $(LDLIBS)

simulation: $(OBJSSIM)
	$(CXX) $(LDFLAGS) -o bin/lupus_simulation.bin $(OBJSSIM) $(LDLIBS)

clean:
	$(RM) $(OBJS) $(OBJSSIM)

distclean: clean
	$(RM) bin/lupus_simulation.bin bin/lupus.bin

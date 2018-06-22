CC = gcc
CXX = g++
RM = rm -f
CPPFLAGS = $(IS) -Wall -g
LDFLAGS = -g
LDLIBS = -lpthread -lpigpio

IS=\
-Isrc\
-Isrc/constructions\
-Isrc/navigation\
-Isrc/pwm\
-Isrc/simulations\
-Isrc/profiles\
-Isrc/sensors\

CORE=\
src/main.cpp\
src/constructions/local_construction_factory.cpp\
src/constructions/local_construction.cpp\
src/navigation/propulsion_unit.cpp\
src/navigation/steering_unit.cpp\
src/navigation/acceleration_service.cpp\
src/profiles/granny_profile.cpp\
src/sensors/ultrasonic_sensor.cpp\
src/sensors/ultrasonic_service.cpp\

SRCS=$(CORE)\
src/pwm/pwm_control_unit.cpp\
src/pwm/pwm_driver.cpp\

SRCSSIM=$(CORE)\
src/simulations/simulated_control_unit.cpp

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

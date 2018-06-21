CC=g++
CFLAGS=$(IS) -Wall -g
CLIBS=-lpthread -lpigpio

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

IS=\
-Isrc\
-Isrc/constructions\
-Isrc/navigation\
-Isrc/pwm\
-Isrc/simulations\
-Isrc/profiles\
-Isrc/sensors\



# linking
make:
	$(CC) -o bin/lupus.bin $(CORE) src/pwm/pwm_control_unit.cpp src/pwm/pwm_driver.cpp $(CLIBS) $(CFLAGS)


simulation:
	$(CC) -o bin/lupus.bin $(CORE) src/simulations/simulated_control_unit.cpp $(CLIBS) $(CFLAGS)

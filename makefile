CC=g++
CFLAGS=$(IS) -Wall
CLIBS=-lpthread

CORE=\
src/main.cpp\
src/constructions/lupus.cpp\
src/navigation/propulsion_unit.cpp\
src/navigation/steering_unit.cpp\
src/navigation/acceleration_service.cpp\
src/profiles/granny_profile.cpp\

IS=\
-Isrc\
-Isrc/constructions\
-Isrc/navigation\
-Isrc/pwm\
-Isrc/simulations\
-Isrc/profiles\



# linking
make:
	$(CC) -o bin/lupus.bin $(CORE) src/pwm/pwm_control_unit.cpp src/pwm/pwm_driver.cpp $(CLIBS) $(CFLAGS)


simulation:
	$(CC) -o bin/lupus.bin $(CORE) src/simulations/simulated_control_unit.cpp $(CLIBS) $(CFLAGS)

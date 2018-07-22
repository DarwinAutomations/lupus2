import sys
import matplotlib.pyplot as plt

steering_direction = []
steering_left_raw_direction = []
steering_right_raw_direction = []

motor_front_left_power = []
motor_front_left_raw_power = []
motor_front_left_rps = []

motor_front_right_power = []
motor_front_right_raw_power = []
motor_front_right_rps = []

motor_back_left_power = []
motor_back_left_raw_power = []
motor_back_left_rps = []

motor_back_right_power = []
motor_back_right_raw_power = []
motor_back_right_rps = []

print("generating plot for", sys.argv[1])
with open(sys.argv[1]) as log:
    for entry in log:
        values = entry.split()
        if len(values) != 15:
            continue
        
        steering_direction.append(float(values[0]))
        steering_left_raw_direction.append(float(values[1]))
        steering_right_raw_direction.append(float(values[2]))

        motor_front_left_power.append(float(values[3]))
        motor_front_left_raw_power.append(float(values[4]))
        motor_front_left_rps.append(float(values[5]))

        motor_front_right_power.append(float(values[6]))
        motor_front_right_raw_power.append(float(values[7]))
        motor_front_right_rps.append(float(values[8]))

        motor_back_left_power.append(float(values[9]))
        motor_back_left_raw_power.append(float(values[10]))
        motor_back_left_rps.append(float(values[11]))


        motor_back_right_power.append(float(values[12]))
        motor_back_right_raw_power.append(float(values[13]))
        motor_back_right_rps.append(float(values[14]))


plt.figure(1)

plt.subplot(321)
plt.plot(
        range(len(steering_direction)),
        steering_direction)

plt.subplot(323)
plt.plot(
        range(len(steering_left_raw_direction)),
        steering_left_raw_direction,
        range(len(steering_right_raw_direction)),
        steering_right_raw_direction)

plt.subplot(322)
plt.plot(
        range(len(motor_front_left_power)),
        motor_front_left_power,
        range(len(motor_front_right_power)),
        motor_front_right_power,
        range(len(motor_back_left_power)),
        motor_back_left_power,
        range(len(motor_back_right_power)),
        motor_back_right_power)

plt.subplot(324)
plt.plot(
        range(len(motor_front_left_raw_power)),
        motor_front_left_raw_power,
        range(len(motor_front_right_raw_power)),
        motor_front_right_raw_power,
        range(len(motor_back_left_raw_power)),
        motor_back_left_raw_power,
        range(len(motor_back_right_raw_power)),
        motor_back_right_raw_power)

plt.subplot(326)
plt.plot(
        range(len(motor_front_left_rps)),
        motor_front_left_rps,
        "--",
        range(len(motor_front_right_rps)),
        motor_front_right_rps,
        "--",
        range(len(motor_back_left_rps)),
        motor_back_left_rps,
        "--",
        range(len(motor_back_right_rps)),
        motor_back_right_rps,
        "--")

plt.show()

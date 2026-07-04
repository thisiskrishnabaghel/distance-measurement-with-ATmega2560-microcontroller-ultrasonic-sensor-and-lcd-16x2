# Ultrasonic Distance Measurement Using ATmega2560 (Register-Level)

## Project Overview

This project measures distance to an object using an ultrasonic sensor and displays the result on a 16x2 LCD. Unlike typical Arduino projects that rely on library functions (`pulseIn()`, `LiquidCrystal`, etc.), this implementation is written entirely at the register level — direct manipulation of `DDRx`, `PORTx`, `PINx`, and Timer1 registers — with no Arduino framework calls.

## Components Used

1. **Microcontroller: ATmega2560**
   - 8-bit AVR microcontroller (used here on a Mega-class board), programmed directly via its hardware registers rather than through Arduino library abstractions.
2. **Ultrasonic Sensor: HC-SR04**
   - Measures distance by timing a sound pulse's round trip. Range: 2 cm to 400 cm.
3. **LCD Display: 16x2**
   - 8-bit parallel interface, driven directly via a data port and three control lines (RS, RW, EN).

## Working Concept

The HC-SR04 works by timing a sound wave's round trip, not by any digital protocol. A trigger pulse tells it to fire; the `echo` pin then stays HIGH for exactly as long as the sound takes to travel to the object and back. Measuring that pulse width — and converting it via the speed of sound — gives the distance.

### Steps

1. **Initialization**
   - Configure I/O directions: LCD data port and control pins as outputs, sensor trigger pin as output, echo pin as input.
   - Initialize the LCD (function set, display on, clear).
   - Configure Timer1 in free-running mode (prescaler /64 at 16MHz → 4µs per tick), used purely as a stopwatch.

2. **Triggering the Sensor**
   - Drive the `trig` pin HIGH for ~10µs, then LOW — the pulse width the HC-SR04 datasheet actually specifies (a common mistake in example code online is using a pulse in the millisecond range, which is 500x longer than necessary).

3. **Timing the Echo (the core of this implementation)**
   - Poll the `echo` pin until it goes HIGH, then snapshot the free-running `TCNT1` value (`t_start`).
   - Poll until `echo` goes LOW, then snapshot `TCNT1` again (`t_end`).
   - `t_end - t_start` gives the pulse width directly in timer ticks — this works correctly even if the timer wraps around mid-measurement, since unsigned subtraction handles the wraparound automatically.
   - A software timeout guards both polling loops, so the code can't hang indefinitely if the sensor doesn't respond or reports the maximum out-of-range timeout (~38ms).

4. **Distance Calculation**
   - Convert ticks to microseconds, then to distance using the round-trip formula:

     ```
     distance (cm) = pulse width (µs) / 58
     ```

   - This constant comes from the speed of sound (~343 m/s at 20°C ≈ 29.1µs per cm one-way, doubled for the round trip ≈ 58µs per cm). It's temperature-dependent — a natural extension of this project is compensating it with a live temperature reading (see Future Work).
   - Results outside the sensor's valid 0–400cm range are reported as "out of range" rather than a garbage number.

5. **Displaying the Distance**
   - The calculated value is formatted and written to the 16x2 LCD over the parallel interface.

## Design Notes / Why Register-Level

This project intentionally avoids Arduino's `pulseIn()` and `LiquidCrystal` library, to demonstrate direct hardware control.

## Applications

1. **Robotics** — obstacle detection and avoidance for autonomous robots.
2. **Automotive** — parking assistance sensors.
3. **Industrial Automation** — distance/position sensing in automated processes.
4. **Security Systems** — proximity or motion-based triggers.

## Conclusion

This project uses an ATmega2560, programmed entirely through direct register access, to measure distance with an HC-SR04 ultrasonic sensor and display the result on a 16x2 LCD. A custom Timer1 driver generates the sensor's trigger pulse and captures the echo pulse width using a free-running counter, which is then converted to distance via the standard 58µs-per-cm formula. The project demonstrates core embedded systems skills — timer configuration, pulse measurement, and manual peripheral control — without relying on library abstractions.

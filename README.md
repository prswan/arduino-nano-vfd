# Arduino Nano VFD

## Overview

This is a hardware & software project to utilize various Vacuum Fluorescent Displays (VFD) in art projects driven from an Arduino Nano system. Most of the displays are sourced from recycled consumer electronics. In almost all volume consumer products the displays themselves were customized for each product, necessitating both the hardware & software being flexible enough to efficiently accommodate each displays uniqueness.

## Hardware

VFD are somewhat awkward to use. They need a low voltage high current biased filament supply (a few volts and a few hundred milliamps) and a high voltage drive supply for the digit elements (around 40 volts). Thankfully they were so prevalent several driver ICs were manufactured that included basic serial shift registers, bit map integrated stand alone driver ICs, alphanumeric controllers and microcontrollers with integrated VFD support. In almost all cases, the communications with these driver ICs is by 2-wire serial that the Arduino SPI port can drive efficiently.

### Universal VFD PCB

This PCB is designed for raw serial shift register drive using up to three SN75518 (or equivalent, there are several) ICs.

Features:

 - 210mm maximum display width
 - 96-pin 2mm pitch VFD connector
 - 80-pin 0.1" pitch VFD connector
 - 3-row patch area to facilitate rewiring.
 - Filament voltage tuning resistors.

## Software

The software design aims to minimize the effort needed to use the diverse range of VFDs.

## Further Reading

 - **[Wikipedia Vacuum Fluorescent Display](https://en.wikipedia.org/wiki/Vacuum_fluorescent_display)**
 - **[Wikipedia 7-Segment Display](https://en.wikipedia.org/wiki/Seven-segment_display)**
 - **[Wikipedia 14-Segment Display](https://en.wikipedia.org/wiki/Fourteen-segment_display)**
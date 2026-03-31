# Errata for Universal VFD PCB V1.10



None



## Design Improvements for the Next Version



1. R1 - R4 should be 1W but were placed as 0.25W so the pads, holes and spacing are too small. They should be 0.6" pitch.
2. The 12-pin header pinout was set based on ease of routing and the Controller PCB designed to match it, however the VFD's are mounted to the underside so the connector is now upside down causing a twist in the cable for bottom pinned VFD that are more common and have the shortest cable to the controller. Top pinned VFD (upside down PCB) are have a straight cable, but in this case the universal connector is at the opposite end leaving a lot of cable length to accommodate a twist. Needs review of the routing impact of flipping the 12-pin header whilst keeping the same pinout. 




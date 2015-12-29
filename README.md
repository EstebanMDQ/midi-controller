Basic MIDI foot controller
==========================

I've been wanting to try a guitar looper for a while, but I don't like the idea
of expending money on a looper specific pedal when I can use a computer for that
and since I've been learning arduino for fun made perfect sense to make a
an arduino based controller.

After some experiments and search on the web I found a similar project,
https://rideonbeat.wordpress.com/2014/08/18/controlador-midi-con-arduino-leonardo-prototipo-terminado/
and that pointed me in the right direction, this lib https://github.com/rkistner/arcore that provides basic MIDI device functionality
for arduino.


### Instructions

- install https://github.com/rkistner/arcore into your computer
- clone this repo
- compile and upload the scketch to your arduino (I used Leonardo)
- build the circuit showed here
- change the circuit and the scketch to suit your needs

### Troubleshooting

I found out the hard way that some bad soldering can create some weird bugs,
this MIDI monitor software is really helpful to understand what was happening

http://www.snoize.com/MIDIMonitor/

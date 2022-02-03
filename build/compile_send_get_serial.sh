#usefun commands
#ls -ls /dev/cu.*

cmake ..
make
cp pico_test.uf2 /Volumes/RPI-RP2
#minicom -o -D /dev/cu.usbmodem1101
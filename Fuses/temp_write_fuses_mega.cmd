pushd "<path_to_avrdude.exe>"
@REM ...Adruino\hardware\tools\avr\bin
avrdude.exe -c stk500v1 -p m328p -P com3 -U lfuse:w:0xee:m -U hfuse:w:0xd7:m -U efuse:w:0xfd:m -v -C ..\etc\avrdude.conf -b 19200
popd
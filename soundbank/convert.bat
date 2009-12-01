@ECHO OFF
SET PATH=C:\devkitPRO\devkitARM\bin
mmutil -d *.wav *.xm -osoundbank.bin -hsoundbank.h

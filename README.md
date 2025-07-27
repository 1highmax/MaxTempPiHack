# problem statement
rpi4/5 and cm4/5 have max temperatures of 85/90 degrees, degrading performance continously in that 5 degree range.
to have higher limits, one must patch the closed source proprietary video core firmware. May break the pi, obviously. 

```bash
# get the firmware from a raspberry pi 5
scp -P 22222 root@10.32.0.2:/mnt/boot/start.elf .
# to later replace the firmware, we must remount the directory as read write
mount -o remount,rw /mnt/boot
# when done, scp back and boil rice on the pi
```

# running
```bash
gcc patch_start_elf.c -o patch_start_elf
./patch_start_elf 
# Successfully patched at offset 0x1b357c: 26 b2 55 00 -> 26 b2 64 00
# Successfully patched at offset 0x1b3560: 26 b2 5a 00 -> 26 b2 69 00
# Patched 2 out of 2 locations
```

# summary

used ghidra to find the max temp setting in the firmware, increase it with the c program

the `Ghidra/` folder must be merged into a fresh ghidra from-source-build. https://github.com/NationalSecurityAgency/ghidra?tab=readme-ov-file#build

Took the videocore assembler patch in `Ghidra/` from here: https://github.com/jobermayr/ghidra-staging and fixed it


<img width="1488" height="905" alt="image" src="https://github.com/user-attachments/assets/b959fc46-a4e7-46cd-b921-a6ae711e031a" />

# problem statement
rpi4/5 and cm4/5 have max temperatures of 85/90 degrees, degrading performance continously in that 5 degree range.
to have higher limits, one must patch the closed source proprietary video core firmware.

```bash
# get the firmware from a balena compute module
scp -P 22222 root@10.32.0.2:/mnt/boot/start.elf .
# to later replace the firmware, we must remount the directory as read write
mount -o remount,rw /mnt/boot
# when done, scp back and boil rice on the compute module
```

# summary

used ghidra to find the max temp setting in the firmware, increase it with the c program

the `Ghidra/` folder must be merged into a fresh ghidra from-source-build. https://github.com/NationalSecurityAgency/ghidra?tab=readme-ov-file#build

Took the patch in `Ghidra/` from here: https://github.com/jobermayr/ghidra-staging and fixed it


<img width="1488" height="905" alt="image" src="https://github.com/user-attachments/assets/6f0eafe3-a6dc-4be2-8ed6-446b570a8fc2" />

# Build the operating system

NOTE: Before building the operating system you have install/build gcc cross compiler
and install qemu-system-i386

```sh
make clean && ./build.sh
```

# Run the operating system
```sh
qemu-system-i386 -hda ./bin/os.bin
```

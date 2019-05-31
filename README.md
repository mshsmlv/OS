# OS
Simple operating system for x86.

![Everybody loves cats](https://github.com/MashaSamoylova/scan_practice/blob/master/arp-scan.png)


## Bochs installing UBUNTU 18.04
```
tar -xvf  bochs-2.6.9.tar.gz
cd bochs-2.6.9
sudo apt-get install ncurses-dev
sudo apt-get install libsdl1.2-dev
CXXFLAGS='-lpthread' ./configure   --prefix=$HOME/non-reloc  --mandir=\${prefix}/share/man   --with-x11   --with-rfb   --with-term   --with-sdl   --disable-docbook   --enable-cdrom  --enable-x86-64 --enable-idle-hack --enable-pci   --enable-usb   --enable-usb-ohci   --enable-a20-pin --enable-cpu-level=6   --enable-fpu   --enable-disasm   --enable-idle-hack   --enable-all-optimizations   --enable-repeat-speedups   --enable-sb16=linux   --enable-ne2000   --enable-pnic   --enable-debugger   --enable-debugger-gui   --enable-pci
```
fix `iodev/network/slirp/slirp.h` file, line 36:
from `#if defined(__OpenBSD__)` to `#if defined(__OpenBSD__) || (__linux__)`
```
make
make install
```

Add to your `~/.bashrc`:
```
export PATH="$PATH:$HOME/non-reloc/bin"
source ~/.bashrc
``` 

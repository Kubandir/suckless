# Suckless Configuration

My personal configuration for suckless tools including:

- **dmenu** - Dynamic menu
- **dwm** - Dynamic window manager  
- **slock** - Simple screen locker
- **slstatus** - Status monitor
- **st** - Simple terminal

## Installation

Run the build script to compile and install all tools:

```bash
./compile.sh
```

This script will:
- Clean previous builds
- Compile each tool
- Install with sudo privileges

## Requirements

- C compiler (gcc)
- Make
- Xlib development headers
- Sudo access for installation

I stole a lot of stuff from other people, creadit to the original authors
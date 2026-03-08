# Morse

A small set of command-line tools for working with Morse code.

It provides utilities to:

- **Encode** plain text into Morse code
- **Decode** Morse code back into text
- **Compress** Morse symbols into a compact binary form
- **Uncompress** compressed Morse data back into plain text
- **Play Morse as audio** when built with the optional library dependency `libao`

## Tools

This project builds the following command-line programs:

- `morse-encode` — convert text to Morse code
- `morse-decode` — convert Morse code to text
- `morse-compress` — compress Morse symbols into a binary representation
- `morse-uncompress` — uncompress binary representation back into Morse symbols
- `morse-audio` — play Morse code as sound *(requires `libao`)*

## Usage Example

The tools are designed to be piped with each other
and other standard unix utilities, here are some examples:

```bash
morse-encode the quick brown fox jumps over the lazy dog | morse-compress > "my-message.bin" 
```

```bash
cat "my-message.bin" | morse-uncompress | morse-decode
```

```bash
echo "SOS" | morse-encode | morse-audio | morse-decode
```

## Build

This project supports both Autotools and Zig as build systems.
Autotools is the recommended way to build
on POSIX compliant systems with dynamic linking, 
while Zig can be used to easily cross-compile
to many different types of targets with static linking.

---

## Building with Autotools

### Requirements

To build Morse with Autotools, the following utilities will be needed:

- `gcc` or another C compiler
- `autoconf`
- `automake`
- `libtool`
- `make`

Optional for audio support:

- `libao` development headers

### Build steps

1. Run `autoreconf -fi` to build the `configure` and `Makefile` files
2. Run the `./configure` script to automatically set up building against your system or append the `--help` parameter for more advanced options
3. Run `make` to build the source code. `morse-decode`, `morse-encode` etc... will be built in the current path
4. Optionally run `make install` as root/sudo to install the built libraries and binaries to the system so that they can be used from any working directory

## Building with Zig

### Requirements

To build Morse with Zig, Zig 0.15.2 needs to be installed.
Since Zig is in active development with a changing API, other versions are not guaranteed to work. 

### Build steps

Simply run `zig build`. Optionally, add an optimization level and target triplet;
this is extremely powerful as it allows cross-compilation of static binaries
to multiple architectures and operating systems with minimal effort.
For example:

```bash
zig build -Doptimize=ReleaseFast -Dtarget=aarch64-linux-musl
zig build -Doptimize=ReleaseFast -Dtarget=riscv64-linux-musl
zig build -Doptimize=ReleaseFast -Dtarget=x86-linux-musl
zig build -Doptimize=ReleaseFast -Dtarget=x86_64-linux-musl
zig build -Doptimize=ReleaseFast -Dtarget=aarch64-macos-none
zig build -Doptimize=ReleaseFast -Dtarget=x86_64-macos-none
zig build -Doptimize=ReleaseFast -Dtarget=aarch64-windows-gnu 
zig build -Doptimize=ReleaseFast -Dtarget=x86-windows-gnu
zig build -Doptimize=ReleaseFast -Dtarget=x86_64-windows-gnu
```

The binaries will appear in a subdirectory of `zig-out`
under folders that specify the optimization level and target triplet
of the build. 
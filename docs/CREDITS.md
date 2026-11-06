# Credits and licenses

[← Documentation](README.md)

This project is licensed under the **GNU GPL v2 or later** ([LICENSE](../LICENSE)).

## Authors

bbcpu was developed in [bloodborne-recomp](https://github.com/bloodborne-native/bloodborne-recomp)
and moved here with its history, so `git log` has every change.

- **Pablo Souza**: the interpreter, the translator and the recompiled-code runtime.
- **FraSharp**: translator work: the indirect branch cache, direct host calls, guarded returns,
  probes in translated code, and many instructions.
- **Alok K. Dhir**: floating-point control words, FTZ and DAZ, and SSE4A.
- **claitonllemes**: the recompiled-code call path and its function table.
- **deadinside**: bbport, below.

## Built on

- [**bbport**](https://github.com/deadinside28/bloodborne_pc) by deadinside28, the native port of
  Bloodborne this project started from: bbcpu runs the game that port loads.
- [**shadPS4**](https://github.com/shadps4-emu/shadPS4): the PS4 emulator the rendering side of the
  port derives from.

## Libraries

- [Zydis](https://github.com/zyantific/zydis) and Zycore (MIT): the x86-64 decoder, built by
  `build.sh` into `deps/`.

- [StikJIT](https://github.com/StikDebug/StikJIT) (MPL-2.0): the breakpoint protocol its
  universal script answers on iOS devices with TXM (`JIT26PrepareRegion`, `JIT26Detach` in its
  `INTEGRATION.md`), followed by `src/cpu/jit_arm64.c`. No StikJIT code is linked into bbcpu.

## Prior work

[Box64](https://github.com/ptitSeb/box64) and [FEX](https://github.com/FEX-Emu/FEX) are the
established x86-64 translators for arm64; [Architecture](ARCHITECTURE.md) says why this project
wrote its own. No code is taken from them.

## Disclaimer

Not affiliated with Sony Interactive Entertainment or FromSoftware. *Bloodborne* is a trademark of
Sony Interactive Entertainment. No game code or files are included.

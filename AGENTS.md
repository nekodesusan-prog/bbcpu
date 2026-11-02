# bbcpu

Runs x86-64 PS4 game code in an arm64 process. Written for Bloodborne's macOS port; used by
bloodborne-runtime and, through `src/recomp/rc.h`, by bloodborne-recomp. It holds no game code.

## Read first

- `README.md`, `docs/ARCHITECTURE.md`, `docs/API.md`. Other games' projects use this: keep it free
  of any one game's addresses and say "guest", not "the game", in new interfaces.

## Layout

- `src/cpu/`: decoder (Zydis), interpreter (`interp*.c`), arm64 translator (`jit_arm64.c`), record
  and replay tracer (`record.c`), natives (`native.c`), the recompiled-code runtime (`recomp.c`).
  `bbcpu.h` is the public interface.
- `src/recomp/rc.h`: what generated code includes (`BB_RECOMP_API_VERSION`: bump it when RcApi or
  RcFunction change, and update `tools/recomp/bbcpu_api` in bloodborne-recomp).
- `examples/hello.c`: the smallest host. `tests/`: differential tests and fuzzers.
- `tools/cpu/`: test scripts, `census.c`, `encodings.c`.

## Build and check

```sh
bash build.sh                # Zydis into deps/, out/libbbcpu.a, out/hello
out/hello
bash tools/cpu/test_jit.sh   # CPU tests (CI runs them with the arm64 encodings)
```

A change that reaches the game is also checked through bloodborne-runtime (its `tools/test_run.sh`)
and, when it touches instruction behaviour, with bloodborne-recomp's `tools/recomp/fuzz.sh`.

## Working rules

- **The project is five repositories:** [bloodborne-mac](https://github.com/bloodborne-native/bloodborne-mac)
  (the app) ⊃ `runtime/` = [bloodborne-runtime](https://github.com/bloodborne-native/bloodborne-runtime)
  ⊃ `bbcpu/` (this one) and `recomp/` = [bloodborne-recomp](https://github.com/bloodborne-native/bloodborne-recomp);
  the app also has `launcher/`. Commit here, push, then bump the pointer in the runtime and the app.
- **Before any push, check `git remote get-url origin`.** Push to `main`; ask before force-pushing
  anything that existed before this session.
- **Commits:** a short subject, a body that says what changed and why (numbers when measured), and
  the trailer the session asks for.
- **Credits:** code taken from another project or fork is credited in the same commit:
  `docs/CREDITS.md`, the wiki, the commit message and a short code comment.
- **No game code, ever:** no decompiled or generated game code, no game files, no records of game
  memory in any repository or wiki.
- **Docs:** plain, precise English; numbers measured, not guessed. Docs say what is true now. The
  wiki mirrors the docs; update both.
- **Shell:** no `rm -rf` on variable paths; no `xargs ... sh -c '...'`.

# Debugging

## OpenOCD

```
$ openocd -f interface/stlink-v2.cfg -f target/stm32l0.cfg
```

## On Apple Silicon MacOS

`gdb` has not yet been ported to Apple Silicon Mac devices. `lldb` exists and supports the GDB remote server protocol, but is not really fully compatible with `openocd`, nor is the experience ergonomic.

Instead, run `openocd` as usual, and then run `gdb` in a Docker container (which technically is running in a Linux VM on the Apple Silicon host). First, create a `Dockerfile` for a `gdb` instance:

```
FROM alpine:latest

RUN apk add --no-cache gdb

ENTRYPOINT ["gdb"]
```

Build it:

```
$ docker build -t gdb-docker .
```

Run it:

```
$ docker run --rm -it \
    --mount type=bind,source=$(pwd),target=/host \
    -w /host \
    gdb-docker /host/build/eink-discovery.stm32l.exe
```

Once inside gdb, connect to a running `openocd`:

```
(gdb) target remote host.docker.internal:3333
```

To flash the image:

```
(gdb) load
...
(gdb) monitor reset halt
```

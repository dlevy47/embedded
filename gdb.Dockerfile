FROM alpine:latest

RUN apk add --no-cache gdb

ENTRYPOINT ["gdb"]

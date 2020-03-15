#!/bin/bash
ARCH=$(uname -m)
if [ "$ARCH" == "x86_64" ]; 
then 
    TARGET="musl"; 
    apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y musl-tools
else
    TARGET="gnueabihf";
    apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y git make gcc libc-dev
fi

rustup target add ${ARCH}-unknown-linux-${TARGET}
cargo build --target ${ARCH}-unknown-linux-${TARGET} --release
strip target/${ARCH}-unknown-linux-musl/release/hello-world-rust
mv target/${ARCH}-unknown-linux-${TARGET}/release/hello-world-rust /hello-world-rust
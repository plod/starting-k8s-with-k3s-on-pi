FROM rust:1-stretch as builder
# Choose a workdir
WORKDIR /usr/src/app
# Create blank project
RUN USER=root cargo init
# Copy Cargo.toml to get dependencies
COPY Cargo.toml .
COPY src src

RUN cargo build --release
RUN strip target/release/hello-world-rust

FROM rust:1-slim-stretch
# # Copy bin from builder to this new image

COPY --from=builder /usr/src/app/target/release/hello-world-rust /hello-world-rust

ENV WHO "World"

# # Default command, run app
CMD ["/hello-world-rust"]
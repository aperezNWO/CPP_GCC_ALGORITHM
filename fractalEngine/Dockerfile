# Stage 1: Build the C++ binary using Debian Bookworm to match runtime glibc
FROM debian:bookworm-slim AS builder

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

# Compile using Bookworm's toolchain (matches target glibc)
RUN g++ -std=c++17 -O3 FractalDemo.cpp -o fractal_server

# Stage 2: Runtime image
FROM debian:bookworm-slim
WORKDIR /app
COPY --from=builder /app/fractal_server /app/fractal_server

EXPOSE 8080
CMD ["./fractal_server"]
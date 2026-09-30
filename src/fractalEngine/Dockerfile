# Stage 1: Build the C++ binary
FROM debian:bookworm-slim AS builder

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN g++ -std=c++17 -O3 FractalDemo.cpp -I. Dijkstra.cpp -o fractal_server -lpthread

# Stage 2: Runtime image
FROM debian:bookworm-slim
WORKDIR /app

COPY --from=builder /app/Algorithm.ini /app/Algorithm.ini
COPY --from=builder /app/fractal_server /app/fractal_server

EXPOSE 8080
CMD ["./fractal_server"]

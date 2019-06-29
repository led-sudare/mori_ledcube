# BUILD
FROM alpine:3.10.0 as builder
RUN apk add --no-cache \
    ca-certificates \
    make \
    g++ 

## src build
COPY . /app
WORKDIR /app/lib
RUN make
RUN make install
WORKDIR /app/demo
RUN make

# RUN
# FROM alpine:3.10.0 as runner
RUN apk add --no-cache ca-certificates
ARG ip="1.2.3.4"
ENV _IP ${ip}
ARG port="5678"
ENV _PORT ${port}
WORKDIR /app
# COPY --from=builder /app/demo/demo /app/mori
# ENV _APP="/app/mori"
ENV _APP="/app/demo/demo"
CMD ${_APP} ${_IP} ${_PORT}

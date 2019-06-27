# BUILD
FROM alpine:3.10.0 as builder
RUN apk add --no-cache \
    ca-certificates \
    make \
    g++ 
    # wget \
    # tar
    # musl-dev \

# WORKDIR /tmp/lib
# RUN wget -q -O /etc/apk/keys/sgerrand.rsa.pub https://alpine-pkgs.sgerrand.com/sgerrand.rsa.pub
# RUN wget https://github.com/sgerrand/alpine-pkg-glibc/releases/download/2.29-r0/glibc-2.29-r0.apk
# RUN apk add glibc-2.29-r0.apk
# ADD https://github.com/sgerrand/alpine-pkg-glibc/archive/2.29-r0.tar.gz /tmp/lib/glibc/
# RUN tar -xJf /tmp/lib/glibc/2.29-r0.tar.gz -c /tmp/lib/

# RUN touch /etc/ld.so.conf
WORKDIR /usr/local/include

## src build
COPY . /app
WORKDIR /app/lib
RUN make
RUN make install
# RUN ldconfig
RUN cp led.h /app/demo/
RUN cp libled.so /app/demo/
WORKDIR /app/demo
RUN make

# RUN
# FROM alpine:3.10.0 as runner
# ARG IP="1.2.3.4"
# ARG PORT="5678"
# WORKDIR /app
# COPY --from=builder /app/demo /app/mori
# CMD ["/app/mori", ${IP}, ${PORT}]

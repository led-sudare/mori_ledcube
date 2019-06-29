3D LED SDK & DEMO Content
=======
ここには、3D LED SDKと森さんデモコンテンツがあります。

# Build & Run💨
```sh
$ cd lib
$ make
$ sudo make install
$ sudo ldconfig
$ cd ../demo
$ make
$ ./demo 1.2.3.4 5678
```

# Docker🐳
## Require👜
* Git
* Docker

## Get Started🏁

1. Get src
    ```sh
    $ git clone https://github.com/led-sudare/mori-ledcube.git
    ```

2. Build
    ```sh
    $ docker image build --no-cache -t mori:alpine ip=1.2.3.4 port=5678 .

    $ docker image ls
    REPOSITORY          TAG                  IMAGE ID            CREATED             SIZE
    <none>              <none>               ed2d0858bcf0        22 minutes ago      162MB
    ```

    Change ip:port
    ```sh
    $ docker image build -t mori:alpine ip=1.2.3.4 port=5678 .
    $ docker image prune
    ```

3. Run
    ```sh
    $ docker container run --rm mori:alpine
    ```


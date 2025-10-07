FROM alpine:3.18

RUN apk update && apk add \
    build-base \
    cmake \
    make \
    gtest \
    gtest-dev

WORKDIR /app
COPY . .

RUN mkdir -p build && cd build && cmake .. && make

RUN ln -sf /app/build/lab2_main /usr/local/bin/lab2_main && \
    ln -sf /app/build/lab2_test /usr/local/bin/lab2_test

CMD ["lab2_test"]
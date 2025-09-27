FROM alpine:3.18

RUN apk update && apk add build-base cmake make

WORKDIR /app
COPY . .

RUN rm -rf build && mkdir build && cd build && cmake .. && make

CMD ["./build/laba1"]

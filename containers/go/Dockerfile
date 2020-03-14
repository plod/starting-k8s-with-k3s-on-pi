FROM  golang:1.14-alpine3.11 
# AS builder

WORKDIR /go/src/app
COPY main.go .

RUN go build -ldflags="-w -s" -o /go/bin/hello


# FROM scratch
# COPY --from=builder /go/bin/hello /go/bin/hello

EXPOSE 8080

ENV WHO=""

ENTRYPOINT ["/go/bin/hello"]
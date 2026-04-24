# cserve — Async HTTP Server

A non-blocking TCP HTTP server built from scratch using kqueue.

## Features

- Non-blocking I/O with kqueue (macOS)
- Multi-client support (single process, event-driven)
- HTTP GET parsing with `sscanf`
- Static file serving from `./www/`
- Content-Type detection by file extension
- Path traversal protection (`..` check)
- Proper HTTP error responses (400, 403, 404, 500)

## Architecture

```
socket → bind → listen → kqueue
loop:
  kevent() → for each event:
    listen fd  → accept + register client fd
    client fd  → handle_client + delete_event
```

## Build

```bash
gcc -o server server.c
./server
```

Server listens on port 8080. Place static files in `./www/`.

## Supported Content-Types

| Extension | Content-Type |
|-----------|-------------|
| .html | text/html |
| .css | text/css |
| .js | application/javascript |
| .png | image/png |
| .jpg/.jpeg | image/jpeg |
| other | text/plain |

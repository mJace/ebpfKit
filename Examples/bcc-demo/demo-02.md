# Demo 2



## container 1 - bcc tool

```bash=
docker run -it --rm \
  --privileged \
  -v /lib/modules:/lib/modules:ro \
  -v /usr/src:/usr/src:ro \
  -v /etc/localtime:/etc/localtime:ro \
  --workdir /usr/share/bcc/tools \
  mjace/bcc:bionic
```


## container 2 - target
```bash=
docker run -it --rm --name=demo2 ubuntu bash
```


## Get network namespace of target container
on host

```bash=
docker ps

docker top <cid>

ls /proc/<pid>/ns/net -al

```

## In container 1
```bash=
./tcptracer -N <net_ns>
```

## In container 2

create any process that trigger tcp connection.

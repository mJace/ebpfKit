# Demo1

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
docker run -itd --name=demo1 -p 80:80 nginx 
```


## In container 1
```bash=
ps aux
```


## Get nginx worker pid
```bash=
docker ps

docker top <cid>
```

## In container 1
```bash=
./tcptracer -p <pid>
```




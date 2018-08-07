## Download the Code
To run this docker cluster, you will need to have docker and docker-compose
installed on your machine.  You can get these by following the instructions
here:

https://docs.docker.com/get-started/
https://docs.docker.com/compose/

Once you have these, you should clone
[this](https://github.com/oweidner/docker.openmpi) repository.  When you have
that downloaded, you can build your cluster.

## Build the cluster
You should first copy your code and compiled binary into the
`mpi4py_benchmarks/` directory, as that will be copied to each node when the
cluster is built.

Next, run docker-compose.  If you want to set up 4 nodes, with a single head
you can SSH into, for example, run:

```
docker-compose scale mpi_head=1 mpi_node=3
```

Once this has finished running, you can see with `docker ps` that you have 4
docker containers running.  You will want to grab the IP addresses for all of these machines using

```
docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' NAME
```

where name will be `dockeropenmpi_mpi_node_[1-3]` and
`dockeropenmpi_mpi_head_1` for the three nodes and the 1 head.  You can now SSH into the head:

```
chmod 400 ssh/id_rsa.mpi
ssh -i ssh/id_rsa.mpi  mpirun@MPI_HEAD_IP
```

From there, you will be able to set the head node up to behave a bit more like
a regular machine, rather than the stripped-down docker image.  If you want to
play around more with MPI, this will be very useful.

```
sudo unminimize
```

Next, you will want to either use vi or echo (or even install your editor of choice) to write out the
node IPs to a hostfile you will run with.  Finally, you can run your code with mpirun:

```
mpirun -np NUM_PROCS --hostfile HOSTFILE_NAME YOUR_BINARY ARGS
```

Keep in mind, if you want to change your code & recompile, you need to copy the
binary to all of the remote nodes:  MPI doesn't transmit the binary, it assumes
it exists on all of the remote machines.  Have fun!

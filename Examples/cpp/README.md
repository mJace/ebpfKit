# Find thread relationship in a userspace multi-thread program

This program will create 4 threads to perform **enqueue**, inserting data to a linked-list data structure.  
And creates another 4 threads to do the **dequeue**, popping out data.  
We will use bpftrace to insert **uretprobe** to observe the relation between these threads.  
You can even know the exact thread that produce or comsumes the same data.

## Requirement  

1. bpftrace  
   [Check environment preparation for installation.](https://www.github.com/mjace/ebpfKit/docs/prepare.md)

## Steps  

1. Build example.  

    ```bash
    git clone https://www.github.com/mJace/ebpfKit.git
    cd ebpfKit/Examples/cpp
    gcc main.c -pthread -o main
    ```

2. Make sure the functions that we like to see is in the objects of exectable file.  

    ```bash
    jace@ubuntu:~/ebpfKit/Examples/cpp$ objdump -Tt ./main | grep dequeue
    0000000000000b3a g     F .text    000000000000009e              dequeue
    jace@ubuntu:~/ebpfKit/Examples/cpp$  
    jace@ubuntu:~/ebpfKit/Examples/cpp$ objdump -Tt ./main | grep enqueue
    0000000000000a9f g     F .text    000000000000009b              enqueue
    ```

    **Open 3 therminal windows**  

3. Insert a uretprobe to check **enqueue** in terminal 1.  

    ```bash
    bpftrace -e 'uretprobe:/home/jace/ebpfKit/Examples/cpp/main:enqueue { printf("Enqueue - pid:%d tid:%d ret:%d\n",pid, tid, retval); }'
    ```

4. Insert a uretprobe to check **dequeue** in terminal 2.  

    ```bash
    bpftrace -e 'uretprobe:/home/jace/ebpfKit/Examples/cpp/main:dequeue { printf("Dequeue - pid:%d tid:%d ret:%d\n",pid, tid, retval); }'
    ```

5. Run the example program  

    ```bash
    cd ebpfKit/Examples/cpp
    gcc main.c -pthread -o main
    ./main
    ```

6. And you will see the output like this.

    ![Result](https://i.imgur.com/rwIhn1J.png)
    Thread 27240 called **qneueue** put 98 into queue.  
    Thread 27244 called **dequeue** and get the 98 from the queue.  

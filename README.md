# iceoryx2 Publish-Subscribe performance test

This is a test based on the iceoryx2 publisher subscriber example. Before proceeding, all dependencies need to be installed. You can find
the [pub-sub instruction](https://github.com/eclipse-iceoryx/iceoryx2/tree/main/examples/cxx/publish_subscribe).

## Running The Test

This test illustrates a performance test to the common publisher-subscriber communication pattern. The publisher sends a message every millisecond,
each containing [`TransmissionData`]. On the receiving end, the subscriber
checks for the transmitted data every nanosecond. 

The subscriber is printing the data on the console whenever new data arrives and the local receiving time as well as the delay between the local receiving time and the data timestamp. If you are running in a same machine, you have the same system time. If you are running publisher and subscriber in different machines, you may need other mechanism to sync the systems' clocks such as PTP. The implementation used std::chrono (ns) instead of std::time_t (s).



First, copy/paste the public_subscribe_performance_test into [the iceoryx2 cxx examples directory](https://github.com/eclipse-iceoryx/iceoryx2/tree/main/examples/cxx/publish_subscribe)

Next, build the C++ examples:

```sh
cmake -S . -B target/ffi/build -DBUILD_EXAMPLES=ON
cmake --build target/ffi/build
```

Then, open two separate terminals and
execute the following commands:

### Terminal 1

```sh
./target/ffi/build/examples/cxx/publish_subscribe_performance_test/cxx_publisher
```
or for the testing convenience, you may create a pub alias below:
```sh
alias pub="./target/ffi/build/examples/cxx/publish_subscribe_performance_test/cxx_publisher"
pub
```

### Terminal 2

```sh
./target/ffi/build/examples/cxx/publish_subscribe_performance_test/cxx_subscriber > example_data
```
or for the testing convenience, you may create a pub alias below:
```sh
alias sub="./target/ffi/build/examples/cxx/publish_subscribe_performance_test/cxx_subscriber"
sub > example_data
```

Finally, once you collect the enough data in the example_data file, overwrite it to this repo's resources directory, install pip pre-requisite

```py
pip install -r /path/to/requirements.txt
```

and run the find_delay.py to find the delay information. 
```py
$ python3 find_delay.py
Item 8373 has the max delay: 1519990 ns
Delay 90th percentile: 1250823.5 ns
Delay 50th percentile: 194548.5 ns
```

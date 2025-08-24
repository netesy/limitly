#include "backend/concurrency/channel.hh"
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <numeric>

void test_simple_send_receive() {
    std::cout << "Running test: Simple Send/Receive... ";
    Channel<int> ch;
    ch.send(42);
    int received_val;
    bool success = ch.receive(received_val);
    assert(success);
    assert(received_val == 42);
    std::cout << "PASSED" << std::endl;
}

void test_multi_threaded_producer_consumer() {
    std::cout << "Running test: Multi-threaded Producer/Consumer... ";
    Channel<int> ch;
    std::vector<int> received_values;
    const int num_items = 100;

    std::thread producer([&]() {
        for (int i = 0; i < num_items; ++i) {
            ch.send(i);
        }
        ch.close();
    });

    std::thread consumer([&]() {
        int val;
        while (ch.receive(val)) {
            received_values.push_back(val);
        }
    });

    producer.join();
    consumer.join();

    assert(received_values.size() == num_items);
    for (int i = 0; i < num_items; ++i) {
        assert(received_values[i] == i);
    }
    std::cout << "PASSED" << std::endl;
}

void test_channel_close() {
    std::cout << "Running test: Channel Close... ";
    Channel<int> ch;
    ch.close();
    int val;
    bool success = ch.receive(val);
    assert(!success); // Should return false immediately on a closed, empty channel
    std::cout << "PASSED" << std::endl;
}

void test_multiple_producers() {
    std::cout << "Running test: Multiple Producers... ";
    Channel<int> ch;
    const int num_producers = 5;
    const int items_per_producer = 20;
    std::vector<std::thread> producers;

    for (int i = 0; i < num_producers; ++i) {
        producers.emplace_back([&, i]() {
            for (int j = 0; j < items_per_producer; ++j) {
                ch.send(i * 100 + j);
            }
        });
    }

    std::vector<int> received_values;
    std::thread consumer([&]() {
        int val;
        for (int i = 0; i < num_producers * items_per_producer; ++i) {
            if (ch.receive(val)) {
                received_values.push_back(val);
            }
        }
    });

    for (auto& p : producers) {
        p.join();
    }

    // After producers are done, close the channel to unblock consumer if it's waiting
    ch.close();
    consumer.join();

    assert(received_values.size() == num_producers * items_per_producer);
    std::cout << "PASSED" << std::endl;
}


int main() {
    test_simple_send_receive();
    test_channel_close();
    test_multi_threaded_producer_consumer();
    test_multiple_producers();

    std::cout << "\nAll channel tests passed!" << std::endl;
    return 0;
}

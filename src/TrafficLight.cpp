#include "TrafficLight.h"
#include <iostream>
#include <random>

#include <chrono>

using namespace std::chrono;
/* Implementation of class "MessageQueue" */

/*
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and
_condition.wait()
    // to wait for and receive new messages and pull them from the queue using
move semantics.
    // The received object should then be returned by the receive function.
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms
std::lock_guard<std::mutex>
    // as well as _condition.notify_one() to add a new message to the queue and
afterwards send a notification.
}
*/

/* Implementation of class "TrafficLight" */

/*
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an
infinite while-loop
    // runs and repeatedly calls the receive function on the message queue.
    // Once it receives TrafficLightPhase::green, the method returns.
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be
started in a thread when the public method „simulate“ is called. To do this, use
the thread queue in the base class.
}

*/
// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases() {
  // FP.2a : Implement the function with an infinite loop that measures the
  // time between two loop cycles
  // and toggles the current phase of the traffic light between red and green
  // and sends an update method
  // to the message queue using move semantics. The cycle duration should be a
  // random value between 4 and 6 seconds.
  // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms
  // between two cycles.
  auto stopWatch{high_resolution_clock::now()};
  while (true) {
    auto timeDiff = duration_cast<duration<double>>(
                        high_resolution_clock::now() - stopWatch)
                        .count();
    std::cout << "Time difference between cycles is " << timeDiff << " seconds"
              << std::endl;
    auto cycleDuration = std::rand() % 3 + 4; // duration to change traffic light state
    if (timeDiff < cycleDuration) // check if between random values of 4 to 6 seconds
    {
      _currentPhase = this->_currentPhase == TrafficLightPhase::green
                          ? TrafficLightPhase::red
                          : TrafficLightPhase::green;
      // DO UPDATE METHOD AFTER NOTIFICIATION IN FP.3
      _condition.notify_one();
      stopWatch = high_resolution_clock::now();
    }
    std::this_thread::sleep_for(milliseconds(1)); // wait between cycles
  }
}

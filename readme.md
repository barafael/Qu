# Q

A POC (proof-of-concept/piece-of-crap) implementation of the basic idea of Rust async/await in C++. Event-based lazy cooperative multitasking with informed polling.

Events are pushed on a queue. Each event is broadcast to tasks which are interested in it. "Interested in an event" means "given this event, a task can proceed one step". On event reception, a task is resumed from its last yield point. A task will then complete the current "continuation region". I define for this project a continuation region to be the region between two yield points. In my naive implementation, a continuation will likely be a "branch" of a switch. On completing a continuation region, a task returns.

To support tasks which await multiple different events and proceed on any of them, I decided to move the responsibility of the "is an event interesting" check to the task. This means each incoming event has to be sent to each task to check for interest. The alternative would be to yield from a continuation region a set of interesting event ID codes and storing it in the broker registry as key.

In principle, interrupts should push events onto the queue, where they are pulled from by the broker. Care must be taken to synchronize the queue access.

Simplifying assumptions (non-exhaustive list):

* No `resumable` function loops around for too long
* Events have a global shared ID code that is cheap to pass arround
* Number of tasks is known and static (for now)

Of course, void pointers, switch cases etc. galore. Don't use. I don't even know what's the point of this besides demo&learning.